#include <iostream>
#include "Utilities.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    int n = iread()[0];
    Matrix d(n, vector<int>(n));
    for(int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) cin >> d[i][j];
    }
    cout << limbLength(d, 0) << endl;
    return 0;
}
