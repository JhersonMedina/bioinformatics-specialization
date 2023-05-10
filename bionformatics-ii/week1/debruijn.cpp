#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <array>
#include <iomanip>

using namespace std;
/* *
 *
 * Too many mind, no mind.
 *
 * */

void debruijn(string s, int k) {
	map <string, vector <string>> graph;
	for (int i = 0; i + k - 1 < s.size(); i++) {
		string from = s.substr(i, k - 1);
		string to = s.substr(i + 1, k - 1);
		graph[from].push_back(to);
	}
	for (auto& u: graph) {
		cout << u.first << ": ";
		for (auto& v : u.second) cout << v << ' ';
		cout << '\n';
	}
}
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int k; cin >> k;
	string s; cin >> s;
	debruijn(s, k);
	return 0;
}
