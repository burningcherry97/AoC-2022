#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream in{"input.txt"};
	char opponent, response;
	int score_table[3][3] = {
		{3, 6, 0},
		{0, 3, 6},
		{6, 0, 3}
	};
	int score = 0;
	while (in >> opponent >> response) {
		score += score_table[opponent - 'A'][response - 'X'];
		score += response - 'W';
	}

	cout << score << endl;

	return 0;
}