#include <fstream>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void adjust(int& fx, int&fy, int& bx, int& by) {
	if (abs(fx-bx) == 2 || abs(fy-by) == 2) {
		if (fx > bx)
			++bx;
		if (fx < bx)
			--bx;
		if (fy > by)
			++by;
		if (fy < by)
			--by;
	}
}

int main(int argc, char const *argv[])
{
	fstream in{"../P1/input.txt"};
	char direction;
	int steps;
	auto bridge = vector<pair<int,int>>{10, make_pair(0, 0)};
	set<pair<int,int>> trail{};

	while (!in.eof()) {
		in >> direction >> steps;

		for (int i = 0; i < steps; ++i) {
			switch (direction) {
			case 'L':
				--bridge.begin()->first;
				break;
			case 'R':
				++bridge.begin()->first;
				break;
			case 'U':
				++bridge.begin()->second;
				break;
			case 'D':
				--bridge.begin()->second;
				break;
			}
			for (int i = 1; i < 10; ++i) {
				adjust(bridge[i-1].first, bridge[i-1].second, bridge[i].first, bridge[i].second);
			}
			trail.insert(bridge.back());
		}
	}

	cout << trail.size() << endl;

	return 0;
}