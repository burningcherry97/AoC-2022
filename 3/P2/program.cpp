#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int priority (char error) {
	if (error >= 'a')
		return error - 'a' + 1;
	else
		return error - 'A' + 27;
}

int main(int argc, char const *argv[])
{
	fstream in{"../P1/input.txt"};
	int res = 0;
	string first, second, third, common1, common2;
	while (getline(in, first)) {
		getline(in, second);
		getline(in, third);
		sort(first.begin(), first.end());
		sort(second.begin(), second.end());
		sort(third.begin(), third.end());
		common1 = common2 = "";
		set_intersection(first.begin(), first.end(),
						 second.begin(), second.end(),
						 back_inserter(common1));
		set_intersection(common1.begin(), common1.end(),
						 third.begin(), third.end(),
						 back_inserter(common2));
		res += priority(common2.back());
	}

	cout << res << endl;

	return 0;
}