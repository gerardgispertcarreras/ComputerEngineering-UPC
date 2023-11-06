import Data.Ratio

nats :: [Integer]
nats = iterate (+1) 0

factorial :: Integer -> Integer
factorial 0 = 1
factorial n = n * factorial (n - 1)


termes_cosinus :: Rational -> [Rational]
termes_cosinus a = map (single_term) nats
    where
        single_term :: Integer -> Rational
        single_term n = (-1) ^ n * a ^ (2 * n) / (fromIntegral $ factorial $ 2 * n)

cosinus :: Rational -> Rational -> Rational
cosinus a e = foldl (+) 0 $ takeWhile (\t -> e < (abs t)) $ termes_cosinus a
