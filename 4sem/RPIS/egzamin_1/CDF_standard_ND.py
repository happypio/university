import math
def f(x):
    return math.exp(-(x**2/2))
def compositeTrapezoid(n,a,b):
    h = (b-a)/n
    sum = 0
    for i in range(1,n):
        sum += f(a + i*h)
    return (1/2)*h*(f(a) + 2*sum + f(b))

def RombergsMethod(n,a,b, Rombergs_tab):
    new_R_tab = [compositeTrapezoid(n,a,b)]
    for r in range(len(Rombergs_tab)):
        new_R_tab.append(1/(4**(r+1) - 1) * ((4**(r+1)) * (new_R_tab[r]) - Rombergs_tab[r]))
    Rombergs_tab = new_R_tab
    return Rombergs_tab

def I(x,experiment = True):
    a,b = 0,x
    N = 2 # N + 1 is number of points between (a,b) to error less than 10^(-8)
    # We want to have N as a power of 2
    bound = math.sqrt(((b-a)**3)/12) * 10**4
    while N < bound:
        N *= 2
    if(experiment):
        print("Minimum N required for given error:",N)
        print("Composite Trapezoid for", N, "subsets:", compositeTrapezoid(N,a,b))
    Rombergs_tab = []
    i = 1
    while i <= N:
        Rombergs_tab = RombergsMethod(i,a,b,Rombergs_tab)
        i *= 2
    if (not experiment):
        return Rombergs_tab[-1]
    print("Romberg's method for", N, "subsets:", Rombergs_tab[-1],'\n')
    Rombergs_tab = []
    # Just for experiment with results of 2 methods
    for n in [2**i for i in range(15)]:
        Rombergs_tab = RombergsMethod(n,a,b,Rombergs_tab)
        if n >= (2**10):
            print("Composite Trapezoid for", n, "subsets:", compositeTrapezoid(N,a,b))
            print("Romberg's method for", n, "subsets:", Rombergs_tab[-1])

def phi(t):
    if t >= 0:
        return 1/2 + 1/(math.sqrt(2 * math.pi)) * I(t,False)
    else:
        return 1/2 - 1/(math.sqrt(2 * math.pi)) * I(-t,False)

I(0.2)
print('\n')
I(2)
print('\n',phi(-2),'\n',phi(1.2),'\n',phi(0.2),'\n',phi(3),'\n',phi(5),'\n',phi(8),'\n')

import matplotlib.pyplot as plt
import numpy as np

# 100 linearly spaced numbers
x = np.linspace(-5,5,100)

# the function
y = [phi(xi) for xi in x]

# setting the axes at the centre
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
ax.spines['left'].set_position('center')
ax.spines['bottom'].set_position('zero')
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.yaxis.set_ticks_position('left')

# plot the function
plt.plot(x,y, 'r')

# show the plot
plt.show()