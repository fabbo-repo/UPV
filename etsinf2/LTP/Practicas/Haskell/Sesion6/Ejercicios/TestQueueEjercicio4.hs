import Queue1
main = do
   let m = (dequeue (enqueue 1 empty))
   let x = (enqueue 10 (enqueue 5 empty))
   let n = (enqueue 10 (enqueue 5 empty))
   let z = empty
   putStrLn (show (m == n))
   putStrLn (show (x == n))
   putStrLn (show (z == n))
   
   