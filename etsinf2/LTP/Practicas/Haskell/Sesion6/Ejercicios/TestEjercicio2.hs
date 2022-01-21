-- Test2.hs   runghc ------.hs
import qualified Circle
import qualified Triangle
main = do
   let n = (Circle.area 2)
   putStrLn ("The area of the circle is " ++ show n)
   let m = (Triangle.area 4 5)
   putStrLn ("The area of the triangle is " ++ show m)