#include "Utilities.h"

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
void printSet(vector<pt> p) {
    for(pt& pi : p) {
        for(T& d : pi) cout << d << ' ';
    }
    cout << endl;
}
