#include <iostream>
#include "Utilities.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    string pep = sread()[0];
    Spectrum spec = iread();
    int k = iread()[0];
    cout << spectralAlignmentProblem(pep, spec, k) << endl;
    return 0;
}
