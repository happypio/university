import math as m

def sol (a , b , c):
	s_d = m.sqrt(b ** 2 - 4 * a * c)
	x1 = (-b - s_d) / (2 * a)
	x2 = (-b + s_d) / (2 * a)
	return x1,x2

def sol_better(a , b , c):
	s_d = m.sqrt(b ** 2 - 4 * a * c)
	if b > 0:
		x1 = (-2 * c) / (s_d + b)
		x2 = (-b - s_d) / (2 * a)
	else:
		x1 = (2 * c) / (s_d - b)
		x2 = (-b + s_d) / (2 * a)
	return x1,x2

#tescik
print(sol(pow(10,-10), pow(10,6), pow(10,-10)))
print(sol_better(pow(10,-10), pow(10,6), pow(10,-10)))