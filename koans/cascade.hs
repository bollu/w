{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE FlexibleInstances #-}

-- http://www-verimag.imag.fr/~maler/Papers/kr-new.pdf

-- | a is alphabet
data Endo a = Endo { runEndo :: a -> a }
instance Semigroup (Endo a) where (Endo f) <> (Endo g) = Endo (f . g)

-- |act (a <> a') = act a <> act a' 
class Semigroup a => Action a x where act :: a -> Endo x

type Automata a x = a -> x -> x

-- | transformation semigroup for a given automata
transformation :: Automata a x -> a -> Endo x
transformation f a = Endo (\x -> a `f` x)

-- | take cascade product of two automata
cascadeProduct :: Automata a x -> Automata (a, x) y -> Automata a (x, y)
cascadeProduct p q = (\a (x, y) -> (a `p` x, (a, x) `q` y))

-- Endo a -> Endo (Endo (a, x))
instance Action (Endo a) (Endo (a, x)) where
    act sa = Endo $ \eax -> Endo $ \(a, x) -> runEndo eax (runEndo sa a, x)



data Semidirect a x = Semidirect a x deriving(Eq, Show)

instance (Semigroup a, Semigroup x, Action a x) => Semigroup (Semidirect a x) where
  (Semidirect a x) <> (Semidirect a' x') = Semidirect (a <> a') (x <> runEndo (act a) x')

data L = L1 | L2 | L3 deriving(Eq, Show, Ord, Bounded, Enum)
data SA = SA1 | SA2 | SA3 deriving(Eq, Show, Ord, Bounded, Enum)
data SB = SB1 | SB2 | SB3 deriving(Eq, Show, Ord, Bounded, Enum)

automata_a :: Automata L SA
automata_a L1 SA1 = SA2
automata_a L2 SA2 = SA3
automata_a L3 SA3 = SA1
automata_a _ sa = sa

automata_b :: Automata (L, SA) SB
automata_b (L1,SA2) SB1 = SB2
automata_b (L2,SA3) SB2 = SB3
automata_b _ sb = sb

-- let p :: (Automata a x)
--     q :: (Automata (a, x) y)
-- now check if 
-- Semidirect (transformation p, transformation q) ~= 
--     transformation (cascadeProduct a b)

