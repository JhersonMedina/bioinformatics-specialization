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

const int maxn = 1e5 + 10;
int in[maxn], out[maxn];
bool vis[maxn];
vector <int> euler;
vector <int> graph[maxn], taken[maxn]; 
void dfs(int u) {
	//cout << u << endl;
	for (int i = 0; i < graph[u].size(); i++) {
		if (taken[u][i]) continue;
		int v = graph[u][i];
		taken[u][i] = 1;
		dfs(v);
	}
	euler.push_back(u);
}
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int m; cin >> m;
	vector <string> patterns;
	string s;
	while (cin >> s) patterns.push_back(s);
	int n = patterns.size();

	forn(i, n) cin >> patterns[i];
	forn(i, n) {
		forn(j, n) if (i!= j) {
			if (patterns[i].substr(1) == patterns[j].substr(0, m-1)) {
				graph[i].pb(j);
				out[i]++, in[j]++;
				//cout << patterns[i] << ' ' << patterns[j] << endl;
				//cout << i << ' ' << j << endl;
			}
		}
	}
	vi roots;
	forn(i, n) {
		if (in[i] != out[i]) roots.pb(i);
		taken[i].assign(graph[i].size(), 0);
	}
	int root = 0;
	for (int& i : roots) {
		if (out[i] - 1 == in[i]) root = i;
	}
	dfs(root);
	reverse(ALL(euler));
	cout << patterns[euler[0]];
	fore(i, 1, euler.size()-1) cout << patterns[euler[i]][m-1];
	cout << endl;
	return 0;
}

