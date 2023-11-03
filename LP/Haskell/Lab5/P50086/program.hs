import Control.Monad

data Queue a = Queue [a] [a]
    deriving (Show)


create :: Queue a
create = Queue [] []

push :: a -> Queue a -> Queue a
push x (Queue f s) = (Queue f (x:s))

pop :: Queue a -> Queue a
pop (Queue (f:fs) s) = Queue fs s
pop (Queue [] s) = Queue (tail (reverse s)) []

top :: Queue a -> a
top (Queue (f:fs) s) = f
top (Queue _ s) = last s

empty :: Queue a -> Bool
empty (Queue f s) = null f && null s

q2l :: Queue a -> [a]
q2l (Queue f s) = f ++ (reverse s)

instance Eq a => Eq (Queue a)
    where
       p == q = q2l p == q2l q

instance Functor Queue where
    fmap f (Queue x y) = Queue (fmap f x) $ fmap f y

translation :: Num b => b -> Queue b -> Queue b
translation n p = fmap (+ n) p

instance Applicative Queue where
    pure x = push x create
    qf <*> qv = Queue (q2l qf <*> q2l qv) []

instance Monad Queue where
    return x = Queue [x] []
    qv >>= f = Queue ((q2l qv) >>= q2l . f) []

kfilter :: (p -> Bool) -> Queue p -> Queue p
kfilter f q = do
    x <- q
    if f x then return x
    else create
