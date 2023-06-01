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
int nodes=0;
int in[maxn], out[maxn];
string s[maxn];
map<string, int> id;
vector <int> euler, graph[maxn];
void dfs(int u) {
	while (graph[u].size()) {
		int v = graph[u].back(); graph[u].pop_back();
		dfs(v);
	}
	euler.push_back(u);
}
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int m; cin >> m;
	int n = 1<<m;

	forn(mask, 1<<m) {
		string t="";
		forn(j, m) t+= char((mask>>j&1) + '0');
		string a = t.substr(0, m-1), b = t.substr(1);
		int u = id.count(a) ? id[a] : nodes++;
		id[a] = u; s[u] = a;
 
		int v = id.count(b) ? id[b] : nodes++;
		id[b] = v, s[v] = b;

		graph[u].pb(v);
		out[u]++, in[v]++;
	}

	int g = -1;
	forn(i, n) {
		if (in[i] != out[i]) {
			if (out[i]-1==in[i]) g = i;
		}
	}
	int root = g==-1 ? 0 : g;
	dfs(root);
	reverse(ALL(euler));
	forn(i, m-1) euler.pop_back();
	cout << s[euler[0]];
	fore(i, 1, euler.size()-1) cout << s[euler[i]].back();

	return 0;
}

