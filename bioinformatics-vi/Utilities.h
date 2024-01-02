#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using Path = vector<int>;
using Graph = vector<vector<int>>;
using Match = pair<string, vector<int>>;
using Matrix = vector<vector<ld>>;

struct BWT {
    string p;
    int top, bottom, d;
};

const int MAXN = 1e5, INF = 1e9;
const ld oo = 1e18;
const string line = "--------";

struct Trie {
    vector<vector<int>> trie = {vector<int>(256, 0)};
    vector<int> leaf = {0}, color = {0};

    int size() { return trie.size(); }
    void extend() {
        trie.push_back(vector<int>(256, 0));
        leaf.push_back(0);
        color.push_back(0);
    }

    Trie(vector<string> p) { for(string& s : p) add(s, 0); }
    Trie () {}

    void add(string s, int c) {
        int cur=0;
        for(char& c : s) {
            if (!trie[cur][c]) {
                trie[cur][c]=trie.size();
                extend();
            }
            cur = trie[cur][c];
        }
        leaf[cur]=1;
        color[cur]=c;
    }
    vector<string> prefixTrieMatching (string text) {
        int cur=0;
        vector<string> s;
        string p;
        for(char& c : text) {
            if (leaf[cur]) s.push_back(p);
            if (!trie[cur][c]) break;

            p += c;
            cur=trie[cur][c];
        }
        return s;
    }
    void print() {
        for(int i=0; i<trie.size(); ++i) {
            for(int c=0; c<256; ++c) {
                if (trie[i][c]) cout << i << ' ' << trie[i][c] << ' ' << char(c) << endl;
            }
        }
    }
};
struct SuffixTree {
    int n=1, leaves=0;
    Trie trie;
    vector<map<string, int>> tree = {{}};
    vector<int> cnt = {0}, color = {0};
    string s;

    int size() { return tree.size(); }
    SuffixTree (string s): s(s) {
        s += '$';
        for(int i=0; i<(int)s.size(); ++i) trie.add(s.substr(i), 0);
        dfs(0, 0, "");
        go(0);
    }
    void dfs(int u, int p, string t) {
        vector<int> ch;
        for(int c=0; c<256; ++c) if (trie.trie[u][c]) ch.push_back(c);
        int q=p;
        if (u && ch.size() != 1) {
            tree[p][t] = q = n++;
            tree.push_back({});
            cnt.push_back(0), color.push_back(0);
            leaves += t.back() == '$';
            t.clear();
            color[q] = trie.color[u];
        }
        for(int& c : ch) dfs(trie.trie[u][c], q, t+string(1, c));
    }
    void go(int u) {
        cnt[u] = tree[u].empty();
        for(auto& [c, v] : tree[u]) {
            go(v);
            cnt[u] += cnt[v];
            color[u] |= color[v];
        }
    }
    string longestRepeat() {
        string ans;
        queue <pair<int, string>> q;
        q.push({0, ""});
        while (!q.empty()) {
            int u = q.front().first;
            string t = q.front().second;
            q.pop();

            if (cnt[u]>1) {
                if (t.size()>ans.size()) ans=t;
            }

            for(auto& [c, v] : tree[u]) q.push({v, t+c});
        }
        return ans;
    }
    string longestSharedString() {
        string ans;
        queue <pair<int, string>> q;
        q.push({0, ""});
        while (!q.empty()) {
            int u = q.front().first;
            string t = q.front().second;
            q.pop();

            if (color[u]==3) {
                if (t.size()>ans.size()) ans=t;
            }

            for(auto& [c, v] : tree[u]) q.push({v, t+c});
        }
        return ans;
    }
    string shortestNonSharedString() {
        string ans;
        queue <pair<int, string>> q;
        q.push({0, ""});
        while (!q.empty()) {
            int u = q.front().first;
            string t = q.front().second;
            q.pop();

            if (color[u]==1) {
                if (t.find("#") == string::npos && (ans.empty() || t.size()<ans.size())) {
                    ans=t;
                }
            }

            for(auto& [c, v] : tree[u]) q.push({v, t+c});
        }
        return ans;
    }
    void printEdges() {
        for (int i=0; i<n; ++i) {
            for(auto& [c, _] : tree[i]) cout << c << ' ';
        }
        cout << endl;
    }
};

vector<string> sread() {
    string s; getline(cin, s);
    vector<string> ans;
    string cur;
    for(int i=0; i<(int)s.size(); ++i) {
        if (s[i] == ' ' || s[i] == '\t') {
            if (!cur.empty()) ans.push_back(cur);
            cur="";
        } else cur+=s[i];
    }
    ans.push_back(cur);
    return ans;
}
string cread() {
    vector<string> p = sread();
    string s;
    for(string& t : p) s += t[0];
    return s;
}
vector<int> iread() {
    string s; getline(cin, s);
    vector<int> ans;
    for(int i=0, j=0; i<(int)s.size(); ++i) {
        if (s[i] != '-' && s[i] != '+' && !isdigit(s[i])) continue;
        j=i;
        while (j<(int)s.size() && (s[j] == '-' || s[j] == '+' || isdigit(s[j]))) j++;
        ans.push_back(stoi(s.substr(i, j-i)));
        i=j;
    }
    return ans;
}
vector<ld> fread() {
    string s; getline(cin, s);
    vector<ld> ans;
    for(int i=0, j=0; i<(int)s.size(); ++i) {
        if (s[i] != '-' && s[i] != '+' && s[i] != '.' && !isdigit(s[i])) continue;
        j=i;
        while (j<(int)s.size() && (s[j] == '-' || s[j] == '+' || s[j] == '.' || isdigit(s[j]))) j++;
        ans.push_back(stod(s.substr(i, j-i)));
        i=j;
    }
    return ans;
}

void printMatch(pair<string, vector<int>> match) {
    cout << match.first << ": ";
    for(int& i : match.second) cout << i << ' ';
    cout << endl;
}
map<string, vector<int>> trieMatching (string text, Trie trie) {
    map<string, vector<int>> matches;
    for(int i=0; i<(int)text.size(); ++i) {
        vector<string> p = trie.prefixTrieMatching(text.substr(i));
        for(string& s : p) matches[s].push_back(i);
    }
    return matches;
}
vector<Path> maximalNonBranchingPaths(Graph graph) {
    int n=graph.size();
    vector<int> in(n), out(n), vis(n, 0);
    for (int u=0; u<n; ++u) {
        for(int& v : graph[u]) out[u]++, in[v]++;
    }

    vector<Path> ans;
    queue <pair<int, Path>> q;
    for(int u=0; u<n; ++u) if (in[u]!=1 || out[u]!=1) {
        for(int& v : graph[u]) q.push({v, {u}});
    }

    while (!q.empty()) {
        int u = q.front().first;
        Path p = q.front().second;
        q.pop();

        vis[u]=1;
        p.push_back(u);
        if (in[u]!=1 || out[u]!=1) ans.push_back(p);
        else q.push({graph[u][0], p});
    }

    for (int u=0; u<n; ++u) if (in[u]==1 && out[u]==1 && !vis[u]) {
        Path p;
        int v=u;

        do {
            vis[v]=1;
            p.push_back(v);
            v=graph[v][0];
        } while (v!=u);

        p.push_back(u);
        ans.push_back(p);
    }
    return ans;
}
vector<int> treeColoring(Graph tree, vector<int> col) {
    int n=tree.size(), r;
    vector<int> in(n);
    for (int u=0; u<n; ++u) for(int& v : tree[u]) in[v]++;
    for(int u=0; u<n; ++u) if (!in[u]) r=u;

    function<void(int)> dfs = [&](int u) {
        for(int& v : tree[u]) {
            dfs(v);
            col[u] |= col[v];
        }
    };
    dfs(r);
    return col;
}
vector<int> suffixArrayBrute(string s) {
    int n = s.size();
    vector<int> a(n); iota(a.begin(), a.end(), 0);
    sort(a.begin(), a.end(), [&](int i, int j) {
         return s.substr(i) < s.substr(j);
    });
    return a;
}
vector<pair<int, int>> partialSuffixArray(string s, int k) {
    vector<int> sa = suffixArrayBrute(s);
    vector<pair<int,int>> psa;
    for (int i=0; i<(int)sa.size(); ++i) {
        if (sa[i]%k == 0 )psa.push_back({i, sa[i]});
    }
    return psa;
}
string burrowsWheelerTransform(string s) {
    vector<string> m;
    int n=s.size();
    for (int i=0; i<n; ++i) {
        m.push_back(s);
        rotate(s.begin(), s.begin()+1,s.end());
    }
    sort(m.begin(), m.end());
    string bwt;
    for(string& t : m) bwt += t.back();
    return bwt;
}
string inverseBurrowsWheelerTransform(string s) {
    int n=s.size();
    string f = s, res;
    sort(f.begin(), f.end());

    vector<vector<int>> pos(256, vector<int>());
    for(int i=n-1; i>=0; --i) pos[s[i]].push_back(i);
    vector<int> to(n);
    for (int i=0; i<n; ++i) {
        to[i] = pos[f[i]].back();
        pos[f[i]].pop_back();
    }

    for (int i=0, k=0; i<n; ++i) {
        res += f[k];
        k = to[k];
    }
    rotate(res.begin(), res.begin()+1, res.end());
    return res;
}
vector<int> getLastToFirst (string s) {
    int n = s.size();
    string f = s;
    sort(f.begin(), f.end());

    vector<vector<int>> pos(256, vector<int>());
    vector<int> lastToFirst(n);

    for (int i=n-1; i>=0; i--) pos[f[i]].push_back(i);

    for (int i=0; i<n; ++i) {
        lastToFirst[i] = pos[s[i]].back();
        pos[s[i]].pop_back();
    }

    return lastToFirst;
}
int bwtMatching(string lc, string p) {
    int n=lc.size();
    vector<int> lastToFirst = getLastToFirst(lc);

    int top=0, bottom=n-1;
    while (top <= bottom) {
        if (p.empty()) return bottom - top + 1;
        assert(top<=bottom);
        char c = p.back();
        p.pop_back();

        int topIndex=n, bottomIndex=-1;
        for (int i=top; i<=bottom; ++i) {
            if (lc[i] == c) bottomIndex=i, topIndex=min(topIndex, i);
        }

        if (bottomIndex == -1) return 0;
        top = lastToFirst[topIndex], bottom = lastToFirst[bottomIndex];
    }

    return bottom - top + 1;
}
vector<int> betterBWTMatching(string lc,vector<string> patterns) {
    int n=lc.size();

    string fc = lc; sort(fc.begin(), fc.end());
    vector<int> firstOcurrence(256);
    vector<vector<int>> cnt(n+1, vector<int>(256, 0));
    for(int i= n-1; i>=0; --i) firstOcurrence[fc[i]] = i;
    for (int i=1; i<=n; ++i) {
        cnt[i] = cnt[i-1];
        cnt[i][lc[i-1]]++;
    }

    vector<int> ans;
    for(string& p : patterns) {
        int top=0, bottom=n-1;
        while (top<=bottom) {
            if (p.empty()) {
                ans.push_back(bottom-top+1);
                break;
            }
            char c = p.back(); p.pop_back();
            if (cnt[bottom+1][c] - cnt[top][c] <= 0) {
                ans.push_back(0);
                break;
            }
            top = firstOcurrence[c] + cnt[top][c];
            bottom = firstOcurrence[c] + cnt[bottom+1][c]-1;
        }
    }
    return ans;
}
vector<Match> multiplePatternMatching(string s, vector<string> patterns) {
    s += '$';
    int n=s.size();

    string lc = burrowsWheelerTransform(s), fc = s;
    sort(fc.begin(), fc.end());

    vector<int> firstOcurrence(256), sa = suffixArrayBrute(s);
    vector<vector<int>> cnt(n+1, vector<int>(256, 0));

    for(int i= n-1; i>=0; --i) firstOcurrence[fc[i]] = i;
    for (int i=1; i<=n; ++i) {
        cnt[i] = cnt[i-1];
        cnt[i][lc[i-1]]++;
    }

    vector<Match> ans;
    for(string& p : patterns) {
        string pt = p;
        int top=0, bottom=n-1;
        while (top<=bottom) {
            if (p.empty()) {
                Match m = {pt, {}};
                for(int i=top; i<=bottom; ++i) m.second.push_back(sa[i]);
                ans.push_back(m);
                break;
            }

            char c = p.back(); p.pop_back();

            if (cnt[bottom+1][c] - cnt[top][c] <= 0) {
                ans.push_back({pt, {}});
                break;
            }

            top = firstOcurrence[c] + cnt[top][c];
            bottom = firstOcurrence[c] + cnt[bottom+1][c]-1;
        }
    }

    return ans;
}
vector<Match> multipleAproximatePatternMatching(string s, vector<string> patterns, int d) {
    s += '$';
    int n=s.size();

    string lc = burrowsWheelerTransform(s), fc = s;
    sort(fc.begin(), fc.end());

    vector<int> lastToFirst = getLastToFirst(lc), sa = suffixArrayBrute(s);
    map<string, vector<int>> matches;

    for(string& t : patterns) {
        queue <BWT> q;
        q.push({t, 0, n-1, d});

        while (!q.empty()) {
            BWT u = q.front(); q.pop();
            string p = u.p;
            int top = u.top, bottom = u.bottom, rem = u.d;

            if (top>bottom) break;

            if (p.empty()) {
                for(int i=top; i<=bottom; ++i) matches[t].push_back(sa[i]);
                continue;
            }

            char c = p.back();
            p.pop_back();

            vector<int> bottomIndex(256, -1), topIndex(256, n);

            for (int i=top; i<=bottom; ++i) {
                if (rem - (lc[i] != c) >= 0) bottomIndex[lc[i]] = i, topIndex[lc[i]] = min(topIndex[lc[i]], i);
            }

            for(int i=0; i<256; ++i) if (bottomIndex[i] != -1) {
                q.push({p, lastToFirst[topIndex[i]], lastToFirst[bottomIndex[i]], rem - (char(i) != c)});
            }
        }

        if (!matches.count(t)) matches[t] = {};
    }

    vector<Match> ans;
    for(auto& [t, a] : matches) {
        Match m = {t, {}};
        for(int& i : a) m.second.push_back(i);
        ans.push_back(m);
    }

    return ans;
}
ld hiddenPathProbability(string p, Matrix t, int n) {
    double ans = 1.0/double(n);
    for(int i=1; i<(int)p.size(); ++i) ans *= t[p[i-1]][p[i]];
    return ans;
}
ld outcomehiddenProbability(string x, string pi, Matrix t) {
    ld ans = 1.0;
    for(int i=0; i<(int)x.size(); ++i) ans *= t[pi[i]][x[i]];
    return ans;
}
struct HMM {
    int s, t, c;
    ld theta, sig;

    string sigma, sigmaStates;
    vector<int> pi, x;
    vector<ld> frac;

    map<int, map<int, ld>> transition;
    map<int, map<char, ld>> emmit;
    map<int, int> cnt, total;

    map<int, map<int, int>> edge;
    map<int, map<char, int>> gen;

    HMM(ld theta, ld sig, string sigma, vector<string> reads): theta(theta), sig(sig), sigma(sigma) {
        sort(this->sigma.begin(), this->sigma.end());

        computeFraction(reads);
        c=seedColumns(),s=-2, t=-4;

        for(string& r : reads) {
            int u = s, v;

            for(int i=0; i<(int)r.size(); ++i) {
                if (isRemoved(i)) {
                    if (r[i] != '-') v = u!=s? 2*((abs(u)+1)/2) : 0; //insertion
                    else continue; //ignore
                } else {
                    if (r[i] == '-') v = u!=s ? -2*((abs(u)+1)/2 + 1) + 1 : -1; //deletion
                    else v = u!=s ? 2*((abs(u)+1)/2 + 1) - 1 : 1; //match
                }

                edge[u][v]++;
                cnt[u]++;
                if (r[i]!='-') total[v]++, gen[v][r[i]]++;
                u=v;
            }

            cnt[u]++;
            edge[u][t]++;
            cnt[t]++;
        }

        computeProbabilities(s); //start
        computeProbabilities(t); // end
        computeProbabilities(0); //I0
        for (int i=1; i<=c; ++i) {
            computeProbabilities(2*i); //insertion
            computeProbabilities(2*i-1); //match
            computeProbabilities(-2*i+1); //deletion
        }

    }
    HMM(string generated, string sigma, string path, string sigmaStates):sigma(sigma), sigmaStates(sigmaStates) {
        sort(this->sigma.begin(), this->sigma.end());
        sort(this->sigmaStates.begin(), this->sigmaStates.end());

        for(char& c : generated) x.push_back(getEstimatedGen(c));
        for(char& c : path) pi.push_back(getEstimatedState(c));

        for (int i=0; i+1<(int)pi.size(); ++i) {
            cnt[pi[i]]++;
            edge[pi[i]][pi[i+1]]++;
        }
        for (int i=0; i<(int)x.size(); ++i) {
            total[pi[i]]++;
            gen[pi[i]][x[i]]++;
        }

        for (int i=0; i<(int)sigmaStates.size(); ++i) {
            for (int j=0; j<(int)sigmaStates.size(); ++j) {
                if (cnt[i]) transition[i][j] = ld(edge[i][j]) / ld(cnt[i]);
                else transition[i][j] = ld(1) / ld(sigmaStates.size());
            }

            for (int j=0; j<(int)sigma.size(); ++j) {
                if (total[i]) emmit[i][j] = ld(gen[i][j]) / ld(total[i]);
                else emmit[i][j] = ld(1) / ld(sigma.size());
            }
        }
    }
    int getEstimatedState(char c) { return lower_bound(sigmaStates.begin(), sigmaStates.end(), c) - sigmaStates.begin(); }
    int getEstimatedGen(char c) { return lower_bound(sigma.begin(), sigma.end(), c) - sigma.begin(); }
    void computeProbabilities(int u) {
        if (cnt[u]) {
            transition[u][s] = ld(edge[u][s])/ld(cnt[u]); // start
            transition[u][t] = ld(edge[u][t])/ld(cnt[u]); // end
            transition[u][0] = ld(edge[u][0])/ld(cnt[u]); // I0

            for (int i=1; i<=c; ++i) {
                transition[u][2*i] = ld(edge[u][2*i])/ld(cnt[u]); // insertion
                transition[u][2*i-1] = ld(edge[u][2*i-1])/ld(cnt[u]); // match
                transition[u][-2*i+1] = ld(edge[u][-2*i+1])/ld(cnt[u]); // deletion
            }
        }


        if (total[u]) for(char& c : sigma) emmit[u][c] = ld(gen[u][c])/ld(total[u]);

        if (sig == 0.0 || u == t) return;

        vector<int> states;

        { //add pseudocounts
            int v = (abs(u)+1)/2;
            if (u == s) { //start
                states = {-1, 0, 1};
            } else if (u<0 && u!=t) { //deletion
                if (v == c) states = {2*v, t};
                else states = {2*v, 2*(v+1)-1, -2*(v+1)+1};
            } else if (u%2) { //match
                if (v==c) states = {2*v,t};
                else states = {2*v, 2*(v+1)-1, -2*(v+1)+1};
            } else { //insertion
                if (v==c) states = {u, t};
                else states = {u, -2*(v+1)+1, 2*(v+1)-1};
            }
        }

        ld sum=0;
        for(int& v : states) {
            transition[u][v] += sig;
            sum += transition[u][v];
        }
        for(int& v : states) transition[u][v] /= sum;

        if (u>=0) { //insertion or match
            sum = 0;
            for(char& c : sigma) {
                emmit[u][c] += sig;
                sum += emmit[u][c];
            }
            for(char& c : sigma) emmit[u][c] /= sum;
        }
    }
    void computeFraction(vector<string> reads) {
        int n = reads.size(), m=reads[0].size();
        frac.resize(m);

        for (int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) frac[i] += reads[j][i] == '-';
            frac[i] /= ld(n);
        }
    }
    int seedColumns() {
        int val = 0;
        for(ld& d : frac) val += d<theta;
        return val;
    }
    bool isRemoved(int i) { return frac[i] >= theta; }
    string getState(int u) {
        if (u == -2) return "S";
        if (u == -4) return "E";
        if (u<0) return "D" + to_string((abs(u)+1)/2);
        if (u%2) return "M" + to_string((u+1)/2);
        return "I" + to_string(u/2);
    }

    void printEstimatedTransition(int u) {
        cout << sigmaStates[u] << ' ';
        for (int i=0; i<(int)sigmaStates.size(); ++i) cout << transition[u][i] << ' ';
        cout << endl;
    }
    void printEstimatedTranstions() {
        cout << fixed << setprecision(5);
        cout << '\t';
        for (char& c : sigmaStates) cout << c << '\t';
        cout << endl;
        for (int i=0; i<(int)sigmaStates.size(); ++i) {
            printEstimatedTransition(i);
        }
    }
    void printTransition(int u) {
        cout << getState(u) << ' ' << transition[u][s] << ' ' << transition[u][0] << ' ';
        for (int i=1; i<=c; ++i) {
            cout << transition[u][2*i-1] << ' ' << transition[u][-2*i+1] << ' ' << transition[u][2*i] << ' ';
        }
        cout << transition[u][t] << endl;
    }
    void printTransitions() {
        cout << fixed << setprecision(3);
        cout << '\t' << getState(s) << '\t' << getState(0) << '\t';
        for (int i=1; i<=c; ++i) cout << getState(2*i-1) << '\t' << getState(-2*i+1) << '\t' << getState(2*i) << '\t';
        cout << getState(t) << endl;

        printTransition(s);
        printTransition(0);
        for (int i=1; i<=c; ++i) {
            printTransition(2*i-1);
            printTransition(-2*i+1);
            printTransition(2*i);
        }
        printTransition(t);
    }
    void printEmmit(int u) {
        cout << getState(u) << ' ';
        for(char& c : sigma) cout << emmit[u][c] << ' ';
        cout << endl;
    }
    void printEstimatedEmmit(int u) {
        cout << sigmaStates[u] << ' ';
        for (int i=0; i<(int)sigma.size(); ++i) cout << emmit[u][i] << ' ';
        cout << endl;
    }
    void printEstimatedEmmits() {
        cout << fixed << setprecision(5);
        cout << '\t';
        for (char& c : sigma) cout << c << '\t';
        cout << endl;
        for (int i=0; i<(int)sigmaStates.size(); ++i) {
            printEstimatedEmmit(i);
        }
    }
    void printEmmits() {
        cout << fixed << setprecision(3);
        for (char& c : sigma) cout << '\t' << c;
        cout << endl;

        printEmmit(s);
        printEmmit(0);
        for (int i=1; i<=c; ++i) {
            printEmmit(2*i-1);
            printEmmit(-2*i+1);
            printEmmit(2*i);
        }
        printEmmit(t);
    }
};
struct Viterbi {
    int n, m;
    vector<int> x;
    string xs, e,  a;
    Matrix g, t;

    Viterbi(string xs, string e, string a): xs(xs), e(e), a(a) {
        sort(this->e.begin(), this->e.end());
        sort(this->a.begin(), this->a.end());

        n = a.size(), m=e.size();

        for(char& c : xs) x.push_back(getE(c));
    }

    int getE(char c) {
        sort(e.begin(), e.end());
        return lower_bound(e.begin(), e.end(), c) - e.begin();
    }
    int getA(char c) {
        sort(a.begin(), a.end());
        return lower_bound(a.begin(), a.end(), c) - a.begin();
    }

    void readTransition() {
        string col = cread();
        Matrix d(n, vector<ld>(n));

        for (int i=0; i<n; ++i) {
            vector<string> row = sread();
            int r = getA(row[0][0]);
            for (int j=1; j<=n; ++j) {
                int c = getA(col[j-1]);
                ld val = stod(row[j]);

                d[r][c] = val;
            }
        }
        t = d;
    }

    void readEmission() {
        string col = cread();
        Matrix d(n, vector<ld>(m));

        for (int i=0; i<n; ++i) {
            vector<string> row = sread();
            int r = getA(row[0][0]);
            for (int j=1; j<=m; ++j) {
                int c = getE(col[j-1]);
                ld val = stod(row[j]);

                d[r][c] = val;
            }
        }
        g = d;
    }

    string decodingProblem () {
        int l = x.size();
        vector<vector<ld>> dp(l, vector<ld>(n, -oo));
        vector<vector<bool>> memo(l, vector<bool>(n));
        string pi;

        function<ld(int, int)> go = [&](int i, int j) {
            if (i>=l) return ld(0.0);
            ld& ans = dp[i][j];
            if (memo[i][j]) return ans;

            for (int k=0; k<n; ++k) ans = max(ans, go(i+1, k)+log2(t[j][k]*g[j][x[i]]));

            memo[i][j]=1;
            return ans;
        };

        ld best = -oo;
        int s = -1;
        for(int i=0; i<n; ++i) if (go(0, i)+log2(1.0/ld(n)) > best) {
            best = go(0, i)+log2(1.0/ld(n));
            s=i;
        }

        function<void(int, int)> build = [&](int i, int j) {
            if (i>=l) return;
            ld ans = go(i, j);

            pi += a[j];
            for (int k=0; k<n; ++k) {
                if (go(i+1, k)+log2(t[j][k]*g[j][x[i]]) == ans) {
                    build(i+1, k);
                    return;
                }
            }
        };

        build(0, s);
        return pi;
    }
    ld outcomeLikelihoodProblem () {
        int l = x.size();
        vector<vector<ld>> dp(l, vector<ld>(n, 0.0));
        vector<vector<bool>> memo(l, vector<bool>(n));
        string pi;

        function<ld(int, int)> go = [&](int i, int j) {
            if (i>=l) return ld(1.0);
            ld& ans = dp[i][j];
            if (memo[i][j]) return ans;

            for (int k=0; k<n; ++k) ans += go(i+1, k)*t[j][k]*g[j][x[i]];

            memo[i][j]=1;
            return ans;
        };

        ld best = 0.0;
        for(int i=0; i<n; ++i) best += go(0, i)*(1.0/ld(n));
        return best;
    }
    void forwardBackwardAlgorithm () {
        int l = x.size();
        vector<vector<ld>> dp(l, vector<ld>(n, 0.0));
        vector<vector<bool>> memo(l, vector<bool>(n));
        string pi;

        function<ld(int, int)> go = [&](int i, int j) {
            if (i>=l) return ld(1.0);
            ld& ans = dp[i][j];
            if (memo[i][j]) return ans;

            for (int k=0; k<n; ++k) ans += go(i+1, k)*t[j][k]*g[j][x[i]];

            memo[i][j]=1;
            return ans;
        };

        vector<vector<ld>> dp2(l, vector<ld>(n, 0.0));
        vector<vector<bool>> memo2(l, vector<bool>(n));

        function<ld(int, int)> go2 = [&](int i, int j) {
            if (i<0) return ld(1.0);
            ld& ans = dp2[i][j];
            if (memo2[i][j]) return ans;

            for (int k=0; k<n; ++k) ans += go2(i-1, k)*t[j][k]*g[j][x[i]];

            memo2[i][j]=1;
            return ans;
        };

        ld best = 0.0;
        for(int i=0; i<n; ++i) best += go(0, i)*(1.0/ld(n));

        cout << fixed << setprecision(5);
        for(int i=0; i<n; ++i) cout << a[i] << ' '; cout << endl;
        for (int i=0; i<(int)x.size(); ++i) {
            for (int j=0; j<n; ++j) cout << go(i, j)*go2(i, j) / best << ' ';
            cout << endl;
        }
    }
    void printTransition() {
        cout << fixed << setprecision(3);
        for (char& c : a) cout << '\t' << c; cout << endl;
        for(int i=0; i<n; ++i) {
            cout << a[i] << ' ';
            for(int j=0; j<n; ++j) cout << t[i][j] << ' ';
            cout << endl;
        }
    }
    void printEmmision() {
        cout << fixed << setprecision(3);
        for (char& c : e) cout << '\t' << c; cout << endl;
        for(int i=0; i<n; ++i) {
            cout << a[i] << ' ';
            for(int j=0; j<m; ++j) cout << g[i][j] << ' ';
            cout << endl;
        }
    }
    void learning(int iterations) {
        while (iterations--) {
            HMM hmm(xs, e, decodingProblem(), a);

            t = Matrix(n, vector<ld>(n)), g = Matrix(n, vector<ld>(m));

            for (int i=0; i<n; ++i) {
                for (int j=0; j<n; ++j) t[i][j] = hmm.transition[i][j];
            }

            for (int i=0; i<n; ++i) {
                for (int j=0; j<m; ++j) g[i][j] = hmm.emmit[i][j];
            }
        }

        printTransition();
        cout << line << endl;
        printEmmision();
    }
};


