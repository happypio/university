days = {0 : 0,1 : 0,2 : 0,3 : 0,4 : 0,5 : 0,6 : 0}

normal =   [0,3,3,6,1,4,6,2,5,0,3,5]
not_normal=[0,3,4,0,2,5,0,3,6,1,4,6]

act = 6

for j in range (1601,2001):
	if j % 4 == 0 and (j % 100 != 0 or j % 400 == 0):
		for i in not_normal:
			days[(act + i) % 7] += 1
		act = (act + 6 + 3) % 7
	else:
		for i in normal:
			days[(act + i) % 7] += 1
		act = (act + 5 + 3) % 7

print(days)


# if j % 4 == 0 and (j % 100 != 0 or j % 400 == 0):
# if j % 4 != 0 or (j % 100 == 0 and j % 400 != 0):
