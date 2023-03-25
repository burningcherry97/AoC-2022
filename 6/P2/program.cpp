#include <fstream>
#include <iostream>
#include <set>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream in{"../P1/input.txt"};
	string transmission = "";

	for (int i = 0; i < 14; ++i)
		transmission += in.get();

	for (int read = 14; ;) {
		transmission += in.get(); ++read;
		if (set<char>(transmission.end()-14, transmission.end()).size() == 14) {
			cout << read << endl;
			break;
		}
	}

	return 0;
}