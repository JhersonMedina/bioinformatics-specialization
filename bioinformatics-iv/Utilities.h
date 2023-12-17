#include <bits/stdc++.h>
using namespace std;

using Edge = pair<int, int>;
using WEdge = pair<double, Edge>;
using Matrix = vector<vector<double>>;
using Cluster = vector<int>;
using WTree = vector<WEdge>;
using PEdge = pair<int, pair<string, string>>;
using PTree = vector<PEdge>;
using Label = vector<string>;
using Adj = vector<vector<int>>;
using Tree = vector<Edge>;
using Item = pair<int, int>;
struct Parsimony {
    int score;
    Adj tree;
    Label label;

    bool operator < (const Parsimony& b) const {
        if (score != b.score) return score<b.score;
        if (tree != b.tree) return tree<b.tree;
        return label<b.label;
    }
};

const int oo = 1e9;
const char nuc[4] = {'A', 'T', 'C', 'G'};

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
WEdge weread() {
    string s; getline(cin, s);
    return toWEdge(s);
}
string printWEdge(WEdge e) {
    return to_string(e.second.first) + "->" + to_string(e.second.second) + ":" +to_string(e.first);
}
string printPEdge (PEdge e) {
    return e.second.first + "->" + e.second.second + ":" + to_string(e.first);
}
string printEdge (Edge e) {
    return to_string(e.first) + "->" + to_string(e.second);
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
WTree readyToPrint(WTree t) {
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
Tree fromAdjToTree(Adj tree) {
    Tree t;
    int n=tree.size();
    for(int u=0; u<n; ++u) {
        for(int&v : tree[u]) t.push_back({u, v});
    }
    return t;
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
Matrix getDistance(WTree t) {
    Matrix dis = matrixFromEdges(t, numNodes(t));
    return floydWarshall(dis);
}
WTree additivePhylogeny(Matrix m, int leaves) {
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

    WTree t = additivePhylogeny(mtrim, leaves);
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
WTree UPGMA(Matrix d, int n) {
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
WTree neighborJoining(Matrix d) {
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

    WTree tree = neighborJoining(dnew);
    tree.push_back({lu, {u, n}});
    tree.push_back({lv, {v, n}});
    return tree;
}
int diff(string& s, string& t) {
    int ans=0;
    for (int i=0; i<(int)s.size(); ++i) ans += s[i]!=t[i];
    return ans;
}
Parsimony smallParsimony (Adj tree, Label& label, int root, int m, int l) {
    int n = tree.size(), total=0;

    for(int pos=0; pos<m; ++pos) {
        vector<vector<int>> dp(4, vector<int>(n, -1));
        function<int(int, int)> go = [&](int c, int u) {
            if (u<l) return label[u][pos] == nuc[c] ? 0 : oo;
            int& ans = dp[c][u];
            if (ans!=-1) return ans;

            int l=oo, r=oo;
            for (int j=0; j<4; ++j) l=min(l, go(j, tree[u][0]) + (c!=j));
            for (int k=0; k<4; ++k) r=min(r, go(k, tree[u][1]) + (c!=k));
            return ans = l+r;
        };
        function<void(int, int)> build = [&](int c, int u) {
            if (u<l) return;
            label[u] += nuc[c];

            int  l=0, r=0;
            for (int j=0; j<4; ++j) if (go(l, tree[u][0]) + (l!=c) > go(j, tree[u][0]) + (j!=c)) l=j;
            for (int k=0; k<4; ++k) if (go(r, tree[u][1]) + (r!=c) > go(k, tree[u][1]) + (k!=c)) r=k;

            build(l, tree[u][0]);
            build(r, tree[u][1]);
        };

        int best = oo, c=0;
        for(int i=0; i<4; ++i) {
            if (go(i, root) < best) best = go(i, root), c= i;
        }
        total += best;
        build(c, root);
    }
    return {total, tree, label};
}
void removeEdge(vector<int>& adj, int u) {
    auto it = find(adj.begin(), adj.end(), u);
    adj.erase(it);
}
Parsimony smallParsimonyUnrooted(Adj tree, Label label, int m, int l) {
    int n=tree.size();
    int root = n, u=0, v=tree[0][0];
    Adj oldTree = tree;

    tree.push_back({u, v});
    tree[u].push_back(root);
    tree[v].push_back(root);

    label.push_back("");

    removeEdge(tree[u], v);
    removeEdge(tree[v], u);

    function<void(int,int)> addRoot = [&](int u, int p) {
        auto it = find(tree[u].begin(), tree[u].end(), p);
        if (it!=tree[u].end()) tree[u].erase(it);

        for(int& v : tree[u]) addRoot(v, u);
    };
    addRoot(root, root);

    Parsimony ans = smallParsimony(tree, label, root, m, l);
    ans.tree = oldTree;
    return ans;
}
void edgeReplace(vector<int>& adj, int u, int v) { for(int& i : adj) if (i == u) i = v; }
pair<Adj, Adj> nearestNeighborsTree(Adj tree, int u, int v) {
    vector<int> eu, ev;
    for(int i=0; i<(int)tree[u].size(); ++i) {
        if (tree[u][i]!=v) eu.push_back(i);
    }
    for(int i=0; i<(int)tree[v].size(); ++i) {
        if (tree[v][i]!=u) ev.push_back(i);
    }
    pair<Adj, Adj> ans;

    edgeReplace(tree[tree[u][eu[0]]], u, v);
    edgeReplace(tree[tree[v][ev[0]]], v, u);
    swap(tree[u][eu[0]], tree[v][ev[0]]);

    ans.first = tree;

    swap(tree[u][eu[0]], tree[v][ev[0]]);
    edgeReplace(tree[tree[u][eu[0]]], v, u);
    edgeReplace(tree[tree[v][ev[0]]], u, v);


    edgeReplace(tree[tree[u][eu[0]]], u, v);
    edgeReplace(tree[tree[v][ev[1]]], v, u);
    swap(tree[u][eu[0]], tree[v][ev[1]]);

    ans.second = tree;
    return ans;
}

vector<Parsimony> nearestNeighborInterchange(Adj tree, Label label, int l) {
    int score = oo, m=label[0].size();
    Parsimony p = smallParsimonyUnrooted(tree, label, m, l);
    vector<Parsimony> ans;
    while (p.score < score) {
        score = p.score;
        tree = p.tree;
        ans.push_back(p);

        Parsimony best = p;
        for(int u=l; u<(int)tree.size(); ++u) {
            for(int& v : tree[u]) if (v>=l) {
                pair<Adj, Adj> neighborTrees = nearestNeighborsTree(tree, u, v);

                Parsimony a = smallParsimonyUnrooted(neighborTrees.first, label, m, l);
                Parsimony b = smallParsimonyUnrooted(neighborTrees.second, label, m, l);

                if (a.score>b.score) swap(a, b);
                if (a.score<best.score) best = a;
            }
        }
        p=best;
    }
    return ans;
}

