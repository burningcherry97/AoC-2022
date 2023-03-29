#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void cycle(int& reg, int& clock, int& signal) {
	++clock;
	static int stop = 20;
	if (clock == stop) {
		signal += reg * clock;
		if (clock < 220)
			stop += 40;
	}
}

int main(int argc, char const *argv[])
{
	fstream in{"input.txt"};
	string command;
	int argument;
	int clock = 0;
	int reg = 1;
	int signal = 0;

	while (!in.eof()) {
		in >> command;
		if (command == "noop") 
			cycle(reg, clock, signal);
		else {
			in >> argument;
			cycle(reg, clock, signal);
			cycle(reg, clock, signal);
			reg += argument;
		}
	}

	cout << signal << endl;

	return 0;
}