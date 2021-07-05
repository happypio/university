import random
import time
def deepcopy(board):
    return [list(row) for row in board]

class Jungle:
    PIECE_VALUES = {
        0: 4,
        1: 1,
        2: 2,
        3: 3,
        4: 5,
        5: 7,
        6: 8,
        7: 10
    }
    MAXIMAL_PASSIVE = 30
    DENS_DIST = 0.1
    MX = 7
    MY = 9
    traps = {(2, 0), (4, 0), (3, 1), (2, 8), (4, 8), (3, 7)}
    ponds = {(x, y) for x in [1, 2, 4, 5] for y in [3, 4, 5]}
    dens = [(3, 8), (3, 0)]
    dirs = [(0, 1), (1, 0), (-1, 0), (0, -1)]

    rat, cat, dog, wolf, jaguar, tiger, lion, elephant = range(8)

    def __init__(self):
        self.board = self.initial_board()
        self.pieces = {0: {}, 1: {}}

        for y in range(Jungle.MY):
            for x in range(Jungle.MX):
                C = self.board[y][x]
                if C:
                    pl, pc = C
                    self.pieces[pl][pc] = (x, y)
        self.curplayer = 0
        self.peace_counter = 0
        self.winner = None

    def initial_board(self):
        pieces = """
        L.....T
        .D...C.
        R.J.W.E
        .......
        .......
        .......
        e.w.j.r
        .c...d.
        t.....l
        """

        B = [x.strip() for x in pieces.split() if len(x) > 0]
        T = dict(zip('rcdwjtle', range(8)))

        res = []
        for y in range(9):
            raw = 7 * [None]
            for x in range(7):
                c = B[y][x]
                if c != '.':
                    if 'A' <= c <= 'Z':
                        player = 1
                    else:
                        player = 0
                    raw[x] = (player, T[c.lower()])
            res.append(raw)
        return res

    def random_move(self, player):
        ms = self.moves(player)
        if ms:
            return random.choice(ms)
        return None

    def can_beat(self, p1, p2, pos1, pos2):
        if pos1 in Jungle.ponds and pos2 in Jungle.ponds:
            return True  # rat vs rat
        if pos1 in Jungle.ponds:
            return False  # rat in pond cannot beat any piece on land
        if p1 == Jungle.rat and p2 == Jungle.elephant:
            return True
        if p1 >= p2:
            return True
        if pos2 in Jungle.traps:
            return True
        return False

    def pieces_comparison(self):
        for i in range(7,-1,-1):
            ps = []
            for p in [0,1]:
                if i in self.pieces[p]:
                    ps.append(p)
            if len(ps) == 1:
                return ps[0]
        return None
                
    def rat_is_blocking(self, player_unused, pos, dx, dy):        
        x, y = pos
        nx = x + dx
        for player in [0,1]:
            if Jungle.rat not in self.pieces[1-player]:
                continue
            rx, ry = self.pieces[1-player][Jungle.rat]
            if (rx, ry) not in self.ponds:
                continue
            if dy != 0:
                if x == rx:
                    return True
            if dx != 0:
                if y == ry and abs(x-rx) <= 2 and abs(nx-rx) <= 2:
                    return True
        return False

    def draw(self):
        TT = {0: 'rcdwjtle', 1: 'RCDWJTLE'}
        for y in range(Jungle.MY):

            L = []
            for x in range(Jungle.MX):
                b = self.board[y][x]
                if b:
                    pl, pc = b
                    L.append(TT[pl][pc])
                else:
                    L.append('.')
            print(''.join(L))
        print('')

    def moves(self, player):
        res = []
        for p, pos in self.pieces[player].items():
            x, y = pos
            for (dx, dy) in Jungle.dirs:
                pos2 = (nx, ny) = (x+dx, y+dy)
                if 0 <= nx < Jungle.MX and 0 <= ny < Jungle.MY:
                    if Jungle.dens[player] == pos2:
                        continue
                    if pos2 in self.ponds:
                        if p not in (Jungle.rat, Jungle.tiger, Jungle.lion):
                            continue
                        #if self.board[ny][nx] is not None:
                        #    continue  # WHY??
                        if p == Jungle.tiger or p == Jungle.lion:
                            if dx != 0:
                                dx *= 3
                            if dy != 0:
                                dy *= 4
                            if self.rat_is_blocking(player, pos, dx, dy):
                                continue
                            pos2 = (nx, ny) = (x+dx, y+dy)
                    if self.board[ny][nx] is not None:
                        pl2, piece2 = self.board[ny][nx]
                        if pl2 == player:
                            continue
                        if not self.can_beat(p, piece2, pos, pos2):
                            continue
                    res.append((pos, pos2))
        return res

    def victory(self, player):
        oponent = 1-player        
        if len(self.pieces[oponent]) == 0:
            self.winner = player
            return True

        x, y = self.dens[oponent]
        if self.board[y][x]:
            self.winner = player
            return True
        
        if self.peace_counter >= Jungle.MAXIMAL_PASSIVE:
            r = self.pieces_comparison()
            if r is None:
                self.winner = 1 # draw is second player's victory 
            else:
                self.winner = r
            return True
        return False

    def do_move(self, m):
        self.curplayer = 1 - self.curplayer
        if m is None:
            return
        pos1, pos2 = m
        x, y = pos1
        pl, pc = self.board[y][x]

        x2, y2 = pos2
        if self.board[y2][x2]:  # piece taken!
            pl2, pc2 = self.board[y2][x2]
            del self.pieces[pl2][pc2]
            self.peace_counter = 0
        else:
            self.peace_counter += 1    

        self.pieces[pl][pc] = (x2, y2)
        self.board[y2][x2] = (pl, pc)
        self.board[y][x] = None

    def update(self, player, move_string):
        assert player == self.curplayer
        move = tuple(int(m) for m in move_string.split())
        if len(move) != 4:
            raise WrongMove
        possible_moves = self.moves(player)
        if not possible_moves:
            if move != (-1, -1, -1, -1):
                raise WrongMove
            move = None
        else:
            move = ((move[0], move[1]), (move[2], move[3]))
            if move not in possible_moves:
                raise WrongMove
        self.do_move(move)
        
        if self.victory(player):
            assert self.winner is not None
            return 2 * self.winner - 1
        else:
            return None


    def simulate(self,move,player):
        K = 1
        curr_player = player
        curr_state = Jungle()
        curr_state.board = deepcopy(self.board) 
        curr_state.player = self.curplayer
        curr_state.peace_counter = self.peace_counter
        curr_state.winner = self.winner
        dict0 = self.pieces[0].copy()
        dict1 = self.pieces[1].copy()
        curr_state.pieces =  {0: dict0, 1: dict1}
        #curr_state = self.new_state(self)
        curr_state.do_move(move)
        player = 1 - player
        while True:
            m = curr_state.random_move(player)
            curr_state.do_move(m)
            K += 1
            if curr_state.victory(player):
                if curr_state.winner == curr_player:
                    return K,1
                else:
                    return K,-1
            player = 1 - player

    def rate_moves(self,ms,N,player):
    	ms_rated = [[0,i] for i in ms]
    	L = len(ms)
    	i = 0
    	while N > 0:
    		K,score = self.simulate(ms[i],player)
    		ms_rated[i][0] += score
    		N -= K
    		i = (i + 1)%L
    	return ms_rated

    def good_move(self,player):
    	N = 20000
    	ms = self.moves(player)
    	if len(ms) == 0:
    		return None
    	ms_rated = self.rate_moves(ms,N,player)
    	move = max(ms_rated)
    	return move[1]

    def new_state(self,state):
        curr_state = Jungle()
        curr_state.board = deepcopy(state.board) 
        curr_state.player = state.curplayer
        curr_state.peace_counter = state.peace_counter
        curr_state.winner = state.winner
        dict0 = state.pieces[0].copy()
        dict1 = state.pieces[1].copy()
        curr_state.pieces =  {0: dict0, 1: dict1}
        return curr_state

    def find_AB_move(self,player):
        my_player = player
        min_int = float('-inf')
        max_int = float('inf')
        def result(move,state):
            new_state = self.new_state(state)
            new_state.do_move(move)
            return new_state

        def utility(state):
            if state.winner == my_player:
                return 10000
            else:
                return -10000

        'rcdwjtle'
        def heuristic_value(state):
            #curr_player = state.curplayer
            curr_player = my_player
            our_pieces = [[k,v] for k, v in state.pieces[my_player].items()]
            en_pieces = [[k,v] for k, v in state.pieces[1 - my_player].items()]
            res = 0
            sum_values = 0
            for i in range(7):
                our = False
                en = False
                if i in state.pieces[my_player]:
                    our = True
                if i in state.pieces[1 - my_player]:
                    en = True
                if our == True and en == False:
                    res += (100 * self.PIECE_VALUES[i])
                    break
                if our == False and en == True:
                    res -= (100 * self.PIECE_VALUES[i])
                    break
            #dist = 1000000000
            for piece in our_pieces:
                res -= abs(state.dens[1 - curr_player][0] - piece[1][0]) + abs(state.dens[1 - curr_player][1] - piece[1][1])
                #tmp = abs(state.dens[1 - curr_player][0] - piece[1][0]) + abs(state.dens[1 - curr_player][1] - piece[1][1])
                #if tmp < dist:
                #    dist = tmp
                sum_values += self.PIECE_VALUES[piece[0]]

            #dist = 0
            for piece in en_pieces:
                res += abs(state.dens[curr_player][0] - piece[1][0]) + abs(state.dens[curr_player][1] - piece[1][1])
                #tmp = abs(state.dens[curr_player][0] - piece[1][0]) + abs(state.dens[curr_player][1] - piece[1][1])
                #if tmp < dist:
                #    dist = tmp
                sum_values -= self.PIECE_VALUES[piece[0]]
            #print(sum_values)
            res += 10*sum_values 
            #print(res)
            return res
        def Alpha_Beta(state):

            def max_value(state,alpha,beta,depth):
                if state.victory(state.curplayer): 
                    return utility(state)
                states = [result(move,state) for move in state.moves(state.curplayer)]

                if depth == 0:
                    return heuristic_value(state)

                if depth == 1:
                    states_sorted = []
                    for state in states:
                        states_sorted.append((heuristic_value(state),state))
                    states_sorted.sort(key = lambda x : x[0])
                    states = []
                    for state in states_sorted:
                        states.append(state[1])

                value = min_int

                for state1 in states:
                    value = max(value,min_value(state1,alpha,beta,depth - 1))
                    
                    if value >= beta:
                        return value
                    alpha = max(alpha,value)

                return value

            def min_value(state,alpha,beta,depth):
                if state.victory(state.curplayer): 
                    return utility(state)

                states = [result(move,state) for move in state.moves(state.curplayer)]

                if depth == 0:
                    return heuristic_value(state)

                if depth == 2:
                    states_sorted = []
                    for state in states:
                        states_sorted.append((heuristic_value(state),state))
                    states_sorted.sort(key=lambda x: x[0])
                    states = []
                    for state in states_sorted:
                        states.append(state[1])

                value = max_int
                for state1 in states:
                    value = min(value,max_value(state1,alpha,beta,depth - 1))
                    if value <= alpha:
                        return value
                    beta = min(beta,value)

                return value

            ms = self.moves(player)
            ms_rated = [[0,i] for i in ms]
            for move in ms_rated:
                curr_state = self.new_state(self)
                curr_state.do_move(move[1])
                move[0] = min_value(curr_state,min_int,max_int,2)
            move = max(ms_rated)
            #print(move[1])
            return move[1]
        return Alpha_Beta(self)



wins = 0
G = 10
start = time.time()
for i in range(G):
    B = Jungle()
    player = 0
    #myself  = random.randint(0,1)
    myself = 1
    while True:
        #B.draw()
        if player:
            if myself:
                m = B.find_AB_move(player)
            else:
                m = B.good_move(player)
            #print(m)
            B.do_move(m)
        else:
            #m = B.random_move(player)
            if myself == player:
                m = B.find_AB_move(player)
            else:
                m = B.good_move(player)
            #print(m)
            B.do_move(m)
        if B.victory(player):
            if B.winner == myself:
                wins += 1
                print('win')
            else:
                print('loss')
            #print(B.winner,'wygral my bylismy: ',myself)
            break
        player = 1 - player 
    #B.draw()
end = time.time()
print(f'Played {G} games and won {wins} in time {end - start}')