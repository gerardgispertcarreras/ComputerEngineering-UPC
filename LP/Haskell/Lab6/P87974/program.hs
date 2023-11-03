

main = do
    nom <- getLine
    let genere = last nom
    if genere == 'a' || genere == 'A'
        then putStrLn $ "Hola maca!"
    else putStrLn $ "Hola maco!"