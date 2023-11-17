// Line 67 starts the remains of a bunch of tests whose idea is to find a cycle in the rock pattern and calculate most of the final rock height as
// a multiple of the cycle length. I found that a cycle starts after rock 1720, lasts 1725 rocks and builds up 2702 height. This gives 579710143 cycles times
// 2703 height + 2692 height + 2506 height after (determined separately), totalling 1566376811584 height.

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
	
	ifstream in{"../P1/input.txt"};
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

	int shape = 0, gas = 0, height = 1, blocks = 0;

	vector<pair<int,int>> curr_shape;

	for (int i = 0; i < 3325; ++i) {
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
				// if (shape == 0 && gas < 100) {
				// 	cout << gas << ' ' << curr_shape[0].second << endl;
				// }
				// if (shape == 0 && gas == 23) {
				// 	cout << i << ' ' << height - 1 << endl;
				// }
				++shape; shape %= shapes.size();
				break;
			}
			else {
				for (auto& b: curr_shape)
					--b.first;
			}
		}
	}
	
	cout << height - 1 << endl;

	return 0;
}