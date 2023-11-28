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

int main(int argc, char** argv) {

    fstream in{"test_input.txt"};
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
    getline(in, line);
    stringstream ss{line};

    int dist = 0; char dir;
    int direction = 0;
    Tile* ptr = &path[{x,y}];
    while (!ss.eof()) {
        ss >> dist;
        ss >> dir;
        // cout << dist <<  ' ' << dir << endl;
        for (int i = 0; i < dist; ++i) {
            switch (direction)
            {
            case 0:
                if (path.find({x+1,y}) != path.end()) {
                    if (path[{x+1,y}].tile == '.') {
                        ++x;
                    }
                } else {
                    int x_mem = x, y_mem = y, direction_mem = direction;
                    while (path.find({x-1,y}) != path.end()) {
                        --x;
                    }
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
                    int y_mem = y;
                    while (path.find({x,y-1}) != path.end()) {
                        --y;
                    }
                    if (path[{x,y}].tile == '#')
                        y = y_mem;
                }
                break;
            case 2:
                if (path.find({x-1,y}) != path.end()) {
                    if (path[{x-1,y}].tile == '.') {
                        --x;
                    }
                } else {
                    int x_mem = x;
                    while (path.find({x+1,y}) != path.end()) {
                        ++x;
                    }
                    if (path[{x,y}].tile == '#')
                        x = x_mem;
                }
                break;
            case 3:
                if (path.find({x,y-1}) != path.end()) {
                    if (path[{x,y-1}].tile == '.') {
                        --y;
                    }
                } else {
                    int y_mem = y;
                    while (path.find({x,y+1}) != path.end()) {
                        ++y;
                    }
                    if (path[{x,y}].tile == '#')
                        y = y_mem;
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
    cout << x * 4 + y * 1000 + direction; // 36518
}