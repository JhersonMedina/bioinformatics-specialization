#include <bits/stdc++.h>
using namespace std;

using Path = vector<int>;
using Graph = vector<vector<int>>;
using Match = pair<string, vector<int>>;
struct BWT {
    string p;
    int top, bottom, d;
};

const int MAXN = 1e5, INF = 1e9;
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
        if (s[i] == ' ') {
            ans.push_back(cur);
            cur="";
        } else cur+=s[i];
    }
    ans.push_back(cur);
    return ans;
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


