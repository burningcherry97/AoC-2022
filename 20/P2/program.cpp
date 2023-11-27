#include <fstream>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    list<long long int> file;
    vector<list<long long int>::iterator> original_ptrs;

    ifstream in{"../P1/input.txt"};

    long long int n;
    while (!in.eof()) {
        in >> n;
        n *= 811589153;
        file.push_back(n);
    }
    in.close();

    for (auto it = file.begin(); it != file.end(); ++it)
        original_ptrs.push_back(it);

    for (int j = 0; j < 10; ++j) {
        for (auto& it : original_ptrs) {
            long long int n = *it;
            long long int moves = abs(n)%(file.size()-1);
            if (n > 0) {
                auto pos = file.erase(it);
                for (int i = 0; i < moves; ++i) {
                    if (pos == file.end())
                        pos = file.begin();
                    ++pos;
                }
                it = file.insert(pos, n);
            }
            if (n < 0) {
                auto pos = file.erase(it);
                for (int i = 0; i < moves; ++i) {
                    if (pos == file.begin())
                        pos = file.end();
                    --pos;
                }
                it = file.insert(pos, n);
            }
        }
    }

    long long int res = 0;
    auto it = file.begin();
    while (*it != 0)
        ++it;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 1000; ++j) {
            if (it == file.end())
                it = file.begin();
            ++it;
        }
        res += *it;
    }

    cout << res; // 9862431387256
}