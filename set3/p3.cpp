#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> inp;
    for (int i = 0; i < n; i++){
        int num;
        cin >> num;
        inp.push_back(num);
    }

    vector<uint32_t> arr;
    vector<uint32_t> temp(n);
    for (int i = 0; i < n; i++)
        arr.push_back(uint32_t(inp[i]) ^ 0x80000000u);

    for (int byte = 0; byte < 4; byte++) {
        vector<int> cnt(256, 0); 

        for (int i = 0; i < n; i++) {
            uint32_t c = (arr[i] >> (byte * 8)) & 0xFF;
            cnt[c]++;
        }

        int pref = 0;
        for (int i = 0; i < 256; i++) {
            int tmp = cnt[i];
            cnt[i] = pref;
            pref += tmp;
        }

        for (int i = 0; i < n; i++) {
            uint32_t c = (arr[i] >> (byte * 8)) & 0xFF;
            temp[cnt[c]] = arr[i];
            cnt[c]++;
        }
        arr.swap(temp);
    }

    for (int i = 0; i < n; i++) {
        int x = int(arr[i] ^ 0x80000000u);
        cout << x << " ";
    }
    return 0;
}
