#include <bits/stdc++.h>
using namespace std;

using Edge = pair<int, int>;
using WEdge = pair<double, Edge>;
using Matrix = vector<vector<double>>;
using Cluster = vector<int>;
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
    return {ans[2], {ans[0], ans[1]}};
}
WEdge eread() {
    string s; getline(cin, s);
    return toWEdge(s);
}
string printWEdge(WEdge e) {
    return to_string(e.second.first) + "->" + to_string(e.second.second) + ":" +to_string(e.first);
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
        swap(e.second.first, e.second.second);
        t.push_back(e);
    }
    sort(t.begin(), t.end(), [&](WEdge& a, WEdge& b) {
        if (a.second.first == b.second.first) return a.second.second<b.second.second;
        return a.second.first<b.second.first;
    });
    return t;
}
int numNodes(vector<WEdge> edges) {
    int total = 0;
    for(auto& e : edges) total = max(total, max(e.second.second, e.second.first));
    return total+1;
}
Matrix matrixFromEdges(vector<WEdge> edges, int n) {
    Matrix m(n, vector<double>(n, oo));
    for(auto& e : edges) {
        int u=e.second.second, v=e.second.first;
        double w=e.first;
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
    Matrix ans(leaves, vector<double> (leaves));
    for(int i=0; i<leaves; ++i) {
        for(int j=0; j<leaves; ++j) ans[i][j] = dis[i][j];
    }
    return ans;
}
int limbLength(Matrix d, int j) {
    int n=d.size();
    int i=0 + (j==0);
    double ans=oo;
    for(int k=0; k<n; ++k) if (k!=j) ans=min(ans, (d[i][j] + d[j][k] - d[i][k])/2);
    return ans;
}
Matrix getDistance(Tree t) {
    Matrix dis = matrixFromEdges(t, numNodes(t));
    return floydWarshall(dis);
}
Tree additivePhylogeny(Matrix m, int leaves) {
    int n = m.size();
    if (n == 2) return {{m[0][1], {0, 1}}};

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
        int i=e.second.first, j=e.second.second, l=e.first;
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
            t.push_back({x, {i, w}});
            t.push_back({l-x, {w, j}});
            t.erase(t.begin()+it);
            break;
        }
    }

    t.push_back({ll, {w, n-1}});
    return t;
}
double clusterDistance(Cluster& a, Cluster& b, Matrix d) {
    double dis=0.0;
    for(int& i : a) for(int& j : b) dis += d[i][j];
    return dis / double(a.size()*b.size());
}
Cluster mergeClusters(Cluster& a, Cluster& b) {
    Cluster c;
    for(int i=0, j=0; i<(int)a.size() || j<(int)b.size(); ) {
        if (i<(int)a.size() && j<(int)b.size()) {
            if (a[i]<b[j]) {
                c.push_back(a[i]);
                i++;
            } else {
                c.push_back(b[j]);
                j++;
            }
        } else if (i<(int)a.size()) {
            c.push_back(a[i]);
            i++;
        } else {
            c.push_back(b[j]);
            j++;
        }
    }
    return c;
}
Tree UPGMA(Matrix d, int n) {
    vector<Cluster> clusters(n);
    map<Cluster, int> id;
    map<Cluster, double> age;
    for(int i=0; i<n; ++i) {
        clusters[i]={i};
        id[clusters[i]]=i;
        age[clusters[i]]=0;
    }
    int nodes=n;
    vector<WEdge> tree;

    while (clusters.size()>1) {
        double best = oo;
        int u, v;

        for(int i=0; i<(int)clusters.size(); ++i) {
            for(int j=i+1; j<(int)clusters.size(); ++j) {
                double cur = clusterDistance(clusters[i], clusters[j], d);
                if (cur<best) best=cur, u=i, v=j;
            }
        }

        Cluster c = mergeClusters(clusters[u], clusters[v]), a=clusters[u], b=clusters[v];
        id[c] = nodes++;

        age[c] = best / 2.0;
        tree.push_back({age[c] - age[a], {id[c], id[a]}});
        tree.push_back({age[c] - age[b], {id[c], id[b]}});

        clusters.erase(clusters.begin()+v);
        clusters.erase(clusters.begin()+u);
        clusters.push_back(c);
    }
    return tree;
}
bool available(double n) { return n!=-1; }
Tree neighborJoining(Matrix d) {
    int n=d.size();

    vector<double> totalDistance(n, 0);
    vector<int> av;

    for(int i=0; i<n; ++i) if (available(d[i][i])) {
        for(int j=0; j<n; ++j) if (available(d[j][j])) totalDistance[i] += d[i][j];
        av.push_back(i);
    }

    int m=av.size();
    if (m==2) {
        int u=av[0], v=av[1];
        return {{d[u][v], {u, v}}};
    }

    Matrix dstar = d;
    for(int i=0; i<n; ++i) for (int j=0; j<n; ++j) if (i!=j) {
        if (available(d[i][i]) && available(d[j][j])) {
            dstar[i][j] = d[i][j]*(m-2) - totalDistance[i] - totalDistance[j];
        }
    }

    int u=av[0], v=av[1];
    for(int i=0; i<n; ++i) for(int j=i+1; j<n; ++j) {
        if (available(d[i][i]) && available(d[j][j])) {
            if (dstar[i][j]<dstar[u][v]) u=i, v=j;
        }
    }

    double delta = (totalDistance[u] - totalDistance[v])/double(m-2);
    double lu = (d[u][v] + delta)/2.0, lv = (d[u][v] - delta)/2.0;

    Matrix dnew = d;
    dnew.push_back(vector<double>(n+1));
    for(int i=0; i<n; ++i) {
        dnew[i].push_back((d[i][u] + d[i][v] - d[u][v]) / 2.0);
        if (!available(d[i][i])) dnew[i][n] = -1;
        dnew[n][i] = dnew[i][n];
    }
    for(int i=0; i<=n; ++i) dnew[u][i]=dnew[i][u]=dnew[v][i]=dnew[i][v]=-1;

    Tree tree = neighborJoining(dnew);
    tree.push_back({lu, {u, n}});
    tree.push_back({lv, {v, n}});
    return tree;
}
