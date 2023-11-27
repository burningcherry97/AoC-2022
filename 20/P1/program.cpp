#include <fstream>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    list<int> file;
    vector<list<int>::iterator> original_ptrs;

    ifstream in{"input.txt"};

    int n;
    while (!in.eof()) {
        in >> n;
        file.push_back(n);
    }
    in.close();

    for (auto it = file.begin(); it != file.end(); ++it)
        original_ptrs.push_back(it);

    for (auto it : original_ptrs) {
        int n = *it;
        int moves = abs(n)%(file.size()-1);
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

    int res = 0;
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

    cout << res; // 5962
}