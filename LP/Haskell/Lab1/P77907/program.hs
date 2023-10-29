absValue :: Integral a => a -> a
absValue n
    | n >= 0    = n
    | otherwise = -n

power :: Integral a => a -> a -> a
power _ 0 = 1
power x n
    | even n = y * y
    | odd n = y * y * x
    where
        y = power x n_halved
        n_halved = div n 2

isPrime :: Int -> Bool
isPrime n = isPrime' 2
    where
        isPrime' :: Int -> Bool
        isPrime' d
            | n <= 1 = False
            | n == 2 = True
            | d > floor (sqrt (fromIntegral n)) = True
            | mod n d == 0 = False
            | otherwise = isPrime' (d + 1)

slowFib :: Integral a => a -> a
slowFib 0 = 0
slowFib 1 = 1
slowFib n = (slowFib (n - 1) + slowFib (n - 2))

quickFib :: Integral a => a -> a
quickFib 0 = 0
quickFib 1 = 1
quickFib n = ((fst y) + (snd y))
	where
		y = (quickFib' (n - 1))
			where
				quickFib' :: Integral a => a -> (a, a)
				quickFib' 1 = (0, 1)
				quickFib' 2 = (1, 1)
				quickFib' n = (((fst z) + (snd z)), (fst z))
					where
						z = (quickFib' (n - 1))

