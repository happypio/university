
def B(i,j):
    return 'B_%d_%d' % (i,j)

def domains(Vs):
    return [q + ' in 0..1' for q in Vs]

def sum(Qs):
    return 'sum([' + ', '.join(Qs) + ']'

def get_column(j,R):
    return [B(i, j) for i in range(R)]

def get_raw(i,C):
    return [B(i, j) for j in range(C)]

def radar_sum(raws,cols):
    return [sum(get_raw(i,len(cols))) + ', #=, ' + str(raws[i]) + ')' for i in range(len(raws))] + \
    [sum(get_column(i,len(raws))) + ', #=, ' + str(cols[i]) + ')' for i in range(len(cols))]

def rectangle(R,C):
    result = []
    for i in range(R - 1):
        for j in range(C - 1):
            a = B(j, i)
            b = B(j, i + 1)
            c = B(j + 1, i)
            d = B(j + 1, i + 1)
            result.append(b + ' + ' + c + ' #= 2 #<==> ' + a + ' + ' + d + ' #= 2')
    return result

def size2x2(R,C):
    result = []
    for i in range(1,R - 1):
        for j in range(1,C - 1):
            x = B(j, i)
            a = B(j, i + 1)
            b = B(j, i - 1)
            c = B(j + 1, i)
            d = B(j - 1,i)
            result.append(x + ' #= 1 #==> ' + c + ' + ' + d + ' #> 0')
            result.append(x + ' #= 1 #==> ' + a + ' + ' + b + ' #> 0')
    return result
def check_corners(R,C):
    result = []
    for i in range(R-1):
        x1 = B(0,i)
        x2 = B(C-1,i)
        a = B(1,i)
        b = B(C-2,i)
        result.append(x1 + ' #= 1 #==> ' + a + ' #> 0')
        result.append(x2 + ' #= 1 #==> ' + b + ' #> 0')

    for j in range(C-1):
        x1 = B(j,0)
        x2 = B(j,R-1)
        a = B(j,1)
        b = B(j,R-2)
        result.append(x1 + ' #= 1 #==> ' + a + ' #> 0')
        result.append(x2 + ' #= 1 #==> ' + b + ' #> 0')
    return result


def print_constraints(Cs, indent, d):
    position = indent
    print((indent - 1) * ' ', end=' ', file=output)
    for c in Cs:
        print(c + ',', end=' ', file=output)
        position += len(c)
        if position > d:
            position = indent
            print(file=output)
            print((indent - 1) * ' ', end=' ', file=output)

def storms(raws, cols, triples):
    R = len(raws)
    C = len(cols)
    bs = [ B(i,j) for i in range(R) for j in range(C)]

    print(':- use_module(library(clpfd)).',file=output)    
    print('solve([' + ', '.join(bs) + ']) :- ',file=output)

    cs = domains(bs) + radar_sum(raws,cols) + rectangle(R,C) + size2x2(R,C) + check_corners(R,C)

    for i, j, val in triples:
        cs.append('%s #= %d' % (B(i, j), val))

    print_constraints(cs, 4, 70)
    print(file=output)
    print('    labeling([ff], [' +  ', '.join(bs) + ']).' ,file=output)
    print(file=output)
    print(":- tell('prolog_result.txt'), solve(X), write(X), nl, told.",file=output)


txt = open('zad_input.txt',encoding='utf8').readlines()
output = open('zad_output.txt', 'w',encoding='utf8')

raws = list(map(int, txt[0].split()))
cols = list(map(int, txt[1].split()))
triples = []

for i in range(2, len(txt)):
    if txt[i].strip():
        triples.append(map(int, txt[i].split()))

storms(raws, cols, triples)            
        
