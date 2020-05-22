import Data.List
import Control.Arrow

-- v1

lrot :: [a] -> [a]
lrot [] = []; lrot (a:as) = as ++ [a]

lrots :: [a] -> [[a]]; lrots as = take (length as) (iterate lrot as)

position :: Eq a => a -> [a] -> Int
position a as = length (takeWhile (/= a) as)

lastcol :: [[a]] -> [a]; lastcol = map last

bwt :: Eq a => Ord a => [a] -> ([a], Int)
bwt as = let as' = (sort . lrots) as in (lastcol as', position as as')

bwtinv :: Eq a => Ord a => ([a], Int) -> [a]
bwtinv (as, k) = recreate as !! k

-- recreate · lastcol · sort · rots = sort · rots
recreate :: (Eq a, Ord a) => [a] -> [[a]]
recreate as = recreate' (length as) as

recreate' :: (Eq a, Ord a) => Int -> [a] -> [[a]]
recreate' 0 = map (const [])
recreate' n = hdsort . consCol . (id &&& recreate' (n-1))


hdsort :: Ord a => [[a]] -> [[a]]
hdsort = let cmp (x:xs) (y:ys) = compare x y
         in sortBy cmp 

consCol :: ([a], [[a]]) -> [[a]]
consCol = uncurry (zipWith (:))

