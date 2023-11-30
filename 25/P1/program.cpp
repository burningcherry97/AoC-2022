#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char** argv) {

    fstream in{"input.txt"};
    string line;
    long long int res = 0;

    while (!in.eof()) {
        in >> line;
        stringstream ss{line};
        long long int n = 0; char c;
        
        for (char c : line) {
            n *= 5;
            if ('0' <= c && c <= '2')
                n += c - '0';
            if (c == '-')
                n -= 1;
            if (c == '=') 
                n -= 2;
        }
        res += n;
    }

    int n_glyphs = 1;
    while (pow(5,n_glyphs)/2 < res) {
        ++ n_glyphs;
    }

    long long int S = 0;
    for (int i = 0; i < n_glyphs; ++i) {
        S += 2 * pow(5,i);
    }

    for (int i = n_glyphs; i > 0; --i) {
        long long int R = S - res;
        long long int R_part = R/pow(5, i-1);
        S -= R_part*pow(5, i-1);
        if (R_part == 4)
            cout << '=';
        else if (R_part == 3)
            cout << '-';
        else
            cout << 2-R_part;
    }

    // result: 20-1-0=-2=-2220=0011

    return 0;
}