from collections import deque

def all_possibilities(pattern,length):

    if length == 0:
        return [[]]
    if len(pattern) == 0:
        return [[0] * length]
    possibilities = []
    if sum(pattern) + len(pattern) - 1 < length:
        possibilities += [[0] + new_block for new_block in all_possibilities(pattern,length - 1)]
    block = [1 for i in range(pattern[0])]
    if len(pattern[1:]) > 0:
        block += [0]
    length -= len(block)
    possibilities += [block + new_block for new_block in all_possibilities(pattern[1:],length)]
    return possibilities

def solution(rows,columns):
    possible_rows = [all_possibilities(ROWS[i],columns) for i in range(rows)]
    possible_columns = [all_possibilities(COLUMNS[i],rows) for i in range(columns)]
    img = [[0 for j in range(rows)] for i in range(columns)]
    not_good_points = deque()
    def modify_columns(x, y,point):
        good = []
        for column in possible_columns[x]:
            if column[y] == point:
                good.append(column)
        possible_columns[x] = good

    def modify_rows(x, y,point):
        good = []
        for row in possible_rows[y]:
            if row[x] == point:
                good.append(row)
        possible_rows[y] = good

    def is_point_good (x,y):
        x_smpl = possible_rows[y][0][x]
        if all(x_smpl == row[x] for row in possible_rows[y]):
            img[x][y] = x_smpl
            modify_columns(x,y,x_smpl)
        else:
            y_smpl = possible_columns[x][0][y]
            if all(y_smpl == column[y] for column in possible_columns[x]):
                img[x][y] = y_smpl
                modify_rows(x,y,y_smpl)

            else:
                not_good_points.append((x,y))

    for heigth in range(rows):
        for width in range (columns):
            is_point_good(width,heigth)

    while len(not_good_points) > 0:
        item = not_good_points.popleft()
        is_point_good(item[0],item[1])

    return img
ROWS = []
IMG = []
COLUMNS = []
rows_num = 0
col_num = 0
def input():
    with open('zad_input.txt','r') as INPUT:
        num = INPUT.readline().split()
        global rows_num
        rows_num = int(num[0])
        row_help = rows_num
        global col_num
        col_num = int(num[1])
        for line in INPUT:
            if row_help > 0:
                tmp = line.split()
                tmp2 = []
                for i in range(len(tmp)):
                    tmp2.append(int(tmp[i]))
                ROWS.append(tmp2)
                row_help -= 1
            else:
                tmp = line.split()
                tmp2 = []
                for i in range(len(tmp)):
                    tmp2.append(int(tmp[i]))
                COLUMNS.append(tmp2)

def output():
    with open('zad_output.txt','w') as OUTPUT:
        for column in range(len(IMG[0])):
            for row in range(len(IMG)):
                element = 0
                if IMG[row][column] == 1:
                    element = '#'
                else:
                    element = '.'
                OUTPUT.write(element)
            OUTPUT.write('\n')

input()
IMG = solution(rows_num,col_num)
output()





