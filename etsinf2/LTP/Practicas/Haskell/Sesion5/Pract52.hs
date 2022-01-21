module Pract52 where
    type Person = String
    type Book = String
    type Database = [(Person,Book)]
    data Tree a = Leaf a | Branch (Tree a) (Tree a) deriving Show
    data BinTreeInt = Void | Node Int BinTreeInt BinTreeInt deriving Show

    exampleBase :: Database
    exampleBase = [("Alicia","El nombre de la rosa"),("Juan","La hija del canibal"),("Pepe","Odesa")]
    
    --Ejercicio 11
    borrow :: Database -> Book -> Person -> Database
    return' :: Database -> (Person,Book) -> Database
    borrow x y z = (y,z):x 
    return' [] y = [] 
    return' (x:xs) y 
        | x == y = xs
        | otherwise = return' xs y
    
    --Ejercicio 12
    symmetric :: Tree a -> Tree a
    symmetric (Leaf x) = (Leaf x)
    symmetric (Branch x y) = Branch (symmetric y) (symmetric x)
    
    --Ejercicio 13
    listToTree :: [a] -> Tree a
    treeToList :: Tree a -> [a]
    listToTree [x] = Leaf x
    listToTree (x:xs) = Branch (Leaf x) (listToTree xs) 
    treeToList (Leaf x) = [x]
    treeToList (Branch x y) = (treeToList x)++(treeToList y)
    
    --Ejercicio 14
    insTree :: Int -> BinTreeInt -> BinTreeInt
    insTree x Void = (Node x Void Void) 
    insTree x (Node y m n)
        | x <= y = (Node y (insTree x m) n)
        | otherwise = (Node y m (insTree x n))
    
    --Ejercicio 15
    creaTree :: [Int] -> BinTreeInt
    creaTree [] = Void
    creaTree (x:xs) = insTree x (creaTree xs)
    
    --Ejercicio 16
    treeElem :: Int -> BinTreeInt -> Bool
    treeElem x Void = False
    treeElem x (Node y m n)
        | x == y = True
        | x < y = treeElem x m
        | otherwise = treeElem x n

    test1 = treeElem 9 (Node 3 (Node 2 Void Void) (Node 7 (Node 4 Void Void) (Node 9 Void Void)))
    test2 = treeElem 6 (Node 3 (Node 2 Void Void) (Node 7 (Node 4 Void Void) (Node 9 Void Void)))