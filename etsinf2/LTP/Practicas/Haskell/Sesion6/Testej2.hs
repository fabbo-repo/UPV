-- Test.hs  ghc --make Test.hs
import qualified Circle
import qualified Rectangle
-- main = putStrLn ("The area is " ++ show (areaRectangle 2 3))
main = do
    putStrLn ("The area of circle is " ++ (show (Circle.area 2)))
    putStrLn ("The area of rectangle is  " ++ (show (Rectangle.area 4 5)))