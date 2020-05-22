-- Reference: Richard Bird, Pearls of functional algorithm design:
--   All the common prefixes.
--
--
-- Kasai's algorithm
import Data.List

mapadj :: (a -> a -> b) -> [a] -> [b]
mapadj f xs = zipWith f xs (tail xs)

lcp :: Eq a => [a] -> [a] -> [a]
lcp _ [] = []
lcp [] _ = []
lcp (a:as) (b:bs) = 
  case a == b of
    True -> a:lcp as bs; False -> []

llcp :: Eq a => [a] -> [a] -> Int
llcp as bs = length (lcp as bs)

tails' :: [a] -> [[a]]
tails' [] = []; tails' xs = xs:tails' (tail xs)

type Rank = Int
rank0 :: Ord a => [a] -> [Rank]
rank0 xs = [length (filter (< x) xs) | x <- xs]

-- | list of soerted tails
sorttails :: Ord a => [a] -> [[a]]
sorttails = sort . tails'

-- contains lcp(a[ix], a[ix-1])
lcparr_spec :: Ord a => [a] -> [Int]
lcparr_spec xs = mapadj llcp (sorttails xs)

-- https://cp-algorithms.com/string/suffix-array.html#toc-tgt-8
lcparr_nlong = undefined

-- https://cp-algorithms.com/string/suffix-array.html#toc-tgt-9
lcparr_n = undefined 
