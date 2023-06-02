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

const int maxn = 1e6;
int nodes=0;
char ans[maxn];
int vis[maxn], in[maxn], out[maxn];
string s[maxn];
map<string, int> id;
vi graph[maxn];
vector <string> contigs;
void print(vi& path) {
	memset(ans, '\0', sizeof(ans));
	vector <string> t;
	for(int &i : path) {
		vis[i]=1;
		t.pb(s[i]);
	}

	forn(i, t.size()) {
		string x = t[i];
		forn(j, x.size()) {
			ans[i+j] = x[j];
		}
	}
	contigs.pb(ans);
}
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n; string t;
	while (cin >> t) {
		n = t.size();
		string a = t.substr(0, n-1), b = t.substr(1);
		int u = id.count(a) ? id[a] : nodes++;
		int v = id.count(b) ? id[b] : nodes++;

		id[a]=u, id[b]=v;
		s[u]=a, s[v]=b;

		graph[u].pb(v);
		out[u]++, in[v]++;
	}

	forn(i, nodes) {
		if ((in[i] == 1 && out[i] == 1) || !out[i]) continue;
		for(int&v : graph[i]) {
			vi path; path.pb(i);
			int w = v;
			while (in[w] == 1 && out[w] ==1) {
				path.pb(w);
				w = graph[w][0];
			}
			path.pb(w);
			print(path);
		}
	}

	forn(i, nodes) {
		if (vis[i] || (in[i]!=1 || out[i]!=1)) continue;
		int u = i;
		vi path;
		do {
			vis[u]=1;
			path.pb(u);
			u = graph[u][0];
		} while (u != i);
		path.pb(u);
		print(path);
	}
	sort(ALL(contigs));
	for(string& s : contigs) cout << s << ' '; 
	return 0;
}
