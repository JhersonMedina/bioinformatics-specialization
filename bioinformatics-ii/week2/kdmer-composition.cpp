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

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	string s; cin >> s;
	vector <pair<string, string>> ans;
	int k=3,d=2, n = s.size();
	for(int i=0; i+2*k+d-1<n; i++) {
		string a = s.substr(i, k), b = s.substr(i + k + d, k);
		ans.pb(mp(a, b));
	}
	sort(ALL(ans));
	for(auto&it : ans) {
		cout << "(" << it.fi << "|" << it.se<<")" << ' ';
	}
	return 0;
}
