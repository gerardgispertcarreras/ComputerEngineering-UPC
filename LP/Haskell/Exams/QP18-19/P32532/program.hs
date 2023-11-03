divisors :: Int -> [Int]
divisors n = [x | x <- [1 .. n], mod n x == 0]

nbDivisors :: Int -> Int
nbDivisors = length . divisors

moltCompost :: Int -> Bool
moltCompost n = and [y > nbDivisors x | x <- [1 .. n - 1]]
    where y = nbDivisors n

-- moltCompost n 
--     | n == 1 = True
--     | otherwise = nbDivisors n > maximum ([nbDivisors x | x <- [1 .. n - 1]])
