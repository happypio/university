import heapq

board = []
boxes = []
good_boxes = []
goals = []
start = (0,0)
WIDTH = 0
HEIGTH = 0 #things we read from input
MOVES = [(1,0),(0,1),(-1,0),(0,-1)]
ANS = []
STATES = set() # we will keep here positions of boxes
def go_through(act_boxes,start_p,goal_p):
    def new_heuristic(position):
        return abs(position[0] - goal_p[0]) + abs(position[1] - goal_p[1])
    def new_can_move(y,x):
        if (y,x) in newstates:
            return False
        #check if player is out of board/on wall/ on box
        if not(0 <= y < HEIGTH) or not(0 <= x < WIDTH) or board[y][x] == 'W' or (y,x) in act_boxes:
            return False
        return True
    if start_p == goal_p:
        return ([],True)
    queue = []
    newstates = set()
    heapq.heapify(queue)
    state = (start_p,0,[]) #state is position, number of moves and sequence
    newstates.add(start_p)
    heapq.heappush(queue,(new_heuristic(start_p),state))
    while len(queue) > 0:
        tmp_state = heapq.heappop(queue)
        act_state = tmp_state[1]
        y = act_state[0][0]
        x = act_state[0][1]
        for move in MOVES:
            # CHECK EVERY POSSIBLE MOVE FROM THIS POSSITION
            new_x = x + move[1]
            new_y = y + move[0]
            if new_can_move(new_y,new_x):
                newstates.add((new_y,new_x))
                #modify current state
                moves = act_state[2].copy()
                moves += [convert_move(move)]
                way_length = act_state[1] + 1
                new_state = ((new_y,new_x),way_length,moves)
                # check if its goal
                if (new_y, new_x) == goal_p:
                    return (moves,True)
                heapq.heappush(queue,(new_heuristic((new_y,new_x)) + way_length,new_state))
    return ([],False)

def output():
    with open("zad_output.txt",'w') as OUTPUT:
        for i in range(len(ANS)):
            OUTPUT.write(ANS[i])

def input():
    global start
    heigth = 0
    global WIDTH,HEIGTH
    with open("zad_input.txt",'r') as INPUT:
        for line in INPUT:
            board.append([line[i] for i in range(len(line) - 1)])
            for width in range(len(board[heigth])):
                if board[heigth][width] == 'K':
                    start = (heigth, width)
                if board[heigth][width] == 'G' or board[heigth][width] == '*' or board[heigth][width] == '+':
                    goals.append((heigth,width))
                if board[heigth][width] == 'B' or board[heigth][width] == '*':
                    boxes.append((heigth, width))
                if board[heigth][width] == '*':
                    good_boxes.append((heigth,width))
                if board[heigth][width] == '+':
                    start = (heigth, width)
            heigth += 1
        HEIGTH = heigth - 1
        WIDTH = len(board[0])

def blocked_chest(y,x,act_boxes):
    #check if its corner
    if (y,x) in goals:
        return False
    if (x == 0 or x == WIDTH - 1) and (y == 0 or y == HEIGTH - 1):
        return True
    #check if its band and wall is upper or lower
    if x == 0 or x == WIDTH - 1:
        if board[y-1][x] == 'W' or board[y+1][x] == 'W':
            return True
        #return False
    # check if its band and wall is on right or left
    if y == 0 or y == HEIGTH - 1:
        if board[y][x-1] == 'W' or board[y][x+1] == 'W':
            return True
        #return False
    #we are not on the band so check if we are in corner of walls
    if board[y-1][x] == 'W' and (board[y][x-1] == 'W' or board[y][x+1] == 'W'):
        return True
    if board[y + 1][x] == 'W' and (board[y][x - 1] == 'W' or board[y][x + 1] == 'W'):
        return True
    #check if two boxes are side by side and next to wall
    if board[y-1][x] == 'W':
        if board[y-1][x-1] == 'W' and (y,x-1) in act_boxes:
            return True
        if board[y-1][x+1] == 'W' and (y,x+1) in act_boxes:
            return True
    if board[y+1][x] == 'W':
        if board[y+1][x-1] == 'W' and (y,x-1) in act_boxes:
            return True
        if board[y+1][x+1] == 'W' and (y,x+1) in act_boxes:
            return True
    if board[y][x-1] == 'W':
        if board[y-1][x-1] == 'W' and (y-1,x) in act_boxes:
            return True
        if board[y+1][x-1] == 'W' and (y+1,x) in act_boxes:
            return True
    if board[y][x+1] == 'W':
        if board[y-1][x+1] == 'W' and (y-1,x) in act_boxes:
            return True
        if board[y+1][x+1] == 'W' and (y+1,x) in act_boxes:
            return True
    return False

def good_move(box,act_boxes,move,player_pos):
    new_x = act_boxes[box][1] + move[1]
    new_y = act_boxes[box][0] + move[0]
    #chcek if move is out of board, on chest, on wall
    if not(0 <=  new_y < HEIGTH) or not(0 <= new_x < WIDTH) or ((new_y,new_x) in act_boxes) or board[new_y][new_x] == 'W':
        return (False,[])
    #tmp array of boxes to check if its in states
    tmp_boxes = act_boxes.copy()
    tmp_boxes[box] = (new_y,new_x)
    #check if we move this chest in corner
    if blocked_chest(new_y,new_x,tmp_boxes):
        return (False,[])
    required_player_pos = (new_y - (2 * move[0]),new_x - (2 * move[1]))
    # check if this state was (sort boxes and move player at the goal position)
    tmp_boxes.sort()
    if (tuple(tmp_boxes), (new_y - move[0],new_x - move[1])) in STATES:
        return (False, [])
    player_y = required_player_pos[0]
    player_x = required_player_pos[1]
    # chcek if player is out of board, on chest, on wall
    if not (0 <= player_y < HEIGTH) or not (0 <= player_x < WIDTH) or (player_y, player_x) in act_boxes or board[player_y][player_x] == 'W':
        return (False,[])
    #find sequence to get to required position (new A*)
    path_to_box = go_through(act_boxes,player_pos,required_player_pos)
    #print((new_y,new_x)," ruch to ",move," droga z ",player_pos, " do ", required_player_pos, path_to_box)
    if path_to_box[1]:
        return (True,path_to_box[0])
    return (False,[])

def convert_move(move):
    if move[0] == 1:
        return 'D'
    if move[0] == -1:
        return 'U'
    if move[1] == 1:
        return 'R'
    return 'L'
def min_dist(block):
    dist = 1000000
    for goal in goals:
        tmp = abs(goal[0] - block[0]) + abs(goal[1] - block[1])
        dist = min(tmp, dist)
    return dist
def heuristic2(blocks_positions):
    result = 0
    for block in blocks_positions:
        result += min_dist(block)
    return result

def manhattan_dist(A, B):
    return abs(A[0] - B[0]) + abs(A[1] - B[1])


def heuristic(state):
    # player_x, player_y = state[0][0], state[0][1]
    chests = state.copy()

    dist = 0
    for g in goals:
        if not chests:
            break

        distances = [(manhattan_dist(c, g), c) for c in chests]
        min_dist = min(distances)

        chests.remove(min_dist[1])
        dist += min_dist[0]

    return dist
def solution_Astar():
    global ANS
    positions=[]
    queue = [] #priority queue
    heapq.heapify(queue)
    player_pos = (start[0],start[1])
    boxes.sort()
    state = (player_pos,boxes,good_boxes,[],0) #,[(start)])
    heapq.heappush(queue,(heuristic(boxes),state))
    STATES.add((tuple(boxes),start))
    #A*
    while len(queue) > 0:
        queue_tmp = heapq.heappop(queue)
        act_state = queue_tmp[1]
        act_boxes = act_state[1].copy()
        act_good_boxes = act_state[2].copy()
        player_pos = act_state[0]
        for box in range(len(act_boxes)):
            #TRY TO MOVE THIS BOX
            y = act_boxes[box][0]
            x = act_boxes[box][1]
            for move in MOVES:
                #CHECK EVERY POSSIBLE MOVE FROM THIS POSSITION
                new_x = x + move[1]
                new_y = y + move[0]
                can_move = good_move(box,act_boxes,move,player_pos)
                #check if we can move
                if can_move[0] != False:
                    new_boxes = act_boxes.copy()
                    new_good_boxes = act_good_boxes.copy()
                    new_boxes[box] = (new_y, new_x) # change position of current box
                    moves = act_state[3].copy()
                    #modify good boxes
                    if (new_y,new_x) in goals:
                        new_good_boxes.append((new_y,new_x))
                    if (y,x) in goals:
                        new_good_boxes.remove((y,x))
                   # print(len(new_good_boxes),len(goals))


                    moves += can_move[1]
                    moves.append(convert_move(move))
                    #DEBUG
                    #moves.append("totu")
                    #moves.append(str(len(new_good_boxes)))
                    #moves.append((new_y,new_x,y,x))
                    new_player_pos = (y,x)
                    new_boxes.sort()
                    STATES.add((tuple(new_boxes),new_player_pos))
                    new_state = (new_player_pos,new_boxes,new_good_boxes,moves,act_state[4] + 1)#,act_state[5] + [convert_move(move)])
                    #print(moves)
                    if len(new_good_boxes) == len(goals):
                        #ITS OVER!!!!!
                        #print("over")
                       # print(new_player_pos,move)
                       # print(new_boxes)
                       # print(new_state[5])
                        ANS = moves
                        return
                    heapq.heappush(queue,(heuristic(new_boxes) + act_state[4] + 1,new_state))
                    ANS = moves
input()
solution_Astar()
output()
#print(ANS)