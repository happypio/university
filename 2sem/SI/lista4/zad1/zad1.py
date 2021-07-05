import random
import sys
from collections import defaultdict as dd
import time
import my_move

BOK = 50
SX = -100
SY = 0
M = 8
DIRS = [(0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1)]
def kwadrat(x, y, kolor):
    x = 2
    '''fillcolor(kolor)
      pu()
      goto(SX + x * BOK, SY + y * BOK)
      pd()
      begin_fill()
      for i in range(4):
        fd(BOK)
        rt(90)
      end_fill() '''

def kolko(x, y, kolor):
    x = 2
    '''fillcolor(kolor)

  pu()
  goto(SX + x * BOK + BOK/2, SY + y * BOK - BOK)
  pd()
  begin_fill()
  circle(BOK/2)
  end_fill() '''

#####################################################

def initial_board():
    B = [ [None] * M for i in range(M)]
    B[3][3] = 1
    B[4][4] = 1
    B[3][4] = 0
    B[4][3] = 0
    return B

    
class Board:
    dirs  = [ (0,1), (1,0), (-1,0), (0,-1), (1,1), (-1,-1), (1,-1), (-1,1) ]
    
    
    def __init__(self):
        self.board = initial_board()
        self.fields = set()
        self.move_list = []
        self.history = []
        for i in range(M):
            for j in range(M):
                if self.board[i][j] == None:   
                    self.fields.add( (j,i) )
                                                
    def draw(self):
        for i in range(M):
            res = []
            for j in range(M):
                b = self.board[i][j]
                if b == None:
                    res.append('.')
                elif b == 1:
                    res.append('#')
                else:
                    res.append('o')
            print (''.join(res)) 
        print()          
        
    
    def show(self):
        for i in range(M):
            for j in range(M):
                kwadrat(j, i, 'green')
                
        for i in range(M):
            for j in range(M):                
                if self.board[i][j] == 1:
                    kolko(j, i, 'black')
                if self.board[i][j] == 0:
                    kolko(j, i, 'white')
                                   
    def moves(self, player):
        res = []
        for (x,y) in self.fields:
            if any( self.can_beat(x,y, direction, player) for direction in Board.dirs):
                res.append( (x,y) )
        if not res:
            return [None]
        return res            
    
    def can_beat(self, x,y, d, player):
        dx,dy = d
        x += dx
        y += dy
        cnt = 0
        while self.get(x,y) == 1-player:
            x += dx
            y += dy
            cnt += 1
        return cnt > 0 and self.get(x,y) == player
    
    def get(self, x,y):
        if 0 <= x < M and 0 <=y < M:
            return self.board[y][x]
        return None
                        
    def do_move(self, move, player):
        self.history.append([x[:] for x in self.board])
        self.move_list.append(move)
        
        if move == None:
            return
        x,y = move
        x0,y0 = move
        self.board[y][x] = player
        self.fields -= set([move])
        for dx,dy in self.dirs:
            x,y = x0,y0
            to_beat = []
            x += dx
            y += dy
            while self.get(x,y) == 1-player:
              to_beat.append( (x,y) )
              x += dx
              y += dy
            if self.get(x,y) == player:              
                for (nx,ny) in to_beat:
                    self.board[ny][nx] = player
                                                     
    def result(self):
        res = 0
        for y in range(M):
            for x in range(M):
                b = self.board[y][x]                
                if b == 0:
                    res -= 1
                elif b == 1:
                    res += 1
        return res
                
    def terminal(self):
        if not self.fields:
            return True
        if len(self.move_list) < 2:
            return False
        return self.move_list[-1] == self.move_list[-2] == None 

    def random_move(self, player):
        ms = self.moves(player)
        if ms:
            return random.choice(ms)
        return [None]
#kodowanie mapy w bitach (dla kazdego koloru inna liczba (bitmapa):
#pozycja (x,y) to: (8 * x) + y 
#state to [bits1,bits2,player,cnt_moves,moves]
A = [[[0,7,56,63],[2,4,11,16,25,31,32,38,47,52,59,61],[18,20,21,23,27,29,30,34,36,40,42,44,46,53,58],[3,5,9,10,12,13,14,17,19,22,24,26,28,33,35,37,41,43,45,47,49,50,51,54],[1,6,8,15,39,48,55,57,60,62]],
    [[0,7,56,63],[2,11,16,25,37,47,52,58,61],[4,5,13,17,18,20,21,22,23,27,29,31,32,34,36,38,40,41,42,43,45,46,47,50,52,53,58,59,61],[3,6,10,12,14,15,19,24,26,28,30,33,35,37,39,44,49,51,54,60],[1,7,8,9,48,55,57,62]],
    [[0,7,56,63],[9,14,16,18,21,42,45,47,49,54],[2,3,4,5,11,12,13,19,20,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,43,44,50,51,52,58,59,60,61],[1,6,8,10,15,17,46,48,53,55,57,62],[]],
    [[0,7,56,63],[9,14,16,18,21,42,45,47,49,54],[1,2,3,4,5,6,8,10,11,12,13,15,19,23,24,25,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,43,48,50,51,52,55,57,58,59,60,62,61],[13,17,20,22,26,44,46,53],[]],
    [[0,1,2,3,4,5,6,7,8,9,14,15,16,18,21,23,24,27,28,31,32,35,36,39,40,42,45,47,48,49,54,55,56,57,58,59,60,61,62,63],[10,11,12,13,17,19,20,22,25,26,29,30,33,34,37,38,41,43,44,46,50,51,52,53],[],[],[]]]
K = [ [set() for i in range(5)] for i in range(5)]
for i in range(len(A)):
    for j in range(len(A[i])):
        for elem in A[i][j]:
            K[i][j].add(elem)
# + 10 , + 7, + 5, - 3 , -7

def check(map,values):
    val = 0
    for i in range(64):
        if (map>>i)&1 == 1:
            if i in values[0]:
                val += 10
            else:
                if i in values[1]:
                    val += 7
                else:
                    if i in values[2]:
                        val += 5
                    else:
                        if i in values[3]:
                            val -= 3
                        else:
                            val -= 7
    return val



min_int = float('-inf')
max_int = float('inf')

def terminal(state):
    map1 = state[0]
    map2 = state[1]
    for i in range(64):
        if (map1>>i)&1 == 0 and (map2>>i)&1 == 0:
            return False
    return True

def utility(state):
    result1 = 0
    result2 = 0
    r = 0
    for i in range(64):
        if (map1>>i)&1 == 1:
            result1 += 1
        if (map2>>i)&1 == 1:
            result2 += 1
    if result1 == result2:
        r = result1
    else:
        if result1 < result2:
            r = (-200) * (1/state[3])
        else:
            r = 300 * (1/state[3])
    return r


def opposite(direction):
    return (direction[0] * (-1),direction[1] * (-1))

def find_field(direction,map,my_map,pos):
    cnt = 1
    while cnt < 90:
        new_y = pos[0] + direction[0]*cnt
        new_x = pos[1] + direction[1]*cnt
        if 0 <= new_x < 8 and 0 <= new_y < 8 and (my_map>>((8 * new_x) + new_y))&1 != 1:
            if (map>>((8 * new_x) + new_y))&1 == 0:
                return (1<<(8 * new_x + new_y))
            else:
                cnt += 1
        else:
            return False

def actions(state):
    m_set = set()
    moves = []
    map1 = state[0]
    map2 = state[1]
    if state[2] == 0:
        for i in range(64):
            #check if this is enemy player's field
            if (map2>>i)&1 == 1:
                #check if there is opposite colour 
                for direction in DIRS:
                    new_y = i%8 + direction[0]
                    new_x = i // 8 + direction[1]
                    if 0 <= new_x < 8 and 0 <= new_y < 8 and (map1>>(8*new_x + new_y))&1 == 1:
                        field = find_field(opposite(direction),map2,map1,(i%8,i // 8))
                        if field != False:
                            if field not in m_set:
                                m_set.add(field)
                                moves.append(field)
    else:
        for i in range(64):
            #check if this is enemy player's field
            if (map1>>i)&1 == 1:
                #check if there is opposite colour 
                for direction in DIRS:
                    new_y = i%8 + direction[0]
                    new_x = i // 8 + direction[1]
                    if 0 <= new_x < 8 and 0 <= new_y < 8 and (map2>>(8*new_x + new_y))&1 == 1:
                        field = find_field(opposite(direction),map1,map2,(i%8,i // 8))
                        if field != False:
                            if field not in m_set:
                                m_set.add(field)
                                moves.append(field)

    return moves

def heuristic_value(state):
    r = 0
    if state[3] <= 6:
        r = check(state[0],K[0])
    if 6 < state[3] <= 10:
        r = check(state[0],K[1])
    if 10 < state[3] <= 30:
        r = check(state[0],K[2])
    if 30 < state[3] <= 40:
        r = check(state[0],K[3])
    if state[3] > 40:
        r = check(state[0],K[4])

    return r

OLD_CHILDRENS = {}

def alfa_beta(state):
    global OLD_CHILDRENS
    NEW_CHILDRENS = {}
    def max_value(state,alpha,beta):
        if terminal(state): 
            return utility(state),0
        if state in OLD_CHILDRENS:
            states = list(OLD_CHILDRENS[state])
            print('found')
        else:
            states = [result(a,state) for a in actions(state)]

            if state[3] >= 3:
                return heuristic_value(state),0

            if state[3] <= 1:
                states_sorted = []
                for state in states:
                    states_sorted.append((heuristic_value(state),state))
                states_sorted.sort()
                states = []
                for state in states_sorted:
                    states.append(state[1])

        NEW_CHILDRENS[state] = states
        value = min_int
        max_value = min_int
        best_move = 0
        for state1 in states:
            value = max(value,min_value(state1,alpha,beta))
            if value > max_value:
                max_value = value
                best_move = state1[4]
            if value >= beta:
                return value,best_move
            alpha = max(alpha,value)

        return value,best_move

    def min_value(state,alpha,beta):
        if terminal(state): 
            return utility(state)
        if state in OLD_CHILDRENS:
            states = list(OLD_CHILDRENS[state])
            print('found')
        else:
            states = [result(a,state) for a in actions(state)]

            if state[3] >= 3:
                return heuristic_value(state)

            if state[3]  <= 1:
                states_sorted = []
                for state in states:
                    states_sorted.append((heuristic_value(state),state))
                states_sorted.sort()
                states = []
                for state in states_sorted:
                    states.append(state[1])

        NEW_CHILDRENS[state] = states
        value = max_int
        for state1 in states:
            tmp = max_value(state1,alpha,beta)
            value = min(value,tmp[0])
            if value <= alpha:
                return value
            beta = min(beta,value)
        return value
    OLD_CHILDRENS = NEW_CHILDRENS
    w = max_value(state,min_int,max_int)
    return w[1]

def to_beat(direction,map,my_map,pos):
    result = []
    cnt = 1
    while cnt < 100:
        new_y = pos[0] + direction[0]*cnt
        new_x = pos[1] + direction[1]*cnt
        if 0 <= new_x < 8 and 0 <= new_y < 8:
            if (map>>((8 * new_x) + new_y))&1 == 0:
                if (my_map>>((8 * new_x) + new_y))&1 == 1:
                    return result
                else:
                    return []
            else:
                result.append((1<<(8 * new_x) + new_y))
        else:
            return []
        cnt += 1

def beat(action,map,my_map):
    k = 0
    result = []
    while (action>>k)&1 != 1:
        k += 1
    pos = (k % 8, k // 8)
    for direction in DIRS:
        new_y = pos[0] + direction[0]
        new_x = pos[1] + direction[1]
        if 0 <= new_x < 8 and 0 <= new_y < 8 and (map>>(8*new_x + new_y))&1 == 1:
            fields = to_beat(direction,map,my_map,pos)
            result += fields
    return result

def result(action,state):
    map1 = state[0]
    map2 = state[1]
    player = state[2]
    moves = state[3]
    tmp = []
    for i in state[4]:
        tmp.append(i)
    tmp.append(action)
    actions = tuple(tmp)
    #print('ackja to : ', convert_to_move(action))
    if player == 0:
        map1 = map1 ^ action
        fields = beat(action,map2,map1)
        for field in fields:
            #print('ruch do zbicia',convert_to_move(field))
            map1 = map1 ^ field
            map2 = map2 ^ field
    else:
        map2 = map2 ^ action
        fields = beat(action,map1,map2)
        for field in fields:
            #print('ruch do zbicia', convert_to_move(field))
            map1 = map1 ^ field
            map2 = map2 ^ field
    return (map1,map2,1 - player,moves + 1,actions)
    
def convert_to_move(bits):
    k = 0
    result = []
    while (bits>>k)&1 != 1 and k < 100:
        k += 1
    pos = (k // 8, k % 8)
    return pos

def convert_to_bit(move):
    bits = (1<< (8 * move[0] + move[1]))  
    return bits


def convert_map_to_bit(map):
    map1 = 1 << 64
    map2 = 1 << 64
    for i in range(M):
        for j in range(M):
            if map[i][j] == 0:
                map1 = map1 ^ (1 << (j * 8) + i)
            else:
                if map[i][j] == 1:
                    map2 = map2 ^ (1 << (j * 8) + i)
    return map1,map2

def print_bit_map(map1,map2):
    map = []
    column = []
    for i in range(64):
        if i % 8 == 0:
            map.append(column)
            column = []
        if (map1 >> i)&1 == 1:
            column.append('o')
        else:
            if (map2 >> i)&1 == 1:
                column.append('#')
            else:
                column.append('.')
    map.append(column)
    for i in range(M):
        for j in range(1,M + 1):
            print(map[j][i],end = '')
        print()

B = Board()
init_map1,init_map2 = convert_map_to_bit(B.board)

enemy = 1
myself = 0

wins = 0
start = time.time()
N = 1000
for i in range(N):
    player = 0
    cnt = 0
    map1 = init_map1
    map2 = init_map2
    moves_cnt = 0
    while True:
        cnt += 1
        if cnt > 74:
            break
        '''print("MAPA Z BITOW:")
        print_bit_map(map1,map2)
        print()
        print('DOBRA MAPA')
        B.draw()
        B.show()'''
        if player == enemy:
            m = B.random_move(player)
            if m != None:
                bit_m = convert_to_bit(m)
                move_m = convert_to_move(bit_m)
                B.do_move(m, player)
                res = result(bit_m,(map1,map2,player,moves_cnt,()))
                map1 = res[0]
                map2 = res[1]
                moves_cnt = res[3]       
        if player == myself:
            #m = B.random_move(player)
            movik = alfa_beta((map1,map2,player,0,()))
            if movik != 0:
                conv_movik = convert_to_move(movik[0])
                #print(conv_movik)
                #bit_m = convert_to_bit(m)
                move_m = conv_movik
                B.do_move(move_m, player)
                res = result(movik[0],(map1,map2,player,moves_cnt,()))
                map1 = res[0]
                map2 = res[1]
                moves_cnt = res[3]

        player = 1-player
        if B.terminal():
            break
    '''print("MAPA Z BITOW:")
    print_bit_map(map1,map2)
    print()
    print('DOBRA MAPA')
    B.draw()
    B.show()'''
    if B.result() <= 0:
        wins += 1
    print(B.result(),myself)
    B = Board()
end = time.time()
    
#B.draw()
#B.show()
#print ('Result', B.result())
print('PLAYED GAMES: ',N,' wins: ',wins,' time: ',end-start)
  
'''przykald = ['........',
'.....1..',
'....1...',
'.0110...',
'.11100..',
'..0011..',
'.0..0...',
'0....0..']

tmp1,tmp2 = convert_map_to_bit(przykald)
print(bin(tmp1))
print(bin(tmp2))
print_bit_map(tmp1,tmp2)
cos = actions((tmp1,tmp2,0,0,[]))
#m = (4,3)
movik = alfa_beta((tmp1,tmp2,0,0,[]))
bit_m = movik[0]
print(convert_to_move(movik[0]))
tmp = result(bit_m,(tmp1,tmp2,0,0,[bit_m]))
tmp1 = tmp[0]
tmp2 = tmp[1]
print(bin(tmp1))
print(bin(tmp2))
print_bit_map(tmp1,tmp2)'''
sys.exit(0)                 
