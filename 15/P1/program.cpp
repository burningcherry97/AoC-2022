// can be done faster using algorithms for overlapping ranges like in part 2

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
	if (x == s.bx && y == s.by)
		return false;
	if (abs(x-s.x) + abs(y-s.y) <= s.distance)
		return true;
	return false;
}

int main(int argc, char const *argv[])
{
	FILE* input = fopen("input.txt", "r");
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

	int res = 0;
	for (int x = xmin; x <= xmax; ++x) {
		if (any_of(sensors.begin(), sensors.end(), [=](sensor& s){ return in_range(x, 2000000, s); }))
			++res;
	}

	cout << res << endl;

	return 0;
}