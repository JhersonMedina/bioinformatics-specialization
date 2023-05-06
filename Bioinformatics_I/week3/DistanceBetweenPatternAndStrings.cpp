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
const int oo = 1e9;
int hammingDistance(string s, string t) {
	int distance = 0;
	for (int i = 0; i < s.size(); i++) distance += s[i] != t[i];
	return distance;
}
int findDistance (string& pattern, string& text) {
	int best = oo;
	for (int i = 0; i + pattern.size() - 1 < text.size(); i++) {
		best = min(best, hammingDistance(pattern, text.substr(i, pattern.size())));
	}
	return best;
}
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	string pattern, input; cin >> pattern;
	vector <string> dna;
	while (cin >> input) dna.push_back(input);

	int ans = 0;
	for (string& s : dna) ans += findDistance(pattern, s);
	cout << ans << '\n';
	return 0;
}
