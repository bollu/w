{-# LANGUAGE DeriveFunctor #-}
{-# LANGUAGE NoImplicitPrelude #-}
{-# LANGUAGE TypeOperators #-}
import Prelude hiding (flip)

-- | a tree, the space where all our action is going to happen.
data Tree a = Branch a (Tree a) (Tree a) | Leaf a deriving(Functor)

instance Show a => Show (Tree a) where
  show (Leaf a) = show a
  show (Branch a trl trr) = show a <> " (L " <> show trl <> ") (R " <> show trr <> ")" 

treen :: Int -> Tree Int
treen 0 = Leaf 1
treen n = Branch (2 ^ n) (treen (n-1)) (fmap (+ (2^n)) (treen (n-1)))

data LR = L | R deriving(Eq, Show)
data Flip = Flip | Id deriving(Eq, Show)

flip :: Flip -> LR -> LR; flip Id lr = lr; flip Flip L = R; flip Flip R = L;
diff :: LR -> LR -> Flip; diff x y = if x == y then Id else Flip

-- | original coord system
newtype Crumbs = Crumbs [LR]  deriving(Eq, Show)
-- | new coord system
newtype Flips = Flips [Flip]  deriving(Eq, Show)


ixcrumbs :: Crumbs -> Tree a -> a
ixcrumbs (Crumbs []) (Leaf a) = a
ixcrumbs (Crumbs []) (Branch a _ _) = a
ixcrumbs (Crumbs (L:cs)) (Branch _ trl _) = ixcrumbs (Crumbs cs) trl
ixcrumbs (Crumbs (R:cs)) (Branch _ _ trr) = ixcrumbs (Crumbs cs) trr

ixflips :: Flips -> Tree a -> a
ixflips = ixflips_ L

ixflips_ :: LR -> Flips -> Tree a -> a
ixflips_ _ (Flips []) (Leaf a) = a
ixflips_ _ (Flips []) (Branch a _ _) = a
ixflips_ lr (Flips (f:fs)) (Branch _ trl trr) =
  let flr = flip f lr in 
  ixflips_ flr (Flips fs) (if flr == L then trl else trr)

crumbs2flips :: Crumbs -> Flips
crumbs2flips (Crumbs cs) = Flips (zipWith diff (L:cs) cs)

flips2crumbs :: Flips -> Crumbs
flips2crumbs (Flips fs) = Crumbs (flips2crumbs_ L fs)

flips2crumbs_ :: LR -> [Flip] -> [LR]
flips2crumbs_ _ [] = []
flips2crumbs_ lr (f:fs) = let flr = flip f lr in flr:flips2crumbs_ flr fs

crumbsfn2flipsfn :: (Crumbs -> a) -> (Flips -> a)
crumbsfn2flipsfn cfn fs = cfn (flips2crumbs fs)
