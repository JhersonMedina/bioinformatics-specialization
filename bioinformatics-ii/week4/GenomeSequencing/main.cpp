#include <iostream>
#include "Utilities.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    vector<string> peps = readStrings();
    vector<int> spec = read();
    int n = read()[0];
    vector<pair<int, string>> a;
    for(string& s : peps) a.push_back({linearScore(s, spec), s});
    for(auto& [_, s] : trim(a, n)) cout << s << ' ';

    return 0;
}
