// This one is unfinished and runs in a horrible time. It's Sunday 11 PM, I leave this where it is.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Blueprint 1:
//   Each ore robot costs 4 ore.
//   Each clay robot costs 2 ore.
//   Each obsidian robot costs 3 ore and 14 clay.
//   Each geode robot costs 2 ore and 7 obsidian.

int ore_robot_cost_ore = 4;
int clay_robot_cost_ore = 2;
int obsidian_robot_cost_ore = 3;
int obsidian_robot_cost_clay = 14;
int geode_robot_cost_ore = 2;
int geode_robot_cost_obsidian = 7;

// int max_total = 0;

int process(int ore_robot,
			int clay_robot,
			int obsidian_robot,
			int geode_robot,
			// int ore_robot_cost_ore,
			// int clay_robot_cost_ore,
			// int obsidian_robot_cost_ore,
			// int obsidian_robot_cost_clay,
			// int geode_robot_cost_ore,
			// int geode_robot_cost_obsidian,
			int ore,
			int clay,
			int obsidian,
			int geode,
			int time,
			int max_total) {
	vector<int> results;
	if (time == 1) {
		geode += geode_robot;
		if (geode > max_total)
			max_total = geode;
		return geode;
	}

	if (geode + geode_robot * time < max_total)
		return 0;

	if (ore >= geode_robot_cost_ore && obsidian >= geode_robot_cost_obsidian) {
		return process(ore_robot, clay_robot, obsidian_robot, geode_robot + 1, 
			ore - geode_robot_cost_ore + ore_robot, clay + clay_robot, obsidian - geode_robot_cost_obsidian + obsidian_robot, geode + geode_robot, time - 1, max_total);
	}
	vector<int> costs;
	if (ore >= ore_robot_cost_ore && (ore_robot < ore_robot_cost_ore || ore_robot < clay_robot_cost_ore || ore_robot < obsidian_robot_cost_ore || ore_robot < geode_robot_cost_ore))
		results.push_back(process(ore_robot + 1, clay_robot, obsidian_robot, geode_robot, 
			ore - ore_robot_cost_ore + ore_robot, clay + clay_robot, obsidian + obsidian_robot, geode + geode_robot, time - 1, max_total));
	if (ore >= clay_robot_cost_ore && clay_robot < obsidian_robot_cost_clay)
		results.push_back(process(ore_robot, clay_robot + 1, obsidian_robot, geode_robot, 
			ore - clay_robot_cost_ore + ore_robot, clay + clay_robot, obsidian + obsidian_robot, geode + geode_robot, time - 1, max_total));
	if (ore >= obsidian_robot_cost_ore && clay >= obsidian_robot_cost_clay && obsidian_robot < geode_robot_cost_obsidian) {
		results.push_back(process(ore_robot, clay_robot, obsidian_robot + 1, geode_robot, 
			ore - obsidian_robot_cost_ore + ore_robot, clay - obsidian_robot_cost_clay + clay_robot, obsidian + obsidian_robot, geode + geode_robot, time - 1, max_total));
	}
	// if (results.empty())
		results.push_back(process(ore_robot, clay_robot, obsidian_robot, geode_robot, 
			ore + ore_robot, clay + clay_robot, obsidian + obsidian_robot, geode + geode_robot, time - 1, max_total));
	int res = *max_element(results.begin(), results.end());
	// if (res > max_total)
	// 	max_total = res;
	return res;
}


int main(int argc, char const *argv[]) {

	cout << process(1,0,0,0,0,0,0,0,atoi(argv[1]), 0) << endl;

	return 0;
}