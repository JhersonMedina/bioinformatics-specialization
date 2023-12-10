#include <iostream>
#include "Utilities.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    vector<int> input = iread();
    int ma = input[0], mma=input[1], indel=input[2];
    string s=sread()[0], t=sread()[0];
    auto ans = overlapAlignment(ma, mma, indel, s, t);
    cout << ans.first << endl << ans.second.first << endl << ans.second.second << endl;

    return 0;
}
