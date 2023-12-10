#include <bits/stdc++.h>
using namespace std;

vector<int> iread() {
    string s;
    getline(cin, s);
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
    string s;
    getline(cin, s);
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

int dpChange(int n, vector<int> coins) {
    vector<int> dp(n+1, -1);
    dp[0] = 0;
    for (int i=1; i<=n; ++i) {
        for(int& c : coins) {
            if (i-c>=0) dp[i] = dp[i] == -1 ? dp[i-c]+1 : min(dp[i], dp[i-c]+1);
        }
    }
    return dp[n];
}
int manhattanTourist(int n, int m, vector<vector<int>> down, vector<vector<int>> right) {
    vector<vector<int>> dp(n, vector<int>(m, -1));
    dp[0][0] = 0;
    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            if (i) dp[i][j] = max(dp[i][j], dp[i-1][j]+down[i-1][j]);
            if (j) dp[i][j] = max(dp[i][j], dp[i][j-1]+right[i][j-1]);
        }
    }
    return dp[n-1][m-1];
}
int manhattanTouristExtedned(int n, int m, vector<vector<int>> down, vector<vector<int>> right, vector<vector<int>> dig) {
    vector<vector<int>> dp(n, vector<int>(m, -1));
    dp[0][0] = 0;
    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            if (i) dp[i][j] = max(dp[i][j], dp[i-1][j]+down[i-1][j]);
            if (j) dp[i][j] = max(dp[i][j], dp[i][j-1]+right[i][j-1]);
            if (i && j) dp[i][j] = max(dp[i][j], dp[i-1][j-1]+dig[i-1][j-1]);
        }
    }
    return dp[n-1][m-1];
}
string outputLCS(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    dp[0][0] = 0;
    for (int i=0; i<=n; ++i) {
        for (int j=0; j<=m; ++j) {
            if (i) dp[i][j] = max(dp[i][j], dp[i-1][j]);
            if (j) dp[i][j] = max(dp[i][j], dp[i][j-1]);
            if (i && j && s[i-1] == t[j-1]) dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
        }
    }
    int i = n, j = m;
    string ans = "";
    while (i!=0 || j!=0) {
        if (i && j && dp[i-1][j-1]+1 == dp[i][j] && s[i-1] == t[j-1]) {
            ans += s[i-1];
            i--, j--;
        } else if (i && dp[i][j] == dp[i-1][j]) i--;
        else j--;

    }
    reverse(ans.begin(), ans.end());
    return ans;
}
vector<int> longestPathInDag(int s, int m, vector<vector<pair<int, int>>> dag) {
    vector<int> dp(m+1, 0), par(m+1);
    for(int u=s; u<=m; ++u) {
        for (auto& e : dag[u]) {
            int v = e.first, w = e.second;
            dp[v] = max(dp[v], dp[u]+w);
            if (dp[v] == dp[u]+w) par[v] = u;
        }
    }
    vector<int> path;
    int u=m;
    while (u!=s) {
        path.push_back(u);
        u=par[u];
    }
    path.push_back(s);
    path.push_back(dp[m]);
    reverse(path.begin(), path.end());
    return path;
}
