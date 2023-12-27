#include <iostream>
#include "Utilities.h"
using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    string x = sread()[0], d;
    d=sread()[0];

    string e = cread();
    d=sread()[0];

    string a = cread();
    d=sread()[0];

    Viterbi v(x, e, a);
    v.readTransition();
    d=sread()[0];
    v.readEmission();

    cout <<v.decodingProblem() << endl;
    return 0;
}
