calculateBMI :: Float -> Float -> Float
calculateBMI m h = m / (h ^ 2)

interpretateBMI :: Float -> String
interpretateBMI bmi
  | bmi < 18.0 = "underweight"
  | bmi < 25.0 = "normal weight"
  | bmi < 30.0 = "overweight"
  | bmi < 40.0 = "obese"
  | otherwise = "severely obese"

s2f :: String -> Float
s2f = read

main = do
  x <- getLine
  if x /= "*" then do
    let (name:mass:height:_) = words x
    let bmi = calculateBMI (s2f mass) (s2f height)
    putStrLn (name ++ ": " ++ interpretateBMI bmi)
    main
  else
    return ()