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

void overlap(vector <string> patterns) {
	for (string& s : patterns) {
		vector <string> edges;

		for (string& t : patterns) {
			if (t == s) continue;
			if (s.substr(1) == t.substr(0, t.size() - 1)) edges.push_back(t);
		}
		if (edges.empty()) continue;
		cout << s << ": ";
		for (string& t : edges) cout << t << ' ';
		cout << '\n';
	}
}
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	string s;
	vector <string> patterns;
	while (cin >> s) patterns.push_back(s);
	overlap(patterns);
	return 0;
}
