#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream in{"input.txt"};
	string line;
	int range_1_begin, range_1_end, range_2_begin, range_2_end, overlaps = 0;
	char delimiter;

	while (getline(in, line)) {
		istringstream iss(line);
		iss >> range_1_begin >> delimiter >> range_1_end >> delimiter >> range_2_begin >> delimiter >> range_2_end;
		if (range_1_begin > range_2_begin) {
			if (range_1_end <= range_2_end)
				++overlaps;
		} else if (range_1_begin < range_2_begin) {
			if (range_1_end >= range_2_end)
				++overlaps;
		} else {
			++overlaps;
		}
	}

	cout << overlaps << endl;

	return 0;
}