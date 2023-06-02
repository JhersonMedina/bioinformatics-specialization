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
int nodes=0;
int in[maxn], out[maxn];
bool vis[maxn];
vi graph[maxn], path;
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	string s;
	while (getline(cin, s)) {
		string t;
		int i=0;
		while(s[i]!=':') {
			t += s[i];
			i++;
		}
		int u = stoi(t);
		for(i+=2, t=""; i<s.size(); i++) {
			if (s[i]==' ') {
				int v = stoi(t);
				graph[u].pb(v);
				out[u]++, in[v]++;
				t="";
			} else t += s[i];
		}
		if (t.size()){
			int v = stoi(t);
			graph[u].pb(v);
			out[u]++, in[v]++;
		}
		nodes=max(nodes, u);
	}

	fore(i, 1, nodes) {
		if ((in[i] == 1 && out[i] == 1) || !out[i]) continue;
		for(int&v : graph[i]) {
			vi path = {i};
			int w = v;
			while (in[w] == 1 && out[w] ==1) {
				path.pb(w);
				w = graph[w][0];
			}
			path.pb(w);
			for(int& j : path) {
				vis[j]=1;
				cout << j << ' '; 
			}
			cout << endl;
		}
	}
	fore(i, 1, nodes) {
		if (vis[i] || (in[i]!=1 || out[i]!=1)) continue;
		int u = i;
		do {
			vis[u]=1;
			cout << u << ' ';
			u = graph[u][0];
		} while (u != i);
		cout << u << endl;
	}

	return 0;
}
