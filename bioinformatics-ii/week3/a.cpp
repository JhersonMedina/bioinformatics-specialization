#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
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
    function<multiset<int>()> read = [&](){
        string s;
        getline(cin, s);
        multiset<int> ans;
        int cur=0;
        for(int i=0; i<s.size(); ++i) {
            if (s[i] == ' ') {
                ans.insert(cur);
                cur=0;
            } else cur = cur*10 + (s[i] - '0');
        }
        ans.insert(cur);
        return ans;
    };

    assert(code.size() == 64);
    function<string(string)> toRNA = [&](string s) {
        string ans = s;
        for(char& c : ans) if (c == 'T') c = 'U';
        return ans;
    };
    function<string(string)> toPep = [&](string s) {
        s = toRNA(s);
        string ans="";
        for(int i=0; i<s.size(); i+=3) ans += code[s.substr(i, 3)];
        return ans;
    };
    function<string(string)> rev = [&](string s) {
        reverse(s.begin(), s.end());
        string ans=toRNA(s);
        for(char& c : ans) {
            if (c == 'A') c='U';
            else if (c == 'U') c='A';
            else if (c=='C') c='G';
            else c='C';
        }
        return ans;
    };
    function<void()> pepEncoding = [&]() {
        string s, t; cin >> s >> t;
        cout << t << endl;

        return;
        for (int i=0; i+3*t.size()<s.size(); ++i) {
            string w = s.substr(i, 3*t.size());
            if (toPep(w) == t || toPep(rev(w)) == t) cout << w << endl;
        }
    };
    function<int(string)> weight = [&](string s) {
        int ans=0;
        for(char& c : s) ans += pepCode[c];
        return ans;
    };
    function<vector<int>()> spectrum = [&]() {
        string s; cin >> s;
        int n = s.size();
        s += s;
        vector<pair<string,int>> ans;
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
    };
    function<long long(int)> countPep = [&](int sum) {
        vector <long long> dp(sum+1);
        dp[0] = 1;
        for (int i=1; i<=sum; ++i) {
            for (int& w : weights) if (i-w>=0) dp[i] += dp[i-w];
        }
        double avg = 0;
        for (int i=1000; i<=sum; ++i)avg += double(dp[i]) / double(dp[i-1]);
        cout << avg / double(sum - 1000+1) << endl;
        return dp[sum];
    };
    function<vector<int>(string)> linearSpectrum = [&](string s) {
        int n=s.size();
        vector<int> pre(n);
        for (int i=0; i<n; ++i) {
            pre[i] = pepCode[s[i]];
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
    };
    function<bool(vector<int>, multiset<int>)>subset = [&](vector<int>a, multiset<int> b) {
        for(int& i : a) {
            if (!b.count(i)) return 0;
        }
        return 1;
    };
    function<void()> cyclopeptideSequencing = [&]() {
        multiset<int> specs = read();
        queue<string> candidates;
        set<string> ans;

        for(auto& it : pepCode) candidates.push(string(1, it.first));
        while (!candidates.empty()) {
            string c = candidates.front(); candidates.pop();
            if (!subset(linearSpectrum(c), specs)) continue;
            if (weight(c) == *specs.rbegin()) {
                string cur = "";
                for (int i = 0; i<c.size(); ++i) {
                    if (i) cur += '-';
                    cur += to_string(pepCode[c[i]]);
                }
                ans.insert(cur);
            } else {
                for(auto& it : pepCode) candidates.push(c + it.first);
            }
        }
        for(auto& it : ans) cout << it << ' ';
    };

    multiset<int> want = read(), a;
    string s; cin >> s;
    vector<int> ans = linearSpectrum(s);
    for(int i : ans) a.insert(i);
    for(auto i : a) cout << i <<' ';
    cout << endl;
    cout << subset(ans, want) << endl;
    return 0;
}
