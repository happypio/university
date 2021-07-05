import sys
import math
import heapq
import random
from _collections import deque
# Grab the pellets as fast as you can!

# width: size of the grid
# height: top left corner is (x=0, y=0)

PACDICT = {}
MAP = []
pellets = []
MOVES = [(0,-1),(-1,0),(0,1),(1,0)]
PATHS = set()
COLLISION = set()

def modify_visible_pelets(position):
    global pellets
    count = 0
    i = position[1]
    while MAP[position[0]][i] != '#' and count <= 40:
        pellets[position[0]][i] = 0
        i += 1
        if i >= width:
            i = 0
        count += 1
    count = 0
    i = position[1]
    while MAP[position[0]][i] != '#' and count <= 40:
        pellets[position[0]][i] = 0
        if i <= 0:
            i = width - 1
        i -= 1
        count += 1
    count = 0
    i = position[0]
    while MAP[i][position[1]] != '#' and count <= 40:
        pellets[i][position[1]] = 0
        if i >= height:
            i = 0
        i += 1
        count += 1

    count = 0
    i = position[0]
    while MAP[i][position[1]] != '#' and count <= 40:
        pellets[i][position[1]] = 0
        if i <= 0:
            i = height-1
        i -= 1
        count += 1

def update_val(visit,pos,q_mv):
    if pos in visit:
        return 0
    minus_factor = 1 - (q_mv * (1/15))
    return pellets[pos[0]][pos[1]]*minus_factor

def make_move(pac_state,i):
    if i > len(pac_state):
        return []
    pac_id = pac_state[i][0]
    pos = pac_state[i][1]
    visit = pac_state[i][2]
    fast_mv = pac_state[i][3]
    moves = pac_state[i][4]
    type_id = pac_state[i][5]
    cool_time = pac_state[i][6]
    for move in MOVES:
        new_y = pos[0] + move[0]
        new_x = pos[1] + move[1]
        if move == (0,-1):
            if pos[1] == 0:
                new_x = width - 1
        if move == (0,1):
            if pos[1] == width - 1:
                new_x = 0
        if move == (-1,0):
            if pos[0] == 0:
                new_y = height - 1
        if move == (1,0):
            if pos[0] == height - 1:
                new_y = 0
        if 0 <= new_y < height and 0 <= new_x < width and MAP[new_y][new_x] != '#' and (new_y,new_x) not in visit:
            new_pos = (new_y,new_x)
            new_visit = visit.copy()
            new_visit.add(new_pos)
            new_moves = moves.copy()
            new_moves.add(new_pos)

            new_pac_state =[]
            new_pac_state.append((pac_id,pos,new_visit,fast_mv - 1,new_moves,type_id,cooldown_time - 1))
            return new_pac_state + make_move(pac_state, i + 1)

def path_find(start,fast_moves):
    best_value = 0
    best_state = []
    queue = deque()
    # state = (set(), [], int speed_moves , int val, pos ()) visited, moves ,speed_moves left, value of move and act_position
    tmp_set = set()
    tmp_set.add(start)
    queue.append((tmp_set,[start],fast_moves,0,start))
    while len(queue) > 0:
        act_state = queue.popleft()
        visit = act_state[0]
        moves = act_state[1]
        fast_mv = act_state[2]
        val = act_state[3]
        pos = act_state[4]
        if len(moves) >= 11:
            if val > best_value:
                best_value = val
                best_state = act_state
        else:
            for move in MOVES:
                new_y = pos[0] + move[0]
                new_x = pos[1] + move[1]
                if move == (0,-1):
                    if pos[1] == 0:
                        new_x = width - 1
                if move == (0,1):
                    if pos[1] == width - 1:
                        new_x = 0
                if move == (-1,0):
                    if pos[0] == 0:
                        new_y = height - 1
                if move == (1,0):
                    if pos[0] == height - 1:
                        new_y = 0
                if 0 <= new_y < height and 0 <= new_x < width and MAP[new_y][new_x] != '#' and (new_y,new_x) not in visit:
                    #update value new_val
                    new_pos = (new_y,new_x)
                    new_val = val + update_val(visit,new_pos,len(moves) - 1)
                    new_visit = visit.copy()
                    new_visit.add(new_pos)
                    new_moves = moves.copy()
                    new_moves.append(new_pos)
                    if fast_mv > 0:
                        for move in MOVES:
                            new_y = new_pos[0] + move[0]
                            new_x = new_pos[1] + move[1]
                            if move == (0,-1):
                                if new_pos[1] == 0:
                                    new_x = width - 1
                            if move == (0,1):
                                if new_pos[1] == width - 1:
                                    new_x = 0
                            if move == (-1,0):
                                if new_pos[0] == 0:
                                    new_y = height - 1
                            if move == (1,0):
                                if new_pos[0] == height - 1:
                                    new_y = 0
                            if 0 <= new_y < height and 0 <= new_x < width and MAP[new_y][new_x] != '#' and (new_y,new_x) not in new_visit:
                                #update value new2_val
                                new2_pos = (new_y,new_x)
                                new2_val = new_val + update_val(new_visit,new2_pos,len(moves) - 1)
                                new2_visit = new_visit.copy()
                                new2_visit.add(new2_pos)
                                new2_moves = moves.copy()
                                new2_moves.append(new2_pos)
                                new_fast_mv = max(0,fast_mv - 1)
                                queue.append((new2_visit,new2_moves,new_fast_mv,new2_val,new2_pos))
                    else:
                        new_fast_mv = max(0,fast_mv - 1)
                        queue.append((new_visit,new_moves,new_fast_mv,new_val,new_pos))
    return best_state

def run_away(my_type,type_enemy):
    if my_type == "SCISSORS" and type_enemy == "ROCK":
        return True
    if my_type == "ROCK" and type_enemy == "PAPER":
        return True
    if my_type == "PAPER" and type_enemy == 'SCISSORS':
        return True
    return False

def chase_enemy(my_type,type_enemy):
    if type_enemy == "SCISSORS" and my_type == "ROCK":
        return True
    if type_enemy == "ROCK" and my_type == "PAPER":
        return True
    if type_enemy == "PAPER" and my_type == 'SCISSORS':
        return True
    return False

def check_collision(path1,path2):
    if len(path1) == 1:
        return False
    for i in range(min(3, min(len(path1),len(path2) ) ) ):
        if path1[i] == path2[i]:
            return path1[i]
    return False

def modify_moves(my_pacmans,en_pacmans):
    paths = []
    for pacman in my_pacmans:
        start = (pacman[1],pacman[2])
        fast_moves = pacman[3]
        pac_id = pacman[0]
        state = path_find(start,fast_moves)
        val = state[3]
        path = state[1]
        paths.append((val,pacman,path))
    paths.sort()
    for i in range(len(paths)):
        tmp_walls = []
        for j in range(len(paths)):
            if i != j:
                to_check = check_collision(paths[i][2],paths[j][2])
            else:
                to_check = False
            while to_check != False:
                tmp_walls.append(to_check)
                MAP[to_check[0]][to_check[1]] = "#"
                start = (paths[i][1][1],paths[i][1][2])
                fast_moves = paths[i][1][3]
                state = path_find(start,fast_moves)
                if len(state) == 0:
                    to_check = False
                else:
                    paths[i] = (state[3], paths[i][1] , state[1])
                    to_check = check_collision(paths[i][2],paths[j][2])
        for pos in tmp_walls:
            MAP[pos[0]][pos[1]] = ' '
    return paths


def find_moves(my_pacmans,en_pacmans):
    orders = []
    paths = modify_moves(my_pacmans,en_pacmans)
    for path in paths:
        order = []
        order.append(path[1][0])
        moves = path[2]
        if len(moves) >= 2:
            goal = moves[1]
        else:
            goal = moves[0]
        order.append(goal[0])
        order.append(goal[1])
        orders.append(order)
    return orders


width, height = [int(i) for i in input().split()]
for i in range(height):
    tmp_row = []
    tmp2_row = []
    row = input()  # one line of the grid: space " " is floor, pound "#" is wall
    for elem in range(len(row)):
        if row[elem] == " ":
            tmp_row.append(1)
            tmp2_row.append(" ")
        else:
            tmp_row.append(0)
            tmp2_row.append("#")
    MAP.append(tmp2_row)
    pellets.append(tmp_row)



# game loop

move_count = 0
constant = 0.02
while True:
    move_count += 1
    my_score, opponent_score = [int(i) for i in input().split()]
    visible_pac_count = int(input())  # all your pacs and enemy pacs in sight
    my_pacmans = []
    en_pacmans = []
    for i in range(visible_pac_count):
        # pac_id: pac number (unique within a team)
        # mine: true if this pac is yours
        # x: position in the grid
        # y: position in the grid
        # type_id: unused in wood leagues
        # speed_turns_left: unused in wood leagues
        # ability_cooldown: unused in wood leagues
        pac_id, mine, x, y, type_id, speed_turns_left, ability_cooldown = input().split()
        pac_id = int(pac_id)
        mine = mine != "0"
        x = int(x)
        y = int(y)
        speed_turns_left = int(speed_turns_left)
        ability_cooldown = int(ability_cooldown)
        if mine:
            my_pacmans.append((pac_id,y,x,speed_turns_left,type_id,ability_cooldown))
            modify_visible_pelets((y,x))
        else:
            en_pacmans.append((pac_id,y,x,speed_turns_left,type_id,ability_cooldown))


    visible_pellet_count = int(input())  # all pellets in sight
    command = ""
    for pacman in my_pacmans:
        if pacman[5] == 0:
            command += "SPEED " + str(pacman[0]) + "|"
            pacman = (pacman[0],pacman[1],pacman[2],5,pacman[4],pacman[5])
            didspeed = 1
    big_pellets = []
    for i in range(visible_pellet_count):
        # value: amount of points this pellet is worth
        x, y, value = [int(j) for j in input().split()]
        if value == 10:
            big_pellets.append((y,x))
            pellets[y][x] = 10 + move_count*constant
        else:
            pellets[y][x] = 1 + move_count*constant
    pacman_moves = find_moves(my_pacmans,en_pacmans)
    if didspeed == 0:
        for elem in pacman_moves:
            command += "MOVE " + str(elem[0]) + " " + str(elem[2]) + " " + str(elem[1]) + "|"
    command = command.rstrip("|")
    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr)

    # MOVE <pacId> <x> <y>
    didspeed = 0
    print(command)
