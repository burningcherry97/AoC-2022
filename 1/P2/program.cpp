#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
	int max = 0, curr_sum = 0;
	ifstream in{"input.txt"};
	vector<int> sums{};

	for (string line; getline(in, line); ) {
		if (line == "") {
			sums.push_back(curr_sum);
			curr_sum = 0;
		} else {
			curr_sum += stoi(line);
		}
	}

	sort(sums.begin(), sums.end(), greater<int>{});

	cout << sums[0] + sums[1] + sums[2] << endl;

	return 0;
}