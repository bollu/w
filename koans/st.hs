import Control.Monad.ST
import Data.STRef
import Data.Foldable

-- playing around with ST monad

sumST :: Num a => [a] -> a
sumST xs = runST $ do
    n <- newSTRef 0
    for_ xs $ \x ->
        modifySTRef n (+x)
    readSTRef n

