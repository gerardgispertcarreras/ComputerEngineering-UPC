nats :: [Integer]
nats = iterate (+1) 0

fact :: Integer -> Integer
fact 0 = 1
fact i = i * fact (i - 1)

exps :: Float -> [Float]
exps x = map serieTaylor nats
    where serieTaylor i = x ^ i / (fromIntegral $ fact i)

exponencial :: Float -> Float -> Float
exponencial x є =  exponencial' (exps x)
    where
        exponencial' (x:xs)
            | x < є = 0.0
            | otherwise = x + exponencial' xs