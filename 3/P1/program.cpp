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
	fstream in{"input.txt"};
	int res = 0;
	string rucksack, errors;
	while (getline(in, rucksack)) {
		int size = rucksack.size();
		// can be optimized if we care
		sort(rucksack.begin(), rucksack.begin() + size/2);
		sort(rucksack.begin() + size/2, rucksack.begin() + size);
		set_intersection(rucksack.begin(), rucksack.begin() + size/2,
						 rucksack.begin() + size/2, rucksack.begin() + size,
						 back_inserter(errors));
		res += priority(errors.back());
	}

	cout << res << endl;

	return 0;
}