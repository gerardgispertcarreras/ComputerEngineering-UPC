import Data.List (sort)

calcFreq :: [String] -> [(String, Int)]
calcFreq l = (foldl (calcFreq') [] l)
    where
        calcFreq' :: [(String,Int)] -> String -> [(String, Int)]
        calcFreq' [] s = [(s, 1)]
        calcFreq' (x:xs) s
            | (fst x) == s = ((s, (snd x + 1)) : xs)
            | otherwise = ((s, 1) : x : xs)

joinString :: String -> (String, Int) -> String
joinString s f = fst f ++ " " ++ show (snd f) ++ "\n" ++s

listWords :: [String] -> String
listWords l = foldl (joinString) "" $ calcFreq l

main = do
    x <- getContents
    let w = sort $ words x
    putStr $ listWords w