#include <bits/stdc++.h>
using namespace std;


using WEdge = vector<int>;
using Matrix = vector<vector<int>>;
using Tree = vector<WEdge>;
const int oo = 1e9;

vector<int> iread() {
    string s; getline(cin, s);
    vector<int> ans;
    int cur=0;
    for(int i=0; i<(int)s.size(); ++i) {
        if (s[i] == ' ') {
            ans.push_back(cur);
            cur=0;
        } else cur = cur*10 + (s[i] - '0');
    }
    ans.push_back(cur);
    return ans;
}
vector<string> sread() {
    string s; getline(cin, s);
    vector<string> ans;
    string cur;
    for(int i=0; i<(int)s.size(); ++i) {
        if (s[i] == ' ') {
            ans.push_back(cur);
            cur="";
        } else cur+=s[i];
    }
    ans.push_back(cur);
    return ans;
}
WEdge toWEdge(string s) {
    vector<int> ans;
    string t;
    for(char& c : s) {
        if (isdigit(c)) t += c;
        else if (t.empty() || isdigit(t.back())) t += c;
    }

    int cur=0;
    for(char& c : t) {
        if (isdigit(c)) cur=10*cur+(c-'0');
        else {
            ans.push_back(cur);
            cur=0;
        }
    }
    ans.push_back(cur);
    return ans;
}
WEdge eread() {
    string s; getline(cin, s);
    return toWEdge(s);
}
string printWEdge(WEdge e) {
    string s = to_string(e[0]) + "->" + to_string(e[1]) + ":" + to_string(e[2]);
    return s;
}
vector<WEdge> readEdges() {
    vector<WEdge> ans;
    string s;
    while (getline(cin, s)) ans.push_back(toWEdge(s));
    return ans;
}
string printMatrix(Matrix m) {
    int n=m.size();
    string ans = "";
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) ans += to_string(m[i][j]) + " ";
        ans += '\n';
    }
    return ans;
}
Tree readyToPrint(Tree t) {
    int n=t.size();
    for(int i=0; i<n; ++i) {
        WEdge e = t[i];
        swap(e[0], e[1]);
        t.push_back(e);
    }
    sort(t.begin(), t.end());
    return t;
}
int numNodes(vector<WEdge> edges) {
    int total = 0;
    for(auto& e : edges) total = max(total, max(e[0], e[1]));
    return total+1;
}
Matrix matrixFromEdges(vector<WEdge> edges, int n) {
    Matrix m(n, vector<int>(n, oo));
    for(auto& e : edges) {
        int u=e[0], v=e[1], w=e[2];
        m[u][v]=m[v][u] = w;
    }
    for(int i=0; i<n; ++i) m[i][i]=0;
    return m;
}
Matrix floydWarshall(Matrix dis) {
    int n=dis.size();
    for(int k=0; k<n; ++k) {
        for (int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
            }
        }
    }
    return dis;
}
Matrix leavesDistance (vector<WEdge> edges, int leaves) {
    int n = numNodes(edges);
    Matrix dis = floydWarshall(matrixFromEdges(edges, n));
    Matrix ans(leaves, vector<int> (leaves));
    for(int i=0; i<leaves; ++i) {
        for(int j=0; j<leaves; ++j) ans[i][j] = dis[i][j];
    }
    return ans;
}
int limbLength(Matrix d, int j) {
    int n=d.size();
    int i=0 + (j==0), ans=oo;
    for(int k=0; k<n; ++k) if (k!=j) ans=min(ans, (d[i][j] + d[j][k] - d[i][k])/2);
    return ans;
}
Matrix getDistance(Tree t) {
    Matrix dis = matrixFromEdges(t, numNodes(t));
    return floydWarshall(dis);
}
Tree additivePhylogeny(Matrix m, int leaves) {
    int n = m.size();
    if (n == 2) return {{0, 1, m[0][1]}};

    int ll = limbLength(m, n-1);
    Matrix mbold = m;
    for (int i=0; i<n-1; ++i) {
        mbold[i][n-1] -= ll;
        mbold[n-1][i] = mbold[i][n-1];
    }

    int u, v;
    for (int i=0; i<n-1; ++i) for(int j=0; j<n-1; ++j) {
        if (mbold[i][j] == mbold[i][n-1] + mbold[n-1][j]) {
            u=i, v=j;
        }
    }
    int x=mbold[u][n-1];

    Matrix mtrim=m;
    for (int i=0; i<n; ++i) mtrim[i].pop_back();
    mtrim.pop_back();

    Tree t = additivePhylogeny(mtrim, leaves);
    int w=max(numNodes(t), leaves);
    Matrix dis = getDistance(t);

    for(int it=0; it<(int)t.size(); ++it) {
        WEdge e = t[it];
        int i=e[0], j=e[1], l=e[2];
        if (dis[u][i]>dis[u][j]) swap(i, j);
        if (dis[u][v]!=dis[u][i] + l + dis[j][v]) continue;

        if (dis[u][i] == x) {
            w = i;
            break;
        } else if (dis[u][j] == x) {
            w = j;
            break;
        } else if (dis[u][i]<x && x<dis[u][j]) {
            x -= dis[u][i];
            t.push_back({i, w, x});
            t.push_back({w, j, l-x});
            t.erase(t.begin()+it);
            break;
        }
    }

    t.push_back({w, n-1, ll});
    return t;
}
