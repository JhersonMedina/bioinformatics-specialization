#include <iostream>
#include "Utilities.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    int n, l=0; cin >> n;
    int total = 2*n-2;
    vector<string> label(total, "");
    vector<vector<int>> tree(total, vector<int>());
    map<string, int> id;

    for (int i=0; i<2*(total-1); ++i) {
        string s; cin >> s;
        int it = s.find("->"), u, v;
        string a = s.substr(0, it), b = s.substr(it+2);

        if (isdigit(a[0])) u=stoi(a);
        else {
            if (!id.count(a)) id[a] = l++;
            u=id[a], label[u]=a;
        }
        if (isdigit(b[0])) v=stoi(b);
        else {
            if (!id.count(b)) id[b] = l++;
            v=id[b], label[v]=b;
        }

        tree[u].push_back(v);
    }

    vector<Parsimony> ans = nearestNeighborInterchange(tree, label, n);
    for(int i=1; i<(int)ans.size(); ++i) {
        Parsimony p = ans[i];
        cout << p.score << endl;
        for(int u=0; u<total; ++u) {
            for(int& v : p.tree[u]) {
                PEdge e = {diff(p.label[u], p.label[v]), {p.label[u], p.label[v]}};
                cout << printPEdge(e) << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
