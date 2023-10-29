s2i :: String -> Int
s2i = read

getResult :: [String] -> [Int] -> Either String Int
getResult [] [] = Left "Error"
getResult [] [x] = Right x
getResult (x:xs) (y1:y2:ys)
	| x == "+" = getResult xs ((y1 + y2):ys)
	| x == "-" = getResult xs ((y1 - y2):ys)
	| x == "*" = getResult xs ((y1 * y2):ys)
	| x == "/" = getResult xs ((div y1 y2):ys)
	| otherwise = getResult xs ((s2i x):y1:y2:ys)
getResult (x:xs) y = getResult xs ((s2i x):y)

main = do
	x <- getLine
	print (getResult (words x) [])