#define SORTINGS

#include <iostream>
#include <vector>
using namespace std;

const int THRESHOLD = 15; 

void merge(vector<int>& arr, int left, int mid, int right) {
    int i = left;      
    int j = mid + 1;   
    vector<int> temp;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp.push_back(arr[i++]); 
        else temp.push_back(arr[j++]);
    }

    while (i <= mid) 
        temp.push_back(arr[i++]);
    while (j <= right) 
        temp.push_back(arr[j++]);
    
    for (size_t k = 0; k < temp.size(); ++k)
        arr[left + k] = temp[k];
}

void insertion_sort(vector<int>& arr, int left, int right) {
    for (size_t i = left + 1; i <= right; ++i) {
        int curr = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > curr) {
            arr[j + 1] = arr[j]; j--;
        }
        arr[j + 1] = curr;
    }
}

void hybrid_sort(vector<int>& arr, int left, int right) {
    int len = right - left + 1;
    if (len <= 1) return;

    if (len <= THRESHOLD) {
        insertion_sort(arr, left, right); return;
    }

    int mid = left + (right - left) / 2;
    hybrid_sort(arr, left, mid);
    hybrid_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (size_t i = 0; i < n; i++)
        cin >> arr[i];
    hybrid_sort(arr, 0, n - 1);
    for (size_t i = 0; i < n; i++) 
        cout << arr[i] << ' ';
    cout << '\n';
    return 0;
}
