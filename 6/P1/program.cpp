#include <fstream>
#include <iostream>
#include <set>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream in{"input.txt"};
	string transmission = "";

	for (int i = 0; i < 3; ++i)
		transmission += in.get();

	for (int read = 3; ;) {
		transmission += in.get(); ++read;
		if (set<char>(transmission.end()-4, transmission.end()).size() == 4) {
			cout << read << endl;
			break;
		}
	}

	return 0;
}