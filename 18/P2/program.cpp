#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

void flood_fill(set<array<int,3>>& space, set<array<int,3>>& filled, array<int,3>& node, int x_max, int y_max, int z_max, int& res) {
	// cout << node[0] << ' ' << node[1] << ' ' << node[2] << endl;
	filled.insert(node);
	array<int,3> right = node; right[0]++;
	if (filled.find(right) == filled.end()){ 
		if (space.find(right) != space.end()) {
			++res;
		} else if (right[0] >= -1 && right[0] <= x_max) {
			flood_fill(space, filled, right, x_max, y_max, z_max, res);
		}
	}
	array<int,3> left = node; left[0]--;
	if (filled.find(left) == filled.end()){ 
		if (space.find(left) != space.end()) {
			++res;
		} else if (left[0] >= -1 && left[0] <= x_max) {
			flood_fill(space, filled, left, x_max, y_max, z_max, res);
		}
	}
	array<int,3> behind = node; behind[1]++;
	if (filled.find(behind) == filled.end()){ 
		if (space.find(behind) != space.end()) {
			++res;
		} else if (behind[1] >= -1 && behind[1] <= y_max) {
			flood_fill(space, filled, behind, x_max, y_max, z_max, res);
		}
	}
	array<int,3> before = node; before[1]--;
	if (filled.find(before) == filled.end()){ 
		if (space.find(before) != space.end()) {
			++res;
		} else if (before[1] >= -1 && before[1] <= y_max)  {
			flood_fill(space, filled, before, x_max, y_max, z_max, res);
		}
	}
	array<int,3> up = node; up[2]++;
	if (filled.find(up) == filled.end()){ 
		if (space.find(up) != space.end())  {
			++res;
		} else if (up[2] >= -1 && up[2] <= z_max) {
			flood_fill(space, filled, up, x_max, y_max, z_max, res);
		}
	}
	array<int,3> down = node; down[2]--;
	if (filled.find(down) == filled.end()){ 
		if (space.find(down) != space.end())  {
			++res;
		} else if (down[2] >= -1 && down[2] <= z_max) {
			flood_fill(space, filled, down, x_max, y_max, z_max, res);
		}
	}
}

int flood_fill_count(set<array<int,3>>& space) {
	int x_max = 0, y_max = 0, z_max = 0; // using the fact that all the indices are non-negative
	for (auto& a: space) { // for convenience
		x_max = max(x_max, a[0]);
		y_max = max(y_max, a[1]);
		z_max = max(z_max, a[2]);
	}

	set<array<int,3>> filled;
	array<int,3> start{-1,-1,-1};
	int res = 0;
	++x_max; ++y_max; ++z_max;

	flood_fill(space, filled, start, x_max, y_max, z_max, res);

	cout << res << endl;
}

int main(int argc, char const *argv[]) {

	fstream in{"../P1/input.txt"}; char delim;
	set<array<int,3>> cubes;
	int res = 0;
	while (!in.eof()) {
		array<int,3> cube;
		in >> cube[0] >> delim >> cube[1] >> delim >> cube[2];
		cubes.insert(cube);
	}

	in.close();

	flood_fill_count(cubes); // 2516

	return 0;
}