import Data.List

isInPair :: (Eq a) => a -> (a, a) -> Bool
isInPair y (x1, x2)
  | y == x1 || y == x2 = True
  | otherwise = False

degree :: Eq a => [(a, a)] -> a -> Int
degree [] _ = 0
degree (x:xs) y
  | isInPair y x = 1 + degree xs y
  | otherwise = degree xs y

degree' :: Eq a => [(a, a)] -> a -> Int
degree' l y = length $ filter (isInPair y) l
--degree' l y = length $ filter (\x -> isInPair y ) l

neighbor :: Eq a => a -> (a, a) -> a
neighbor y x
  | y == fst x = snd x
  | otherwise = fst x

neighbors :: Ord a => [(a, a)] -> a -> [a]
neighbors l y = sort [(neighbor y) x | x <- l, isInPair y x]
