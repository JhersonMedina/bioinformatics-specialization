#include <bits/stdc++.h>
using namespace std;

map <string, char> code = {
    {"AAA", 'K'},
    {"AAC", 'N'},
    {"AAG", 'K'},
    {"AAU", 'N'},
    {"ACA", 'T'},
    {"ACC", 'T'},
    {"ACG", 'T'},
    {"ACU", 'T'},
    {"AGA", 'R'},
    {"AGC", 'S'},
    {"AGG", 'R'},
    {"AGU", 'S'},
    {"AUA", 'I'},
    {"AUC", 'I'},
    {"AUG", 'M'},
    {"AUU", 'I'},
    {"CAA", 'Q'},
    {"CAC", 'H'},
    {"CAG", 'Q'},
    {"CAU", 'H'},
    {"CCA", 'P'},
    {"CCC", 'P'},
    {"CCG", 'P'},
    {"CCU", 'P'},
    {"CGA", 'R'},
    {"CGC", 'R'},
    {"CGG", 'R'},
    {"CGU", 'R'},
    {"CUA", 'L'},
    {"CUC", 'L'},
    {"CUG", 'L'},
    {"CUU", 'L'},
    {"GAA", 'E'},
    {"GAC", 'D'},
    {"GAG", 'E'},
    {"GAU", 'D'},
    {"GCA", 'A'},
    {"GCC", 'A'},
    {"GCG", 'A'},
    {"GCU", 'A'},
    {"GGA", 'G'},
    {"GGC", 'G'},
    {"GGG", 'G'},
    {"GGU", 'G'},
    {"GUA", 'V'},
    {"GUC", 'V'},
    {"GUG", 'V'},
    {"GUU", 'V'},
    {"UAA", ' '},
    {"UAC", 'Y'},
    {"UAG", ' '},
    {"UAU", 'Y'},
    {"UCA", 'S'},
    {"UCC", 'S'},
    {"UCG", 'S'},
    {"UCU", 'S'},
    {"UGA", ' '},
    {"UGC", 'C'},
    {"UGG", 'W'},
    {"UGU", 'C'},
    {"UUA", 'L'},
    {"UUC", 'F'},
    {"UUG", 'L'},
    {"UUU", 'F'}
};
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
map<char, int> pepCodeUnique = {
    {'G', 57},
    {'A', 71},
    {'S', 87},
    {'P', 97},
    {'V', 99},
    {'T', 101},
    {'C', 103},
    {'I', 113},
    {'N', 114},
    {'D', 115},
    {'K', 128},
    {'E', 129},
    {'M', 131},
    {'H', 137},
    {'F', 147},
    {'R', 156},
    {'Y', 163},
    {'W', 186}
};
vector<char> peps = {
    'G',
    'A',
    'S',
    'P',
    'V',
    'T',
    'C',
    'I',
    'N',
    'D',
    'K',
    'E',
    'M',
    'H',
    'F',
    'R',
    'Y',
    'W'
};
vector<int> weights = {
    57,
    71,
    87,
    97,
    99,
    101,
    103,
    113,
    114,
    115,
    128,
    129,
    131,
    137,
    147,
    156,
    163,
    186
};
vector<int> extendedAlp() {
    vector<int> alp;
    for(int i =57; i<=200; ++i) alp.push_back(i);
    return alp;
}
vector<int> read() {
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
vector<string> readStrings() {
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
string toRNA(string s) {
    string ans = s;
    for(char& c : ans) if (c == 'T') c = 'U';
    return ans;
}
string toPep (string s) {
    s = toRNA(s);
    string ans="";
    for(int i=0; i<(int)s.size(); i+=3) ans += code[s.substr(i, 3)];
    return ans;
}
string rev (string s) {
    reverse(s.begin(), s.end());
    string ans=toRNA(s);
    for(char& c : ans) {
        if (c == 'A') c='U';
        else if (c == 'U') c='A';
        else if (c=='C') c='G';
        else c='C';
    }
    return ans;
}
vector<string> pepEncoding(string s, string t) {
    vector<string> ans;
    for (int i=0; i+3*t.size()<s.size(); ++i) {
        string w = s.substr(i, 3*t.size());
        if (toPep(w) == t || toPep(rev(w)) == t) ans.push_back(w);
    }
    return ans;
}
int weight(string s) {
    int ans=0;
    for(char& c : s) ans += pepCode[c];
    return ans;
}
vector<int> cycloSpectrum(string s) {
    int n = s.size();
    s += s;
    vector<pair<string, int>> ans;
    for (int i=0; i<n; ++i) {
        string cur="";
        for (int j=i; j-i<n-1; ++j) {
            cur+=s[j];
            ans.push_back({cur, weight(cur)});
        }
    }
    ans.push_back({s.substr(0, n), weight(s.substr(0, n))});
    sort(ans.begin(), ans.end(), [&](pair<string, int> a, pair<string, int> b) {
        if (a.first.size()!=b.first.size()) return a.first.size()<b.first.size();
        return a.first<b.first;
    });

    vector<int> res = {0};
    for(auto& it : ans) res.push_back(it.second);
    return res;
}
long long countPep(int sum) {
    vector <long long> dp(sum+1);
    dp[0] = 1;
    for (int i=1; i<=sum; ++i) {
        for (int& w : weights) if (i-w>=0) dp[i] += dp[i-w];
    }
    double avg = 0;
    for (int i=1000; i<=sum; ++i)avg += double(dp[i]) / double(dp[i-1]);
    return dp[sum];
}
vector<int> linearSpectrum(string s) {
    int n=s.size();
    vector<int> pre(n);
    for (int i=0; i<n; ++i) {
        pre[i] = weight(string(1, s[i]));
        if (i) pre[i] += pre[i-1];
    }
    vector<int> ans={0};
    for (int i=0; i<n; ++i) {
        for (int j=i; j<n; ++j) {
            int cur = pre[j] - (i?pre[i-1]:0);
            ans.push_back(cur);
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}
bool subset(vector<int>a, vector<int> b) {
    multiset<int> in;
    for(int& i : b) in.insert(i);

    for(int& i : a) {
        if (!in.count(i)) return 0;
    }
    return 1;
}
string toWeights (string c) {
    string cur = "";
    for (int i = 0; i<(int)c.size(); ++i) {
        if (i) cur += '-';
        cur += to_string(pepCode[c[i]]);
    }
    return cur;
}
vector<string> cyclopeptideSequencing(vector<int> specs) {
    queue<string> candidates;
    vector<string> ans;
    int parent = *max_element(specs.begin(), specs.end());

    for(auto& it : pepCode) candidates.push(string(1, it.first));
    while (!candidates.empty()) {
        string c = candidates.front(); candidates.pop();
        if (!subset(linearSpectrum(c), specs)) continue;
        if (weight(c) == parent) ans.push_back(toWeights(c));
        else {
            for(auto& it : pepCode) candidates.push(c + it.first);
        }
    }
    return ans;
}
int cycloScore(string s, vector<int> expSpec) {
    map <int, int> cnt;
    for (int& i : expSpec) cnt[i]++;
    vector<int> spec = cycloSpectrum(s);
    sort(spec.begin(), spec.end());

    int ans=0;
    for(int l=0, r=0; l<(int)spec.size(); l=r) {
        while (r<(int)spec.size() && spec[l] == spec[r]) r++;
        ans += min(r-l, cnt[spec[l]]);
    }
    return ans;
}
int linearScore(string s, vector<int> expSpec) {
    map <int, int> cnt;
    for (int& i : expSpec) cnt[i]++;
    vector<int> spec = linearSpectrum(s);
    sort(spec.begin(), spec.end());

    int ans=0;
    for(int l=0, r=0; l<(int)spec.size(); l=r) {
        while (r<(int)spec.size() && spec[l] == spec[r]) r++;
        ans += min(r-l, cnt[spec[l]]);
    }
    return ans;
}
vector<string> expand(vector<string> in) {
    vector<string> ans;
    for(string& s : in) {
        for(auto& p : pepCode) ans.push_back(s+p.first);
    }
    return ans;
}
vector<pair<int, string>> trim (vector<pair<int, string>> keep, int n) {
    sort(keep.rbegin(), keep.rend());
    while ((int)keep.size()>n && keep.back().first < keep[n-1].first){
        keep.pop_back();
    }
    return keep;
}
vector<string> leaderboardCyclopeptideSequencing(int n, vector<int> spec) {
    vector<string> candidates = {""};
    vector<string> ans;
    int best=0, parent = *max_element(spec.begin(), spec.end());

    while (!candidates.empty()) {
        vector<pair<int, string>> keep;
        for(string& s : expand(candidates)) {
            int sc=cycloScore(s, spec), w=weight(s);
            if (w >= parent) {
                if (w == parent) {
                    if (sc>best) best = sc, ans = {s};
                    else if (sc == best) ans.push_back(s);
                    keep.push_back({linearScore(s, spec), s});
                }
            } else keep.push_back({linearScore(s, spec), s});
        }

        candidates.clear();
        for(auto& it : trim(keep, n)) candidates.push_back(it.second);
    }

    for(string& s : ans) {
        s = toWeights(s);
    }
    return ans;
}
vector<string> leaderboardCyclopeptideSequencingExtended(int n, vector<int> spec, vector<int> alp) {
    pepCode.clear();
    for(int& i : alp) pepCode[char(i)] = i;

    return leaderboardCyclopeptideSequencing(n, spec);
}
vector<int> spectralConvolution (vector<int> spec) {
    int n=spec.size();
    vector<int> ans;
    sort(spec.begin(), spec.end());
    for(int i=0; i<n; ++i) {
        for(int j=i+1; j<n; ++j) if (spec[j]>spec[i]) ans.push_back(spec[j]-spec[i]);
    }
    return ans;
}
vector<pair<int, int>> freq(vector<int> a) {
    sort(a.begin(), a.end());
    int n=a.size();
    vector<pair<int, int>> ans;
    for(int l=0, r=0; l<n; l=r) {
        while (r<n && a[r] == a[l]) r++;
        if (57 <= a[l] && a[l] <= 200) ans.push_back({r-l, a[l]});
    }
    return ans;
}
vector<string> convolutionCyclopeptideSequencing (int m, int n, vector<int> spec) {
    vector<pair<int, int>> f = freq(spectralConvolution(spec));
    sort(f.rbegin(), f.rend());

    vector<int> alp;
    for (int i=0; i<(int)f.size(); ++i) {
        if (i<m || f[i].first >= f[m-1].first) {
           alp.push_back(f[i].second);
        }
    }

    return leaderboardCyclopeptideSequencingExtended(n, spec, alp);
}
