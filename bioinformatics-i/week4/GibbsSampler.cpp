#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <array>
#include <iomanip>

using namespace std;
/* *
 *
 * Too many mind, no mind.
 *
 * */
int N, k, t;
char alp[4] = {'A', 'C', 'G', 'T'};
vector <string> patterns;
 

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 
int rand(int l, int r) {
	return uniform_int_distribution<int>(l,r)(rng);
}

int random (vector <double>& prob) {
	discrete_distribution<int> d(prob.begin(), prob.end());
	return d(rng);
}

vector < vector <double>> formProfile(vector <string>& motifs) {
	vector < vector <double>> profile(4, vector <double> (k));

	for (int i = 0; i < k; i++) {
		for (int c = 0; c < 4; c++) {
			int cnt = 0;
			for (int j = 0; j < t; j++) cnt += motifs[j][i] == alp[c];
			profile[c][i] = double(cnt + 1) / double(t + t);
		}
	}

	return profile;
}
double getKmerProb(string s, vector <vector<double>>& profile) {
	double cur = 1.0;
	for (int i = 0; i < k; i++) {
		if (s[i] == 'A') cur *= profile[0][i];
		if (s[i] == 'C') cur *= profile[1][i];
		if (s[i] == 'G') cur *= profile[2][i];
		if (s[i] == 'T') cur *= profile[3][i];
	}
	return cur;
}
int score(vector <string> motifs) {
	int ans = 0;
	for (int i = 0; i < k; i++) {
		int best = 0;
		map <char, int> m;

		for (int j = 0; j < t; j++) {
			m[motifs[j][i]]++;
			best = max(best, m[motifs[j][i]]);
		}
		ans += t - best;
	}
	return ans;
}

string getMotif(vector <vector<double>>& profile, string pattern) {
	vector <double> prob;
	for (int i = 0; i + k - 1 < pattern.size(); i++) {
		prob.push_back(getKmerProb(pattern.substr(i, k), profile));
	}
	int pos = random(prob);
	return pattern.substr(pos, k);
}

vector <string> gibbsSampler(vector <string>& motifs) {
	vector <string> bestMotifs = motifs;

	for (int i = 0; i < N; i++) {
		int j = rand(0, t - 1);
		vector <string> profileMotifs = motifs;
		for (int it = 0; it < motifs.size(); it++) {
			if (it != j) profileMotifs.push_back(motifs[it]);
		}

		vector <vector <double>> profile = formProfile(profileMotifs);
		motifs[j] = getMotif(profile, patterns[j]);
		if (score(motifs) < score(bestMotifs)) bestMotifs = motifs;
	}
	return bestMotifs;
}
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin >> k >> t >> N;

	patterns.resize(t);
	for (int i = 0; i < t; i++) cin >> patterns[i];

	vector <string> bestMotifs(t), motifs(t);;
	for (int i = 0; i < 20; i++) { 
		for (int j = 0; j < t; j++) {
			int l = rand(0, patterns[j].size() - k);
			motifs[j] = patterns[j].substr(l, k);
		}

		motifs = gibbsSampler(motifs);
		if (bestMotifs[0].empty() || score(motifs) < score(bestMotifs)) bestMotifs = motifs;
	}

	for (string& s : bestMotifs) cout << s << ' ';
	return 0;

}
