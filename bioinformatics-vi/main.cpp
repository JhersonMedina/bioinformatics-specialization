#include <iostream>
#include "Utilities.h"
using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    string x = sread()[0];
    sread();
    string sigma = cread();
    sread();
    string sigmaStates = cread();
    sread();
    Viterbi viterbi(x, sigma, sigmaStates);
    viterbi.readTransition();
    sread();
    viterbi.readEmission();

    viterbi.forwardBackwardAlgorithm();
    return 0;
}
