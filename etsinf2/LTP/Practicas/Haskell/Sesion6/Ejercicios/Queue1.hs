module Queue1 where
   
   data Queue a = EmptyQueue | Item a (Queue a)
   
   empty = EmptyQueue
   
   enqueue x EmptyQueue = Item x EmptyQueue
   enqueue x (Item a q) = Item a (enqueue x q)
   
   dequeue (Item _ q) = q
   
   first (Item a _) = a
   
   isEmpty EmptyQueue = True
   isEmpty _ = False
   
   size EmptyQueue = 0
   size (Item _ q) = 1 + size q

   instance (Show a) => Show (Queue a) where
      show EmptyQueue = " <- "
      show (Item x y) = " <- " ++ (show x) ++ (show y)

   --Ejercicio 4
   instance (Eq a) => Eq (Queue a) where
      EmptyQueue == EmptyQueue = True 
      (Item x xs) == (Item y ys) = x == y
      EmptyQueue == (Item x y) = False 
      (Item x y) == EmptyQueue = False    

   --Ejercicio 5
   toList :: (Queue a) -> [a]
   toList a 
      | isEmpty a = []
      | otherwise = (first a):(toList (dequeue a))
   fromList :: [a] -> (Queue a)
   fromList [] = empty
   fromList (x:xs) = enqueue x (fromList xs)

   