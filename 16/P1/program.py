import itertools as it
import networkx as nx

G = nx.Graph()
file = open('input.txt')

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

max_score = 0
for perm in DLS('AA', outlets, 30):
	time = 30
	curr = "AA"
	score = 0
	for node in perm[1:]:
		time = time - dist(curr, node)
		if time <= 0:
			break
		curr = node
		score = score + time * press(curr)
	if score > max_score:
		max_score = score

print(max_score) # 2253