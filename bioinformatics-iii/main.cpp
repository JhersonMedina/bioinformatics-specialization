#include <iostream>
#include "Utilities.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    int k = iread()[0];
    string s = sread()[0], t = sread()[0];
    cout << sharedKmer(k, s, t) << endl;
    return 0;
}
