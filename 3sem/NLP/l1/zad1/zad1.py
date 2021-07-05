good_tokens = []
sizeofcorpus = 10000
with open('polish_corpora.txt', 'r') as f:
    for i in range(sizeofcorpus):
        line = f.readline()
        good_tokens.append(line.split())

corpus = set()

for line in good_tokens:
    for e in line:
        corpus.add(e)


def MaxMatch (s):
    ans = []
    while(len(s) > 0):
        found = False
        idx = 0
        for i in range(len(s),0,-1):
            if s[:i] in corpus:
                idx = i
                found = True
                break
        if found:
            ans.append(s[:idx])
            s = s[idx:]
        else:
            ans.append(s[0])
            s = s[1:]
    return ans

def dp_solution (line):
    dp_length = [[] for i in range (len(line))]
    dp_beginning =  [[] for i in range (len(line))]
    for i in range (1, len(line) + 1):
        if line[:i] in corpus:
            dp_beginning[i-1].append(-1)
            dp_length[i-1].append(i ** 2)
        for j in range(i):
           if j + 1 < i and len(dp_beginning[j]) > 0 and line[j + 1:i] in corpus:
               dp_beginning[i-1].append(j)
               dp_length[i-1].append((i - j -1) ** 2)
    sum_length = [ 0 for i in range(len(line)) ]
    words = [ 0 for i in range(len(line)) ]
    for i in range (len(line)):
        if len(dp_beginning[i]) > 0:
            for j in range(len(dp_beginning[i])):
                if dp_length[i][j] + sum_length[dp_beginning[i][j]] >  sum_length[i]:
                    sum_length[i] = dp_length[i][j] + sum_length[dp_beginning[i][j]]
                    words[i] = dp_beginning[i][j]
    ans = []
    n = len(line)-1
    while n > -1:
        ans.append(line[words[n]+1:n+1])
        #print(line[words[n]+1:n+1])
        n = words[n]
    ans.reverse()
    return ans

def count_length(s):
    ans = 0
    for i in s:
        ans += len(i) ** 2
    return ans

def errors(g,s1,s2):
	ans1,ans2 = 0,0
	good = set(g)
	for i in s1:
		if i in good:
			ans1 += 1
	for i in s2:
		if i in good:
			ans2 += 1
	return ans1,ans2,len(g)

# sposób mierzenia podobieństwa  :
# 100% * [ilosc_tych samych slow / ilosc wszystkich slow]
good_words = 0
recovered_length = 0
second_recovered_length = 0
i = 0
for line in good_tokens:
    recovered = MaxMatch(''.join(line))
    second_recovered = dp_solution(''.join(line))

   
    a,b,c = errors(line,recovered,second_recovered)
    if i < 20:
        print(line)
        print(recovered)
        print(second_recovered)
        print("ilosc slow:",c,"wartosc dla maxM:",a,"wartosc dla dp:",b)
    i += 1
    good_words += c
    recovered_length += a
    second_recovered_length += b
    #good_words += count_length(line)
    #recovered_length += count_length(recovered)
    #second_recovered_length += count_length(second_recovered)
print("Podobieństwo dla MaxMatch wynosi:", 100 * (recovered_length) / good_words, '%')
print("Podobieństwo dla dynamicznego algorytmu wynosi:", 100 * (second_recovered_length) / good_words, '%')
#print("Podobieństwo dla MaxMatch wynosi", (100 - ((good_words - recovered_length)/good_words)*100), '%')
#print("Podobieństwo dla dynamicznego algorytmu wynosi", (100 - ((good_words - second_recovered_length)/good_words)*100), '%')