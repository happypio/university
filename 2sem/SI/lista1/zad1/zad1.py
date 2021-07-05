INPUT = open("zad1_input.txt","r")
OUTPUT = open("zad1_output.txt","w")
BEST_MATE = 1000
BEST_MOVES = []
STATES = set()
king_range = [[0,1],[1,1],[1,0],[1,-1],[0,-1],[-1,-1],[-1,0],[-1,1]]
def convert(pos):
    #convert chars to int
    return [ord(pos[0]) - 96, int(pos[1])]
def rev_convert(crd):
    #convert int do chars
    return chr(crd + 96)
def check_mate(state):
    #check if its check_mate
    if state[3] == 'white':
        return False
    if state[2][0] == 1 and state[0][0] == 3 and state[2][1] == state[0][1] and state[1][0] == 1 and abs(state[2][1] - state[1][1]) > 1:
        return True
    if state[2][0] == 8 and state[0][0] == 6 and state[2][1] == state[0][1] and state[1][0] == 8 and abs(state[2][1] - state[1][1]) > 1:
        return True
    if state[2][1] == 1 and state[0][1] == 3 and state[2][0] == state[0][0] and state[1][1] == 1 and abs(state[2][0] - state[1][0]) > 1:
        return True
    if state[2][1] == 8 and state[0][1] == 6 and state[2][0] == state[0][0] and state[1][1] == 8 and abs(state[2][0] - state[1][0]) > 1:
        return True
    return False

def is_good(state,x,y,figure):
    #CHECK IF ITS GOOD MOVE
    if state[3] == 'white':
        #WHITE'S MOVES
        if figure == 'wk':
            #WHITE KING
            st_tmp = ((x,y),(state[1][0],state[1][1]),(state[2][0],state[2][1]),'black')
            if st_tmp in STATES:
                return False
            STATES.add(st_tmp)
            for i in range(8):
                new_x = x + king_range[i][0]
                new_y = y + king_range[i][1]
                if 1 <= new_x <=8 and 1 <= new_y <=8:
                    if new_x == state[2][0] and new_y == state[2][1]:
                        return False

            if x == state[1][0] and y == state[1][1]:
                return False
            return True
        else:
            #WHITE ROOK
            st_tmp = ((state[0][0], state[0][1]), (x,y), (state[2][0], state[2][1]), 'black')
            if st_tmp in STATES:
                return False
            STATES.add(st_tmp)
            if (x < state[0][0] < state[1][0] or state[1][0] < state[0][0] < x) and state[0][1] == y:
                return False
            if (y < state[0][1] < state[1][1] or state[1][1] < state[0][1] < y) and state[0][0] == x:
                return False
            if x == state[0][0] and y == state[0][1]:
                return False
            return True
    #BLACK'S MOVE
    else:
        #BLACK KING
        st_tmp = ((state[0][0], state[0][1]), (state[1][0], state[1][1]), (x, y), 'white')
        if st_tmp in STATES:
            return False
        STATES.add(st_tmp)
        for i in range(8):
            new_x = x + king_range[i][0]
            new_y = y + king_range[i][1]
            if 1 <= new_x <= 8 and 1 <= new_y <= 8:
                if new_x == state[0][0] and new_y == state[0][1]:
                    return False
        if x == state[1][0] and y == state[1][1]:
            return False
        if state[1][0] == x:
            if not ((y <= state[0][1] <= state[1][1] or y >= state[0][1] >= state[1][1]) and state[0][0] == x):
                return False
        if state[1][1] == y:
            if not ((x <= state[0][0] <= state[1][0] or x >= state[0][0] >= state[1][0]) and state[0][1] == y):
                return False
        return True

#BFS
def play_game(wk,wr,bk,move):

    global BEST_MATE, BEST_MOVES
    BEST_MATE = 1000
    BEST_MOVES = []
    STATES.clear()
    queue = []
    #WK,WR,BK FIRST ELEMENT IS X COORDINATE (LETTER ON CHESSBOARD, SECOND IS Y
    beg_state = [wk,wr,bk,move,0,[[wk,wr,bk]]]
    st_tmp = ((wk[0],wk[1]),(wr[0],wr[1]),(bk[0],bk[1]),(move))
    STATES.add(st_tmp)
    queue.append(beg_state)
    while(len(queue) > 0):
        act_state = queue.pop(0)
        if check_mate(act_state):
            BEST_MATE = act_state[4]
            BEST_MOVES = act_state
            #IT'S BFS SO FIRST CHECK_MATE IS THE BEST
            return

        if act_state[3] == 'white':
            #WHITE KING MOVES
            for i in range(8):
                new_x = act_state[0][0] + king_range[i][0]
                new_y = act_state[0][1] + king_range[i][1]
                if 1 <= new_x <= 8 and 1 <= new_y <=8:
                    if is_good(act_state,new_x,new_y,'wk'):
                        temp_state = [[new_x,new_y],act_state[1],act_state[2],'black',act_state[4] + 1,[act_state[5]]]
                        temp_state[5].append([act_state[0],act_state[1],act_state[2]])
                        queue.append(temp_state)
            #WHITE ROOK MOVES
            for i in range(1,8):
                new_x = (i + act_state[1][0]) % 8 + 1
                new_y = (i + act_state[1][1]) % 8 + 1
                if is_good(act_state,new_x,act_state[1][1],'wr'):
                    temp_state = [act_state[0],[new_x,act_state[1][1]],act_state[2],'black',act_state[4] + 1,[act_state[5]]]
                    temp_state[5].append([act_state[0],act_state[1],act_state[2]])
                    queue.append(temp_state)
                if is_good(act_state,act_state[1][0],new_y,'wr'):
                    temp_state = [act_state[0],[act_state[1][0],new_y],act_state[2],'black',act_state[4] + 1,[act_state[5]]]
                    temp_state[5].append([act_state[0],act_state[1],act_state[2]])
                    queue.append(temp_state)

        if act_state[3] == 'black':
            #BLACK KING MOVES
            for i in range(8):
                new_x = act_state[2][0] + king_range[i][0]
                new_y = act_state[2][1] + king_range[i][1]
                if 1 <= new_x <= 8 and 1 <= new_y <=8:
                    if is_good(act_state,new_x,new_y,'bk'):
                        temp_state = [act_state[0],act_state[1],[new_x,new_y],'white',act_state[4] + 1,[act_state[5]]]
                        temp_state[5].append([act_state[0],act_state[1],act_state[2]])
                        queue.append(temp_state)

def print_out(state):
    moves = []
    moves.append([state[0],state[1],state[2]])
    array = state[5]
    while len(array) != 1:
        moves.append(array[1])
        array = array[0]
    moves.append(array[0])
    moves.pop(len(moves) - 1)
    moves.pop(len(moves) - 1)
    for line in reversed(moves):
        for coordinate in line:
            print(rev_convert(coordinate[0]) + str(coordinate[1]) + " " , end = '')
        print('\n', end = '')


DEBUG = 1
def solve():
    for line in INPUT:
        in_line = line.split()
        wk = convert(in_line[1])
        wr = convert(in_line[2])
        bk = convert(in_line[3])
        who = in_line[0]
        play_game(wk,wr,bk,who)
        OUTPUT.write(str(BEST_MATE) + '\n')
        if DEBUG:
            print(f'\nTO CHECKMATE YOU NEED AT LEAST {BEST_MATE} MOVES:\n')
            print(f'STARTS {who} with position {rev_convert(wk[0])}{wk[1]} {rev_convert(wr[0])}{wr[1]} {rev_convert(bk[0])}{bk[1]}')
            print_out(BEST_MOVES)
            print('\n-------------------------------------')

solve()
INPUT.close()
OUTPUT.close()
