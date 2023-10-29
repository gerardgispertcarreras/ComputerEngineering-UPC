s2i :: String -> Int
s2i = read

main = do
	x <- getContents
	print (sum (map (s2i) (words x)))
