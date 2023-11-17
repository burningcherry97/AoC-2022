#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
	
	ifstream in{"input.txt"};
	string gas_pattern;
	in >> gas_pattern;
	in.close();
	// cout << gas;
	vector<array<char, 7>> cavern;
	cavern.push_back({'#','#','#','#','#','#','#'});

	vector<vector<array<int, 2>>> shapes{
		{{0,0}, {1,0}, {2,0}, {3,0}}, // –
		{{0,1}, {1,0}, {1,1}, {1,2}, {2,1}}, // +
		{{0,0}, {1,0}, {2,0}, {2,1}, {2,2}}, // L
		{{0,0}, {0,1}, {0,2}, {0,3}}, // I
		{{0,0}, {0,1}, {1,0}, {1,1}}
	};

	int shape = 0, gas = 0, height = 1;

	vector<pair<int,int>> curr_shape;

	for (int i = 0; i < 2022; ++i) {
		// prepare cavern
		int s = cavern.size();
		cavern.resize(height + 7);
		for (int j = s; j < cavern.size(); ++j)
			for (int k = 0; k < 7; ++k)
				cavern[j][k] = '.';

		// put new shape
		curr_shape.clear();
		for (auto& a: shapes[shape]) {
			curr_shape.push_back({height + 3 + a[1], 2 + a[0]});
		}

		while (true) {
			if (gas_pattern[gas] == '>') {
				if (all_of(curr_shape.begin(), curr_shape.end(), [&](auto a){ return a.second < 6 && cavern[a.first][a.second + 1] == '.'; }))
					for (auto& b: curr_shape)
						++b.second;
			} else {
				if (all_of(curr_shape.begin(), curr_shape.end(), [&](auto a){ return a.second > 0 && cavern[a.first][a.second - 1] == '.'; }))
					for (auto& b: curr_shape)
						--b.second;
			}
			++gas; gas %= gas_pattern.size();
			if (any_of(curr_shape.begin(), curr_shape.end(), [&](auto a){ return cavern[a.first - 1][a.second] == '#'; })) {
				for (auto& b: curr_shape){
					cavern[b.first][b.second] = '#';
					if (b.first + 1 > height)
						height = b.first + 1;
				}
				++shape; shape %= shapes.size();
				break;
			}
			else {
				for (auto& b: curr_shape)
					--b.first;
			}
		}
	}
	
	cout << height - 1 << endl; // 3186

	return 0;
}