module Main where 

import Lexer 
import Parser 
import Interpreter
import TypeChecker

-- Para testar o interpretador no Linux é possível rodar:
-- * runghc Main.hs < examples/ex1.hs 
-- * echo "2 + 5" | runghc Main.hs

-- Beecrowd 1001: echo "let a = 10 in let b = 9 in a + b" | runghc Main.hs
-- Beecrowd 1004: echo "let a = 3 in let b = 9 in a * b" | runghc Main.hs
-- Beecrowd 1007: echo "let a = 5 in let b = 6 in let c = 7 in let d = 8 in a * b - c * d" | runghc Main.hs

main = getContents >>= print . eval . typecheck . parser . lexer 