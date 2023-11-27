#include <list>
#include <iostream>

using namespace std;

int main() {
    list<long long int> file;
    // 0, -2434767459, 3246356612, -1623178306, 2434767459, 1623178306, 811589153
    file.push_back(0);
    file.push_back(-2434767459);
    file.push_back(3246356612);
    file.push_back(-1623178306);
    file.push_back(2434767459);
    file.push_back(1623178306);
    file.push_back(811589153);    
    auto it = file.begin();
    for (int i = 0; i < 6; ++i)
        ++it;
    // cout << *it;
    for (auto a : file) cout << a << ' '; cout << endl;
    auto pos = file.erase(it);
    for (auto a : file) cout << a << ' '; cout << endl;
    if (pos == file.end())
        pos = file.begin();
    cout << *pos;
}