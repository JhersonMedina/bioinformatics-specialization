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
int in[maxn], out[maxn];
string s[maxn];
map<string, int> id;
vi euler;
vi graph[maxn];
void dfs(int u) {
	while(graph[u].size()) {
		int v = graph[u].back(); 
		graph[u].pop_back();
		dfs(v);
	}
	euler.pb(u);
}
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int k, d; cin >> k >> d;
	string t;
	while (cin >> t) {
		string a = t.substr(0, k), b = t.substr(k + 1);
		string x = a.substr(0, k-1) + b.substr(0, k-1);
		string y = a.substr(1) + b.substr(1);
		int u = id.count(x) ? id[x] : nodes++;
		int v = id.count(y) ? id[y] : nodes++;

		id[x]=u, id[y]=v;
		s[u]=x, s[v]=y;

		graph[u].pb(v);
		out[u]++, in[v]++;
	}
	int g=-1;
	forn(i, nodes) {
		if (in[i] == out[i]) continue;
		if (out[i]-1==in[i]) g=i;
	}
	int root = g!=-1 ? g : 0;
	dfs(root);
	reverse(ALL(euler));
	//int n=euler.size();
	memset(ans, '\0', sizeof(ans));
	for (int i=0; i < euler.size(); i++) {
		string a = s[euler[i]].substr(0, k-1), b = s[euler[i]].substr(k-1);
		for(int j=0; j < a.size(); j++) ans[i+j] = a[j];
		for(int j=0; j < b.size(); j++) ans[i+j+k+d] = b[j];
	}
	cout << ans;
	//forn(i, n+2*k+d) cout << ans[i]; 
	return 0;
}
