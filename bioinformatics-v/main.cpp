#include "Utilities.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    int k, m, n = 1005-1; cin >> k >> m;
    vector<pt> p(n), c(k);
    for(int i=0; i<n; ++i) p[i] = ptRead(m);
    //for(int i=0; i<k; ++i) c[i] = ptRead(m);
    vector<pt> r = lloydAlgorithm(p, k);
    printSet(r);

   // cout << squareErrorDistortion(p, c) << ' ' << squareErrorDistortion(p, r) << endl;
    return 0;
}
