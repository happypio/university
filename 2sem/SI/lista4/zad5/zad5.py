import random
import sys
from collections import defaultdict as dd
import time
import math
BOK = 50
SX = -100
SY = 0
M = 8
DIRS = [(0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1)]

class Node:
    def __init__(self,map1,map2,player,cnt_moves,move,won,games,father):
        self.map1 = map1
        self.map2 = map2
        self.won = won
        self.games = games
        self.father = father
        self.cnt_moves = cnt_moves
        self.player = player
        self.move = move
        self.children = []
    def add_child(self,obj):
        self.children.append(obj)

def ucb_formula(w,n,K):
    log = math.log(K)
    r = w/n + c * math.sqrt(log/n)
    return r

def selection(node):
    if len(node.children) == 0:
        return False
    best_node = None
    best_value = 0
    for child in node.children:
        value = ucb_formula(child.won,child.games,node.games)
        if value > best_value:
            best_value = value
            best_node = child
    return best_node

def backpropagation(games,won,node):
    act_node = node
    while act_node.father != None:
        act_node.games += games
        act_node.won += won
        act_node = act_node.father

    act_node.games += games
    act_node.won += won

def expansion(node):
    state = (node.map1,node.map2,node.player,node.cnt_moves)
    states = [result(a,state) for a in actions(state)]
    played = 0
    won = 0
    for state in states:
        new_node = Node(state[0],state[1],state[2],state[3],state[4],0,1,node)
        #played += 1
        #if simulate_game(state[0],state[1],state[2],state[3]):
            #new_node.won += 1
            #won += 1
        node.children.append(new_node)
    if len(node.children) == 0:
        if simulate_game(node.map1,node.map2,node.player,node.cnt_moves):
            won += 1
        played += 1
    else:
        child = random.choice(node.children)
        if simulate_game(child.map1,child.map2,child.player,child.cnt_moves):
            child.won += 1
            won += 1
        played += 1
    backpropagation(played,won,node)

def MCTS(node):
    start = time.time()
    point = time.time()
    act_node = node
    while point - start < 0.5:
        where_to_go = selection(act_node)
        #print(where_to_go)
        #if act_node == node:
            #print(where_to_go)
        if where_to_go == False:
            expansion(act_node)
            act_node = node
        else:
            act_node = where_to_go
        point = time.time()

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

def game_result(map1,map2):
    play0 = 0
    play1 = 0
    for i in range(64):
        if (map1 >> i)&1 == 1:
            play0 += 1
        if (map2 >> i)&1 == 1:
            play1 += 1

    if myself == 0:
        return play0 > play1
    else:
        return play1 > play0


def simulate_game(map1,map2,player,cnt_moves):
    while terminal((map1,map2)) == False:
        moves = actions((map1,map2,player))
        sum_value = 0
        to_choose = []
        '''for move in moves:
            state1 = result(move,(map1,map2,player,cnt_moves))
            value = heuristic_value(state1)
            to_choose.append((state1,abs(value)))
            sum_value += abs(value)
        if sum_value == 0:
            sum_value = 1'''

        if len(moves) == 0:
            moves2 = actions((map1,map2,1 - player))
            if len(moves2) == 0:
                return game_result(map1,map2)
        else:
            #rdm = random.uniform(0, 1)
            #before = 0
            move_ch = random.choice(moves)
            '''for state in to_choose:
                before += state[1]/sum_value
                if before < rdm:
                    move_ch = state[0][4]
                    break'''

            tmp = result(move_ch,(map1,map2,player,cnt_moves))
            map1 = tmp[0]
            map2 = tmp[1]
            cnt_moves = tmp[3]
        player = 1 - player

    #print_bit_map(map1,map2)
    return game_result(map1,map2)


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
        r = state[3]
    else:
        if result1 < result2:
            r = (-20) * (1/state[3])
        else:
            r = 300 * (1/state[3])
    return r


def opposite(direction):
    return (direction[0] * (-1),direction[1] * (-1))

def find_field(direction,map,my_map,pos):
    cnt = 1
    while True:
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
        r = check(state[state[2]],K[0])
    if 6 < state[3] <= 10:
        r = check(state[state[2]],K[1])
    if 10 < state[3] <= 30:
        r = check(state[state[2]],K[2])
    if 30 < state[3] <= 40:
        r = check(state[state[2]],K[3])
    if state[3] > 40:
        r = check(state[state[2]],K[4])

    return r


def to_beat(direction,map,my_map,pos):
    result = []
    cnt = 1
    while True:
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
    return [map1,map2,1 - player,moves + 1,action]
    
def best_move(node):
    global main_node
    #if len(node.children) <= 100:
        #print(node.cnt_moves)
    if node.cnt_moves < 15:
        expansion(node)
    else:
        MCTS(node)
    #MCTS(node)
    best_value = 0
    best_to_go = None
    #if len(node.children) == 0:
     #   print_bit_map(node.map1,node.map2)
      #  print(node.player)
    do_heura = True
    for child in node.children:
        if child.games > 2 or child.cnt_moves > 20:
            do_heura = False
        if child.games > best_value:
            #best_value = child.won / child.games
            best_value = child.games
            best_to_go = child
    #before_node = best_to_go
    best_value = -100000
    #best_to_go = None
    if do_heura:
        for child in node.children:
            value = heuristic_value((child.map1,child.map2,myself,child.cnt_moves))
            if value > best_value:
                best_value = value
                best_to_go = child
    #if best_to_go != before_node and before_node != None and best_to_go != None:
        #print('HEURYSTYKA:')
        #print_bit_map(best_to_go.map1,best_to_go.map2)
        #print('MCTS:')
        #print_bit_map(before_node.map1,before_node.map2)
    if best_to_go != None:
        main_node = best_to_go
        main_node.father = None
        return best_to_go.move
    else:
        '''print('BLAD : mapka')
        print_bit_map(node.map1,node.map2)
        print(node.player)
        t = actions((node.map1,node.map2,node.player))
        print('ACTIONS : ')
        for a in t:
            print(convert_to_move(a))
        print('CHILDRENS ACTIONS: ')
        for child in node.children:
            print(convert_to_move(child.move))
            print(child.won / child.games)'''
        if len(node.children) == 0:
            new_node = Node(node.map1,node.map2,1 - node.player,node.cnt_moves,0,node.won,node.games,None)
            main_node = new_node
            return 0
        else:
            tmp_node = random.choice(node.children)
            main_node = tmp_node
            main_node.father = None
            return tmp_node.move

def update_main_node(map1,map2,move):
    global main_node
    if move == False:
        #print('KOMPUTER NIE MIAL SIE JAK RUSZYC')
        #print_bit_map(map1,map2)
        new_node = Node(map1,map2,1 - main_node.player,main_node.cnt_moves,0,main_node.won,main_node.games,None)
        main_node = new_node
    else:
        if len(main_node.children) == 0:
            new_node = Node(map1,map2,1 - main_node.player,main_node.cnt_moves + 1,move,0,1,None)
            main_node = new_node
        else:
            for child in main_node.children:
                if child.map1 == map1 and child.map2 == map2:
                    main_node = child
                    main_node.father = None
                    break


def convert_to_move(bits):
    k = 0
    result = []
    while (bits>>k)&1 != 1:
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

#for ic in [1.3,1.7,1.9,2.5,2.7,3.5]:
for ic in [1.4]:
    c = math.sqrt(ic)
    #myself = 0
    #enemy = 1
    wins = 0
    N = 5
    B = Board()
    init_map1,init_map2 = convert_map_to_bit(B.board)
    #huge_node = Node(init_map1,init_map2,0,0,0,0,1,None)
    start = time.time()
    for i in range(N):
        cnt = 0
        #player = random.randint(0,1)
        player = 1
        enemy = player
        myself = 1 - player
        player = 0
        map1 = init_map1
        map2 = init_map2
        huge_node = Node(init_map1,init_map2,0,0,0,0,1,None)
        main_node = huge_node
        #print("NOWA GRA ==============")
        while True:
            #print(main_node.games)
            cnt += 1
            #print(cnt,myself,player,main_node.player)
            if cnt > 74:
                #print(cnt)
                #print_bit_map(map1,map2)
                break
            '''print("MAPA Z BITOW:")
            won = game_result(map1,map2)
            print(won)
            print_bit_map(map1,map2)
            print()'''
            '''print('DOBRA MAPA')
            B.draw()
            B.show()'''
            if player == enemy:
                m = B.random_move(player)
                if m != None:
                    bit_m = convert_to_bit(m)
                    move_m = convert_to_move(bit_m)
                    B.do_move(m, player)
                    res = result(bit_m,(map1,map2,player,0,[]))
                    map1 = res[0]
                    map2 = res[1]
                else:
                    bit_m = False
                update_main_node(map1,map2,bit_m)         
            if player == myself:
                #m = B.random_move(player)
                movik = best_move(main_node)
                if movik != 0:
                    conv_movik = convert_to_move(movik)
                    #print(conv_movik)
                    #bit_m = convert_to_bit(m)
                    move_m = conv_movik
                    B.do_move(move_m, player)
                    res = result(movik,(map1,map2,player,0,[]))
                    map1 = res[0]
                    map2 = res[1]

            player = 1-player
            if B.terminal():
                break
        '''print("MAPA Z BITOW:")
        print_bit_map(map1,map2)
        print()'''
        #print('DOBRA MAPA')
        #B.draw()
        #B.show()
        won = game_result(map1,map2)
        if won:
            wins += 1
        #rint('Game: ', i + 1,' we were:',myself,' result: ', B.result())
        B = Board()
    end = time.time()
    print('played: ', N, ' games and won: ', wins, ' in ', end - start, ic)
    #B.draw()
    #B.show()
    #print ('Result', B.result())
    '''mapaa = ['........',
    '.1......',
    '.010....',
    '...10...',
    '...01...',
    '........',
    '........',
    '........']
    tmp1,tmp2 = convert_map_to_bit(mapaa)
    a = actions((tmp1,tmp2,0))
    for t in a:
        print(convert_to_move(t))'''
sys.exit(0)                 