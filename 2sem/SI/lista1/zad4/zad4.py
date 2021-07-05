OUTPUT = open("zad4_output.txt","w")
def solution(sequence,d):
    length = int(d)
    n = len(sequence)
    ones = [0 for i in range(n)]
    ones[0] = int(sequence[0])
    for i in range(1,n):
        ones[i] = ones[i - 1] + int(sequence[i])
    ans = 10000000000
    for i in range(n - length + 1):
        if i != 0:
            ones_before = ones[i - 1]
        else:
            ones_before = 0
        if length != 0:
            end = i + length -1
        else:
            end = 0
        zeros = length - (ones[end] - ones_before)
        ones_after_length = ones[n - 1] - ones[end]
        swaping = ones_before + ones_after_length + zeros
        ans = min(ans,swaping)
    OUTPUT.write(str(ans) + "\n")
INPUT = open("zad4_input.txt","r")
for line in INPUT:
    solution(line[:len(line)-3],line[len(line)-2])
INPUT.close()
OUTPUT.close()

