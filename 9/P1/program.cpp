#include <fstream>
#include <iostream>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char const *argv[])
{
	fstream in{"input.txt"};
	char direction;
	int steps;
	int h_x = 0, h_y = 0, t_x = 0, t_y = 0;
	set<pair<int,int>> trail{};

	while (!in.eof()) {
		in >> direction >> steps;

		for (int i = 0; i < steps; ++i) {
			switch (direction) {
			case 'L':
				--h_x;
				if (t_x - h_x == 2) {
					--t_x;
					t_y = h_y;
				}
				break;
			case 'R':
				++h_x;
				if (h_x - t_x == 2) {
					++t_x;
					t_y = h_y;
				}
				break;
			case 'U':
				++h_y;
				if (h_y - t_y == 2) {
					++t_y;
					t_x = h_x;
				}
				break;
			case 'D':
				--h_y;
				if (t_y - h_y == 2) {
					--t_y;
					t_x = h_x;
				}
				break;
			}
			trail.insert(make_pair(t_x, t_y));
		}
	}

	cout << trail.size() << endl;

	return 0;
}