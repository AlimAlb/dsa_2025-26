#include <iostream>
using namespace std;


int fast_sum(const vector<int>& arr, int k) { // в данном случае асимптотическая оценка O(n)
    int current_sum = 0;
    // сумма первого окна [0, k)
    for (int i = 0; i < k; ++i) {
        current_sum += arr[i];
    }
    int max_sum = current_sum;

    for (int i = k; i < arr.size(); i++) {
        current_sum += arr[i];
        current_sum -= arr[i - k];   
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }
    return max_sum;
}

int main() {
    vector<int> arr = {3, -2, 5, 1, -6, 4};
    int k = 3;

    int result = fast_sum(arr, k);

    cout << "Array: ";
    for (int x : arr)
        cout << x << " ";
    cout << "\n";
    cout << "Max 3-sum ="  << result << '\n';

    return 0;
}