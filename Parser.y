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
    "&&"            { TokenAnd }
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
    '='             { TokenIgual }
    '('             { TokenLParen }
    ')'             { TokenRParen }

%nonassoc if then else 
%nonassoc '\\' 
%left '+' 
%left "&&"

%% 

Exp     : num                           { Num $1 }
        | true                          { BTrue }
        | false                         { BFalse }
        | Exp '+' Exp                   { Add $1 $3 }
        | Exp "&&" Exp                  { And $1 $3 }
        | if Exp then Exp else Exp      { If $2 $4 $6 }
        | var                           { Var $1 }
        | '\\' var ':' Type "->" Exp    { Lam $2 $4 $6 }
        | Exp Exp                       { App $1 $2 }
        | '(' Exp ')'                   { Paren $2 }
        | let var '=' Exp in Exp        { Let $2 $4 $6 }

Type    : Boolean                       { TBool }
        | Number                        { TNum }
        | '(' Type "->" Type ')'        { TFun $2 $4 }

{ 

parseError :: [Token] -> a 
parseError _ = error "Erro sintático!"

}