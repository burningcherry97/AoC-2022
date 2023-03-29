#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void cycle(int& reg, int& clock, string& image) {
	if (abs(clock-reg) <= 1) {
		image += '#';
	} else {
		image += '.';
	}
	clock = (clock+1)%40;
}

int main(int argc, char const *argv[])
{
	fstream in{"../P1/input.txt"};
	string command;
	string image = "";
	int argument;
	int clock = 0;
	int reg = 1;

	while (!in.eof()) {
		in >> command;
		if (command == "noop") 
			cycle(reg, clock, image);
		else {
			in >> argument;
			cycle(reg, clock, image);
			cycle(reg, clock, image);
			reg += argument;
		}
	}

	for (int i = 0; i < 6; ++i) {
		cout << image.substr(i*40, 40) << endl;
	}

	return 0;
}