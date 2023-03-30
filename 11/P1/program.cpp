#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class monkey {
public:
	list<long long int> items{};
	int test_arg;
	int target_true;
	int target_false;
	int op_mode;
	int op_arg;
	int business;

	// bool inspect() {
	// 	return true;
	// }

	monkey(istream& in) {
		string line, dummy; istringstream is; int n; char c;
		getline(in, line);
		getline(in, line);
		is = istringstream{line};
		is >> dummy;
		while (!is.eof()) {
			is >> dummy;
			is >> n;
			items.push_back(n);
		}
		getline(in, line);
		is = istringstream{line};
		is >> dummy >> dummy >> dummy >> dummy;
		is >> c;
		if (c == '+') {
			op_mode = 0;
			is >> op_arg;
		} else {
			is.get();
			if (is.peek() == 'o') {
				op_mode = 1;
				is >> dummy;
			} else {
				op_mode = 2;
				is >> op_arg;
			}
		}
		getline(in, line);
		is = istringstream{line};
		is >> dummy >> dummy >> dummy >> test_arg;
		getline(in, line);
		is = istringstream{line};
		is >> dummy >> dummy >> dummy >> dummy >> dummy >> target_true;
		getline(in, line);
		is = istringstream{line};
		is >> dummy >> dummy >> dummy >> dummy >> dummy >> target_false;
		getline(in, line);
		business = 0;
	}
};

int main(int argc, char const *argv[])
{
	ifstream in{"input.txt"};
	vector<monkey> monkeys{};
	while (!in.eof()) { 
		monkeys.push_back(monkey{in});
	}

	for (int it = 0; it < 20; ++it) {
		for (monkey& m : monkeys) {
			// cout << count++ << ":::\n";
			while (!m.items.empty()) {
				long long int i = m.items.front();
				long long int j = i;
				++m.business;
				switch (m.op_mode) {
				case 0:
					i += m.op_arg;
					break;
				case 1:
					i *= i;
					break;
				case 2:
					i *= m.op_arg;
					break;
				}
				i /= 3;
				// cout << "Throwing " << i << " (formerly " << j << ") to ";
				if (i%m.test_arg) {
					// cout << m.target_false;
					monkeys[m.target_false].items.push_back(i);
				} else {
					// cout << m.target_true;
					monkeys[m.target_true].items.push_back(i);
				}
				// cout << "." << endl;
				m.items.pop_front();
			}
		}
	}

	vector<int> business{};
	for (monkey& m : monkeys) {
		business.push_back(m.business);
	}
	sort(business.begin(), business.end(), greater<int>{});

	cout << business[0] * business[1];
	cout << endl;

	return 0;
}