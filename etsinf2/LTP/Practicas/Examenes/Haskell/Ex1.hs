module Ex1 where
    
    data BinTreeInt = Void | Node Int BinTreeInt BinTreeInt deriving Show
    
    member x [] = False
    member x (y:ys) 
        | x==y = True
        | otherwise = member x ys

    --Ejercicio 1
    intersect :: (Eq a) => [a] -> [a] -> [a]
    intersect x y = [z | z <- x, (member z y)]

    --Ejercicio 2
    mapTree :: (Int -> Int) -> BinTreeInt -> BinTreeInt
    mapTree f Void = Void
    mapTree f (Node x y z) = (Node (f x) (mapTree f y) (mapTree f z))