module EjerciciosPract4 where
    import Data.Char
    
    nextchar :: Char -> Char
    nextchar c = chr ((ord c) + 1)

    factorial :: Int -> Int
    factorial 0 = 1
    factorial n = n * factorial (n-1)

    numCbetw2 :: Char -> Char -> Int
    numCbetw2 c1 c2
        | ord c1 > ord c2 = ord c1 - ord c2 - 1
        | ord c1 < ord c2 = ord c2 - ord c1 - 1
        | otherwise = 0

    addRange :: Int -> Int -> Int
    addRange x y
        | x > y = addRange y x
        | x == y = x
        | otherwise = x + addRange (x+1) y
    
    max' :: Int -> Int -> Int
    max' x y
        | x > y = x
        | x < y = y
        | otherwise = x

    leapyear :: Int -> Bool
    leapyear x
        | mod x 400 == 0 = True
        | mod x 100 == 0 = False
        | mod x 4 == 0 = True
        | otherwise = False

    daysAmonth :: Int -> Int -> Int 
    daysAmonth x y
        | x == 2 && leapyear y = 29
        | x == 2 && not(leapyear y) = 28
        | even x = 31
        | otherwise = 30

    remainder :: Int -> Int -> Int 
    remainder x y 
        | x < y = x
        | otherwise = remainder (x-y) y

    sumFacts :: Int -> Int
    sumFacts 1 = factorial 1
    sumFacts x = factorial x + sumFacts (x-1) 
