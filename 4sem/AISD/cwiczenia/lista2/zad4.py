stopien = [0] * n #stopien kazdego wierzcholka
G = [[]] * n # lista sasiedztwa grafu
liscie = [] #aktualne liscie
# k dane (kolorowanie w zadaniu)
ans = [] #wierzcholki do optymalnego pokolorowania
for v in G:
	for u in G[v]:
		stopien[v] += 1
for s in range(n):
	if stopien[s] == 1: #znalezlismy lisc
		lisce.append(s)

while k > 1 and liscie:
	nowe_liscie = []
	for l in liscie:
		ans.append(l)
		for u in G[l]:
			stopien[u] -= 1
			if stopien[u] == 1:
				nowe_liscie.append(u)

	liscie = nowe_liscie # aktualizacja lisci

if k == 1 and liscie:
	ans.append(liscie[0]) #dodawanie dowolnego wierzcholka

#w ans mamy optymalne kolorowanie