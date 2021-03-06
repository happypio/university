import sys
import math
from _collections import deque
#MAP IS Y ON X!!!!!!!!!!!!!!
MAP = []
exactMAP = []
SECTORS = [ [(0,0),(4,4)],[(0,5),(4,9)],[(0,10),(4,14)],
            [(5,0),(9,4)],[(5,5),(9,9)],[(5,10),(9,14)],
            [(10,0),(14,4)],[(10,5),(14,9)],[(10,10),(14,14)]]
MOVES = [(-1,0),(1,0),(0,-1),(0,1)]
visited = set()
POSSIBLE = [(0,0),(14,14)] #possible positions of enemy, square (min y,min x), (min y,min x)
ISLANDS = set()
exist_exactMAP = 0

#FUNCTIONS FOR PRECISE MAPS:
def preciseMAP(y,x):
    result_map = []
    tmp_map = []
    result_map.append(POSSIBLE[0])
    result_map.append(POSSIBLE[1])
    sum_posibilities_in_map = 0
    for i in range(y-4,y+5):
        shift = abs(abs(i - y) - 4)
        tmp_line = []
        for j in range(x-4,x+5):
            if POSSIBLE[0][0] <= i <= POSSIBLE[1][0] and POSSIBLE[0][1] <= j <= POSSIBLE[1][1]:
                if x - shift <= j <= x + shift:
                    if (not (x - 1 <= j <= x + 1) or not (y - 1 <= i <= y + 1)) and (i,j) not in ISLANDS:
                        tmp_line.append('P')
                        sum_posibilities_in_map += 1
                        #print('#', end ='')
                    else:
                        tmp_line.append('X')
                        #print('.', end = '')
                else:
                    tmp_line.append('X')
                    #print('.', end = '')
        if len(tmp_line) > 0:
            tmp_map.append(tmp_line)
            #print("")
    result_map.append(sum_posibilities_in_map)
    result_map.append(tmp_map)
    return result_map

def mod_preciseMAP(y,x):
    result_map = []
    tmp_map = []
    result_map.append(POSSIBLE[0])
    result_map.append(POSSIBLE[1])
    sum_posibilities_in_map = 0
    for i in range(y-4,y+5):
        shift = abs(abs(i - y) - 4)
        tmp_line = []
        for j in range(x-4,x+5):
            if POSSIBLE[0][0] <= i <= POSSIBLE[1][0] and POSSIBLE[0][1] <= j <= POSSIBLE[1][1]:
                if x - shift <= j <= x + shift:
                    if (i,j) not in ISLANDS:
                        tmp_line.append('P')
                        sum_posibilities_in_map += 1
                        #print('#', end ='')
                    else:
                        tmp_line.append('X')
                        #print('.', end = '')
                else:
                    tmp_line.append('X')
                    #print('.', end = '')
        if len(tmp_line) > 0:
            tmp_map.append(tmp_line)
            #print("")
    result_map.append(sum_posibilities_in_map)
    result_map.append(tmp_map)
    return result_map

def common_part_maps(map1,map2):
    min_y,min_x= max(map1[0][0],map2[0][0]),max(map1[0][1],map2[0][1])
    max_y, max_x = min(map1[1][0], map2[1][0]), min(map1[1][1], map2[1][1])
    #print((min_y,min_x),(max_y,max_x))
    pos1, pos2 = map1[3] , map2[3]
    result_map = []
    tmp_map = []
    result_map.append((min_y,min_x))
    result_map.append((max_y,max_x))
    sum_posibilities_in_map = 0
    for i in range(min_y,max_y + 1):
        tmp_line = []
        for j in range(min_x,max_x + 1):
            if pos1[i - map1[0][0]][j - map1[0][1]] == 'P' and  pos2[i - map2[0][0]][j - map2[0][1]] == 'P':
                tmp_line.append('P')
                sum_posibilities_in_map += 1
            else:
                tmp_line.append('X')
        tmp_map.append(tmp_line)
    result_map.append(sum_posibilities_in_map)
    result_map.append(tmp_map)
    return result_map

def move_map(direction):
    global exactMAP
    old_map = exactMAP[3]
    min_corner = exactMAP[0]
    max_corner = exactMAP[1]
    result_map = []
    tmp_map = []
    result_map.append(POSSIBLE[0])
    result_map.append(POSSIBLE[1])
    sum_posibilities_in_map = 0
    if direction == 'N':
        if POSSIBLE[0][0] != min_corner[0]:
            tmp_line = []
            for j in range(len(old_map[0])):
                if not (POSSIBLE[0][0],j + min_corner[1]) in ISLANDS and old_map[0][j] == 'P':
                    tmp_line.append('P')
                    sum_posibilities_in_map += 1
                else:
                    tmp_line.append('X')
            tmp_map.append(tmp_line)

        for i in range(1,len(old_map)):
            tmp_line = []
            for j in range(len(old_map[0])):
                if not (min_corner[0] + i - 1,min_corner[1] + j) in ISLANDS and old_map[i][j] == 'P':
                    sum_posibilities_in_map += 1
                    tmp_line.append('P')
                else:
                    tmp_line.append('X')
            tmp_map.append(tmp_line)
    if direction == 'W':
        for i in range(len(old_map)):
            tmp_line =[]
            if POSSIBLE[0][1] != min_corner[1]:
                if not (min_corner[0] + i, POSSIBLE[0][1]) in ISLANDS and old_map[i][0] == 'P':
                    sum_posibilities_in_map += 1
                    tmp_line.append('P')
                else:
                    tmp_line.append('X')
            for j in range(1,len(old_map[0])):
                if not (min_corner[0] + i, min_corner[1] + j - 1) in ISLANDS and old_map[i][j] == 'P':
                    sum_posibilities_in_map += 1
                    tmp_line.append('P')
                else:
                    tmp_line.append('X')
            tmp_map.append(tmp_line)
    if direction == 'S':
        for i in range(0,len(old_map) - 1):
            tmp_line = []
            for j in range(len(old_map[0])):
                if not (min_corner[0] + i + 1,min_corner[1] + j) in ISLANDS and old_map[i][j] == 'P':
                    sum_posibilities_in_map += 1
                    tmp_line.append('P')
                else:
                    tmp_line.append('X')
            tmp_map.append(tmp_line)
        if POSSIBLE[1][0] != max_corner[0]:
            tmp_line = []
            for j in range(len(old_map[0])):
                if not (POSSIBLE[1][0],j + min_corner[1]) in ISLANDS and old_map[len(old_map) - 1][j] == 'P':
                    tmp_line.append('P')
                    sum_posibilities_in_map += 1
                else:
                    tmp_line.append('X')
            tmp_map.append(tmp_line)
    if direction == 'E':
        for i in range(len(old_map)):
            tmp_line =[]
            for j in range(0,len(old_map[0]) - 1):
                if not (min_corner[0] + i, min_corner[1] + j + 1) in ISLANDS and old_map[i][j] == 'P':
                    sum_posibilities_in_map += 1
                    tmp_line.append('P')
                else:
                    tmp_line.append('X')
            if POSSIBLE[1][1] != max_corner[1]:
                if not (min_corner[0] + i, POSSIBLE[1][1]) in ISLANDS and old_map[i][len(old_map[0]) - 1] == 'P':
                    sum_posibilities_in_map += 1
                    tmp_line.append('P')
                else:
                    tmp_line.append('X')
            tmp_map.append(tmp_line)
    result_map.append(sum_posibilities_in_map)
    result_map.append(tmp_map)
    exactMAP = result_map

'''mapa1 = [(2,3),(8,8),10,[
    ['X','X','X','X','X','X'],
    ['X','X','X','X','X','X'],
    ['X','X','X','X','X','X'],
    ['X','P','P','P','P','P'],
    ['X','X','X','P','P','X'],
    ['X','X','X','X','P','X'],
    ['X','X','X','X','X','P']
]]
mapa2 = [(5,6),(10,12),10,[
    ['P','X','P','X','X','X','X'],
    ['P','P','X','X','X','X','X'],
    ['X','P','X','X','X','X','X'],
    ['X','P','P','P','P','P','X'],
    ['X','X','X','P','X','X','X'],
    ['X','X','X','X','P','X','X']
]]
POSSIBLE = [(1,1),(14,14)]
torpedo_shoot(4,4)
odp1 = preciseMAP(4,4)
print(odp1[0],odp1[1],odp1[2])
for line in odp1[3]:
    print(line)
torpedo_shoot(2,2)
print(POSSIBLE)
odp2 = preciseMAP(2,2)
print(odp2[0],odp2[1],odp2[2])
for line in odp2[3]:
    print(line)
odp = common_part_maps(odp1,odp2)
print(odp[0],odp[1],odp[2])
for line in odp[3]:
    print(line)'''
def gen_small_map():
    result_map = []
    tmp_map = []
    result_map.append(POSSIBLE[0])
    result_map.append(POSSIBLE[1])
    sum_posibilities_in_map = 0
    for i in range(POSSIBLE[0][0],POSSIBLE[1][0] + 1):
        tmp_line = []
        for j in range(POSSIBLE[0][1],POSSIBLE[1][1] + 1):
            if not (i,j) in ISLANDS:
                tmp_line.append('P')
                sum_posibilities_in_map += 1
            else:
                tmp_line.append('X')
        tmp_map.append(tmp_line)
    result_map.append(sum_posibilities_in_map)
    result_map.append(tmp_map)
    return result_map

def gen_false_small_map():
    result_map = []
    tmp_map = []
    result_map.append(POSSIBLE[0])
    result_map.append(POSSIBLE[1])
    sum_posibilities_in_map = 0
    for i in range(POSSIBLE[0][0],POSSIBLE[1][0] + 1):
        tmp_line = []
        for j in range(POSSIBLE[0][1],POSSIBLE[1][1] + 1):
            tmp_line.append('X')
        tmp_map.append(tmp_line)
    result_map.append(sum_posibilities_in_map)
    result_map.append(tmp_map)
    return result_map

def modify_map(y,x):
    global exactMAP
    corner_min = exactMAP[0]
    corner_max = exactMAP[1]
    result_map = exactMAP[3]
    for i in range (y-1,y+2):
        for j in range (x-1,x+2):
            if corner_min[0] <= i <= corner_max[0] and corner_min[1] <= j <= corner_max[1]:
                if result_map[i - corner_min[0] ][j - corner_min[1]] == 'P':
                    #print(corner_max[0] - i,corner_max[1] - j)
                    result_map[i - corner_min[0] ][j - corner_min[1] ]= 'X'
                    exactMAP[2] -= 1

def count_possibilities(y,x):
    tmp_moves = [(-1,0),(1,0),(0,-1),(0,1),(-1,-1),(-1,1),(1,1),(1,-1),(0,0)]
    exmp_width = len(exactMAP[3][0])
    exmp_heigth =len(exactMAP[3])
    result = 0
    if exactMAP[3][y][x] == 'P':
        result += 1
    for move in tmp_moves:
        new_x = move[1] + x
        new_y = move[0] + y
        if 0 <= new_x < exmp_width and 0 <= new_y < exmp_heigth:
            if exactMAP[3][new_y][new_x] == 'P':
                result += 1
    return result

def find_path(y,x,gy,gx):
    STATES = set()
    STATES.add((y,x))
    queue = deque()
    state = (y,x,0)
    queue.append(state)
    while len(queue) > 0:
        act_state = queue.popleft()
        positions = (act_state[0],act_state[1])
        if positions[0] == gy and positions[1] == gx:
            return act_state[2]
        for move in MOVES:
            new_y = positions[0] + move[0]
            new_x = positions[1] + move[1]
            if not (new_y,new_x) in STATES and not (new_y,new_x) in ISLANDS:
                if act_state[2] + 1 <= 4:
                    STATES.add((new_y,new_x))
                    queue.append((new_y,new_x,act_state[2] + 1))
    return -1

def find_best_place(y,x):
    places = []
    corner_min = exactMAP[0]
    tmp_map = exactMAP[3]
    for i in range(len(tmp_map)):
        new_y = corner_min[0] + i
        for j in range(len(tmp_map[0])):
            new_x = corner_min[1] + j
            if not (new_y, new_x) in ISLANDS and abs(y - new_y) + abs(x - new_x) <= 4:
                length_of_way = find_path(y,x,new_y,new_x)
                if length_of_way != -1:
                    if abs(y - new_y) <= 1 and abs(x - new_x <= 1):
                        if (new_y,new_x) == (y,x):
                            places.append((count_possibilities(i, j) - 2, (new_y, new_x)))
                        else:
                            places.append((count_possibilities(i, j) - 1, (new_y, new_x)))
                    else:
                        places.append((count_possibilities(i, j), (new_y, new_x)))
    places.sort(reverse=True)
    return places

def change_4(y,x,tmp_map):
    new_width = len(tmp_map[3][0])
    new_heigth = len(tmp_map[3])
    sum_posibilities = 0
    shift_v = exactMAP[0][0] - tmp_map[0][0]
    shift_h = exactMAP[0][1] - tmp_map[0][1]
    #change x
    for i in range (-4,5):
        new_x = x + shift_h + i
        if 0 <= new_x < new_width and not (y + shift_v,new_x) in ISLANDS:
            tmp_map[3][y + shift_v][new_x] = 'P'
            sum_posibilities +=1
    #change y
    for i in range (-4,5):
        new_y = y + shift_v + i
        if 0 <= new_y < new_heigth and not (new_y,x + shift_h) in ISLANDS:
            tmp_map[3][new_y][x + shift_h] = 'P'
            sum_posibilities += 1
    tmp_map[2] = sum_posibilities

def expand_map():
    global exactMAP
    tmp_map = gen_false_small_map()
    small_map = exactMAP[3]
    for i in range (len(small_map)):
        for j in range (len(small_map[0])):
            if small_map[i][j] == 'P':
                change_4(i,j,tmp_map)
    exactMAP = tmp_map

#FUNCTIONS FOR ENEMY'S MOVES
def torpedo_shoot(y,x):
    # modify possible positions square
    global POSSIBLE,exactMAP,exist_exactMAP
    max_x,max_y,min_x,min_y = min(x + 4, 14),min(y + 4,14),max(x - 4,0),max(y - 4,0)
    act_max_y,act_max_x= min(POSSIBLE[1][0],max_y),min(POSSIBLE[1][1],max_x)
    act_min_y,act_min_x = max(POSSIBLE[0][0],min_y),max(POSSIBLE[0][1],min_x)
    POSSIBLE = [(act_min_y,act_min_x),(act_max_y,act_max_x)]
    torpedo_map = preciseMAP(y,x)
    if exist_exactMAP == 0:
        exactMAP = torpedo_map
        exist_exactMAP = 1
    else:
        exactMAP = common_part_maps(torpedo_map,exactMAP)

def mod_torpedo_shoot(y,x):
    # modify possible positions square
    global POSSIBLE, exactMAP, exist_exactMAP
    max_x, max_y, min_x, min_y = min(x + 4, 14), min(y + 4, 14), max(x - 4, 0), max(y - 4, 0)
    act_max_y, act_max_x = min(POSSIBLE[1][0], max_y), min(POSSIBLE[1][1], max_x)
    act_min_y, act_min_x = max(POSSIBLE[0][0], min_y), max(POSSIBLE[0][1], min_x)
    POSSIBLE = [(act_min_y, act_min_x), (act_max_y, act_max_x)]
    torpedo_map = mod_preciseMAP(y, x)
    if exist_exactMAP == 0:
        exactMAP = torpedo_map
        exist_exactMAP = 1
    else:
        exactMAP = common_part_maps(torpedo_map, exactMAP)

def surface(sector):
    # modify possible positions square
    global POSSIBLE,exactMAP,exist_exactMAP
    sector -= 1
    max_x, max_y, min_x, min_y = SECTORS[sector][1][1],SECTORS[sector][1][0],SECTORS[sector][0][1],SECTORS[sector][0][0]
    act_max_y, act_max_x = min(POSSIBLE[1][0], max_y), min(POSSIBLE[1][1], max_x)
    act_min_y, act_min_x = max(POSSIBLE[0][0], min_y), max(POSSIBLE[0][1], min_x)
    POSSIBLE = [(act_min_y, act_min_x), (act_max_y, act_max_x)]
    surface_map = gen_small_map()
    if exist_exactMAP == 0:
        exactMAP = surface_map
        exist_exactMAP = 1
    else:
        exactMAP = common_part_maps(surface_map,exactMAP)

def enemy_move(direction):
    # modify possible positions square
    global POSSIBLE
    max_x, max_y, min_x, min_y = POSSIBLE[1][1],POSSIBLE[1][0],POSSIBLE[0][1],POSSIBLE[0][0]
    if direction == 'N':
        max_y,min_y = max(POSSIBLE[1][0] - 1, 0),max(POSSIBLE[0][0] - 1,0)
    if direction == 'W':
        max_x, min_x = max(POSSIBLE[1][1] - 1, 0), max(POSSIBLE[0][1] - 1, 0)
    if direction == 'S':
        max_y, min_y = min(POSSIBLE[1][0] + 1, 14), min(POSSIBLE[0][0] + 1, 14)
    if direction == 'E':
        max_x, min_x = min(POSSIBLE[1][1] + 1, 14), min(POSSIBLE[0][1] + 1, 14)
    POSSIBLE = [(min_y,min_x),(max_y,max_x)]
    if exist_exactMAP != 0:
        move_map(direction)

def exactly_in_target(y,x):
    # modify possible positions
    global POSSIBLE,exactMAP,exist_exactMAP
    POSSIBLE=[(y,x),(y,x)]
    exactMAP = [(y,x),(y,x),1,['P']]
    exist_exactMAP = 1

def nearly_target(y,x):
    # modify possible positions
    global POSSIBLE,exactMAP,exist_exactMAP
    POSSIBLE = [(max(y-1,POSSIBLE[0][0]), max(x-1,POSSIBLE[0][1])), (min(y+1,POSSIBLE[1][0]), min(x+1,POSSIBLE[1][1]))]
    nearly_target_map = gen_small_map()
    shoot_y = abs(y - nearly_target_map[0][0])
    shoot_x = abs(x - nearly_target_map[0][1])
    if POSSIBLE[0][0] <= y <= POSSIBLE[1][0] and POSSIBLE[0][1] <= x <= POSSIBLE[1][1]:
        if nearly_target_map[3][shoot_y][shoot_x] == 'P':
            nearly_target_map[2] -= 1
            nearly_target_map[3][shoot_y][shoot_x] = 'X'
    if exist_exactMAP == 0:
        exactMAP = nearly_target_map
        exist_exactMAP = 1
    else:
        exactMAP = common_part_maps(nearly_target_map,exactMAP)

def missed_target(y,x):
    global exactMAP
    if exist_exactMAP != 0:
        modify_map(y,x)

def both_nearly_target(y1,x1,y2,x2):
    # modify possible positions
    global POSSIBLE,exactMAP,exist_exactMAP
    POSSIBLE = [(max(max(y1 - 1, y2 - 1), POSSIBLE[0][0]), max(max(x1 - 1, x2 - 1), POSSIBLE[0][1])),
                (min(min(y1 + 1, y2 + 1), POSSIBLE[1][0]), min(min(x1 + 1, x2 + 1), POSSIBLE[1][1]))]
    nearly_target_map = gen_small_map()
    if exist_exactMAP == 0:
        exactMAP = nearly_target_map
        exist_exactMAP = 1
    else:
        exactMAP = common_part_maps(nearly_target_map,exactMAP)

def one_nearly_target(y1,x1,y2,x2):
    # modify possible positions
    global POSSIBLE,exactMAP,exist_exactMAP
    POSSIBLE = [(max(min(y1 - 1,y2 - 1), POSSIBLE[0][0]), max(min(x1 - 1,x2 - 1), POSSIBLE[0][1])),
                (min(max(y1 + 1,y2 + 1), POSSIBLE[1][0]), min(max(x1 + 1,x2 + 1), POSSIBLE[1][1]))]
    nearly_target_map = gen_small_map()
    if exist_exactMAP == 0:
        exactMAP = nearly_target_map
        exist_exactMAP = 1
    else:
        exactMAP = common_part_maps(nearly_target_map,exactMAP)

def enemy_silence():
    global POSSIBLE
    max_x, max_y = min(POSSIBLE[1][1] + 4,14), min(POSSIBLE[1][0] + 4,14)
    min_x, min_y = max(POSSIBLE[0][1] - 4,0), max(POSSIBLE[0][0] - 4,0)
    POSSIBLE = [(min_y,min_x),(max_y,max_x)]
    if exist_exactMAP != 0:
        expand_map()

#MOVING FUNCTIONS
def convert_to_move(direction):
    if direction == 'N':
        return (-1,0)
    if direction == 'W':
        return (0, -1)
    if direction == 'S':
        return (1,0)
    if direction == 'E':
        return (0,1)

def convert_to_direction(move):
    if move == (-1,0):
        return 'N'
    if move == (0, -1):
        return 'W'
    if move == (1,0):
        return 'S'
    if move == (0,1):
        return 'E'

def do_move(y,x):
    middle = (POSSIBLE[0][0] + (POSSIBLE[1][0]- POSSIBLE[0][0])//2 , POSSIBLE[0][1] + (POSSIBLE[1][1] - POSSIBLE[0][1])//2)
    #print(middle,POSSIBLE)
    min_dist = 10000
    best_move = (-1,-1)
    for move in MOVES:
        new_x = x + move[1]
        new_y = y + move[0]
        if 0 <= new_y <= 14 and 0 <= new_x <= 14 and (new_y,new_x) not in ISLANDS and (new_y,new_x) not in visited:
            distance = abs(new_x - middle[1]) + abs(new_y - middle[0])
            if distance < min_dist:
                min_dist = distance
                best_move = move
    if best_move != (-1,-1):
        visited.add((y+best_move[0],x+best_move[1]))
        return convert_to_direction(best_move)
    else:
        visited.clear()
        visited.add((y,x))
        return False

#GAME FUNCTIONS
def react_to_orders(life):
    global enshoot
    tmp_orders = input().split('|')
    opponent_orders = [tmp_orders[i].split() for i in range(len(tmp_orders))]
    for order in opponent_orders:
        if order[0] == 'MOVE':
            global act_move,moved_first
            act_move = convert_to_move(order[1])
            enemy_move(order[1])
            if enshoot == 0:
                moved_first = 1
        else:
            if order[0] == 'TORPEDO':
                global shoots
                global ENEMYSHOOT
                ENEMYSHOOT = (int(order[2]),int(order[1]))
                if enlife_b4 - life == 0:
                    torpedo_shoot(int(order[2]),int(order[1]))
                else:
                    mod_torpedo_shoot(int(order[2]),int(order[1]))
                enshoot = 1
                shoots += 1
            else:
                if order[0] == 'SURFACE':
                    global ensurface
                    ensurface = 1
                    surface(int(order[1]))
                else:
                    if order[0] == 'SILENCE':
                        global ensilence
                        ensilence = 1
                        enemy_silence()

def react_to_opp_life(life):
    #he shooted himself
    if enlife_b4 - life > 0 and myshoot == 0 and ensurface == 0:
        if enlife_b4 - life == 1:
            if moved_first == 0:
                nearly_target(ENEMYSHOOT[0] + act_move[0],ENEMYSHOOT[1] + act_move[1])
            else:
                nearly_target(ENEMYSHOOT[0],ENEMYSHOOT[1])
        else:
            if moved_first == 0:
                exactly_in_target(ENEMYSHOOT[0] + act_move[0], ENEMYSHOOT[1] + act_move[1])
            else:
                exactly_in_target(ENEMYSHOOT[0],ENEMYSHOOT[1])
    # we shooted him
    if enlife_b4 - life > 0 and enshoot == 0 and ensurface == 0:
        if enlife_b4 - life == 1:
            nearly_target(MYSHOOT[0] + act_move[0],MYSHOOT[1] + act_move[1])
        else:
            exactly_in_target(MYSHOOT[0] + act_move[0],MYSHOOT[1] + act_move[1])
    #we both shooted
    if enlife_b4 - life > 0 and enshoot != 0 and myshoot != 0 and ensurface == 0:
        if moved_first == 0:
            one_nearly_target(MYSHOOT[0] + act_move[0], MYSHOOT[1] + act_move[1], ENEMYSHOOT[0] + act_move[0], ENEMYSHOOT[1] + act_move[1])
        else:
            one_nearly_target(MYSHOOT[0] + act_move[0],MYSHOOT[1] + act_move[1],ENEMYSHOOT[0],ENEMYSHOOT[1])

def try_to_shoot(y,x):
    if exist_exactMAP == 0:
        return False
    if exactMAP[2] == 0:
        print('P = 0',exactMAP,POSSIBLE)
    if exactMAP[2] > 12:
        return False
    if exactMAP[1][0] - exactMAP[0][0] > 4 and exactMAP[1][1] - exactMAP[0][1] > 4:
        return False
    if len(exactMAP[3]) == 0:
        print('mapa = []',exactMAP)
    best_shoots = find_best_place(y,x)
    if len(best_shoots) == 0:
        return False
    if exactMAP[2] == 1 and best_shoots[0][0] >= 1:
        return best_shoots[0][1]
    if best_shoots[0][0] < 2:
        return False
    if abs(exactMAP[2] - best_shoots[0][0] - 1 < 3):
        return best_shoots[0][1]
    return False

#INPUT
width,height, my_id = [int(i) for i in input().split()]
for i in range(height):
     MAP.append(input())
     for field in range(len(MAP[i])):
         if MAP[i][field] == 'x':
             ISLANDS.add((i,field))
#for line in MAP:
    #print(line)
#starts here beacause my submarine is going to rush enemy's submarine
if (7,5) not in ISLANDS:
    print("5 7")
    visited.add((7,5))
else:
    y,x = 7,5
    while (y,x) in ISLANDS:
        y += 1
        x += 1
    print(x,y)
    visited.add((y,x))

# game loop
enshoot = 0
ensurface = 0
enlife_b4 = 6
ensilence = 0
moved_first = 0
ENEMYSHOOT = (0,0)
mylife_b4 = 0
myshoot = 0
MYSHOOT = (0,0)
shoots = 0
act_move = (0,0)
while True:
    #x,y,my_life,opp_life,torpedo_cooldown = [int(i) for i in input().split()]
    x, y, my_life, opp_life, torpedo_cooldown, sonar_cooldown, silence_cooldown, mine_cooldown = [int(i) for i in input().split()]
    orders = []
    sonar_result = input()
    react_to_orders(opp_life)
    react_to_opp_life(opp_life)
    #if shoots == 11:
        #print(exactMAP)
    #if myshoot ==1
        #print(exactMAP)
    do_torpedo = try_to_shoot(y,x)
    myshoot = 0
    if do_torpedo != False and torpedo_cooldown == 0:
        orders.append('TORPEDO' + ' ' + str(do_torpedo[1]) + ' ' + str(do_torpedo[0]))
        torpedo_cooldown = 3
        myshoot = 1
        MYSHOOT = (do_torpedo[0],do_torpedo[1])
    my_move = do_move(y,x)
    if my_move != False:
        if torpedo_cooldown > 0:
            orders.append('MOVE' + ' ' + my_move + ' ' + 'TORPEDO')
        else:
            orders.append('MOVE' + ' ' + my_move)
    else:
        orders.append('SURFACE')
    for order in range(len(orders) - 1):
        print(orders[order],'|' ,end = ' ')
    print(orders[len(orders)-1])
    enshoot = 0
    ensurface = 0
    ensilence = 0
    moved_first = 0
    enlife_b4 = opp_life
    act_move = (0,0)