import random
import time
reset = 0

def good(hetmans,x,y):
    #sprawdzam czy mozna polozyc hetmana
    for i in range(len(hetmans)):
        if abs(x - i) == abs(hetmans[i] - y) or hetmans[i] == y:
            return False
    return True

def place(n):
    i = 0
    HETMANS = []
    CHOICES = [j for j in range(n)]
    while i < n:
        hetman_i = random.randint(0,n - 1)
        if good(HETMANS,i,hetman_i):
            HETMANS.append(hetman_i)
        else:
            #tablica CHOICES_tmp bedzie zawierala wybory wierszy
            #ktore nie zostaly sprawdzone w danej kolumnie
            CHOICES_tmp = CHOICES.copy()
            while (not good(HETMANS,i,hetman_i)) and len(CHOICES_tmp) > 0:
                hetman_i = random.choice(CHOICES_tmp)
                CHOICES_tmp.remove(hetman_i)
            if len(CHOICES_tmp) > 0:
                HETMANS.append(hetman_i)
            else:
                if good(HETMANS,i,hetman_i):
                    HETMANS.append(hetman_i)
                else:
                    return (False, -1)
        i += 1
    return (True,HETMANS)

def solve_restarts(n):
    #Aby wyniki byly jednolite ilosc testow mozna zwiekszyc do 1 000 000, ale wtedy dlugo trwa
    TESTS = 100000
    TESTS_n = TESTS
    first = 0
    while TESTS > 0:
        ans = place(n)
        if ans[0] == True:
            first += 1
        TESTS -= 1
    print(f' TESTS: {TESTS_n} , WITHOUT RESTART: {first}, PROBABILITY: {first/TESTS_n * 100}  %')
def solve_max(n):
    ans = place(n)
    while ans[0] != True:
        ans = place(n)
    return

def measure():
    # SZACHOWNICE MNIEJSZE OD 4 SA NIEROZWIAZYWALNE, WIEM ZE DLA 140, srednio czas dzialania < 5 sek
    i = 135
    while i < 300:
        start = time.time()
        solve_max(i)
        end = time.time()
        print(i, end - start)
        i += 1

#PIERWSZY PODPUNKT
#solve_restarts(6) ~ 6, 923

##############################
#DRUGI PODPUNKT
#measure() 148 to maksymalna odp
