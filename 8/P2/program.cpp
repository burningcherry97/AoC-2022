#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int get_score(vector<string>& map, int i, int j, int i_dir, int j_dir) {
	int res = 0;
	int height = map[i][j];
	int rows = map.size();
	int columns = map[0].size();
	while (i > 0 && i < rows-1 && j > 0 && j < columns - 1) {
		i += i_dir;
		j += j_dir;
		++res;
		if (map[i][j] >= height)
			return res;
	}
	return res;
}

int main(int argc, char const *argv[])
{
	fstream in{"../P1/input.txt"};
	vector<string> map;

	while (!in.eof()) {
		map.push_back("");
		getline(in, map.back());
	}

	int rows = map.size();
	int columns = map[0].size();
	int max_score = 0;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			int score = get_score(map, i, j, -1, 0) *
						get_score(map, i, j, 0, -1) *
						get_score(map, i, j, 1, 0) *
						get_score(map, i, j, 0, 1);
			max_score = max(score, max_score);
		}
	}

	cout << max_score << endl;

	return 0;
}