import sys
import math
import heapq
import random
from _collections import deque

MAP = []
pellets = []
MOVES = [(0,-1),(-1,0),(0,1),(1,0)]

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

def update_val(pacmans,pos,q_mv):
	for pac in pacmans:
		if pos in pac[2]:
			return 0
	minus_factor = 1 - (q_mv * (1/15))
	return pellets[pos[0]][pos[1]]*minus_factor

def check_direction(y,x):
	r = []
	if y == 1:
		 r.append('D')
	if y == -1:
		r.append('U')
	if x == 1:
		r.append('R')
	if x == -1:
		r.append('L')
	return r

def not_our_direction(old_pos,new_pos,our_pos):
	x = new_pos[1] - old_pos[1]
	y = new_pos[0] - old_pos[0]
	direction = check_direction(y,x)
	x = our_pos[1] - old_pos[1]
	y = our_pos[0] - old_pos[0]
	our_direction = check_direction(y,x)
	for i in our_direction:
		if i in direction:
			return False
	return True

def make_move(pac_state,i,good_state):
	result = []
	if i >= len(pac_state):
		return []
	pac_id = pac_state[i][0]
	pos = pac_state[i][1]
	visit = pac_state[i][2]
	fast_mv = pac_state[i][3]
	moves = pac_state[i][4]
	type_id = pac_state[i][5]
	cool_time = pac_state[i][6]
	val = pac_state[i][7]
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
		if 0 <= new_y < height and 0 <= new_x < width and MAP[new_y][new_x] != '#' and (new_y,new_x) not in visit \
		and all([(new_y,new_x) != pos[1] for pos in good_state]) and \
		all([((new_y,new_x) != pac_state[j][1]) or not_our_direction(pac_state[j][1],good_state[j][1],pos) for j in range(len(pac_state[0:i]))]):
			new_pos = (new_y,new_x)
			new_val = val + update_val(good_state,new_pos,len(moves) - 1)
			new_visit = visit.copy()
			new_visit.add(new_pos)
			new_moves = moves.copy()
			new_moves.append(new_pos)
			new_pac_state =[]
			new_pac_state.append((pac_id,new_pos,new_visit,fast_mv - 1,new_moves,type_id,cool_time - 1,new_val))
			if i + 1 >= len(pac_state):
				result += [new_pac_state]
			else:
				result += [new_pac_state + rest for rest in make_move(pac_state, i + 1,good_state + new_pac_state)]
			#print(new_pac_state)
	return result 

'''MAP = [ [' ' for j in range(20) ] for i in range(20)]
width = 20
height = 20
my_pacmans = [(0,3,4,5,"ROCK",10),(1,3,5,2,"SCISSORS",5)]
pacmans_state = []
for pac in my_pacmans:
	moves = []
	pac_id = [pac[0]]
	pos = (pac[1],pac[2])
	visit = set()
	visit.add(pos)
	fast_mv = pac[3]
	type_id = pac[4]
	cooldown_time = pac[5]
	val = 0
	pacmans_state.append((pac_id,pos,visit,fast_mv,moves,type_id,cooldown_time,val))
#odp = make_move(pacmans_state,0,[])
#for i in odp:
	#print(i)'''

def sum_val(pac_state):
	r = 0
	for pac in pac_state:
		r += pac[7]
	return r

def pathfinding(my_pacmans):
	pacmans_state = []
	for pac in my_pacmans:
		moves = []
		pac_id = pac[0]
		pos = (pac[1],pac[2])
		visit = set()
		visit.add(pos)
		fast_mv = pac[3]
		type_id = pac[4]
		cooldown_time = pac[5]
		val = 0
		pacmans_state.append((pac_id,pos,visit,fast_mv,moves,type_id,cooldown_time,val))
	queue = [] #priority queue
	heapq.heapify(queue)
	heapq.heappush(queue, (sum_val(pacmans_state),pacmans_state)) #state: position, boxes, good boxes and saved_moves
	while len(queue) > 0:
		tmp_state = heapq.heappop(queue)
		pac_state = tmp_state[1]
		if len(pac_state[0][4]) >= 15:
			return pac_state
		if len(pac_state[0][4]) == 8 and len(queue) >= 30:
			tmp_queue = []
			heapq.heapify(tmp_queue)
			for i in range(20):
				heapq.heappush(tmp_queue, (heapq.heappop(queue)))
			queue = tmp_queue
		to_move = make_move(pac_state,0,[])
		for state in to_move:
			heapq.heappush(queue, (sum_val(state),state))

def find_move(my_pacmans):
	pacmans = pathfinding(my_pacmans)
	orders = []
	for pac in pacmans:
		order = []
		order.append(pac[0])
		order.append(pac[4][0][0])
		order.append(pac[4][0][1])
		orders.append(order)
	return orders

#INPUT
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

move_count = 0
constant = 0.02
while True:
    move_count += 1
    my_score, opponent_score = [int(i) for i in input().split()]
    visible_pac_count = int(input())  # all your pacs and enemy pacs in sight
    my_pacmans = []
    en_pacmans = []
    for i in range(visible_pac_count):
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

    for i in range(visible_pellet_count):
        # value: amount of points this pellet is worth
        x, y, value = [int(j) for j in input().split()]
        if value == 10:
            pellets[y][x] = 10 + move_count*constant
        else:
            pellets[y][x] = 1 + move_count*constant
    pacman_moves = find_move(my_pacmans)
    if didspeed == 0:
        for elem in pacman_moves:
            command += "MOVE " + str(elem[0]) + " " + str(elem[2]) + " " + str(elem[1]) + "|"
    command = command.rstrip("|")
    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr)

    # MOVE <pacId> <x> <y>
    didspeed = 0
    print(command)