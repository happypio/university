from collections import deque
import random
import itertools
ANS = []
MAP = []
goals = []
starts = []
WIDTH = 0
HEIGTH = 0
MOVES = [(-1,0),(1,0),(0,-1),(0,1)]
input_t = [
    'zad_input.txt',
    "map1.txt",'map2.txt','map3.txt','map4.txt','map5.txt',
    'map6.txt','map7.txt','map8.txt','map9.txt','map10.txt'
]

def input(input_name):
    global WIDTH, HEIGTH
    HEIGTH = 0
    with open(input_name, 'r') as INPUT:
        for line in INPUT:
            MAP.append(line.strip())
            for width in range(len(MAP[HEIGTH])):
                if MAP[HEIGTH][width] == 'S' or MAP[HEIGTH][width] == 'B':
                    starts.append((HEIGTH,width))
                if MAP[HEIGTH][width] == 'G' or MAP[HEIGTH][width] == 'B':
                    goals.append((HEIGTH,width))

            HEIGTH +=1
    HEIGTH -= 1
    WIDTH = len(MAP[HEIGTH])

def output():
    with open("zad_output.txt",'w') as OUTPUT:
        for i in range(len(ANS)):
            OUTPUT.write(ANS[i])

def do_moves(sequence):
    tmp_starts = starts.copy()
    for start in range(len(starts)):
        y = starts[start][0]
        x = starts[start][1]
        for move in sequence:
            new_x = x + move[1]
            new_y = y + move[0]
            if (0 <= new_x < WIDTH) and (0 <= new_y < HEIGTH):
                if MAP[new_y][new_x] != '#':
                    x = new_x
                    y = new_y
        tmp_starts[start] = (y,x)
    tmp_starts = list(set(tmp_starts))
    return (tmp_starts,len(tmp_starts))

def find_best_initial():
    NUMBER = 40
    TRIES = 50
    best_positions = []
    best_moves = []
    length_sequence = 10000
    while TRIES > 0:
        rdm_moves = [random.choice(MOVES) for i in range(NUMBER)]
        tmp_sequence = do_moves(rdm_moves)
        if tmp_sequence[1] < length_sequence:
            best_moves = rdm_moves
            length_sequence = tmp_sequence[1]
            best_positions = tmp_sequence[0]
        TRIES -= 1
    return (best_positions,best_moves)

def another_find_best_initial():
    all_sequences = list(itertools.permutations(MOVES))
    best_seq = ''
    minimal_moves = 10000
    best_positions = []

    for seq in all_sequences:
        no = 10
        act_seq = []
        for move in seq:
            for i in range(no):
                act_seq.append(move)
        after_seq = do_moves(act_seq)
        positions = after_seq[0]
        after_seq = after_seq[1]

        if after_seq < minimal_moves:
            minimal_moves = after_seq
            best_seq = act_seq
            best_positions = positions
    return(best_positions,best_seq)
def win(positions):
    for position in positions:
        if not (position in goals):
            return False
    return True

def convert_move(move):
    if move[0] == 1:
        return 'D'
    if move[0] == -1:
        return 'U'
    if move[1] == 1:
        return 'R'
    return 'L'

queue = deque()
STATES = set()
MOVES2 = [(0,1),(0,-1),(1,0),(-1,0)]

def solution_BFS(possible_positions,sequence):
    global ANS
    for i in range(len(sequence)):
        sequence[i] = convert_move(sequence[i])
    queue.append((possible_positions,sequence,0))
    STATES.add(tuple(possible_positions))
    # check if we win
    if win(possible_positions):
        ANS = sequence
        return
    cnt = 0
    while len(queue) > 0:
        cnt += 1
        if cnt % 100000 == 0:
            print(cnt)
        act_state = queue.popleft()
        act_positions = act_state[0]
        for move in MOVES2:
            new_act_positions = act_positions.copy()
            #move every position with given move
            for position in range(len(new_act_positions)):
                x = new_act_positions[position][1]
                y = new_act_positions[position][0]
                if (0 <= x + move[1] < WIDTH) and (0 <= y + move[0] < HEIGTH):
                    if MAP[y + move[0]][x + move[1]] != '#':
                        new_act_positions[position] = (y + move[0],x + move[1])
            #check if this state was
            tmp = tuple(new_act_positions)
            if not (tmp in STATES):
                moves = act_state[1].copy()
                moves += convert_move(move)
                #check if we win
                if win(new_act_positions):
                    #print("WE DID IT!!! MOVES:",len(moves))
                    ANS = moves
                    return
                merged_positions = new_act_positions.copy()
                merged_positions = list(set(merged_positions))
                merged_positions.sort()
                #check if its possible to merge
                if len(merged_positions) < len(new_act_positions):
                    queue.clear()
                    STATES.clear()
                    STATES.add(tuple(merged_positions))
                    queue.append((merged_positions,moves,act_state[2] + 1))
                    break

                STATES.add(tuple(merged_positions))
                queue.append((merged_positions,moves,act_state[2] + 1)) #BUG - TEN MALY BARDZO BLAD WSZYSTKO ZEPSUL

                #STATES.add(tuple(new_act_positions))
                #queue.append((new_act_positions,moves,act_state[2] + 1))

input(input_t[0])
#for line in MAP:
    #print(line)
#print(input_t[0])
#initial = another_find_best_initial()
initial = find_best_initial()
IN_ALG = 'RANDOM'
solution_BFS(initial[0],initial[1])
print("WE STARTED WITH",len(initial[0]),"POSITIONS moved times:", len(ANS), "and used at first",IN_ALG)
output()
