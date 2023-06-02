// Too many mind, no mind.
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

#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define COMP(x) sort(ALL(x)); x.resize(unique(ALL(x)) - (x).begin())
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)

using pii = pair <int, int>;
using vi = vector <int>;
using vpi = vector <pii>;
using ll = long long;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using ld = long double;
using vld = vector<ld>;

const int maxn = 1e5;
char ans[maxn];
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int k, d; cin >> k >> d;
	string t; 
	vector<string> s;
	while (cin >> t) {
		s.pb(t);
	}
	memset(ans, '\0', sizeof(ans));
	forn(i, s.size()) {
		string x = s[i].substr(0, k), y = s[i].substr(k + 1);
		forn(j, k) {
			ans[i+j] = x[j];
			ans[i+k+d+j] = y[j];
		}
	}
	cout << ans << endl;

	return 0;
}
