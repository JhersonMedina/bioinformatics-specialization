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
using SEdge = pair<char, Edge>;
using Spectrum = vector<int>;
using PSMatch = pair<string, int>;

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

const int oo = 1e9, maxp = 201;
const char nuc[4] = {'A', 'T', 'C', 'G'};
map<char, int> pepCode = {
    {'G', 57},
    {'A', 71},
    {'S', 87},
    {'P', 97},
    {'V', 99},
    {'T', 101},
    {'C', 103},
    {'I', 113},
    {'L', 113},
    {'N', 114},
    {'D', 115},
    {'K', 128},
    {'Q', 128},
    {'E', 129},
    {'M', 131},
    {'H', 137},
    {'F', 147},
    {'R', 156},
    {'Y', 163},
    {'W', 186}
};
map<int, char> toPepCode = {
    {57,'G'},
    {71,'A'},
    {87,'S'},
    {97,'P'},
    {99,'V'},
    {101,'T'},
    {103,'C'},
    {113,'I'},
    {113,'L'},
    {114,'N'},
    {115,'D'},
    {128,'K'},
    {128,'Q'},
    {129,'E'},
    {131,'M'},
    {137,'H'},
    {147,'F'},
    {156,'R'},
    {163,'Y'},
    {186,'W'}
};
map<char, int> decoyPep = {{'X', 4}, {'Z', 5}};
map<int, char> toDecoyPep = {{4,'X'}, {5, 'Z'}};
vector<int> iread() {
    string s; getline(cin, s);
    vector<int> ans;
    for(int i=0, j=0; i<(int)s.size(); ++i) {
        j=i;
        while (j<(int)s.size() && (s[j] == '-' || s[j] == '+' || isdigit(s[j]))) j++;
        ans.push_back(stoi(s.substr(i, j-i)));
        i=j;
    }
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
string printSEdge (SEdge e) {
    string s = to_string(e.second.first) + "->" + to_string(e.second.second) + ":";
    return s += e.first;
}
string iprint(int n) { return (n>0 ? "+":"") + to_string(n); }
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
Matrix buildDStar(Matrix d) {
    int n=d.size();
    vector<double> totalDistance(n, 0);

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) totalDistance[i] += d[i][j];
    }


    Matrix dstar = d;
    for(int i=0; i<n; ++i) for (int j=0; j<n; ++j) if (i!=j) {
        dstar[i][j] = d[i][j]*(n-2) - totalDistance[i] - totalDistance[j];
    }
    return dstar;
}
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

    cout << "D star "<< endl;
    for(int i=0; i<(int)dstar.size(); ++i) {
        for(int j=0; j<dstar[i].size(); ++j) {
            if (available(dstar[i][j])) cout << dstar[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    int u=av[0], v=av[1];
    for(int i=0; i<n; ++i) for(int j=i+1; j<n; ++j) {
        if (available(d[i][i]) && available(d[j][j])) {
            if (dstar[i][j]<dstar[u][v]) u=i, v=j;
        }
    }
    if (u == 1 && v == 3) {
        assert(dstar[1][4] <= dstar[u][v]);
        u=1, v=4;
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

    cout << "join: " << u << ' ' << v << endl;
    for(int i=0; i<(int)dnew.size(); ++i) {
        for(int j=0; j<dnew[i].size(); ++j) {
            if (available(dnew[i][j])) cout << dnew[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
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
Adj graphSpectrum(vector<int> spec) {
    spec.insert(spec.begin(), 0);
    int n=spec.size();
    Adj graph(n, vector<int>());
    for(int i=0; i<n; ++i) {
        for (int j=i+1; j<n; ++j) {
            int d = spec[j] - spec[i];
            if (toPepCode.count(d)) cout << i << ' ' << j << endl, graph[i].push_back(j);
        }
    }
    return graph;
}
vector<int> idealSpectrum(string s) {
    int n = s.size();
    vector<int> spec;
    for(int i=0, sum=0; i<n; ++i) {
        sum += pepCode[s[i]];
        spec.push_back(sum);
    }
    for(int i=n-1, sum=0; i>0; --i) {
        sum += pepCode[s[i]];
        spec.push_back(sum);
    }
    sort(spec.begin(), spec.end());
    return spec;
}
string decodingIdealSpectrum(vector<int> spec) {
    string s="", t="";
    Adj graph = graphSpectrum(spec);
    function<void(int)> go = [&](int u) {
        vector<int> is = idealSpectrum(t);
        if (!is.empty() && is.back() >= spec.back()) {
            if (is == spec) s = t;
            return;
        }

        for(int& v : graph[u]) {
            char c = toPepCode[spec[v] - spec[u]];
            t += c;
            go(v);
            t.pop_back();
        }
    };
    go(0);
    return s;
}
vector<int> peptideToVector(string s) {
    vector<int> ans;
    for(char& c : s) {
        for(int i=0; i < pepCode[c] - 1; ++i) ans.push_back(0);
        ans.push_back(1);
    }
    return ans;
}
string vectorToPeptide(vector<int> a) {
    string s="";
    int n=a.size();
    for (int i=0, j=0; i<n; i=j) {
        while (j<n && a[j]==0) j++;
        s += toPepCode[j-i+1];
        j++;
    }
    return s;
}
string peptideSequencing(vector<int> spec) {
    spec.insert(spec.begin(), 0);
    int n=spec.size();
    string ans;

    vector<int> dp(n), vis(n);
    function<int(int)> go = [&](int u) {
        if (vis[u]) return dp[u];
        dp[u] = u == n- 1 ? 0 : -oo;
        for(auto& [w, _] : toPepCode) {
            int v = u+w;
            if (v<n) dp[u] = max(dp[u], spec[v] + go(v));
        }
        vis[u]=1;
        return dp[u];
    };
    function<void(int)> build = [&](int u) {
        int best = go(u);
        for(auto& [w, c] : toPepCode) {
            int v = u+w;
            if (v<n && best == spec[v] + go(v)) {
                ans += c;
                build(v);
                return;
            }
        }
    };
    build(0);

    return ans;
}
int pepScore(Spectrum spec, string pep) {
    spec.insert(spec.begin(), 0);
    int score=0, k=0;
    for(char& c : pep) {
        k += pepCode[c];
        score += spec[k];
    }
    return score;
}
PSMatch peptideIdentification(Spectrum spec, string pep) {
    int best=-oo, n=pep.size(), m=spec.size();
    string s;

    for(int i=0; i<n; ++i) {
        int length = 0, j=i;
        while (j<n && length < m) {
            length += pepCode[pep[j]];
            j++;
        }
        if (length == m) {
            string t = pep.substr(i, j-i);
            int score = pepScore(spec, t);
            if (score>best) best=score, s=t;
        }
    }
    return {s, best};
}
vector<string> PSMSearch(vector<Spectrum> specs, string proteome, int threshold) {
    vector<string> ans;
    for(Spectrum spec : specs) {
        PSMatch res = peptideIdentification(spec, proteome);
        if (res.second >= threshold) ans.push_back(res.first);
    }
    return ans;
}
long long spectralDictionarySize(Spectrum spec, int lo, int hi) {
    spec.insert(spec.begin(), 0);
    int n = spec.size();
    vector<vector<int>> dp(n, vector<int>(hi+1));
    dp[0][0]=1;
    for (int i=0; i<n; ++i) for(int t=0; t<=hi; ++t) {
        for(auto& [_, p] : pepCode) {
            if (i+p<n && 0<=t+spec[i+p] && t+spec[i+p]<=hi) {
                dp[i+p][t+spec[i+p]] += dp[i][t];
            }
        }
    }
    long long ans=0;
    while (lo<=hi) ans += dp[n-1][lo++];
    return ans;
}
double spectralDictionaryProb(Spectrum spec, int lo, int hi) {
    spec.insert(spec.begin(), 0);
    int n = spec.size();
    vector<vector<double>> dp(n, vector<double>(hi+1));
    dp[0][0]=1.0;
    for (int i=0; i<n; ++i) for(int t=0; t<=hi; ++t) {
        for(auto& [_, p] : pepCode) {
            if (i+p<n && 0<=t+spec[i+p] && t+spec[i+p]<=hi) {
                dp[i+p][t+spec[i+p]] += dp[i][t]/20.0;
            }
        }
    }
    double ans=0;
    while (lo<=hi) ans += dp[n-1][lo++];
    return ans;
}
string spectralAlignmentProblem(string pep, Spectrum spec, int k) {
    int n=spec.size(), m=pep.size();
    spec.insert(spec.begin(), 0);
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(m+1, vector<int>(k+1)));
    vector<vector<vector<bool>>> memo(n+1, vector<vector<bool>>(m+1, vector<bool>(k+1)));

    function<int(int, int, int)> go = [&](int i, int j, int r) {
        if (j>=m) return i==n ? 0 : -oo;
        int& ans = dp[i][j][r];
        if (memo[i][j][r]) return ans;

        ans = -oo;
        int p = pepCode[pep[j]]-1;
        for(int a=0; i+a+1<=n; ++a) {
            if (r-(a!=p) >= 0) ans=max(ans, go(i+a+1, j+1, r-(a!=p)) + spec[i+a+1]);
        }

        memo[i][j][r]=1;
        return ans;
    };
    string pepMod;

    function<void(int, int, int)> build = [&](int i, int j, int r) {
        if (j>=m) return;
        int best = go(i, j, r);

        int p = pepCode[pep[j]]-1;
        pepMod += pep[j];
        for(int a=0; i+a+1<=n; ++a) {
            if (r-(a!=p) >= 0 && best == go(i+a+1, j+1, r-(a!=p))+spec[i+a+1]) {
                if (a!=p) pepMod += "(" + iprint(a-p) + ")";
                build(i+a+1, j+1, r-(a!=p));
                return;
            }
        }
    };

    build(0, 0, k);
    return pepMod;
}
