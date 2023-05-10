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
vector <string> patterns;
vector <string> ans;
char alp[4] = {'A', 'T', 'C', 'G'};
int k, best = 1e9;
int missmatch(string& s, string&& t){
	int miss = 0;
	for (int i = 0; i < s.size(); i++) miss += s[i] != t[i];
	return miss;
}
int distance(string s) {
	int ans = 0;
	for (string t : patterns) {
		int best = 1e9;
		for (int i = 0; i + k - 1 < t.size(); i++) {
			best = min(best, missmatch(s, t.substr(i, k)));
		}
		ans += best;
	}
	return ans;
}
void generate(int i, string& s) {
    if (i >= k) {
		int cur = distance(s);
		if (best > cur) ans.clear();
		best = min(cur, best);
		if (best == cur) ans.push_back(s);
        return;
    }
 
    for (int j = 0; j < 4; j++) {
         s.push_back(alp[j]);
         generate(i + 1, s);
         s.pop_back();
      }
 }
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> k;
	string t; 
	while (cin >> t) patterns.push_back(t);
	t = "";

	generate(0, t);
	for (string& s : ans) cout << s << ' ' << endl;

	return 0;
}
