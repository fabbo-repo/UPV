import Queue2
main = do
   putStrLn (show (dequeue (enqueue 1 empty)))
   putStrLn (show (enqueue 10 (enqueue 5 empty)))