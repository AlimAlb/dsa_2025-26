#define ARRAY_GEN

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

class ArrayGenerator {
private:
    static const size_t MAX_SIZE = 100000;
    static const int MAX_VAL = 10000;
    vector<int> random;        
    vector<int> reversed;      
    vector<int> near_sorted;  
    mt19937 rng;

    void generateAll() {
        uniform_int_distribution<int> unif(0, MAX_VAL);
        for (size_t i = 0; i < MAX_SIZE; i++) 
            random.push_back(unif(rng));
        reversed = random;
        sort(reversed.begin(), reversed.end(), greater<int>());
        near_sorted = random;
        sort(near_sorted.begin(), near_sorted.end()); 

        int cnt = (int) (1 + MAX_SIZE * .05); 
        uniform_int_distribution<int> idx(0, MAX_SIZE - 1);
        for (size_t i = 0; i < cnt; ++i) {
            int n = idx(rng);
            int m = idx(rng);
            if (n != m) {
                swap(near_sorted[n], near_sorted[m]);
            }
        }
    }

public:
    ArrayGenerator() {
        rng.seed(21);
        generateAll();
    }

    vector<int> rnd_arr(int n)  {return vector<int>(random.begin(), random.begin() + n);}

    vector<int> rev_arr(int n)  {return vector<int>(reversed.begin(), reversed.begin() + n);}

    vector<int> near_sorted_arr(int n) {return vector<int>(near_sorted.begin(), near_sorted.begin() + n);}


};
