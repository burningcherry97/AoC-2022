#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream in{"input.txt"};
    char opponent, response;
    int score_table[3][3] = {
        {3, 1, 2},
        {1, 2, 3},
        {2, 3, 1}
    };
    int score = 0;
    while (in >> opponent >> response) {
        score += score_table[opponent - 'A'][response - 'X'];
        score += (response - 'X') * 3;
    }

    cout << score << endl;

    return 0;
}