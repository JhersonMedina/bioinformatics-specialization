#include <iostream>
#include "Utilities.h"
using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    string s, t; cin >> s >> t;
    SuffixTree tree(s + "#" + t);
    cout << tree.shortestNonSharedString() << endl;
    return 0;
}
