import qualified Data.Array as A
import qualified Data.List as L

ranktails :: Ord a => [a] -> Int
ranktails xs = resort n . concat. label . applyUntil (all single) (repartitions  n) . psort . zip [0..] $ xs where n = length xs


applyUntil :: (a -> Bool) -> [a -> a] -> a -> a
applyUntil p (f:fs) x = if p x then x else applyUntil p fs (f x)

resort n = A.elems . A.array (0, n-1)

label iss = zipWith tag iss (scanl (+) 0 (map length iss))
tag is j = [(i , j) | i <- is]
repartitions n = map (repartition n) (iterate (*2) 1)

repartition n k iss = concatMap (psort . map install ) iss where
  install i = (i , if j < n then k + a ! j else n-i -1)
  a = A.array (0, n-1) (concat (label iss))


psort :: Ord b => [(a, b)] -> [[a]]
psort xys = pass xys [ ]

pass [] xss = xss
pass (e@(x, y):xys) xss = step y xys [] [x] [] xss

step = undefined

single :: [a] -> Bool
single [_] = True
single _ = False


-- step _ [] as bs cs xss  = pass as (bs:pass cs xss)
-- step y (e@(x , y'):xys) as bs cs xss
--  | y' < y  = step y xs (e:as) bs cs xss
--  | y' == y  = step y xs as (e:bs) cs xss
--  | y' > y  = step y xs as bs (e:cs) xss

