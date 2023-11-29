#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Tile {
    char content;
    int incoming;
    bool valid_target = false;

    Tile(char c) {
        content = c;
        incoming = 0;
    }

    Tile() {
        ;
    }
};

struct Elf {
    int x, target_x;
    int y, target_y;

    static const int directions[4][3][2];
    static const int surrounding[8][2];
    static int round;

    void expand(map<pair<int,int>,Tile>& grove, int x, int y) {
        if (grove.find({x,y}) == grove.end()) {
            grove[{x,y}] = Tile('.');
        }
    }

    void determine_next_step(map<pair<int,int>,Tile>& grove) {
        string dir = "";
        for (int i = 0; i < 4; ++i) {
            bool flag = false;
            for (int j = 0; j < 3; ++j) {
                int xx = x + directions[(i+round)%4][j][0];
                int yy = y + directions[(i+round)%4][j][1];
                expand(grove, xx, yy);
                if (grove[{xx, yy}].content == '#') {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                dir += "NSWE"[(i+round)%4];
            }
        }
        if (dir == "" || dir.length() == 4) {
            target_x = x;
            target_y = y;
        } else switch (dir[0])
        {
        case 'N':
            target_x = x;
            target_y = y-1;
            break;

        case 'S':
            target_x = x;
            target_y = y+1;
            break;

        case 'W':
            target_x = x-1;
            target_y = y;
            break;

        case 'E':
            target_x = x+1;
            target_y = y;
            break;

        default:
            break;
        }
        ++grove[{target_x,target_y}].incoming;
        // cout << x << ' ' << y << ' ' << dir << endl;
    }

    Elf(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Elf() {}
};

const int Elf::directions[4][3][2] = {{{-1,-1}, {0,-1}, {1,-1}},
                                      {{-1,1}, {0,1}, {1,1}},
                                      {{-1,-1}, {-1,0}, {-1,1}},
                                      {{1,-1}, {1,0}, {1,1}}
                                      };
const int Elf::surrounding[8][2] = {{-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}};
int Elf::round = 0;

int main(int argc, char** argv) {

    fstream in{"input.txt"};
    string line; char c;
    int x = 0, y = 0;
    map<pair<int,int>,Tile> grove;
    vector<Elf> elves;

    while (!in.eof()) {
        getline(in, line);
        for (char c : line) {
            grove[{x,y}] = Tile(c);
            if (c == '#') {
                elves.emplace_back(x,y);
            }
            ++x;
        }
        x = 0;
        ++y;
    }

    for (int i = 0; i < atoi(argv[1]); ++i) {
        for (auto& a : grove) {
            a.second.incoming = 0;
            a.second.valid_target = false;
        }
        for (Elf& e : elves) {
            e.determine_next_step(grove);
        }
        for (auto& a: grove) {
            if (a.second.incoming == 1) {
                a.second.valid_target = true;
            }
        }
        for (Elf& e : elves) {
            if (grove[{e.target_x, e.target_y}].valid_target) {
                grove[{e.x, e.y}].content = '.';
                e.x = e.target_x;
                e.y = e.target_y;
                grove[{e.target_x, e.target_y}].content = '#';
            }
        }
        ++Elf::round;
    }

    int x_min = 0, x_max = 0, y_min = 0, y_max = 0;
    for (auto& a : grove) {
        if (a.second.content == '.')
            continue;
        x_min = min(x_min, a.first.first);
        x_max = max(x_max, a.first.first);
        y_min = min(y_min, a.first.second);
        y_max = max(y_max, a.first.second);
    }

    // cout << x_min << ' ' << x_max << ' ' << y_min << ' ' << y_max << endl;

    // for (int i = x_min; i <= x_max; ++i) {
    //     for (int j = y_min; j <= y_max; ++j) {
    //         if (grove.find({j,i}) == grove.end()) 
    //             cout << '.';
    //         else
    //             cout << grove[{j,i}].content;
    //     }
    //     cout << endl;
    // }

    cout << (x_max - x_min + 1) * (y_max - y_min + 1) - elves.size() << endl; // 4116

    return 0;
}