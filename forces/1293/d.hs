p0=(2,2)
m=(1,1)

x = fst
y = snd

s = (3, 3)

dist (x,y) (x',y') = abs (x - x') + abs (y - y')
line n =  (fst m) * line (n-1) + fst p0 + fst 

pts = [ | n <- [1..]]

