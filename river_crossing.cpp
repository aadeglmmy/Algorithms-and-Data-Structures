#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <array>
#include <cstdio>
#include <ios>
#include <iostream>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::freopen("input.txt", "r", stdin);
	std::freopen("output.txt", "w", stdout);

	short n;
	std::cin >> n;

	std::array<int, 1000> a;
	std::array<int, 1000> b;
	std::array<int, 1000> timeOfCycle;

	short fullCycle = 1;

	for (short i = 0; i < n; ++i) {
		std::cin >> a[i] >> b[i];
		timeOfCycle[i] = a[i] + b[i];

		if (fullCycle < 2520) {
			fullCycle = std::lcm(fullCycle, timeOfCycle[i]);
		}
	}

	std::queue<std::pair<short, short>> islandsToVisit;
	short currTime = 1;
	std::vector<bool> visited(n, false);
	std::pair<short, short> island;
	bool found = false;
	bool visitedFirstIsland = false;

	islandsToVisit.push({ -1, 0 });

	while (islandsToVisit.empty() == false && found == false && currTime <= fullCycle) {
		island = islandsToVisit.front();
		islandsToVisit.pop();

		if (currTime < island.second + 1) {
			++currTime;
			std::fill(visited.begin(), visited.end(), false);
			visitedFirstIsland = false;
		}

		for (int i = island.first - 5; i <= island.first + 5; ++i) {
			if (i >= 0 && i < n && visited[i] == false && island.second % timeOfCycle[i] < a[i] && island.second + 1 < fullCycle) {
				islandsToVisit.push({ i, island.second + 1 });
				visited[i] = true;
			}
			else if (i == -1 && visitedFirstIsland == false && island.second + 1 < fullCycle) {
				islandsToVisit.push({ -1, island.second + 1 });
				visitedFirstIsland = true;
			}
			else if (i == n) {
				found = true;

				break;
			}
		}
	}

	if (found == true) {
		std::cout << currTime << '\n';
	}
	else {
		std::cout << "No\n";
	}

	return 0;
}
