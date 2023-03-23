#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	int max = 0, curr_sum = 0;
	ifstream in{"input.txt"};

	for (string line; getline(in, line); ) {
		if (line == "") {
			max = std::max(max, curr_sum);
			curr_sum = 0;
		} else {
			curr_sum += stoi(line);
		}
	}

	cout << max << endl;

	return 0;
}