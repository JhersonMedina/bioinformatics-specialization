#include "Utilities.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    int n; cin >> n;
    Matrix d(n, vector<T> (n));
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) cin >>d[i][j];
    for(Cluster& i : HierarchialClustering(d, n)) printCluster(i);
    return 0;
}
