module Interpreter where 

import Lexer 

isValue :: Expr -> Bool 
isValue BTrue       = True 
isValue BFalse      = True  
isValue (Num _)     = True 
isValue (Lam _ _ _) = True
isValue _           = False 

subst :: String -> Expr -> Expr -> Expr
subst v e BTrue = BTrue 
subst v e BFalse = BFalse 
subst v e (Num x) = Num x 
subst v e (Add e1 e2) = Add (subst v e e1) (subst v e e2)
subst v e (And e1 e2) = And (subst v e e1) (subst v e e2)
subst v e (If e1 e2 e3) = If (subst v e e1) (subst v e e2) (subst v e e3)
subst v e (Var x) = if v == x then 
                      e 
                    else 
                      Var x 
subst v e (Lam x t b) = Lam x t (subst v e b)
subst v e (App e1 e2) = App (subst v e e1) (subst v e e2)
subst v e (Paren e1) = Paren (subst v e e1)
subst v e (Let x e1 e2) = if v == x then 
                            (subst x e1 e2)
                          else 
                            Let x e1 e2


step :: Expr -> Expr 
step (Add (Num n1) (Num n2)) = Num (n1 + n2)     -- S-Add
step (Add (Num n1) e2) = let e2' = step e2       -- S-Add2
                           in Add (Num n1) e2' 
step (Add e1 e2) = Add (step e1) e2              -- S-Add1
step (And BTrue e2) = e2 
step (And BFalse e2) = BFalse 
step (And e1 e2) = And (step e1) e2 
step (If BTrue e1 e2) = e1 
step (If BFalse e1 e2) = e2
step (If e e1 e2) = If (step e) e1 e2 
step (App e1@(Lam x t b) e2) | isValue e2 = subst x e2 b
                             | otherwise  = App e1 (step e2)
step (App e1 e2) = App (step e1) e2 
step (Paren e) = e 
step (Let v (Num n1) e2) = (subst v (Num n1) e2) 
step (Let v e1 e2) = Let v (step e1) e2

eval :: Expr -> Expr 
eval e | isValue e = e 
       | otherwise = eval (step e)

