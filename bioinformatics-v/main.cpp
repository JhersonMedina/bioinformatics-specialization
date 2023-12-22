#include "Utilities.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    int k, m, n = 1313-2; cin >> k >> m;
    T beta; cin >> beta;

    vector<pt> p(n), c(k);
    for(int i=0; i<n; ++i) p[i] = ptRead(m);
    vector<pt> r = softKMeans(p, k, m, beta);
    printSet(r);
    return 0;
}
