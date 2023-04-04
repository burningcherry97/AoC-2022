#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>

using namespace std;

bool stable(vector<vector<char>>& map, int x, int y) {
	return map[y+1][x-1] != '.' && map[y+1][x] != '.' && map[y+1][x+1] != '.';
}

pair<int,int> move_sand(vector<vector<char>>& map, int x, int y) {
	map[y][x] = '.';
	for (int i : {0,-1,1}) {
		if (map[y+1][x+i] == '.') {
			map[y+1][x+i] = 'o';
			return {y+1, x+i};
		}
	}
}

int main(int argc, char const *argv[])
{
	fstream in{"../P1/input.txt"};
	string line;

	vector<vector<pair<int,int>>> labirynth{};
	while (getline(in, line)) {
		vector<pair<int,int>> path{};
		int x, y;
		char comma;
		string dummy;
		istringstream iss{line};
		pair<int,int> start{};
		iss >> start.second >> comma >> start.first;
		path.push_back(start);
		while (!iss.eof()) {
			pair<int,int> node{};
			iss >> dummy >> node.second >> comma >> node.first;
			path.push_back(node);
		}
		labirynth.push_back(path);
	}

	int x_min = INT32_MAX, x_max = INT32_MIN, y_min = 0, y_max = INT32_MIN;
	for (auto& a : labirynth) {
		for (auto& b : a) {
			x_min = min(x_min, b.second);
			x_max = max(x_max, b.second);
			y_max = max(y_max, b.first);
		}
	}

	y_max += 2;
	x_min = min(x_min, 500-y_max);
	x_max = max(x_max, 500+y_max);
	int source = 500 - x_min;

	for (auto& a : labirynth) {
		for (auto& b : a) {
			b.second -= x_min;
		}
	}
	x_max -= x_min;
	x_min = 0;
	// cout << x_min << ' ' << x_max << ' ' << y_min << ' ' << y_max << endl;

	vector<vector<char>> map(y_max - y_min + 1, vector<char>(x_max - x_min + 1, '.'));

	for (auto& a: labirynth) {
		int y = a.front().first;
		int x = a.front().second;
		map[y][x] = '#';
		int xx, yy;
		for (int i = 1; i < a.size(); ++i) {
			if (a[i].second != x) {
				xx = a[i].second;
				for (int j = x; ; j += (xx > x ? 1 : -1)) {
					map[y][j] = '#';
					if (j == xx)
						break;
				}
				x = xx;
			} else {
				yy = a[i].first;
				for (int j = y; ; j += (yy > y ? 1 : -1)) {
					map[j][x] = '#';
					if (j == yy)
						break;
				}
				y = yy;
			}
		}
	}
	for (char& c : map.back())
		c = '#';


	int grains = 0;
	while (!stable(map, source, 0)) {
		++grains;
		int x = source;
		int y = 0;
		map[y][x] = 'o';
		while (!stable(map, x, y)) {
			std::tie(y, x) = move_sand(map, x, y);
		}
	}
	map[0][source] = 'o';
	++grains;

	// for (int i = 0; i < map.size(); ++i) {
	// 	for (int j = 0; j < map.front().size(); ++j) {
	// 		cout << map[i][j];
	// 	}
	// 	cout << endl;
	// }

	cout << grains << endl;

	return 0;
}