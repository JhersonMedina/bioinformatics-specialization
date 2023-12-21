#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r) {
	return uniform_int_distribution<int>(l,r)(rng);
}

using T = double;
struct pt {
    vector<T> x;
    pt operator + (pt p) {
        vector<T> y = x;
        for(int i=0; i<(int)x.size(); ++i) y[i] += p.x[i];
        return {y};
    }
    pt operator - (pt p) {
        vector<T> y = x;
        for(int i=0; i<(int)x.size(); ++i) y[i] -= p.x[i];
        return {y};
    }
    pt operator / (T d) {
        vector<T> y = x;
        for(T& i : y) i /= d;
        return {y};
    }
    bool operator == (pt p) {
        if (x.size()!=p.x.size()) return 0;

        for(int i=0; i<(int)x.size(); ++i) if (x[i]!=p.x[i]) return 0;
        return 1;
    }
    bool operator <(pt p) {
        for(int i=0; i<(int)x.size(); ++i) {
            if (x[i] < p.x[i]) return 1;
        }
        return 0;
    }
};
double sq(pt p) {
    double ans=0.0;
    for(T& xi : p.x) ans += xi*xi;
    return ans;
}
double abs(pt p) { return sqrt(sq(p)); }
double distance(pt p, pt q) { return abs(p - q); }
double distanceSquare(pt p, pt q) { return sq(p - q); }

bool arraysAreEqual(vector<pt> a, vector<pt> b) {
    if (a.size()!=b.size()) return 0;
    sort(a.begin(), a.end()); sort(b.begin(), b.end());
    for(int i=0; i<(int)a.size(); ++i) if (!(a[i] == b[i])) return 0;
    return 1;
}
void shuffleArray(vector<pt>& a) {
    int n=a.size();
    for(int i=0; i<n; ++i) swap(a[i], a[rand(0, i)]);
}

using PD = pair<T, int>;

pt ptRead(int m) {
    pt p;
    for(int i=0; i<m; ++i) {
        T xi; cin >> xi;
        p.x.push_back(xi);
    }
    return p;
}
vector<double> dread() {
    string s; getline(cin, s);
    vector<double> ans;
    for(int i=0, j=0; i<(int)s.size(); ++i) {
        j=i;
        while (j<(int)s.size() && (s[j] == '-' || s[j] == '+' || isdigit(s[j]))) j++;
        ans.push_back(stod(s.substr(i, j-i)));
        i=j;
    }
    return ans;
}
void printPoint(pt p) { for(T d : p.x) cout << d << ' '; cout << endl;}
void printSet(vector<pt> p) {
    for(pt& pi : p) printPoint(pi);
}


double maxDistance(vector<pt> points, vector<pt> centres) {
    double ans = -1.0;
    for(pt& p : points) {
        double best=-1.0;
        for(pt& q : centres) {
            double d = abs(q - p);
            if (best == -1.0 || d<best) best = d;
        }
        ans=max(ans, best);
    }
    return ans;
}
PD closestDistance(pt p, vector<pt> centres) {
    PD ans; ans.first = -1.0;
    for(int i=0; i<(int)centres.size(); ++i) {
        pt& c = centres[i];
        if (ans.first == -1.0 || distanceSquare(p, c) < ans.first) ans= {distanceSquare(p, c), i};
    }
    return ans;
}
pt farthestFromCentre(vector<pt> points, vector<pt> centres) {
    pt ans = points[0];
    T d = closestDistance(ans, centres).first;
    for(pt& p : points) {
        T cur = closestDistance(p, centres).first;
        if (cur>d) ans=p, d=cur;
    }

    return ans;
}
vector<pt> farthestFirstTraversal(vector<pt> p, int k) {
    vector<pt> centres = {p[0]};
    while ((int)centres.size()<k) {
        pt c = farthestFromCentre(p, centres);
        centres.push_back(c);
    }
    return centres;
}
T squareErrorDistortion(vector<pt> points, vector<pt> centres) {
    T ans = 0.0;
    for(pt& p : points) {
        ans += closestDistance(p, centres).first;
    }
    return ans / double(points.size());
}
pt gravityCentre(vector<pt>& a) {
    int n = a.size(), m = a[0].x.size();
    pt ans; ans.x.assign(m, 0.0);
    for(pt& p : a) ans = ans + p;
    return ans / T(n);
}
vector<pt> lloydAlgorithm(vector<pt> points, int k) {
    int m=points[0].x.size();
    vector<pt> centres = vector<pt>(points.begin(), points.begin()+k);

    while (true) {
        vector<pt> centres_new;
        vector<vector<pt>> cluster(k);

        for(pt& p : points)  {
            PD best = closestDistance(p, centres);
            cluster[best.second].push_back(p);
        }

        for(vector<pt>& c : cluster) centres_new.push_back(gravityCentre(c));

        //if (arraysAreEqual(centres, centres_new)) break;
        if(squareErrorDistortion(points, centres) - squareErrorDistortion(points, centres_new) <= 1e-6) break;
        centres = centres_new;
    }
    return centres;
}
vector<pt> bestLloyd(vector<pt> points, int k) {
    vector<pt> ans = lloydAlgorithm(points, k);
    /*for (int _=0; _<100; ++_) {
        shuffleArray(points);
        vector<pt> cur = lloydAlgorithm(points, k);
        if (squareErrorDistortion(points, ans) > squareErrorDistortion(points, cur)) ans=cur;
    }*/
    return ans;
}
