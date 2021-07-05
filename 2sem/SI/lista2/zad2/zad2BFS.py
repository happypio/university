from collections import deque

board = []
boxes = []
good_boxes = []
goals = []
start = (0,0)
WIDTH = 0
HEIGTH = 0 #things we read from input
MOVES = [(1,0),(0,1),(-1,0),(0,-1)]
ANS = []
STATES = set()

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
def output():
    with open("zad_output.txt",'w') as OUTPUT:
        for i in range(len(ANS)):
            OUTPUT.write(ANS[i])
def can_move_box(y,x,boxes,move_y,move_x):
    new_x = x + move_x
    new_y = y + move_y
    if new_x >= 0 and new_x <= WIDTH and new_y >= 0 and new_y <= HEIGTH:
        if board[new_y][new_x] != 'W':
            if (new_y, new_x) in boxes:
                return False
            else:
                return True
        else:
            return False
    else:
        return False

def win(modgood_boxes):
    if len(modgood_boxes) == len(goals):
        return True
    return False

def convert_move(move):
    if move[0] == 1:
        return 'D'
    if move[0] == -1:
        return 'U'
    if move[1] == 1:
        return 'R'
    return 'L'

def bfs_solution(y,x):
    queue = deque()
    queue.append((y,x,boxes,good_boxes,[])) #state: position, boxes, good boxes and saved_moves
    STATES.add((y,x,tuple(boxes),tuple(good_boxes)))
    global ANS
    #BFS
    while len(queue) > 0:
        act_state = queue.popleft()
        y = act_state[0]
        x = act_state[1]
        act_boxes = act_state[2].copy()
        act_good_boxes = act_state[3].copy()
        saved_moves = act_state[4].copy()
        for move in MOVES:
            #CHECK EVERY POSSIBLE MOVE FROM THIS POSSITION
            new_x = x + move[1]
            new_y = y + move[0]

            if new_x >= 0 and new_x <= WIDTH and new_y >= 0 and new_y <= HEIGTH:
                #check if the move is still on board

                if board[new_y][new_x] != 'W':
                    #check if new position is not on wall

                    if (new_y,new_x) in act_boxes:
                        #check if new position is on box

                        if can_move_box(new_y,new_x,act_boxes,move[0],move[1]):
                            #check if we can move current box
                            new_act_good_boxes = act_good_boxes.copy()
                            new_act_boxes = act_boxes.copy()
                            for box in range(len(act_boxes)):
                                #change position of current box
                                if act_boxes[box] == (new_y, new_x):
                                    new_act_boxes[box] = (new_y + move[0], new_x + move[1])


                            #modify good boxes
                            if (new_y, new_x) in act_good_boxes:
                                new_act_good_boxes.remove((new_y, new_x))
                            if (new_y + move[0],new_x + move[1]) in goals:
                                new_act_good_boxes.append((new_y + move[0],new_x + move[1]))

                            if win(new_act_good_boxes):
                                #check if every box is on goal and save moves
                                saved_moves.append(convert_move(move))
                                ANS = saved_moves
                                return new_act_good_boxes
                            else:
                                #check if this state was
                                if not (new_y,new_x,tuple(new_act_boxes),tuple(new_act_good_boxes)) in STATES:
                                    STATES.add((new_y,new_x,tuple(new_act_boxes),tuple(new_act_good_boxes)))
                                    queue.append((new_y,new_x,new_act_boxes,new_act_good_boxes,saved_moves + [convert_move(move)]))
                    else:
                        #new position is on clear area
                        #check if this state was
                        if not (new_y, new_x, tuple(act_boxes),tuple(act_good_boxes)) in STATES:
                            STATES.add((new_y, new_x, tuple(act_boxes),tuple(act_good_boxes)))
                            queue.append((new_y, new_x, act_boxes,act_good_boxes,saved_moves + [convert_move(move)]))


input()
#print(board,start,WIDTH,HEIGTH)
bfs_solution(start[0],start[1])
output()
#print(ANS)






