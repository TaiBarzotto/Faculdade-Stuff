{
module Parser where 

import Lexer
}

%name parser 
%tokentype { Token }
%error { parseError }

%token 
    num             { TokenNum $$ }
    true            { TokenTrue }
    false           { TokenFalse }
    '+'             { TokenAdd }
    '-'             { TokenSub }
    '*'             { TokenMult }
    "&&"            { TokenAnd }
    "||"            { TokenOr }
    if              { TokenIf }
    then            { TokenThen }
    else            { TokenElse }
    var             { TokenVar $$ }
    '\\'            { TokenLam }
    ':'             { TokenColon }
    "->"            { TokenArrow }
    Number          { TokenTNum }
    Boolean         { TokenTBool }
    let             { TokenLet }
    in              { TokenIn }
    "=="            { TokenEqual }
    '='             { TokenIgual }
    '('             { TokenLParen }
    ')'             { TokenRParen }
    "!="            { TokenDiff }
    '!'             { TokenNot }
    '['             { TokenLColch }
    ']'             { TokenRColch }
    ','             { TokenVirgula }
    head            { TokenHead }
    tail            { TokenTail }
    isNull          { TokenIsNull }


%nonassoc if then else 
%nonassoc '\\' 
%left '+' '-'
%left '*' 
%left "&&"

%% 

Exp     : '[' ListItems ']'             { $2 }
        | num                           { Num $1 }
        | head Exp                      { Head $2 }
        | tail Exp                      { Tail $2 }
        | isNull Exp                    { IsNull $2 }
        | true                          { BTrue }
        | false                         { BFalse }
        | Exp '+' Exp                   { Add $1 $3 }
        | Exp '-' Exp                   { Sub $1 $3 }
        | Exp '*' Exp                   { Mult $1 $3 }
        | Exp "&&" Exp                  { And $1 $3 }
        | Exp "||" Exp                  { Or $1 $3 }
        | Exp "==" Exp                  { Equal $1 $3 }
        | Exp "!=" Exp                  { Diff $1 $3 }
        | if Exp then Exp else Exp      { If $2 $4 $6 }
        | var                           { Var $1 }
        | '!' Exp                       { Not $2 }
        | '\\' var ':' Type "->" Exp    { Lam $2 $4 $6 }
        | Exp Exp                       { App $1 $2 }
        | '(' Exp ')'                   { Paren $2 }
        | let var '=' Exp in Exp        { Let $2 $4 $6 }


Type    : Boolean                       { TBool }
        | Number                        { TNum }
        | '(' Type "->" Type ')'        { TFun $2 $4 }



ListItems :                      { Null } 
          | Exp                  { Cons $1 Null }
          | Exp ',' ListItems    { Cons $1 $3 }

{ 

parseError :: [Token] -> a 
parseError _ = error "Erro sintático!"

}