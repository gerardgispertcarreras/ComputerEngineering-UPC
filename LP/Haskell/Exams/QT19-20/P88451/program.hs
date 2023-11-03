data Tree a = Empty | Node a (Tree a) (Tree a)
data Forest a = Forest [Tree a] deriving (Show)

instance Show a => Show (Tree a) where
  show Empty = "()"
  show (Node x tl tr) = "(" ++ show tl ++ "," ++ show x ++ "," ++ show tr ++ ")"

instance Functor (Tree) where
  fmap f Empty = Empty
  fmap f (Node x tl tr) = Node (f x) (fmap f tl) $ fmap f tr

doubleT :: Num a => Tree a -> Tree a
doubleT tree = fmap (*2) tree

instance Functor (Forest) where
  fmap f (Forest tree_list) = Forest (map (fmap f) tree_list)

doubleF :: Num a => Forest a -> Forest a
doubleF forest = fmap (*2) forest
