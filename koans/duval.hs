import Data.List
lrot :: [a] -> [a]
lrot [] = []; lrot (a:as) = as ++ [a]

lrots :: [a] -> [[a]]
lrots xs = take (length xs) (iterate lrot xs)

islyndon :: Ord a => [a] -> Bool
islyndon xs = (head . sort  . lrots) xs == xs

-- found
-- finalized  w^n.pre(w) untouched
-- |----s1----|----s2----|----s3----|
--            i          k       j

duval :: Int -> Int -> [a] -> [[a]]
duval j k as = 
  case (as !! k) `compare` (as !! j) of
    LT -> duval 
    EQ -> duval j (k+1) as
    GT -> 

