#include <bits/stdc++.h>
using namespace std;

using Path = vector<int>;
using Graph = vector<vector<int>>;

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
    int n=1;
    Trie trie;
    vector<map<string, int>> tree = {{}};
    vector<int> cnt = {0}, color = {0};
    string s;

    int size() { return tree.size(); }
    SuffixTree (string s): s(s) {
        s += '$';
        int m = s.find("#");
        for(int i=0; i<(int)s.size(); ++i) trie.add(s.substr(i), i<m ? 1 : 2);
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
void printMatch(map<string, vector<int>> match) {
    for(auto& [s, a] : match) {
        cout << s << ": ";
        for(int& i : a) cout << i << ' ';
        cout << endl;
    }
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

