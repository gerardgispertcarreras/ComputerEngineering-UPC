s2i :: String -> Int
s2i = read

suma :: [String] -> Int
suma [] = 0
suma (x:xs) = s2i x + suma xs

main = do
  x <- getContents
  print $ suma $ words x