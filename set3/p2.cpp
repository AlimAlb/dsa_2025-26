#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int min = -10e6;
    int max =  -min;
    int values = max-min +1;
    vector<int> frequency(values, 0);

    for (int i = 0; i < n; i++) {
        int item;
        cin >> item;
        frequency[item+max]++;
    }

    for (int i = 0; i < values; i++) {
        int value = i - max;
        while (frequency[i]--) {
            cout << value << ' ';
        }
    }
    return 0;
}
