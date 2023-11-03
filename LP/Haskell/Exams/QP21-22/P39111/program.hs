import Data.List (sort)

type Pos = (Int, Int)

dinsNum :: Int -> Bool
dinsNum x = x >= 1 && x <= 8

dins :: Pos -> Bool
dins (f, c) = dinsNum f && dinsNum c

moviments :: Pos -> [Pos]
moviments (f, c) = filter dins 
    [ (f + 2, c - 1),
      (f + 2, c + 1),
      (f - 2, c - 1),
      (f - 2, c + 1),
      (f + 1, c - 2),
      (f + 1, c + 2),
      (f - 1, c - 2),
      (f - 1, c + 2)
    ]

potAnar3 :: Pos -> Pos -> Bool
potAnar3 posI posF = elem posF $ concat $ map moviments $ concat $ map moviments $ moviments posI

potAnar3' :: Pos -> Pos -> Bool
potAnar3' posI posF = elem posF $ (moviments posI) >>= moviments >>= moviments
