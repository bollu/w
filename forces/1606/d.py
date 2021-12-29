#!/usr/bin/env python3
def base11(n):
	tot = 0
	base = 1
	while n > 0:
		tot = tot + (n % 10) * base
		n = n // 10
		base = base * 11
	return tot

def best(s, n):
	if n == 1: return s
	
	for i in range(1, 11):
		x = best(s-i, n-1)

print(f"97 {base11(97)} | {base11(70) + base11(27)}")
print(f"17 {base11(17)}| ")
print(f"111 {base11(111)} | {base11(3) + base11(4) + base11(100) + base11(4)}")
print(f"100 {base11(100)} | {base11(10) + base11(90)} | {base11(50) + base11(50)}")
print(f"10 {base11(10)}")
print(f"999999 {base11(999999)} | {base11(999900) + base11(90) + base11(9)}")
