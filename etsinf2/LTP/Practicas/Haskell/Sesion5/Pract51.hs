module Pract51 where
    
    decBin :: Int -> [Int]
    decBin 0 = [0]
    decBin 1 = [1]
    decBin x = (mod x 2) : decBin (div x 2)

    binDec :: [Int] -> Int
    binDec (x:[]) = x
    binDec (x:xs) = x + binDec xs * 2

    divisors :: Int -> [Int]
    divisors x = [y | y <- [1..x], mod x y == 0]

    member :: Int -> [Int] -> Bool
    member x [] = False
    member x (y:ys) = if x==y then True else member x ys

    isPrime :: Int -> Bool 
    isPrime x 
        |  x == 1 = True
        | length (divisors x) == 2 = True
        | otherwise = False

    primes :: Int -> [Int]
    primes x = take x [y | y <- [1..], isPrime y]

    selectEven :: [Int] -> [Int]
    selectEven [] = []
    selectEven (x:xs) 
        | even x = x : selectEven xs
        | otherwise = selectEven xs

    selectEvenPos :: [Int] -> [Int]
    selectEvenPos x = [x!!y | y <- [0..(length x - 1)] , even y] 

    iSort :: [Int] -> [Int]
    iSort [] = []
    iSort (x:xs) = ins x (iSort xs) 

    ins ::  Int -> [Int] -> [Int]
    ins x [] = [x]
    ins x (y:ys) 
        | x > y = y:(ins x ys)
        | otherwise = x:y:ys
    
    doubleAll :: [Int] -> [Int]
    doubleAll x = map (2*) x

    map' x y = [x z | z <- y]

    filter' x y = [z | z <- y , x z]

