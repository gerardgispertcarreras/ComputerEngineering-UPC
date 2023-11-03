import Control.Monad

data Expr = Val Int | Add Expr Expr | Sub Expr Expr | Mul Expr Expr | Div Expr Expr

eval1 :: Expr -> Int
eval1 (Val n) = n
eval1 (Add n m) = eval1 n + eval1 m
eval1 (Sub n m) = eval1 n - eval1 m
eval1 (Mul n m) = eval1 n * eval1 m
eval1 (Div n m) = div (eval1 n) (eval1 m)

eval2 :: Expr -> Maybe Int
eval2 (Val n) = Just n
eval2 (Add n m) = liftM2 (+) (eval2 n) (eval2 m)
eval2 (Sub n m) = do
    x <- eval2 n
    y <- eval2 m
    return (x - y)
eval2 (Mul n m) = do
    x <- eval2 n
    y <- eval2 m
    return (x * y)
eval2 (Div n m) = do
    x <- eval2 n
    y <- eval2 m
    guard (y /= 0)
    return (div x y)


liftM f x = do  
    vx <- x
    return (f x)

eval3 :: Expr -> Either String Int
eval3 (Val n) = Right n
eval3 (Add n m) = liftM2 (+) (eval3 n) (eval3 m)
eval3 (Sub n m) = do
    x <- eval3 n
    y <- eval3 m
    return (x - y)
eval3 (Mul n m) = do
    x <- eval3 n
    y <- eval3 m
    return (x * y)
eval3 (Div n m) = do
    x <- eval3 n
    y <- eval3 m
    if (y == 0) then (Left "div0")
    else return (div x y)