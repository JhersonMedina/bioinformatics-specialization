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
int k, t;
char alp[4] = {'A', 'C', 'G', 'T'};
vector <string> patterns;

vector < vector <double>> formProfile(vector <string>& motifs) {
	vector < vector <double>> profile(4, vector <double> (k));

	for (int i = 0; i < k; i++) {
		for (int c = 0; c < 4; c++) {
			int cnt = 0;
			for (int j = 0; j < t; j++) cnt += motifs[j][i] == alp[c];
			profile[c][i] = double(cnt) / double(t);
		}
	}

	return profile;
}
string mostProbableKmer(string& s, vector <vector<double>>& profile) {
	string kmer = s.substr(0, k);
	double best = 0.0;

	for (int i = 0; i + k - 1 < s.size(); i++) {
		double cur = 1.0;
		for (int j = 0; j < k; j++) {
			if (s[i + j] == 'A') cur *= profile[0][j];
			if (s[i + j] == 'C') cur *= profile[1][j];
			if (s[i + j] == 'G') cur *= profile[2][j];
			if (s[i + j] == 'T') cur *= profile[3][j];
		}
		if (kmer.empty() || cur > best) best = cur, kmer = s.substr(i, k);
	}
	return kmer;
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
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> k >> t;
	patterns.resize(t);
	vector <string> bestMotifs(t);
	for (int i = 0; i < t; i++) {
		cin >> patterns[i];
		bestMotifs[i] = patterns[i].substr(0, k);
	}

	for (int i = 0; i + k - 1 < patterns[0].size(); i++) {
		vector <string> currentMotifs = {patterns[0].substr(i, k)};

		for (int j = 1; j < t; j++) {
			vector <vector <double>> profile = formProfile(currentMotifs);
			currentMotifs.push_back(mostProbableKmer(patterns[j], profile));
		}
		if (score(currentMotifs) < score(bestMotifs)) bestMotifs = currentMotifs;
	}

	for (auto& s : bestMotifs) cout << s << ' ';
	return 0;
}
