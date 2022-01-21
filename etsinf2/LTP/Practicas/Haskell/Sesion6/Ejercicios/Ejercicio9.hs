module Ejercicio9 where

type Side = Float
type Apothem = Float
type Radius = Float
type Height = Float
type Volume = Float
type Surface = Float

data Shape = Pentagon Side Apothem |
            Circle Radius
data Pentagon = Pentagon Side Apothem
data Circle = Circle Radius

perimeter :: Shape -> Float
perimeter (Pentagon s a) = 5 * s 
perimeter (Circle r)     = 2 * pi * r
area :: Shape -> Float
area (Pentagon s a) = 5 * s * a / 2
area (Circle r) = r * pi * r
volumePrism :: (Shape a) => a -> Height -> Volume
surfacePrism :: (Shape a) => a -> Height -> Surface
volumePrism base height = (area base) * height
surfacePrism base height = (perimeter base)* height + 2 * (area base)

class (Eq a, Show a) => Shape a where

