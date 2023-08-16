# took about half an hour to urn on my laptop but that's probably still faster than it would take to write an efficient implementation

import itertools as it
import networkx as nx

G = nx.Graph()
file = open('../P1/input.txt')

input = file.readlines()
 
count = 0
for line in input:
    tokens = line.split(' ')
    for token in tokens[9:]:
    	G.add_edge(tokens[1].rstrip(',\n'), token.rstrip(',\n'))
    G.nodes[tokens[1].rstrip(',\n')]["pressure"] = int(tokens[4].rstrip(';')[5:])
nodes = dict(G.nodes)

distances = dict(nx.all_pairs_dijkstra(G))

def dist(a, b):
	return distances[a][0][b] + 1;
# print(dist("AA","JJ"))

def press(x):
	return nodes[x]["pressure"]
# print(press("CC"))

outlets = filter(lambda x: (press(x) > 0), nodes)
# print(outlets)

def DLS(start, remaining, time):
	if time < 0:
		return [[]]
	if remaining == []:
		return [[start]]
	res = []
	for elem in remaining:
		for path in DLS(elem, [n for n in remaining if n != elem], time - dist(start,elem)):
			res.append([start] + path)
	return res

def set_score(outlet_set):
	max_score = 0
	for perm in DLS('AA', outlet_set, 26):
		time = 26
		curr = 'AA'
		score = 0
		for node in perm[1:]:
			time = time - dist(curr, node)
			if time <= 0:
				break
			curr = node
			score = score + time * press(curr)
		if score > max_score:
			max_score = score
	return max_score

outlet_n = len(outlets)
# print(outlet_n)

max_score_total = 0;
for i in range(2 ** (outlet_n - 1)):
	print(i)
	set1 = []
	set2 = []
	for j in range(outlet_n):
		if (i >> j) % 2:
			set1.append(outlets[j])
		else:
			set2.append(outlets[j])
	score = set_score(set1) + set_score(set2)
	if score > max_score_total:
		max_score_total = score

print(max_score_total) # 2838