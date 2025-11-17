#include <iostream>
#include <random>
#include <cmath>
#include <string>
using namespace std;

const double x[3] = {1.0, 1.5, 2.0};
const double y[3] = {1.0, 2.0, 1.5};
const double r[3] = {1.0, sqrt(5.0)/2.0, sqrt(5.0)/2.0};

// Точная площадь пересечения трех окружностей (дана по условию)
const double EXACT_AREA = 0.25 * M_PI + 1.25 * asin(0.8) - 1.0;

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n = stoll(argv[1]);
    string region_type = argv[2];
    
    double left_x, right_x, lower_y, upper_y;
    
    if (region_type == "narrow") {
        left_x = max(max(x[0] - r[0], x[1] - r[1]), x[2] - r[2]);
        right_x = min(min(x[0] + r[0], x[1] + r[1]), x[2] + r[2]);
        lower_y = max(max(y[0] - r[0], y[1] - r[1]), y[2] - r[2]);
        upper_y = min(min(y[0] + r[0], y[1] + r[1]), y[2] + r[2]);
    } else {
        left_x = min(min(x[0] - r[0], x[1] - r[1]), x[2] - r[2]);
        right_x = max(max(x[0] + r[0], x[1] + r[1]), x[2] + r[2]);
        lower_y = min(min(y[0] - r[0], y[1] - r[1]), y[2] - r[2]);
        upper_y = max(max(y[0] + r[0], y[1] + r[1]), y[2] + r[2]);
    }
    
    double S_box = (right_x - left_x) * (upper_y - lower_y);
    mt19937_64 gen(42);
    uniform_real_distribution<double> rnd_x(left_x, right_x);
    uniform_real_distribution<double> rnd_y(lower_y, upper_y);
    
    long long cnt = 0;
    double r2[3];
    for (int i = 0; i < 3; i++) {
        r2[i] = r[i] * r[i];
    }
    
    for (long long i = 0; i < n; ++i) {
        double rx = rnd_x(gen);
        double ry = rnd_y(gen);
        bool flag = true;
        for (int j = 0; j < 3; ++j) {
            if ((rx - x[j])*(rx - x[j]) + (ry - y[j])*(ry - y[j]) > r2[j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            cnt += 1;
        }
    }
    
    cout << n << " " << S_box * (double)cnt / n << " " << EXACT_AREA << endl;
    return 0;
}

