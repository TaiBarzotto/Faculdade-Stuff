{-# OPTIONS_GHC -Wno-overlapping-patterns #-}
module Lexer where 

import Data.Char
import Language.Haskell.TH (Exp)

data Expr = BTrue 
          | BFalse 
          | Num Int 
          | Add Expr Expr 
          | Sub Expr Expr
          | Mult Expr Expr
          | And Expr Expr 
          | Or Expr Expr
          | Not Expr
          | If Expr Expr Expr 
          | Var String 
          | Lam String Ty Expr 
          | App Expr Expr 
          | Paren Expr 
          | Let String Expr Expr
          | Diff Expr Expr
          | Equal Expr Expr
          | Null 
          | Cons Expr Expr
          | IsNull Expr 
          | Head Expr
          | Tail Expr
          deriving Show

data Ty = TBool 
        | TNum 
        | TFun Ty Ty
        | TList Ty 
        deriving (Show, Eq)

data Token = TokenTrue 
           | TokenFalse 
           | TokenNum Int 
           | TokenAdd 
           | TokenSub
           | TokenMult
           | TokenAnd 
           | TokenOr 
           | TokenIf 
           | TokenThen
           | TokenElse 
           | TokenVar String 
           | TokenLam 
           | TokenColon
           | TokenArrow 
           | TokenTNum 
           | TokenTBool
           | TokenLParen 
           | TokenRParen  
           | TokenLet
           | TokenIn
           | TokenNot
           | TokenIgual
           | TokenEqual
           | TokenDiff
           | TokenLColch
           | TokenRColch
           | TokenVirgula
           | TokenIsNull
           | TokenHead
           | TokenTail
           deriving Show 

lexer :: String -> [Token]
lexer [] = [] 
lexer ('+':cs) = TokenAdd : lexer cs 
lexer ('-':cs) = TokenSub : lexer cs 
lexer ('*':cs) = TokenMult : lexer cs 
lexer ('\\':cs) = TokenLam : lexer cs 
lexer (':':cs) = TokenColon : lexer cs 
lexer ('(':cs) = TokenLParen : lexer cs 
lexer (')':cs) = TokenRParen : lexer cs 
lexer ('=':'=':cs) = TokenEqual : lexer cs 
lexer ('=':cs) = TokenIgual : lexer cs
lexer ('&':'&':cs) = TokenAnd : lexer cs 
lexer ('|':'|':cs) = TokenOr : lexer cs 
lexer ('-':'>':cs) = TokenArrow : lexer cs 
lexer ('!':'=':cs) = TokenDiff : lexer cs 
lexer ('!':cs) = TokenNot : lexer cs 
lexer ('[':cs) = TokenLColch : lexer cs
lexer (']':cs) = TokenRColch : lexer cs
lexer (',':cs) = TokenVirgula : lexer cs
lexer (c:cs) | isSpace c = lexer cs 
             | isDigit c = lexNum (c:cs) 
             | isAlpha c = lexKW (c:cs)

lexNum :: String -> [Token]
lexNum cs = case span isDigit cs of 
              (num, rest) -> TokenNum (read num) : lexer rest 

lexKW :: String -> [Token]
lexKW cs = case span isAlpha cs of 
             ("true", rest) -> TokenTrue : lexer rest 
             ("false", rest) -> TokenFalse : lexer rest 
             ("if", rest) -> TokenIf : lexer rest 
             ("then", rest) -> TokenThen : lexer rest 
             ("else", rest) -> TokenElse : lexer rest 
             ("Number", rest) -> TokenTNum : lexer rest 
             ("Boolean", rest) -> TokenTBool : lexer rest 
             ("let", rest) -> TokenLet : lexer rest
             ("in", rest) -> TokenIn: lexer rest
             ("isNull", rest) -> TokenIsNull : lexer rest
             ("head", rest) -> TokenHead : lexer rest
             ("tail", rest) -> TokenTail : lexer rest
             (var, rest) -> TokenVar var : lexer rest 
 
