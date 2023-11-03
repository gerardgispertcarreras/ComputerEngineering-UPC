import Control.Monad

data STree a = Nil | Node Int a (STree a) (STree a) deriving Show

--Testing
div10 = flip div 10
t1 = Node 3 99 (Node 1 88 Nil Nil) (Node 1 22 Nil Nil)
t2 = Node 2 77 (Node 1 33 Nil Nil) Nil
t3 = Node 6 44 t1 t2
t4 = Node 7 55 t1 t2

numNodes :: STree a -> Int
numNodes Nil = 0
numNodes (Node x y (stl) (str)) = x

isOk :: STree a -> Bool
isOk Nil = True
isOk (Node x y (stl) (str)) = x == (1 + numNodes stl + numNodes str) && isOk stl && isOk str

nthElement :: STree a -> Int -> Maybe a
nthElement Nil n = Nothing
nthElement (Node x y (stl) (str)) n
  | n > x = Nothing
  | n == (nL + 1) = Just y
  | n <= nL = nthElement stl n
  | otherwise = nthElement str (n - (nL + 1))
  where
    nL = numNodes stl

mapToElements :: (a -> b) -> STree a -> [Int] -> [Maybe b]
mapToElements f st l = fmap (fmap f . nthElement st) l

instance Functor (STree) where
  fmap f Nil = Nil
  fmap f (Node x y (stl) (str)) = Node x (f y) (fmap f stl) $ fmap f str
