ones :: [Integer]
ones = iterate id 1

nats :: [Integer]
nats = scanl (+) 0 ones
--nats = iterate (+1) 0

ints :: [Integer]
{-ints = iterate next 0
    where
        next n
            | n > 0 = (-n)
            | otherwise = (-n) + 1-}

ints = 0 : map next ints
    where
        next n
            | n > 0 = (-n)
            | otherwise = (-n) + 1

triangulars :: [Integer]
triangulars = tail (scanl (+) 0 nats)

factorials :: [Integer]
factorials = scanl (*) 1 (tail nats)

fibs :: [Integer]
fibs = 0 : 1 : zipWith (+) fibs (tail fibs)

primes :: [Integer]
primes = [x | x <- nats, isPrime x]
	where
			isPrime n = isPrime' 2
					where
							isPrime' d
									| n <= 1 = False
									| n == 2 = True
									| d > floor (sqrt (fromIntegral n)) = True
									| mod n d == 0 = False
									| otherwise = isPrime' (d + 1)

hammings :: [Integer]
hammings = 1 : (merge (map (*2) hammings)  (map (*3) hammings) (map (*5) hammings))
	where
		merge (x:xs) (y:ys) (z:zs)
			| x <= y && x <= z = if x == y && x == z then x : (merge xs ys zs) else if x == y then (merge xs ys (z:zs)) else if x == z then (merge xs (y:ys) zs) else (merge xs (y:ys) (z:zs)) 
			| y < x && y <= z = y : if y == z then (merge (x:xs) ys zs) else (merge (x:xs) ys (z:zs))
			| z < x && z < y = z : (merge (x:xs) (y:ys) zs)
			| otherwise = x : (merge (x:xs) (y:ys) zs)
{-
lookNsay :: [Integer]


tartaglia :: [[Integer]]

https://apfelmus.nfshost.com/articles/lazy-eval-intro.html
-}