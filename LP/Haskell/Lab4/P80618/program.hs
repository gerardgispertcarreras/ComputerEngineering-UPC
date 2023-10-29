data Queue a = Queue [a] [a]
    deriving (Show)

{-
Joc de Prova
c = push 3 (push 2 (push 1 create))
-}

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

{-
-}