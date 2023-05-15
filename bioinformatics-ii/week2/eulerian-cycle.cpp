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
const int maxn = 1e5 + 10;
int in[maxn], out[maxn];
bool vis[maxn];
vector <int> euler;
vector <int> graph[maxn], taken[maxn]; 
void dfs(int u) {
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
	string s; 
	while (getline(cin, s)) {
		if (s.empty()) break;
		int i = 0;
		while (s[i] != ':') i++;
		int u = stoi(s.substr(0, i));
		for (i += 2; i < s.size();) {
			int j = i;
			while (j < s.size() && isdigit(s[j])) j++;
			int v = stoi(s.substr(i, j - i));
			graph[u].push_back(v);
			out[u]++; in[v]++;
			j++;
			i = j;
		}
	}
	vector <int> roots;
	for (int i = 0; i < maxn; i++) {
		if (in[i] != out[i]) roots.push_back(i);
		taken[i].assign(graph[i].size(), 0);
	}
	int root = 0;
	for (int&i : roots) {
		if (out[i] - 1 == in[i]) root = i;
	}

	dfs(root);
	reverse(euler.begin(), euler.end());
	for (int& i : euler) cout << i << ' ';
	cout << endl;
	return 0;
}
