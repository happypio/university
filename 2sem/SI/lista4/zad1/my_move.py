#kodowanie mapy w bitach (dla kazdego koloru inna liczba (bitmapa):
#pozycja (x,y) to: (8 * x) + y 
#state to [bits1,bits2,player,cnt_moves,moves]
K = [[[0,7,56,63],[2,4,11,16,25,31,32,38,47,52,59,61],[18,20,21,23,27,29,30,34,36,40,42,44,46,53,58],[3,5,9,10,12,13,14,17,19,22,24,26,28,33,35,37,41,43,45,47,49,50,51,54],[1,6,8,15,39,48,55,57,60,62]],
	[[0,7,56,63],[2,11,16,25,37,47,52,58,61],[4,5,13,17,18,20,21,22,23,27,29,31,32,34,36,38,40,41,42,43,45,46,47,50,52,53,58,59,61],[3,6,10,12,14,15,19,24,26,28,30,33,35,37,39,44,49,51,54,60],[1,7,8,9,48,55,57,62]],
	[[0,7,56,63],[9,14,16,18,21,42,45,47,49,54],[2,3,4,5,11,12,13,19,20,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,43,44,50,51,52,58,59,60,61],[1,6,8,10,15,17,46,48,53,55,57,62],[]],
	[[0,7,56,63],[9,14,16,18,21,42,45,47,49,54],[1,2,3,4,5,6,8,10,11,12,13,15,19,23,24,25,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,43,48,50,51,52,55,57,58,59,60,62,61],[13,17,20,22,26,44,46,53],[]],
	[[0,1,2,3,4,5,6,7,8,9,14,15,16,18,21,23,24,27,28,31,32,35,36,39,40,42,45,47,48,49,54,55,56,57,58,59,60,61,62,63],[10,11,12,13,17,19,20,22,25,26,29,30,33,34,37,38,41,43,44,46,50,51,52,53],[],[],[],[]]]
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



min_int = float('inf')
max_int = float('-inf')

def terminal(state):
	map1 = state[0]
	map2 = state[1]
	for i in range(64):
		if (map1>>i)&1 == 0 and (map2>>i)&1 == 0:
			return False
	return True

def utility(state):
	reslut1 = 0
	reslut2 = 0
	r = 0
	for i in range(64):
		if (map1>>i)&1 == 1:
			reslut1 += 1
		if (map2>>i)&1 == 1:
			result2 += 1
	if result1 == reslut2:
		r = state[3]
	else:
		if result1 < result2:
			r = (-20) * (1/state[3])
		else:
			r = 300 * (1/state[3])
	return r

DIRS = [(0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,1)]

def opposite(direction):
	return (direction[0] * (-1),direction[1] * (-1))

def find_field(direction,map,pos):
	cnt = 1
	while True:
		new_y = pos[0] + direction[0]*cnt
		new_x = pos[1] + direction[1]*cnt
		if 0 <= new_x < 8 and 0 <= new_y < 8:
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
						field = find_field(opposite(direction),map2,(i%8,i // 8))
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
						field = find_field(opposite(direction),map1,(i%8,i // 8))
						if field != False:
							if field not in m_set:
								m_set.add(field)
								moves.append(field)

	return moves

def to_beat(direction,map,pos):
	result = []
	cnt = 1
	while True:
		new_y = pos[0] + direction[0]*cnt
		new_x = pos[1] + direction[1]*cnt
		if 0 <= new_x < 8 and 0 <= new_y < 8:
			if (map>>((8 * new_x) + new_y))&1 == 0:
				return result
			else:
				result.append((1<<(8 * new_x) + new_y))
		else:
			return []

def beat(action,map):
	k = 0
	result = []
	while (action>>k)&1 != 1:
		k += 1
	pos = (k % 8, k // 8)
	for direction in DIRS:
		new_y = pos[0] + direction[0]
		new_x = pos[1] + direction[1]
		if 0 <= new_x < 8 and 0 <= new_y < 8 and (map>>(8*new_x + new_y))&1 == 1:
			fields = to_beat(direction,mapp,pos)
			result += fields
	return result

def result(action,state):
	map1 = state[0]
	map2 = state[1]
	player = state[2]
	moves = state[3]
	if player == 0:
		tmp_map = map1 ^ action
		fields = beat(action,map2)
		for field in fields:
			tmp_map = tmp_map ^ field
		map1 = tmp_map
	else:
		tmp_map = map2 ^ action
		fields = beat(action,map1)
		for field in fields:
			tmp_map = tmp_map ^ field
		map2 = tmp_map
	return [map1,map2,1 - player,moves + 0.5,action]


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
def alfa_beta(state):
	result_move = 0
	def max_value(state,alpha,beta):
		if terminal(state): 
			return utility(state)

		states = [result(a,state) for a in actions(state)]

		if state[3] / 0.5 >= 4:
			return(heuristic_value(state), len(states) == 0)

		value = min_int
		max_value = min_int
		best_state = []
		for state1 in sates:
			value = max(value,min_value(state1,alpha,beta))
			if value > max_value:
				max_value = value
				best_state = state1
			if value >= beta:
				return value
			alpha = max(alpha,value)
		result_move = best_state[4]
		return value

	def min_value(state,alpha,beta):
		if terminal(state): 
			return utility(state)

		states = [result(a,state) for a in actions(state)]

		if state[3] / 0.5 >= 3:
			return(heuristic_value(state),len(states) == 0)

		value = max_int
		for state1 in states:
			value = min(value,max_value(state1,alpha,beta))
			if value <= alpha:
				return value
			beta = min(beta,value)
		return value
	max_value(state,min_int,max_int)
	return result_move
