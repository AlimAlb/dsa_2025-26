#include "arrays.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

int THRESHOLD; 

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

void merge_sort(vector<int>& a, int left, int right) {
    if (left >= right) return;  

    int mid = left + (right - left) / 2;
    merge_sort(a, left, mid);        
    merge_sort(a, mid + 1, right);   
    merge(a, left, mid, right);      
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

long long SortTester(vector<int> arr, bool hybrid) {
    auto start = chrono::high_resolution_clock::now();

    if (!hybrid) {
        merge_sort(arr, 0, arr.size() - 1);
    }
    else {
        hybrid_sort(arr, 0, arr.size() - 1);
    }
    auto elapsed = chrono::high_resolution_clock::now() - start;
    return chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = stoi(argv[1]);
    THRESHOLD = stoi(argv[2]);

    ArrayGenerator gen;
    vector<int> rnd = gen.rnd_arr(n);
    vector<int> rev = gen.rev_arr(n);
    vector<int> near_sorted = gen.near_sorted_arr(n);
    
    cout << "random" << ' ' << SortTester(rnd, false) << ' ' << SortTester(rnd, true) << '\n';
    cout << "reversed" << ' ' << SortTester(rev, false) << ' ' << SortTester(rev, true) << '\n';
    cout << "near_sorted" << ' ' << SortTester(near_sorted, false) << ' ' << SortTester(near_sorted, true) << '\n';

    return 0;

}