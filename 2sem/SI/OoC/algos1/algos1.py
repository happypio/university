import sys
import math

#MAP IS Y ON X!!!!!!!!!!!!!!
MAP = []
SECTORS = [ [(0,0),(4,4)],[(0,5),(4,9)],[(0,10),(4,14)],
            [(5,0),(9,4)],[(5,5),(9,9)],[(5,10),(9,14)],
            [(10,0),(14,4)],[(10,5),(14,9)],[(10,10),(14,14)]]
MOVES = [(-1,0),(1,0),(0,-1),(0,1)]
visited = set()
POSSIBLE = [(0,0),(14,14)] #possible positions of enemy, square (min y,min x), (min y,min x)
ISLANDS = set()
GOOD_POINTS = set() #very possible positions of enemy (points y x)
POSSIBLE_MAP = []

#INPUT
width,height, my_id = [int(i) for i in input().split()]
for i in range(height):
     MAP.append(input())
     for field in range(len(MAP[i])):
         if MAP[i][field] == 'x':
             ISLANDS.add((i,field))
#for line in MAP:
    #print(line)

def gen_possible_pos(y,x,where):
    torpedo_squares = [(y-4,x-1),(y-1,x-4),(y+2,x-1),(y-1,x+2)] #upper square, left square, lower and right
    tmp = [] # if we return list it will be tmp
    for corner_position in torpedo_squares:
        g_y = corner_position[0]
        g_x = corner_position[1]
        for i in range(3):
            for j in range(3):
                #check if this point is not on island and in possible square (on board btw)
                if POSSIBLE[0][0] <= g_y + i <= POSSIBLE[1][0] and POSSIBLE[0][1] <= g_x + j <= POSSIBLE[1][1] and (g_y + i,g_x + j) not in ISLANDS:
                    #where says where we want to save possible point:
                    if where == 1:
                        GOOD_POINTS.add((g_y + i,g_x + j))
                    else:
                        tmp.append((g_y + i,g_x + j))
    #add also the points not from squares
    corners = [(-2,-2),(-2,2),(2,2),(2,-2)]
    for corner in corners:
        if POSSIBLE[0][0] <= y - corner[0] <= POSSIBLE[1][0] and POSSIBLE[0][1] <= x - corner[1] <= POSSIBLE[1][1] and (y - corner[0], x - corner[1]) not in ISLANDS:
            # where says where we want to save possible point:
            if where == 1:
                GOOD_POINTS.add((y - corner[0], x - corner[1]))
            else:
                tmp.append((y - corner[0], x - corner[1]) )
    if where == 2:
        return tmp
    tmp = list(GOOD_POINTS)
    tmp.sort()
    print(tmp)
    print(POSSIBLE)

def move_back(pos,movement):
    for move in reversed(movement):
        pos = (pos[0] - move[0], pos[1] - move[1])
    return pos
def compare_listof_pos(positions,movement):
    new_set = set()
    global GOOD_POINTS
    for pos in positions:
        #move position ! back ! with saved moves
        pos = move_back(pos,movement)
        if pos in GOOD_POINTS:
            new_set.add(pos)
    tmp1 = list(GOOD_POINTS)
    tmp2 = list(new_set)
    tmp1.sort(),tmp2.sort()
    print(tmp1,tmp2)
    print(POSSIBLE)
    GOOD_POINTS = new_set

def torpedo_shoot(y,x,shoot,movement):
    # modify possible positions square
    global POSSIBLE
    max_x,max_y,min_x,min_y = min(x + 4, 14),min(y + 4,14),max(x - 4,0),max(y - 4,0)
    act_max_y,act_max_x= min(POSSIBLE[1][0],max_y),min(POSSIBLE[1][1],max_x)
    act_min_y,act_min_x = max(POSSIBLE[0][0],min_y),max(POSSIBLE[0][1],min_x)
    POSSIBLE = [(act_min_y,act_min_x),(act_max_y,act_max_x)]
    #sets with possible points ( 4 squares)
    #which shoot?
    if shoot == 0:
        gen_possible_pos(y,x,1)
    else:
        positions = gen_possible_pos(y,x,2)
        compare_listof_pos(positions,movement)

def surface(sector):
    # modify possible positions square
    global POSSIBLE
    max_x, max_y, min_x, min_y = SECTORS[sector][1][1],SECTORS[sector][1][0],SECTORS[sector][0][1],SECTORS[sector][0][0]
    act_max_y, act_max_x = min(POSSIBLE[1][0], max_y), min(POSSIBLE[1][1], max_x)
    act_min_y, act_min_x = max(POSSIBLE[0][0], min_y), max(POSSIBLE[0][1], min_x)
    POSSIBLE = [(act_min_y, act_min_x), (act_max_y, act_max_x)]

def convert_to_move(direction):
    if direction == 'N':
        return (-1,0)
    if direction == 'W':
        return (0, -1)
    if direction == 'S':
        return (1,0)
    if direction == 'E':
        return (0,1)

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

def exactly_in_target(y,x):
    # modify possible positions
    global POSSIBLE
    POSSIBLE=[(y,x),(y,x)]
    compare_listof_pos(POSSIBLE_MAP, MOVEMENT)
def gen_possible_map(y1,x1,y2,x2):
    global POSSIBLE_MAP
    POSSIBLE_MAP.clear()
    for i in range(POSSIBLE[0][1] - POSSIBLE[0][0]):
        for j in range(POSSIBLE[1][1] - POSSIBLE[1][0]):
            if (i,j) != (y1,x1) and (i,j) != (y2,x2):
                POSSIBLE_MAP.append((i,j))

def nearly_target(y,x):
    # modify possible positions
    global POSSIBLE
    POSSIBLE = [(max(y-1,POSSIBLE[0][0]), max(x-1,POSSIBLE[0][1])), (min(y+1,POSSIBLE[1][0]), min(x+1,POSSIBLE[1][1]))]
    gen_possible_map(y,x,-1,-1)
    compare_listof_pos(POSSIBLE_MAP, MOVEMENT)


def Sort_Tuple(tup):
    # key is set to sort using second element of
    # sublist lambda has been used
    tup.sort(key = lambda x: x[1])
    return tup
def find_best_field(y,x):
    if POSSIBLE[0][0] <= y <= POSSIBLE[1][0] and POSSIBLE[0][1] <= x <= POSSIBLE[1][1] and (y , x ) not in ISLANDS:
        return (y,x)
    else:
        return (y-1,x-1)

def good_to_shoot():
    #return false if we are not sure were we shoot or field where to shoot
    positions = list(GOOD_POINTS)
    positions.sort()
    if len(positions) == 0:
        print(POSSIBLE)
        print(GOOD_POINTS)
        return False
    pos_heigth = positions[len(positions) - 1][0] - positions[0][0]
    pos_y = positions[0][0] + 1
    positions = Sort_Tuple(positions)
    pos_width = positions[len(positions) - 1][1] - positions[0][1]
    pos_x = positions[0][1] + 1
    if pos_heigth <= 3 and pos_width <= 3:
        return find_best_field(pos_y, pos_x)
    else:
        return False

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
MOVEMENT =[]
SHOOTS = 0
enshoot = 0
myshoot = 0
en_before_life = 6
ENEMYSHOOT = (0,0)
MYSHOOT = (0,0)
SURE = (0,0)
do_torpedo = 0
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
    middle = ((POSSIBLE[1][0]- POSSIBLE[0][0])//2 , (POSSIBLE[1][1] - POSSIBLE[0][1])//2)
    #print(middle,POSSIBLE)
    min_dist = 10000
    best_move = (0,0)
    for move in MOVES:
        new_x = x + move[1]
        new_y = y + move[0]
        if 0 <= new_y <= 14 and 0 <= new_x <= 14 and (new_y,new_x) not in ISLANDS and (new_y,new_x) not in visited:
            distance = abs(new_x - middle[1]) + abs(new_y - middle[0])
            if distance < min_dist:
                min_dist = distance
                best_move = move
    if best_move != (0,0):
        visited.add((y+best_move[0],x+best_move[1]))
        return convert_to_direction(best_move)
    else:
        visited.clear()
        return False



def react_to_orders(life):
    tmp_orders = input().split('|')
    opponent_orders = [tmp_orders[i].split() for i in range(len(tmp_orders))]
    for order in opponent_orders:
        if order[0] == 'MOVE':
            move = convert_to_move(order[1])
            MOVEMENT.append(move)
            enemy_move(order[1])
        if order[0] == 'TORPEDO' and en_before_life - life == 0:
            global SHOOTS
            global enshoot
            global ENEMYSHOOT
            ENEMYSHOOT = (int(order[2]),int(order[1]))
            torpedo_shoot(int(order[2]),int(order[1]),SHOOTS,MOVEMENT)
            SHOOTS += 1
            enshoot =1
            MOVEMENT.clear()
        if order[0] == 'SURFACE':
            surface(int(order[1]))
def both_nearly_target(y1,x1,y2,x2):
    # modify possible positions
    global POSSIBLE
    POSSIBLE = [(max(min(y1 - 1, y2 - 1), POSSIBLE[0][0]), max(min(x1 - 1, x2 - 1), POSSIBLE[0][1])),
                (min(max(y1 + 1, y2 + 1), POSSIBLE[1][0]), min(max(x1 + 1, x2 + 1), POSSIBLE[1][1]))]
    gen_possible_map(y1, x1, y2, x2)
    compare_listof_pos(POSSIBLE_MAP,MOVEMENT)

def one_nearly_target(y1,x1,y2,x2):
    # modify possible positions
    global POSSIBLE
    POSSIBLE = [(max(max(y1 - 1,y2-1), POSSIBLE[0][0]), max(max(x1 - 1,x2-1), POSSIBLE[0][1])),
                (min(min(y1 + 1,y2 + 1), POSSIBLE[1][0]), min(min(x1 + 1,x2 + 1), POSSIBLE[1][1]))]
    gen_possible_map(y1,x1,y2,x2)
    compare_listof_pos(POSSIBLE_MAP, MOVEMENT)
def react_to_opp_life(life):
    #he shooted himself
    if en_before_life - life > 0 and myshoot == 0:
        if en_before_life - life == 1:
            nearly_target(ENEMYSHOOT[0],ENEMYSHOOT[1])
        else:
            exactly_in_target(ENEMYSHOOT[0],ENEMYSHOOT[1])
    # we shooted him
    if en_before_life - life > 0 and enshoot == 0:
        if en_before_life - life == 1:
            nearly_target(MYSHOOT[0],MYSHOOT[1])
        else:
            exactly_in_target(MYSHOOT[0],MYSHOOT[1])
    if en_before_life - life > 0 and enshoot != 0 and myshoot != 0:
        if en_before_life - life == 1:
            one_nearly_target(MYSHOOT[0],MYSHOOT[1],ENEMYSHOOT[0],ENEMYSHOOT[1])
        else:
            both_nearly_target(MYSHOOT[0],MYSHOOT[1],ENEMYSHOOT[0],ENEMYSHOOT[1])

    #not sure if we shooted him or he himselg
while True:
    x,y,my_life,opp_life,torpedo_cooldown = [int(i) for i in input().split()]
    #x, y, my_life, opp_life, torpedo_cooldown, sonar_cooldown, silence_cooldown, mine_cooldown = [int(i) for i in input().split()]
    orders = []
    #sonar_result = input()
    react_to_orders(opp_life)
    react_to_opp_life(opp_life)
    if POSSIBLE[0][0] - POSSIBLE[1][0] == 0 and POSSIBLE[0][1] - POSSIBLE[1][1] == 0:
        SURE = (POSSIBLE[0][0], POSSIBLE[0][1])
        do_torpedo = 1
    else:
        if len(GOOD_POINTS) == 1:
            SURE = GOOD_POINTS.pop()
            do_torpedo = 1
        else:
            if SHOOTS > 0:
                SURE = good_to_shoot()
                if SURE != False:
                    do_torpedo = 1
    if do_torpedo:
        if abs(y-SURE[0]) + abs(x - SURE[1]) <= 4:
            orders.append('TORPEDO' + ' ' + str(SURE[1]) + ' ' + str(SURE[0]))
            torpedo_cooldown = 3
            myshoot = 1
            do_torpedo = 0
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
    myshoot = 0
    en_shoot = 0
    do_torpedo = 0
    en_before_life = opp_life