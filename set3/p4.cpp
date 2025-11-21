#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool is_greater(const string& s1,const string& s2) {
    int n1 = stoi(s1.substr(0, s1.find('/')));
    int d1 = stoi(s1.substr(s1.find('/') + 1));
    int n2 = stoi(s2.substr(0, s2.find('/')));
    int d2 = stoi(s2.substr(s2.find('/') + 1));
    return n1 * d2 < n2 * d1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> a;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        a.push_back(s);
    }

    stable_sort(a.begin(), a.end(), is_greater);

    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}
