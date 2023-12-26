#include <iostream>
#include "Utilities.h"
using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    string s = sread()[0];
    vector<string> p = sread();
    int d = iread()[0];
    for(Match& m : multipleAproximatePatternMatching(s, p, d)) printMatch(m);
    return 0;
}
