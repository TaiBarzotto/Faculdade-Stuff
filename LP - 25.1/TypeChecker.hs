module TypeChecker where 

import Lexer 
import Lexer (Expr(Equal), Ty (TBool))
import Distribution.Compiler (CompilerFlavor(JHC))

type Ctx = [(String, Ty)]

typeof :: Ctx -> Expr -> Maybe Ty 
typeof ctx (Num _) = Just TNum 
typeof ctx BFalse = Just TBool 
typeof ctx BTrue = Just TBool 
typeof ctx (Add e1 e2) = case (typeof ctx e1, typeof ctx e2) of 
                       (Just TNum, Just TNum) -> Just TNum 
                       _                      -> Nothing
typeof ctx (Sub e1 e2) = case (typeof ctx e1, typeof ctx e2) of 
                       (Just TNum, Just TNum) -> Just TNum 
                       _                      -> Nothing
typeof ctx (Mult e1 e2) = case (typeof ctx e1, typeof ctx e2) of 
                       (Just TNum, Just TNum) -> Just TNum 
                       _                      -> Nothing
typeof ctx (And e1 e2) = case (typeof ctx e1, typeof ctx e2) of 
                       (Just TBool, Just TBool) -> Just TBool 
                       _                        -> Nothing 
typeof ctx (Or e1 e2) = case (typeof ctx e1, typeof ctx e2) of 
                       (Just TBool, Just TBool) -> Just TBool 
                       _                        -> Nothing 
typeof ctx (Not e) = case typeof ctx e of 
                       Just TBool -> Just TBool 
                       _          -> Nothing 
typeof ctx (If e1 e2 e3) = 
    case (typeof ctx e1) of 
      Just TBool -> case (typeof ctx e2, typeof ctx e3) of 
                      (Just t1, Just t2) | t1 == t2  -> Just t1  
                                         | otherwise -> Nothing 
                      _ -> Nothing 
      _ -> Nothing
typeof ctx (Equal e1 e2) =
    case (typeof ctx e1, typeof ctx e2) of 
      (Just t1, Just t2) | t1 == t2  -> Just TBool  
                         | otherwise -> Nothing
      _                        -> Nothing  
typeof ctx (Diff e1 e2) =
    case (typeof ctx e1, typeof ctx e2) of 
      (Just t1, Just t2) | t1 == t2  -> Just TBool  
                         | otherwise -> Nothing
      _                        -> Nothing               
typeof ctx (Var v) = lookup v ctx 
typeof ctx (Lam x t1 b) = let ctx' = (x, t1) : ctx in 
                            case typeof ctx' b of 
                              Just t2 -> Just (TFun t1 t2)
                              _       -> Nothing 
typeof ctx (App e1 e2) = 
  case (typeof ctx e1) of 
    Just (TFun t11 t12) -> case typeof ctx e2 of 
                             Just t2 -> if t11 == t2 then 
                                          Just t12 
                                        else 
                                          Nothing 
                             _ -> Nothing 
    _ -> Nothing 
typeof ctx (Paren e) = typeof ctx e 
typeof ctx (Let x e1 e2) = case typeof ctx e1 of
                            Just t1 -> let ctx' = (x, t1) : ctx in 
                                      case typeof ctx' e2 of 
                                        Just t2 -> Just (TFun t1 t2)
                                        _       -> Nothing 
                            _ -> Nothing

                             

typecheck :: Expr -> Expr  
typecheck e = case typeof [] e of 
                Just _ -> e 
                _      -> error "Erro de tipo!"


