flatten :: [[Int]] -> [Int]
flatten x = foldl (++) [] x

myLength :: String -> Int
myLength x = foldl (+) 0 $ map (const 1) x

myReverse :: [Int] -> [Int]
myReverse x = foldl (flip (:)) [] x

myReverse' :: [Int] -> [Int]
myReverse' l = foldl (\acc x -> x : acc) [] l

countIn :: [[Int]] -> Int -> [Int]
countIn l x = map length (map (filter (\n -> n == x)) l) 

firstWord :: String -> String
firstWord s = takeWhile (\c -> c /= ' ' && c /= '\t') (dropWhile (\c -> c == ' ' || c == '\t') s)
