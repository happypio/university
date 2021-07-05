import math as m
import numpy as np

def fact(n):
	fact = 1
	for i in range(2, n + 1):
		fact = fact * i
	return fact

def a (x):
	return 4 * np.cos(x) ** 2 - 3

def a_better (x):
	return -16 * (m.cos((x + m.pi/6)/2)*m.cos((x - m.pi/6)/2)*m.sin((x + m.pi/6)/2)*m.sin((x - m.pi/6)/2))
	"""c = (2 - m.sqrt(3)) / 2
	sign = -1
	p = 2
	for i in range(12):
		c += sign * (m.pow(x,p) / fact(p))
		p += 2
		sign *= -1
	return 2 * c * (2 * m.cos(x) + m.sqrt(3))"""

print(a(m.pi / 6 - m.pow(10, - 10)))
print(a_better(m.pi / 6 - m.pow(10, -10)))
print(a(m.pi / 6 ))
print(a_better(m.pi / 6))
print('\n ================ \n')

def b (x):
	return m.pow(x, -3) * (m.pi / 2 - x - np.arctan(1/x))

def b_better(x):
	c = - 1/6
	sign = 1
	p = 2
	for i in range(12):
		c += sign * (m.pow(x,p) / fact(p + 3))
		p += 2
		sign *= -1
	return c

print(b(m.pow(10, -10)))
print(b_better(m.pow(10, -10)))

