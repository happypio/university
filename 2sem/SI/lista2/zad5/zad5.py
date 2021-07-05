import heapq
from collections import deque

ANS = []
MAP = []
goals = []
starts = []
WIDTH = 0
HEIGTH = 0
MOVES = [(-1,0),(1,0),(0,-1),(0,1)]
DISTANCE = {}
visited = set()
input_t = [
    'zad_input.txt',
    "map1.txt",'map2.txt','map3.txt','map4.txt','map5.txt',
    'map6.txt','map7.txt','map8.txt','map9.txt','map10.txt'
]

def BFS(pos):
    DISTANCE[pos] = 1e9
    bfs_queue = deque()
    visited_bfs = set()
    visited_bfs.add(pos)
    bfs_queue.append((pos, 0))

    while len(bfs_queue) > 0:
        act_state = bfs_queue.popleft()
        dist = act_state[1]
        act_pos = act_state[0]

        if act_pos in goals:
            DISTANCE[pos] = min(DISTANCE[pos], dist)

        for move in MOVES:
            new_x = act_pos[1] + move[1]
            new_y = act_pos[0] + move[0]

            if not (new_y, new_x) in visited_bfs and MAP[new_y][new_x] != '#':
                visited_bfs.add((new_y,new_x))
                bfs_queue.append(((new_y, new_x), dist + 1))


def pre_processing_paths():
    for height in range(HEIGTH):
        for width in range(WIDTH):
            pos = (height,width)
            if MAP[height][width] != '#':
                BFS(pos)
def heuristic(positions):
    distances = [DISTANCE[pos] for pos in positions]
    return max(distances)
    # return sum(distances) #do zadania 6 w tym wypadku jest niedopuszczalna poniewaz szacowany koszt moze byc wiekszy niz realny

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

def make_new_pos(positions,move):
    result_pos = []
    for pos in positions:
        new_x = pos[1] + move[1]
        new_y = pos[0] + move[0]
        if MAP[new_y][new_x] != '#':
            result_pos.append((new_y,new_x))
        else:
            result_pos.append(pos)
    return list(set(result_pos))

def good_move(positions):
    tmp = positions.copy()
    tmp.sort()
    if tuple(tmp) in visited:
        return False
    visited.add(tuple(tmp))
    return True

def solution_Astar(initial_pos):
    global ANS
    cnt = 0
    Q = [] #priority queue
    #Q = heapq.heapify(Q)
    initial_pos = list(set(initial_pos))
    initial_pos.sort()
    visited.add(tuple(initial_pos))
    heapq.heappush(Q,(heuristic(initial_pos),initial_pos,[]))
    while len(Q) > 0:
        cnt += 1
        if cnt % 100000 == 0:
            print(cnt)
        act_state = heapq.heappop(Q)
        positions = act_state[1].copy()
        moves = act_state[2].copy()
        if win(positions):
            #print("WE DID IT!!!!")
            ANS = moves
            return
        for move in MOVES:
            new_positions = make_new_pos(positions,move)
            if good_move(new_positions):
                heapq.heappush(Q,(heuristic(new_positions) + len(moves) + 1,new_positions,moves + [convert_move(move)]))





input(input_t[0])
pre_processing_paths()
#print(DISTANCE)
#for line in MAP:
   #print(line)
#print(input_t[0])
solution_Astar(starts)
print("WE STARTED WITH",len(starts),"POSITIONS AND MADE MOVES:",len(ANS))
output()