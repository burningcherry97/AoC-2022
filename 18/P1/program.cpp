#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	fstream in{"input.txt"}; char delim;
	vector<array<int,3>> cubes;
	int res = 0;
	while (!in.eof()) {
		array<int,3> cube;
		in >> cube[0] >> delim >> cube[1] >> delim >> cube[2];
		res += 6;
		for (auto& a: cubes)
			if (abs(a[0]-cube[0]) == 1 && a[1] == cube[1] && a[2] == cube[2] ||
				a[0] == cube[0] && abs(a[1]-cube[1]) == 1 && a[2] == cube[2] ||
				a[0] == cube[0] && a[1] == cube[1] && abs(a[2]-cube[2]) == 1)
				res -= 2;
		cubes.push_back(cube);
	}

	in.close();
	cout << res << endl; // 4322

	return 0;
}