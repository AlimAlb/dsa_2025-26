#include <iostream>
#include <random>
#include <vector>
#include <chrono>

using namespace std;

long long cmp_cnt = 0;   
long long move_cnt = 0;  

void insertion_sort(vector<int>& arr){
    for(int i = 0; i < arr.size(); i++){
        int tmp = arr[i];
        int j = i - 1;
        
        while(j >= 0 && arr[j] > tmp){
            move_cnt++; cmp_cnt++;
            arr[j+1] = arr[j];
            j--;
        }
        cmp_cnt++;
        move_cnt++;                  
        arr[j+1] = tmp;
    }
}

void shell_sort(vector<int>& arr){
    for(int gap = arr.size()/2; gap > 0; gap /= 2){
        for(int i = gap; i < arr.size(); i++){
            int tmp = arr[i];
            int j = i - gap;
            while(j >= 0 && arr[j] > tmp){
                move_cnt++; cmp_cnt++;
                arr[j+gap] = arr[j];
                j-= gap;
            }
            cmp_cnt++;
            move_cnt++;                 
            arr[j+gap] = tmp;
        }
    }
}

vector<int> random_array(int n, int lower, int upper){
    vector<int> arr;
    arr.reserve(n);

    //random_device rd;
    mt19937 gen(42);
    uniform_int_distribution<int> dist(lower, upper);

    for(int i = 0; i < n; i++){
        int rnd = dist(gen);
        arr.push_back(rnd);
    }

    return arr;
}

void measure(string type, vector<int> arr){
    auto start = chrono::high_resolution_clock::now();
    if(type == "insertion")
        insertion_sort(arr);
    else
        shell_sort(arr);
    auto elapsed = chrono::high_resolution_clock::now() - start;
    long long ns = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
    
    if (type == "insertion")
        cout << "insertion ";
    else
        cout << "shell ";

    cout  << cmp_cnt << ' ' << move_cnt << ' ' << ns << '\n';
    move_cnt = 0; cmp_cnt = 0;
}

int main(int argc, char* argv[]){
    int n     = stoi(argv[1]);
    int lower = stoi(argv[2]);
    int upper = stoi(argv[3]);

    vector<int> arr1 = random_array(n, lower, upper);
    vector<int> arr2 = arr1;
    
    measure("insertion", arr1);
    measure("shell", arr2);

    return 0;
}
