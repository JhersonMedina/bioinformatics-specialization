#include <iostream>
#include "Utilities.h"
using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    ld theta = fread()[0];
    sread();

    string sigma = cread();
    sread();

    int n = 11-4;
    vector<string> reads(n);
    for(int i=0; i<n; ++i) reads[i] = sread()[0];

    HMM hmm(theta, sigma, reads);
    hmm.printTransitions();
    cout << line << endl;
    hmm.printEmmits();
    return 0;
}
