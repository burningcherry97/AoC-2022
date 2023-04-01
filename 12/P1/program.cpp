#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class vertex {
public:
	char letter;
	int distance;
	set<vertex*> neighbours;

	vertex(char c, int d) {
		letter = c;
		distance = d;
		neighbours = set<vertex*>{};
	}
};

int main(int argc, char const *argv[])
{
	fstream in{"input.txt"}; string line;
	vector<vector<vertex>> map;
	set<vertex*> a{}, b{};
	set<vertex*>* current = &a, * next = &b;
	int s_x, s_y, e_x, e_y;
	while (!in.eof()) {
		map.push_back(vector<vertex>{});
		getline(in, line);
		istringstream iss{line};
		char c; int d;
		while (iss >> c) {
			d = INT32_MAX;
			if (c == 'S') {
				c = 'a';
				d = 0;
				s_y = map.size() - 1;
				s_x = map.back().size();
			} else if (c == 'E') {
				c = 'z';
				e_y = map.size() - 1;
				e_x = map.back().size();
			}
			map.back().push_back(vertex{c, d});
		}
	}

	// we know the grid is rectangular
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			if (i > 0 && map[i-1][j].letter <= map[i][j].letter + 1)
				map[i][j].neighbours.insert(&(map[i-1][j]));
			if (i < map.size() - 1 && map[i+1][j].letter <= map[i][j].letter + 1)
				map[i][j].neighbours.insert(&(map[i+1][j]));
			if (j > 0 && map[i][j-1].letter <= map[i][j].letter + 1)
				map[i][j].neighbours.insert(&(map[i][j-1]));
			if (j < map[i].size() - 1 && map[i][j+1].letter <= map[i][j].letter + 1)
				map[i][j].neighbours.insert(&(map[i][j+1]));
		}
	}

	int dist = 1;
	current->insert(&map[s_y][s_x]);

	while(!current->empty()) {
		for (vertex* v : *current) {
			for (vertex* vv : v->neighbours) {
				if (vv->distance == INT32_MAX) {
					vv->distance = dist;
					next->insert(vv);
				}
			}
		}
		swap(current, next);
		next->clear();
		++dist;
	}

	cout << map[e_y][e_x].distance << endl;

	return 0;
}