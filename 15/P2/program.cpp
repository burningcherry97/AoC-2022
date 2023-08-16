#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

struct sensor {
	int x;
	int y;
	int bx;
	int by;
	int distance;
};

bool in_range(int x, int y, sensor& s) {
	if (abs(x-s.x) + abs(y-s.y) <= s.distance)
		return true;
	return false;
}

int main(int argc, char const *argv[])
{
	FILE* input = fopen("../P1/input.txt", "r");
	vector<sensor> sensors;
	int xmax = INT32_MIN, xmin = INT32_MAX;
	int ymax = INT32_MIN, ymin = INT32_MAX;

	while (!feof(input)) {
		sensor s;
		fscanf(input, "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d\n", &s.x, &s.y, &s.bx, &s.by);
		s.distance = abs(s.x-s.bx) + abs(s.y-s.by);
		xmax = max(max(xmax, s.x+s.distance), s.bx+s.distance);
		xmin = min(min(xmin, s.x-s.distance), s.bx-s.distance);
		ymax = max(max(ymax, s.y+s.distance), s.by+s.distance);
		ymin = min(min(ymin, s.y-s.distance), s.by-s.distance);
		sensors.push_back(s);
	}
	fclose(input);

	const int max_range = 4000000;
	for (int x = 0; x <= max_range; ++x) {
		for (int y = 0; y <= max_range; ++y) {
			bool detected = false;
			for (sensor& s : sensors) {
				if (in_range(x, y, s)) {
					y = min(max_range, s.y + s.distance-abs(x-s.x));
					detected = true;
				}
			}
			if (!detected) {
				cout << "x: " << x << " y: " << y << endl;
				return 0;
			}
		}
	}

	return 0;
}