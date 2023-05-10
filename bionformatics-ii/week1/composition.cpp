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

vector <string> composition (string s, int k) {
	vector <string> c;
	for (int i = 0; i + k - 1 < s.size(); i++) c.push_back(s.substr(i, k));
	return c;
}
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int k; cin >> k;
	string s; cin >> s;
	for (string& t : composition(s, k)) cout << t << ' ';
	return 0;
}
