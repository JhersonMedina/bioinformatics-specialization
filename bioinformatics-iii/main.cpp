#include <iostream>
#include "Utilities.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> dag(m+1);
    int u, v, w;
    while (cin >> u >> v >> w) {
        dag[u].push_back({v, w});
    }
    vector<int> ans = longestPathInDag(n, m, dag);
    cout << ans[0] << endl;
    for(int i=1; i<(int)ans.size(); ++i) cout << ans[i] << ' ';
    return 0;
}
