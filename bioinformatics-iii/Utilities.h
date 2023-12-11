#include <bits/stdc++.h>
using namespace std;
using Align = pair<int, pair<string, string>>;
using Edge = pair<pair<int, int>, pair<int, int>>;
using MultipleAlignemnt = pair<int, vector<string>>;

const int oo = 1e9;

int PAM250[26][26] = {
    { 2,  0, -2,  0,  0, -3,  1, -1, -1, 0, -1, -2, -1,  0,  0,  1,  0, -2,  1,  1, 0,  0, -6,  0, -3, 0},
    { 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0, 0},
    {-2,  0, 12, -5, -5, -4, -3, -3, -2, 0, -5, -6, -5, -4,  0, -3, -5, -4,  0, -2, 0, -2, -8,  0,  0, 0},
    { 0,  0, -5,  4,  3, -6,  1,  1, -2, 0,  0, -4, -3,  2,  0, -1,  2, -1,  0,  0, 0, -2, -7,  0, -4, 0},
    { 0,  0, -5,  3,  4, -5,  0,  1, -2, 0,  0, -3, -2,  1,  0, -1,  2, -1,  0,  0, 0, -2, -7,  0, -4, 0},
    {-3,  0, -4, -6, -5,  9, -5, -2,  1, 0, -5,  2,  0, -3,  0, -5, -5, -4, -3, -3, 0, -1,  0,  0,  7, 0},
    { 1,  0, -3,  1,  0, -5,  5, -2, -3, 0, -2, -4, -3,  0,  0,  0, -1, -3,  1,  0, 0, -1, -7,  0, -5, 0},
    {-1,  0, -3,  1,  1, -2, -2,  6, -2, 0,  0, -2, -2,  2,  0,  0,  3,  2, -1, -1, 0, -2, -3,  0,  0, 0},
    {-1,  0, -2, -2, -2,  1, -3, -2,  5, 0, -2,  2,  2, -2,  0, -2, -2, -2, -1,  0, 0,  4, -5,  0, -1, 0},
    { 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0, 0},
    {-1,  0, -5,  0,  0, -5, -2,  0, -2, 0,  5, -3,  0,  1,  0, -1,  1,  3,  0,  0, 0, -2, -3,  0, -4, 0},
    {-2,  0, -6, -4, -3,  2, -4, -2,  2, 0, -3,  6,  4, -3,  0, -3, -2, -3, -3, -2, 0,  2, -2,  0, -1, 0},
    {-1,  0, -5, -3, -2,  0, -3, -2,  2, 0,  0,  4,  6, -2,  0, -2, -1,  0, -2, -1, 0,  2, -4,  0, -2, 0},
    { 0,  0, -4,  2,  1, -3,  0,  2, -2, 0,  1, -3, -2,  2,  0,  0,  1,  0,  1,  0, 0, -2, -4,  0, -2, 0},
    { 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0, 0},
    { 1,  0, -3, -1, -1, -5,  0,  0, -2, 0, -1, -3, -2,  0,  0,  6,  0,  0,  1,  0, 0, -1, -6,  0, -5, 0},
    { 0,  0, -5,  2,  2, -5, -1,  3, -2, 0,  1, -2, -1,  1,  0,  0,  4,  1, -1, -1, 0, -2, -5,  0, -4, 0},
    {-2,  0, -4, -1, -1, -4, -3,  2, -2, 0,  3, -3,  0,  0,  0,  0,  1,  6,  0, -1, 0, -2,  2,  0, -4, 0},
    { 1,  0,  0,  0,  0, -3,  1, -1, -1, 0,  0, -3, -2,  1,  0,  1, -1,  0,  2,  1, 0, -1, -2,  0, -3, 0},
    { 1,  0, -2,  0,  0, -3,  0, -1,  0, 0,  0, -2, -1,  0,  0,  0, -1, -1,  1,  3, 0,  0, -5,  0, -3, 0},
    { 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0, 0},
    { 0,  0, -2, -2, -2, -1, -1, -2,  4, 0, -2,  2,  2, -2,  0, -1, -2, -2, -1,  0, 0,  4, -6,  0, -2, 0},
    {-6,  0, -8, -7, -7,  0, -7, -3, -5, 0, -3, -2, -4, -4,  0, -6, -5,  2, -2, -5, 0, -6, 17,  0,  0, 0},
    { 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0, 0},
    {-3,  0,  0, -4, -4,  7, -5,  0, -1, 0, -4, -1, -2, -2,  0, -5, -4, -4, -3, -3, 0, -2,  0,  0, 10, 0},
    { 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0, 0}
};

int BLOSUM62[26][26] = {
    { 4, 0,  0, -2, -1, -2,  0, -2, -1,  0, -1, -1, -1, -2,  0, -1, -1, -1,  1,  0, 0,  0, -3, 0, -2,  0},
    { 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0, 0,  0,  0},
    { 0, 0,  9, -3, -4, -2, -3, -3, -1,  0, -3, -1, -1, -3,  0, -3, -3, -3, -1, -1, 0, -1, -2, 0, -2,  0},
    {-2, 0, -3,  6,  2, -3, -1, -1, -3,  0, -1, -4, -3,  1,  0, -1,  0, -2,  0, -1, 0, -3, -4, 0, -3,  0},
    {-1, 0, -4,  2,  5, -3, -2,  0, -3,  0,  1, -3, -2,  0,  0, -1,  2,  0,  0, -1, 0, -2, -3, 0, -2,  0},
    {-2, 0, -2, -3, -3,  6, -3, -1,  0,  0, -3,  0,  0, -3,  0, -4, -3, -3, -2, -2, 0, -1,  1, 0,  3,  0},
    { 0, 0, -3, -1, -2, -3,  6, -2, -4,  0, -2, -4, -3,  0,  0, -2, -2, -2,  0, -2, 0, -3, -2, 0, -3,  0},
    {-2, 0, -3, -1,  0, -1, -2,  8, -3,  0, -1, -3, -2,  1,  0, -2,  0,  0, -1, -2, 0, -3, -2, 0,  2,  0},
    {-1, 0, -1, -3, -3,  0, -4, -3,  4,  0, -3,  2,  1, -3,  0, -3, -3, -3, -2, -1, 0,  3, -3, 0, -1,  0},
    { 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0, 0,  0,  0},
    {-1, 0, -3, -1,  1, -3, -2, -1, -3,  0,  5, -2, -1,  0,  0, -1,  1,  2,  0, -1, 0, -2, -3, 0, -2,  0},
    {-1, 0, -1, -4, -3,  0, -4, -3,  2,  0, -2,  4,  2, -3,  0, -3, -2, -2, -2, -1, 0,  1, -2, 0, -1,  0},
    {-1, 0, -1, -3, -2,  0, -3, -2,  1,  0, -1,  2,  5, -2,  0, -2,  0, -1, -1, -1, 0,  1, -1, 0, -1,  0},
    {-2, 0, -3,  1,  0, -3,  0,  1, -3,  0,  0, -3, -2,  6,  0, -2,  0,  0,  1,  0, 0, -3, -4, 0, -2,  0},
    { 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0, 0,  0,  0},
    {-1, 0, -3, -1, -1, -4, -2, -2, -3,  0, -1, -3, -2, -2,  0,  7, -1, -2, -1, -1, 0, -2, -4, 0, -3,  0},
    {-1, 0, -3,  0,  2, -3, -2,  0, -3,  0,  1, -2,  0,  0,  0, -1,  5,  1,  0, -1, 0, -2, -2, 0, -1,  0},
    {-1, 0, -3, -2,  0, -3, -2,  0, -3,  0,  2, -2, -1,  0,  0, -2,  1,  5, -1, -1, 0, -3, -3, 0, -2,  0},
    { 1, 0, -1,  0,  0, -2,  0, -1, -2,  0,  0, -2, -1,  1,  0, -1,  0, -1,  4,  1, 0, -2, -3, 0, -2,  0},
    { 0, 0, -1, -1, -1, -2, -2, -2, -1,  0, -1, -1, -1,  0,  0, -1, -1, -1,  1,  5, 0,  0, -2, 0, -2,  0},
    { 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0, 0,  0,  0},
    { 0, 0, -1, -3, -2, -1, -3, -3,  3,  0, -2,  1,  1, -3,  0, -2, -2, -3, -2,  0, 0,  4, -3, 0, -1,  0},
    {-3, 0, -2, -4, -3,  1, -2, -2, -3,  0, -3, -2, -1, -4,  0, -4, -2, -3, -3, -2, 0, -3, 11, 0,  2,  0},
    { 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0, 0,  0,  0},
    {-2, 0, -2, -3, -2,  3, -3,  2, -1,  0, -2, -1, -1, -2,  0, -3, -1, -2, -2, -2, 0, -1,  2, 0,  7,  0},
    { 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0, 0,  0,  0}
};

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
long long  dpChangeWays(int n, vector<int> coins) {
    vector<long long> dp(n+1, 0);
    dp[0] = 1;
    for (int i=1; i<=n; ++i) {
        for(int& c : coins) {
            if (i-c>=0) dp[i] += dp[i-c];
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
Align globalAlignment(int ma, int mma, int indel, string s, string t) {
    function<int(char, char)> getScore = [&](char a, char b) {return a==b ? ma : -mma; };
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, -oo));

    dp[0][0] = 0;
    for (int i=0; i<=n; ++i) {
        for (int j=0; j<=m; ++j) {
            if (i) dp[i][j] = max(dp[i][j], dp[i-1][j] - indel);
            if (j) dp[i][j] = max(dp[i][j], dp[i][j-1] - indel);
            if (i && j) dp[i][j] = max(dp[i][j], dp[i-1][j-1] + getScore(s[i-1], t[j-1]));
        }
    }

    int i = n, j = m;
    string sa = "", ta="";
    while (i!=0 || j!=0) {
        if (i && j && dp[i-1][j-1] + getScore(s[i-1], t[j-1]) == dp[i][j]) {
            sa += s[i-1], ta += t[j-1];
            i--, j--;
        } else if (i && dp[i][j] == dp[i-1][j] - indel) {
            sa += s[i-1], ta += '-';
            i--;
        } else {
            sa += '-', ta += t[j-1];
            j--;
        }
    }

    reverse(sa.begin(), sa.end());
    reverse(ta.begin(), ta.end());
    return {dp[n][m], {sa, ta}};
}
Align globalAlignmentBLOSUM(int indel, string s, string t) {
    function<int(char, char)> getScore = [&](char a, char b) {return BLOSUM62[a-'A'][b-'A']; };
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, -oo));

    dp[0][0] = 0;
    for (int i=0; i<=n; ++i) {
        for (int j=0; j<=m; ++j) {
            if (i) dp[i][j] = max(dp[i][j], dp[i-1][j] - indel);
            if (j) dp[i][j] = max(dp[i][j], dp[i][j-1] - indel);
            if (i && j) dp[i][j] = max(dp[i][j], dp[i-1][j-1] + getScore(s[i-1], t[j-1]));
        }
    }

    int i = n, j = m;
    string sa = "", ta="";
    while (i!=0 || j!=0) {
        if (i && j && dp[i-1][j-1] + getScore(s[i-1], t[j-1]) == dp[i][j]) {
            sa += s[i-1], ta += t[j-1];
            i--, j--;
        } else if (i && dp[i][j] == dp[i-1][j] - indel) {
            sa += s[i-1], ta += '-';
            i--;
        } else {
            sa += '-', ta += t[j-1];
            j--;
        }
    }

    reverse(sa.begin(), sa.end());
    reverse(ta.begin(), ta.end());
    return {dp[n][m], {sa, ta}};
}
vector<vector<int>> globalAlignmentMatrix(int indel, string s, string t) {
    function<int(char, char)> getScore = [&](char a, char b) {return BLOSUM62[a-'A'][b-'A']; };
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, -oo));

    dp[0][0] = 0;
    for (int i=0; i<=n; ++i) {
        for (int j=0; j<=m; ++j) {
            if (i) dp[i][j] = max(dp[i][j], dp[i-1][j] - indel);
            if (j) dp[i][j] = max(dp[i][j], dp[i][j-1] - indel);
            if (i && j) dp[i][j] = max(dp[i][j], dp[i-1][j-1] + getScore(s[i-1], t[j-1]));
        }
    }
    return dp;
}
Align localAlignment(int indel, string s, string t) {
    function<int(char, char)> getScore = [&](char a, char b) {return PAM250[a-'A'][b-'A']; };
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, -oo));

    dp[0][0] = 0;
    for (int i=0; i<=n; ++i) {
        for (int j=0; j<=m; ++j) {
            dp[i][j] = 0;
            if (i) dp[i][j] = max(dp[i][j], dp[i-1][j] - indel);
            if (j) dp[i][j] = max(dp[i][j], dp[i][j-1] - indel);
            if (i && j) dp[i][j] = max(dp[i][j], dp[i-1][j-1] + getScore(s[i-1], t[j-1]));
        }
    }

    int r = n, c = m;
    for (int i=0; i<=n; ++i) {
        for (int j=0; j<=m; ++j) if (i+j>0) {
            if (dp[i][j] > dp[r][c]) r=i, c=j;
        }
    }

    int best=dp[r][c];
    string sa = "", ta="";
    while (r!=0 || c!=0) {
        if (dp[r][c] == 0) break;
        if (r && c && dp[r-1][c-1] + getScore(s[r-1], t[c-1]) == dp[r][c]) {
            sa += s[r-1], ta += t[c-1];
            r--, c--;
        } else if (r && dp[r][c] == dp[r-1][c] - indel) {
            sa += s[r-1], ta += '-';
            r--;
        } else {
            sa += '-', ta += t[c-1];
            c--;
        }
    }

    reverse(sa.begin(), sa.end());
    reverse(ta.begin(), ta.end());
    return {best, {sa, ta}};
}
int editDistance(string s, string t) {
    function<int(char, char)> getScore = [&](char a, char b) {return a != b; };
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, oo));

    dp[0][0] = 0;
    for (int i=0; i<=n; ++i) {
        for (int j=0; j<=m; ++j) {
            if (i) dp[i][j] = min(dp[i][j], dp[i-1][j] + 1);
            if (j) dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
            if (i && j) dp[i][j] = min(dp[i][j], dp[i-1][j-1] + getScore(s[i-1], t[j-1]));
        }
    }
    return dp[n][m];
}
Align fitttingAlignment (int indel, string s, string t, int ma, int mma) {
    //function<int(char, char)> getScore = [&](char a, char b) {return BLOSUM62[a-'A'][b-'A']; };
    function<int(char, char)> getScore = [&](char a, char b) { return a==b ? ma : -mma; };
    int n = s.size(), m=t.size();
    int best = globalAlignmentMatrix(1, s, t)[n][m], l=0, r=n-1;

    for(int i=0; i<n; ++i) {
        string v = "";
        for (int j=i; j<n && j-i+1 <= m; ++j) {
            v += s[j];
            int cur = globalAlignment(ma, mma, indel, v, t).first   ;
            if (cur>best) best=cur, l=i, r=j;
        }
    }

    n = r-l+1;
    s=s.substr(l, n);
    vector<vector<int>> dp = globalAlignmentMatrix(indel, s, t);

    int i = n, j = m;
    string sa = "", ta="";
    while (i!=0 || j!=0) {
        if (i && j && dp[i-1][j-1] + getScore(s[i-1], t[j-1]) == dp[i][j]) {
            sa += s[i-1], ta += t[j-1];
            i--, j--;
        } else if (i && dp[i][j] == dp[i-1][j] - indel) {
            sa += s[i-1], ta += '-';
            i--;
        } else {
            sa += '-', ta += t[j-1];
            j--;
        }
    }

    reverse(sa.begin(), sa.end());
    reverse(ta.begin(), ta.end());
    return {dp[n][m], {sa, ta}};
}
pair<string, string> build(int ma, int mma, int indel, string&s, string t, vector<vector<int>>& dp) {
    function<int(char, char)> getScore = [&](char a, char b) {return a==b ? ma : -mma; };

    int i=s.size(), j=t.size();
    string sa = "", ta="";
    while (i!=0 || j!=0) {
        if (i && j && dp[i-1][j-1] + getScore(s[i-1], t[j-1]) == dp[i][j]) {
            sa += s[i-1], ta += t[j-1];
            i--, j--;
        } else if (i && dp[i][j] == dp[i-1][j] - indel) {
            sa += s[i-1], ta += '-';
            i--;
        } else {
            sa += '-', ta += t[j-1];
            j--;
        }
    }

    reverse(sa.begin(), sa.end());
    reverse(ta.begin(), ta.end());
    return {sa, ta};
}
Align overlapAlignment (int ma, int mma, int indel, string s, string t) {
    function<int(char, char)> getScore = [&](char a, char b) {return a==b ? ma : -mma; };
    int n = s.size(), m=t.size();
    int best=-oo;
    string sa, ta;

    for (int p=n-1; p>=0; --p) {
        string ss = s.substr(p);
        int nn=ss.size();
        vector<vector<int>> dp(nn+1, vector<int>(m+1, -oo));
        dp[0][0] = 0;

        for (int i=0; i<=nn; ++i) {
            for (int j=0; j<=m; ++j) {
                if (i) dp[i][j] = max(dp[i][j], dp[i-1][j] - indel);
                if (j) dp[i][j] = max(dp[i][j], dp[i][j-1] - indel);
                if (i && j) dp[i][j] = max(dp[i][j], dp[i-1][j-1] + getScore(ss[i-1], t[j-1]));
            }

            for(int j=1; j<=m; ++j) if (dp[nn][j] > best) {
                best = dp[i][j];
                pair<string, string> res = build(ma, mma, indel, ss, t.substr(0, j), dp);
                sa=res.first, ta=res.second;
            }
        }
    }
    return {best, {sa, ta}};
}
Align affineGapAlignment(int ma, int mma, int go, int ge, string s, string t) {
    int n = s.size(), m = t.size();

    vector<vector<int>> dp[3] = {vector<vector<int>>(n+1, vector<int>(m+1)),
                                 vector<vector<int>>(n+1, vector<int>(m+1)),
                                 vector<vector<int>>(n+1, vector<int>(m+1))};
    vector<vector<bool>> memo[3] = {vector<vector<bool>>(n+1, vector<bool>(m+1, 0)),
                                    vector<vector<bool>>(n+1, vector<bool>(m+1, 0)),
                                    vector<vector<bool>>(n+1, vector<bool>(m+1, 0))};

    //0 middle, 2 = lower(s), 1 = upper(t)
    function<int(int, int, int)> solve = [&](int k, int i, int j) {
        if (i>=n && j>=m) return 0;
        int& ans = dp[i][j][k];
        if (memo[i][j][k]) return ans;

        ans= -oo;
        if (i<n) ans=max(ans, solve(1, i+1, j) - (k!=1?go:ge));
        if (j<m) ans=max(ans, solve(2, i, j+1) - (k!=2?go:ge));
        if (i<n && j<m) ans=max(ans, solve(0, i+1, j+1) + (s[i]==t[j]?ma:-mma));

        memo[k][i][j]=1;
        return ans;
    };

    string sa="", ta="";
    function <void(int, int, int)> build = [&](int k, int i, int j) {
        if (i>=n && j>=m) return;

        int best = solve(k, i, j);
        if (i<n && solve(1, i+1, j)-(k!=1?go:ge) == best) {
            ta += '-'; sa += s[i];
            build(1, i+1, j);
            return;
        }
        if (j<m && solve(2, i, j+1)-(k!=2?go:ge) == best) {
            ta += t[j]; sa += '-';
            build(2, i, j+1);
            return;
        }

        ta+=t[j], sa+=s[i];
        build(0, i+1, j+1);
    };

    build(0, 0, 0);
    return {solve(0, 0, 0), {sa, ta}};
}
/*
Edge MiddleEdge(int ma, int mma, int indel, string s, string t) {
    int n=s.size(), m=t.size();
    vector<vector<int>> pre(n+1, vector<int>(2));
    vector<vector<int>> su(n+1, vector<int>(2));

    for(int j=0; j<=m/2; ++j) {
        for(int i=0; i<=n; ++i) {
            if (i) pre[i][j&1] = max(pre[i][j&1], pre[i-1][j&1] - indel);
            if (j) pre[i][j&1] = max(pre[i][j&1], pre[i][(j-1)&1] - indel);
            if (i && j) pre[i][j&1] = max(pre[i][j&1], pre[i-1][(j-1)&1] + (s[i-1]==t[j-1]?ma:-mma));
        }
    }


    for(int j=m; j>=m/2; --j) {
        for(int i=0; i<=n; ++i) {
            if (i) su[i][j&1] = max(su[i][j&1], su[i-1][j&1] - indel);
            if (j+1<=m) su[i][j&1] = max(su[i][j&1], su[i][(j+1)&1] - indel);
            if (i && j+1<=m) su[i][j&1] = max(su[i][j&1], su[i-1][(j+1)&1] + (s[i-1]==t[j-1]?ma:-mma));
        }
    }

    int r1=0, r2=0, c1=(m/2)&1, c2=(m/2+1)&1;
    for(int i=0; i<=n; ++i) if(pre[i][c1] > pre[r1][c1]) r1=i;
    if (r1+1<=n && su[r1+1][c2] + (s[r1]==t[m/2]?ma:-mma) == su[r1+1][c1]) return {{r1, m/2}, {r1+1, m/2+1}};
    if (r1+1<=n && su[r1+1][c1] + (s[r1]==t[m/2]?ma:-mma) == su[r1+1][c1]) return {{r1, m/2}, {r1+1, m/2+1}};


}
*/
MultipleAlignemnt miltipleAlignment(string s, string t, string w) {
    int n=s.size(), m=t.size(), o=w.size();
    int dp[15][15][15];
    bool memo[15][15][15];

    function<int(int, int, int)> solve = [&](int i, int j, int k) {
        if (i>=n && j>=m && k>=o) return 0;
        int& ans = dp[i][j][k];
        if (memo[i][j][k]) return ans;

        ans= -oo;
        if (i<n) ans=max(ans, solve(i+1, j, k));
        if (j<m) ans=max(ans, solve(i, j+1, k));
        if (k<o) ans=max(ans, solve(i, j, k+1));
        if (i<n && j<m)ans=max(ans, solve(i+1, j+1, k));
        if (i<n && k<o) ans=max(ans, solve(i+1, j, k+1));
        if (j<m && k<o) ans=max(ans, solve(i, j+1, k+1));
        if (i<n && j<m && k<o) ans=max(ans, solve(i+1, j+1, k+1)+(s[i]==t[j] && t[j]==w[k]));

        memo[i][j][k]=1;
        return ans;
    };

    vector<string> ans(4, "");
    function<void(int, int, int)> build = [&](int i, int j, int k) {
        if (i>=n && j>=m && k>=o) return;
        int best = solve(i, j, k);

        if (i<n && best == solve(i+1, j, k)) {
            ans[0] += s[i], ans[1] += '-', ans[2]+='-';
            build(i+1, j, k);
            return;
        }
        if (j<m && best == solve(i, j+1, k)) {
            ans[0] += '-', ans[1] += t[j], ans[2]+='-';
            build(i, j+1, k);
            return;
        }
        if (k<o && best == solve(i, j, k+1)) {
            ans[0] += '-', ans[1] += '-', ans[2]+=w[k];
            build(i, j, k+1);
            return;
        }
        if (i<n && j<m && best == solve(i+1, j+1, k)) {
            ans[0] += s[i], ans[1] += t[j], ans[2]+='-';
            build(i+1, j+1, k);
            return;
        }
        if (i<n && k<o && best == solve(i+1, j, k+1)) {
            ans[0] += s[i], ans[1] += '-', ans[2]+=w[k];
            build(i+1, j, k+1);
            return;
        }
        if (j<m && k<o && best == solve(i, j+1, k+1)) {
            ans[0] += '-', ans[1] += t[j], ans[2]+=w[k];
            build(i, j+1, k+1);
            return;
        }

        ans[0] += s[i], ans[1] += t[j], ans[2]+=w[k];

        build(i+1, j+1, k+1);
    };

    build(0, 0, 0);
    return {solve(0, 0, 0), ans};
}

string miltipleLCS(string s, string t, string w) {
    int n=s.size(), m=t.size(), o=w.size();
    int dp[15][15][15];
    bool memo[15][15][15];

    function<int(int, int, int)> solve = [&](int i, int j, int k) {
        if (i>=n && j>=m && k>=o) return 0;
        int& ans = dp[i][j][k];
        if (memo[i][j][k]) return ans;

        ans=0;
        if (i<n) ans=max(ans, solve(i+1, j, k));
        if (j<m) ans=max(ans, solve(i, j+1, k));
        if (k<o) ans=max(ans, solve(i, j, k+1));
        if (i<n && j<m)ans=max(ans, solve(i+1, j+1, k));
        if (i<n && k<o) ans=max(ans, solve(i+1, j, k+1));
        if (j<m && k<o) ans=max(ans, solve(i, j+1, k+1));
        if (i<n && j<m && k<o && s[i]==t[j]&&t[j]==w[k]) ans=max(ans, solve(i+1, j+1, k+1)+1);

        memo[i][j][k]=1;
        return ans;
    };


    vector<string> ans(4, "");
    function<void(int, int, int)> build = [&](int i, int j, int k) {
        if (i>=n && j>=m && k>=o) return;

        int best = solve(i, j, k);
        if (i<n && best == solve(i+1, j, k)) {
            build(i+1, j, k);
            return;
        }
        if (j<m && best == solve(i, j+1, k)) {
            build(i, j+1, k);
            return;
        }
        if (k<o && best == solve(i, j, k+1)) {
            build(i, j, k+1);
            return;
        }
        if (i<n && j<m && best == solve(i+1, j+1, k)) {
            build(i+1, j+1, k);
            return;
        }
        if (i<n && k<o && best == solve(i+1, j, k+1)) {
            build(i+1, j, k+1);
            return;
        }
        if (j<m && k<o && best == solve(i, j+1, k+1)) {
            build(i, j+1, k+1);
            return;
        }

        ans[0] += s[i];
        build(i+1, j+1, k+1);
    };

    build(0, 0, 0);
    return ans[0];
}
