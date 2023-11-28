#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

enum direction {right = 0, below, left, above};

struct Tile {
    char tile = ' ';

    Tile(char tile) {
        this->tile = tile;
    }

    Tile() {
        ;
    }
};

tuple<int,int,int> jump(int x, int y, int d) {
    int xn, yn, dn;
    // cout << "called jump(). x: " << x << " y: " << y << " d: " << d << endl;
    if (x == 51 && 51 <= y && y <= 100 && d == 2) { // 1
        xn = y - 50; yn = 101; dn = 1;
        return {xn,yn,dn};
    }
    if (1 <= x && x <= 50 && y == 101 && d == 3) {
        xn = 51; yn = x + 50; dn = 0;
        return {xn,yn,dn};
    }
    if (x == 51 && 1 <= y && y <= 50 && d == 2) { // 2 
        xn = 1; yn = 151 - y; dn = 0;
        return {xn,yn,dn};
    }
    if (x == 1 && 101 <= y && y <= 150 && d == 2) {
        xn = 51; yn = 151 - y; dn = 0;
        return {xn,yn,dn};
    }
    if (51 <= x && x <= 100 && y == 1 && d == 3) { // 3
        xn = 1; yn = x + 100; dn = 0;
        return {xn,yn,dn};
    }
    if (x == 1 && 151 <= y && y <= 200 && d == 2) {
        xn = y - 100; yn = 1; dn = 1;
        return {xn,yn,dn};
    }
    if (101 <= x && x <= 150 && y == 1 && d == 3) { // 4
        xn = x - 100; yn = 200; dn = 3;
        return {xn,yn,dn};
    }
    if (1 <= x && x <= 50 && y == 200 && d == 1) {
        xn = x + 100; yn = 1; dn = 1;
        return {xn,yn,dn};
    }
    if (51 <= x && x <= 100 && y == 150 && d == 1) { // 5 
        xn = 50; yn = x + 100; dn = 2;
        return {xn,yn,dn};
    }
    if (x == 50 && 151 <= y <= 200 && d == 0) {
        xn = y - 100; yn = 150; dn = 3;
        return {xn,yn,dn};
    }
    if (101 <= x && x <= 150 && y == 50 && d == 1) { // 6 
        xn = 100; yn = x - 50; dn = 2;
        return {xn,yn,dn};
    }
    if (x == 100 && 51 <= y && y <= 100 && d == 0) {
        xn = y + 50; yn = 50; dn = 3;
        return {xn,yn,dn};
    }
    if (x == 150 && 1 <= y && y <= 50 && d == 0) { // 7
        xn = 100; yn = 151 - y; dn = 2;
        return {xn,yn,dn};
    }
    if (x == 100 && 101 <= y && y <= 150 && d == 0) {
        xn = 150; yn = 151 - y; dn = 2;
        return {xn,yn,dn};
    }
    cout << x << ' ' << y << ' ' << d << " ERROR" << endl;
    exit(0);
}

int main(int argc, char** argv) {

    fstream in{"../P1/input.txt"};
    int x = 1, y = 1;
    char tile; string line;
    map<pair<int,int>,Tile> path;

    while (!in.eof()) {
        getline(in, line);
        if (line == "")
            break;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] != ' ')
                path[{x,y}] = Tile(line[i]);
            ++x;
        }
        x = 1;
        ++y;
    }

    x = y = 1;
    while (path.find({x,y}) == path.end()) ++x;
    // cout << x << ' ' << y << endl; return 0;
    getline(in, line);
    stringstream ss{line};

    int dist = 0; char dir;
    int direction = 0;
    Tile* ptr = &path[{x,y}];
    while (!ss.eof()) {
        ss >> dist;
        ss >> dir;
        // cout << x << ' ' << y << ' ' << direction << ' ' << dist <<  ' ' << dir << endl;
        for (int i = 0; i < dist; ++i) {
            // cout << x << ' ' << y << ' ' << direction << endl;
            switch (direction)
            {
            case 0:
                if (path.find({x+1,y}) != path.end()) {
                    if (path[{x+1,y}].tile == '.') {
                        ++x;
                    }
                } else {
                    int x_mem = x, y_mem = y, direction_mem = direction;
                    tie(x,y,direction) = jump(x,y,direction);
                    if (path[{x,y}].tile == '#') {
                        x = x_mem;
                        y = y_mem;
                        direction = direction_mem;
                    }
                }
                break;
            case 1:
                if (path.find({x,y+1}) != path.end()) {
                    if (path[{x,y+1}].tile == '.') {
                        ++y;
                    }
                } else {
                    int x_mem = x, y_mem = y, direction_mem = direction;
                    tie(x,y,direction) = jump(x,y,direction);
                    if (path[{x,y}].tile == '#') {
                        x = x_mem;
                        y = y_mem;
                        direction = direction_mem;
                    }
                }
                break;
            case 2:
                if (path.find({x-1,y}) != path.end()) {
                    if (path[{x-1,y}].tile == '.') {
                        --x;
                    }
                } else {
                    int x_mem = x, y_mem = y, direction_mem = direction;
                    tie(x,y,direction) = jump(x,y,direction);
                    if (path[{x,y}].tile == '#') {
                        x = x_mem;
                        y = y_mem;
                        direction = direction_mem;
                    }
                }
                break;
            case 3:
                if (path.find({x,y-1}) != path.end()) {
                    if (path[{x,y-1}].tile == '.') {
                        --y;
                    }
                } else {
                    int x_mem = x, y_mem = y, direction_mem = direction;
                    tie(x,y,direction) = jump(x,y,direction);
                    if (path[{x,y}].tile == '#') {
                        x = x_mem;
                        y = y_mem;
                        direction = direction_mem;
                    }
                }
                break;
            
            default:
                break;
            }
        }
        if (!ss.eof()) {
            if (dir == 'R') {
                direction = (direction + 1) % 4;
            }
            if (dir == 'L') {
                direction = (direction + 3) % 4;
            }
        }
        // cout << x << ' ' << y << ' ' << direction << endl;
    }
    cout << x * 4 + y * 1000 + direction; // 143208
}