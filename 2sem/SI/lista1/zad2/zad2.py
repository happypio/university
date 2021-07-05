
dict = open("zad2_words.txt", "r")
text = open("zad2_input.txt","r")
output = open("zad2_output.txt", "w")
dictionary = set()
book = []
for line in text:
    book.append(line.rstrip('\n'))
for line in dict:
    dictionary.add(line.rstrip('\n'))

def solution (line):
    dp_length = [[] for i in range (len(line))]
    dp_beginning =  [[] for i in range (len(line))]
    for i in range (1, len(line) + 1):
        if line[:i] in dictionary:
            dp_beginning[i-1].append(-1)
            dp_length[i-1].append(i ** 2)
        for j in range(i):
           if j + 1 < i and len(dp_beginning[j]) > 0 and line[j + 1:i] in dictionary:
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

    output.write(ans[len(ans)-1])
    for i in reversed(range(len(ans)-1)):
        output.write(" " + ans[i])
    output.write("\n")
    
for line in book:
    solution(line)
output.close()
dict.close()
text.close()