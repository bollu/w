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
bwtinv (ys, k) =
  let ps = map snd (sort (zip ys [0..])) 
  in take (length ys) (tail (map (ys !!) (iterate (ps !!) k)))
