import random
INPUT = open("zad5_input.txt" , "r")
OUTPUT = open("zad5_output.txt", "w")

rows_in = [[] for i in range(7)]
columns_in = [[] for i in range(7)]
good_one = 0

ROWS = [[random.randint(0, 1) for i in range(7)] for i in range(7)]
COLUMNS = [[0 for i in range(7)] for i in range(7)]
def opt_dist(sequence,d):
    length = int(d)
    n = len(sequence)
    ones = [0 for i in range(n)]
    ones[0] = int(sequence[0])
    for i in range(1, n):
        ones[i] = ones[i - 1] + int(sequence[i])
    ans = 10000000000
    for i in range(n - length + 1):
        if i != 0:
            ones_before = ones[i - 1]
        else:
            ones_before = 0
        if length != 0:
            end = i + length - 1
        else:
            end = 0
        zeros = length - (ones[end] - ones_before)
        ones_after_length = ones[n - 1] - ones[end]
        swaping = ones_before + ones_after_length + zeros
        ans = min(ans, swaping)
    return ans

def input():
    num_ = 0
    for line in INPUT:
        if(num_ > 0 and num_ < 8):
            rows_in[num_-1].append(int(line))
        else:
            if(num_ > 0):
                columns_in[num_ - 8].append(int(line))
        num_ += 1

def good_block(block,d):
    count1 = 0
    count2 = 0
    if block[0] == 1:
        count2 += 1
    if d == 7:
        if sum(block) == 7:
            return True
        return False
    for i in range(1,len(block)):
        if block[i-1] != block[i]:
            count1 +=1
        if block[i] == 1:
            count2 +=1
    if count1 > 2:
        return False
    if count2 != d:
        return False
    return True

def change_good_blocks(x,y):
    if good_block(ROWS[x], rows_in[x][0]):
        rows_in[x][1] = 1
    else:
        rows_in[x][1] = 0
    if good_block(COLUMNS[y], columns_in[y][0]):
        columns_in[y][1] = 1
    else:
        columns_in[y][1] = 0

def gen_map():
    for i in range(7):
        for j in range(7):
            COLUMNS[i][j] = ROWS[j][i]
    for i in range(7):
        if good_block(ROWS[i],rows_in[i][0]):
            rows_in[i].append(1)
        else:
            rows_in[i].append(0)
        if good_block(COLUMNS[i],columns_in[i][0]):
            columns_in[i].append(1)
        else:
            columns_in[i].append(0)

def change(row,column):
    ROWS[row][column] ^= 1
    COLUMNS[column][row] ^= 1

def done():
    for i in range(7):
        if rows_in[i][1] == 0 or columns_in[i][1] == 0:
            return False
    return True

def find_area():
    x = random.randint(0,6)
    if (opt_dist(ROWS[x], rows_in[x][0]) == 0):
        return
    column_best = 0
    for column in range(7):
        min_col = opt_dist(COLUMNS[column],columns_in[column][0])
        min_row =  opt_dist(ROWS[x],rows_in[x][0])
        change(x,column)
        cng_column = opt_dist(COLUMNS[column],columns_in[column][0])
        cng_row = opt_dist(ROWS[x],rows_in[x][0])
        change(x,column)
        if(cng_column + cng_row < min_row + min_col):
            column_best = column

    change(x,column_best)
    change_good_blocks(x,column_best)

def solve():
    input()
    gen_map()
    COUNT = 10000
    while COUNT > 0 and not done():
        if COUNT % 10 == 0:
            x = random.randint(0, 6)
            y = random.randint(0, 6)
            change(x,y)
            change_good_blocks(x,y)
        find_area()
        COUNT -= 1
    if not done():
        solve()
        #print(line)
    #print(COUNT)
    #print(good_block(ROWS[0],rows_in[0][0]))
    #print(good_block(ROWS[1], rows_in[1][0]))
    #print(good_block(ROWS[2], rows_in[2][0]))
    #print(good_block(ROWS[3], rows_in[3][0]))
    #print(rows_in)
    #print(columns_in)
    #print(done())

solve()
for line in ROWS:
    for sign in line:
        OUTPUT.write('#' if sign == 1 else '.')
    OUTPUT.write('\n')
INPUT.close()
OUTPUT.close()