myLength :: [Int] -> Int
myLength [] = 0
myLength (x:xs) = 1 + myLength xs

--myLength l = if (null l) then 0 else ((myLength xs) + 1)

myMaximum :: [Int] -> Int
myMaximum [x] = x
myMaximum (x:xs) = (max x (myMaximum xs))

average :: [Int] -> Float
average l = ( (fromIntegral (suma l)) / (fromIntegral (length l)))
    where
        suma :: [Int] -> Int
        suma [x] = x
        suma (x:xs) = x + suma xs

buildPalindrome :: [Int] -> [Int]
buildPalindrome l = (reverse l) ++ l

remove :: [Int] -> [Int] -> [Int]
remove x [] = x
remove x (y:ys) = (remove (removeNum x y) ys)
  where
    removeNum :: [Int] -> Int -> [Int]
    removeNum [] _ = []
    removeNum (x:xs) y
      | x == y = (removeNum xs y)
      | otherwise = x : (removeNum xs y)

flatten :: [[Int]] -> [Int]
flatten [] = []
flatten (x:xs) = x ++ flatten xs

oddsNevens :: [Int] -> ([Int],[Int])
oddsNevens [] = ([],[])
oddsNevens (x:xs)
  | odd x = (x : (fst (oddsNevens xs)), (snd (oddsNevens xs)))
  | even x = ((fst (oddsNevens xs)), x : (snd (oddsNevens xs)))

primeDivisors :: Int -> [Int]
primeDivisors x = primeDivisors' x 2
	where
		primeDivisors' :: Int -> Int -> [Int]
		primeDivisors' x y
			| y > (div x 2) = if (isPrime x) then [x] else []
			| ((mod x y) == 0) && (isPrime y) = y : (primeDivisors' x (y + 1))
			| otherwise =  (primeDivisors' x (y + 1))
				where
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
