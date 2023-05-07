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

 

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 
int rand(int l, int r) {
	return uniform_int_distribution<int>(l,r)(rng);
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

vector <string> getMotifs(vector <vector<double>>& profile, vector <string>& motifs) {
	vector <string> newMotifs = motifs;
	for (int i = 0; i < motifs.size(); i++) newMotifs[i] = mostProbableKmer(motifs[i], profile);
	return newMotifs;
}

vector <string> randomizedMotifSearch (vector <string>& motifs) {
	vector <string> bestMotifs = motifs;
	while (true) {
		vector <vector <double>> profile = formProfile(motifs);
		motifs = getMotifs(profile, patterns);
		if (score(motifs) < score(bestMotifs)) bestMotifs = motifs;
		else return bestMotifs;
	}
}
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> k >> t;
	patterns.resize(t);
	for (int i = 0; i < t; i++) {
		cin >> patterns[i];
	}


	vector <string> bestMotifs(t), motifs(t);;
	for (int i = 0; i < 1000; i++) { 

		for (int i = 0; i < t; i++) {
			int l = rand(0, i + k - 1);
			motifs[i] = patterns[i].substr(l, k);
		}

		motifs = randomizedMotifSearch(motifs);
		if (bestMotifs[0].empty() || score(motifs) < score(bestMotifs)) bestMotifs = motifs;
	}

	for (string& s : bestMotifs) cout << s << ' ';
	return 0;

}
