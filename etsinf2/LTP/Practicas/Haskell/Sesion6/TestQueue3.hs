-- TestSQueue3.hs
import Queue
main = do
   putStrLn (show (enqueue 7 (enqueue 5 empty)))
