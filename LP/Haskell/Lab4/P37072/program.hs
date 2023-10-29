data Tree a = Node a (Tree a) (Tree a) | Empty deriving (Show)

{-
Joc de Prova
-}
t7 = Node 7 Empty Empty
t6 = Node 6 Empty Empty
t5 = Node 5 Empty Empty
t4 = Node 4 Empty Empty
t3 = Node 3 t6 t7
t2 = Node 2 t4 t5
t1 = Node 1 t2 t3
t1' = Node 1 t3 t2

size :: Tree a -> Int
size Empty = 0
size (Node n tL tR) = size tL + size tR + 1

height :: Tree a -> Int
height Empty = 0
height (Node n tL tR) = (max (height tL) (height tR)) + 1

equal :: Eq a => Tree a -> Tree a -> Bool
equal Empty Empty = True
equal (Node n1 tL1 tR1) (Node n2 tL2 tR2) = n1 == n2 && equal tL1 tL2 && equal tR1 tR2
equal _ _ = False

isomorphic :: Eq a => Tree a -> Tree a -> Bool
isomorphic (Node n1 tL1 tR1) (Node n2 tL2 tR2) = equal (Node n1 tL1 tR1) (Node n2 tL2 tR2) || equal (Node n1 tL1 tR1) (Node n2 tR2 tL2)
isomorphic Empty Empty = True
isomorphic _ _ = False

preOrder :: Tree a -> [a]
preOrder Empty = []
preOrder (Node n tL tR) = n : (preOrder tL) ++ (preOrder tR)

postOrder :: Tree a -> [a]
postOrder Empty = []
postOrder (Node n tL tR) = (postOrder tL) ++ (postOrder tR) ++ [n]

inOrder :: Tree a -> [a]
inOrder Empty = []
inOrder (Node n tL tR) = (inOrder tL) ++ [n] ++ (inOrder tR)

breadthFirst :: Tree a -> [a]
breadthFirst t = bf [t]
    where
			bf [] = []
			bf ((Node n tL tR):xs) = n : (bf (xs ++ [tL, tR]))
			bf (_:xs) = (bf xs)

{-
breadthFirst Empty = []
breadthFirst (Node n tL tR) = [n] ++ (node tL) ++ (node tR) ++ breadthFirst' tL ++ breadthFirst' tR
    where
        breadthFirst' Empty = []
        breadthFirst' (Node n tL tR) = (node tL) ++ (node tR) ++ breadthFirst' tL ++ breadthFirst' tR
        node Empty = []
        node (Node n tL tR) = [n]
-}