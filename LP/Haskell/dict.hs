type Dict = (String -> Int)

create :: Int -> Dict
search :: Dict -> String -> Int
insert :: Dict -> String -> Int -> Dict

create def = \key -> def

search dict key = dict key

insert dict key value = \x ->
    if key == x then value
    else search dict x

{- 
    search (insert (create (-1)) "hola" 2) "hola"
-}