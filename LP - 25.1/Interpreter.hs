module Interpreter where 

import Lexer 

isValue :: Expr -> Bool 
isValue BTrue       = True 
isValue BFalse      = True  
isValue (Num _)     = True 
isValue (Lam _ _ _) = True
isValue Null = True
isValue (Cons h t) = isValue h && isValue t
isValue _           = False 

subst :: String -> Expr -> Expr -> Expr
subst v e BTrue = BTrue 
subst v e BFalse = BFalse 
subst v e (Num x) = Num x 
subst v e (Add e1 e2) = Add (subst v e e1) (subst v e e2)
subst v e (Sub e1 e2) = Sub (subst v e e1) (subst v e e2)
subst v e (Mult e1 e2) = Mult (subst v e e1) (subst v e e2)
subst v e (And e1 e2) = And (subst v e e1) (subst v e e2)
subst v e (Or e1 e2) = Or (subst v e e1) (subst v e e2)
subst v e (Equal e1 e2) = Equal (subst v e e1) (subst v e e2)
subst v e (Diff e1 e2) = Diff (subst v e e1) (subst v e e2)
subst v e (If e1 e2 e3) = If (subst v e e1) (subst v e e2) (subst v e e3)
subst v e (Var x) = if v == x then 
                      e 
                    else 
                      Var x 
subst v e (Lam x t b) = Lam x t (subst v e b)
subst v e (App e1 e2) = App (subst v e e1) (subst v e e2)
subst v e (Paren e1) = Paren (subst v e e1)
subst v e (Let x e1 e2)
  | v == x    = Let x (subst v e e1) e2 
  | otherwise = Let x (subst v e e1) (subst v e e2)


step :: Expr -> Expr 
step (Add (Num n1) (Num n2)) = Num (n1 + n2)
step (Add (Num n1) e2) = Add (Num n1) (step e2)
step (Add e1 e2) = Add (step e1) e2
step (Sub (Num n1) (Num n2)) = Num (n1 - n2)    
step (Sub (Num n1) e2) = Sub (Num n1) (step e2) 
step (Sub e1 e2) = Sub (step e1) e2  
step (Mult (Num n1) (Num n2)) = Num (n1 * n2)    
step (Mult (Num n1) e2) = Mult (Num n1) (step e2) 
step (Mult e1 e2) = Mult (step e1) e2            
step (And BTrue e2) = e2 
step (And BFalse e2) = BFalse 
step (And e1 e2) = And (step e1) e2 
step (Or BFalse e2) = e2 
step (Or BTrue e2) = BTrue
step (Not BTrue) = BFalse 
step (Not BFalse) = BTrue
step (Not e) = Not (step e)
step (Or e1 e2) = Or (step e1) e2 
step (Equal (Num n1) (Num n2)) | n1 == n2 = BTrue
                               | otherwise = BFalse
step (Equal BTrue BTrue)   = BTrue
step (Equal BFalse BFalse) = BTrue
step (Equal BTrue BFalse)  = BFalse
step (Equal BFalse BTrue)  = BFalse
step (Equal e1 e2) | isValue e1 = Equal e1 (step e2)
                   | otherwise = Equal (step e1) e2
step (Diff (Num n1) (Num n2)) | n1 == n2 = BFalse
                              | otherwise = BTrue
step (Diff (Num n1) e2) = Diff (Num n1) (step e2)
step (Diff e1 e2) = Diff (step e1) e2    
step (If BTrue e1 e2) = e1 
step (If BFalse e1 e2) = e2
step (If e e1 e2) = If (step e) e1 e2 
step (App e1@(Lam x t b) e2) | isValue e2 = subst x e2 b
                             | otherwise  = App e1 (step e2)
step (App e1 e2) = App (step e1) e2 
step (Paren e) = e 
step (Let v e1 e2)
  | isValue e1 = subst v e1 e2
  | otherwise  = Let v (step e1) e2
step (IsNull Null) = BTrue
step (IsNull (Cons _ _)) = BFalse
step (IsNull e) = IsNull (step e)
step (Head (Cons h _)) = h
step (Head e) = Head (step e)
step (Tail (Cons _ t)) = t
step (Tail e) = Tail (step e)
step (Cons h t)
  | isValue h = Cons h (step t)
  | otherwise = Cons (step h) t
step e = error $ "step: expressão não tratada: " ++ show e

eval :: Expr -> Expr 
eval e | isValue e = e 
       | otherwise = eval (step e)

