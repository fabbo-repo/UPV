module Ejercicio7 where
type Side = Float
type Apothem = Float
type Radius = Float
type Height = Float
type Volume = Float

data Pentagon = Pentagon Side Apothem
data Circle = Circle Radius

class Shape a where
    perimeter :: a -> Float
    area :: a -> Float

volumePrism :: (Shape a) => a -> Height -> Volume
surfacePrism :: (Shape a) => a -> Volume

instance Shape Pentagon where
    perimeter (Pentagon s a) = 5 * s
    area (Pentagon s a) = 5 * s * a / 2

instance Shape Circle where
    perimeter (Circle r) = 2 * pi * r
    area (Circle r) = r * pi * r

volumePrism base height = (area base) * height