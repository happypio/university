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
    init_img = [[0 for j in range(rows)] for i in range(columns)]
    not_good_points = deque()
    def is_point_good (x,y,img,poss_columns,poss_rows,queue):
        x_smpl = poss_rows[y][0][x]
        if all(x_smpl == row[x] for row in poss_rows[y]):
            img[x][y] = x_smpl
            modify_columns(x,y,x_smpl,poss_columns)
        else:
            y_smpl = poss_columns[x][0][y]
            if all(y_smpl == column[y] for column in poss_columns[x]):
                img[x][y] = y_smpl
                modify_rows(x,y,y_smpl,poss_rows)

            else:
                queue.append((x,y))

    def modify_columns(x, y,point,poss_columns):
        good = []
        for column in poss_columns[x]:
            if column[y] == point:
                good.append(column)
        poss_columns[x] = good

    def modify_rows(x, y,point, poss_rows):
        good = []
        for row in poss_rows[y]:
            if row[x] == point:
                good.append(row)
        poss_rows[y] = good

    def inference(point,image,poss_rows,poss_columns):
        modify_rows(point[0],point[1],image[point[0]][point[1]],poss_rows)
        modify_columns(point[0],point[1],image[point[0]][point[1]],poss_columns)
        new_q = deque()
        for heigth in range(rows):
            for width in range (columns):
                if len(poss_rows[heigth]) == 0:
                    return False
                if len(poss_columns[width]) == 0:
                    return False
                is_point_good(width,heigth,image,poss_columns,poss_rows,new_q)
        return new_q



    def backtrack (image,poss_rows,poss_columns,q_points):
        if len(q_points) == 0:
            return image
        var = q_points.popleft()
        for i in [0,1]:
            new_img = image.copy()
            new_rows = poss_rows.copy()
            new_columns = poss_columns.copy()
            new_img[var[0]][var[1]] = i
            inferences = inference(var,new_img,new_rows,new_columns)
            if inferences != False:
                result = backtrack(new_img,new_rows,new_columns,inferences)
                if result != False:
                    return result
        return False

    for heigth in range(rows):
        for width in range (columns):
            is_point_good(width,heigth,init_img,possible_columns,possible_rows,not_good_points)

    return backtrack(init_img,possible_rows,possible_columns,not_good_points)
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





