#include <iostream>
#include <random>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double x[3], y[3], r[3];
    for (int i = 0; i < 3; ++i) {
        cin >> x[i] >> y[i] >> r[i];
    }
    //boundaries
    double left_x = max(max(x[0] - r[0], x[1] - r[1]), x[2] - r[2]);
    double right_x = min(min(x[0] + r[0], x[1] + r[1]), x[2] + r[2]);
    double lower_y = max(max(y[0] - r[0], y[1] - r[1]), y[2] - r[2]);
    double upper_y = min(min(y[0] + r[0], y[1] + r[1]), y[2] + r[2]);

    if (right_x<= left_x || upper_y <= lower_y) {
        cout << 0.0; return 0;
    }
    
    double S_box = (right_x - left_x)*(upper_y - lower_y);
    long long n = (long long)(10000 * S_box*S_box);
    mt19937_64 gen(42); 
    uniform_real_distribution<double> rnd_x(left_x, right_x);
    uniform_real_distribution<double> rnd_y(lower_y, upper_y);

    long long cnt = 0;
    double r2[3]; 
    for (size_t i = 0; i < 3; i++)
    {
        r2[i] = r[i] * r[i];
    }
    for (long long i = 0; i < n; ++i) {
        double rx = rnd_x(gen);
        double ry = rnd_y(gen);
        bool flag = true;
        for (int j = 0; j < 3; ++j) {
            if ((rx - x[j])*(rx - x[j]) + (ry - y[j])*(ry - y[j]) > r2[j]) {
                flag = false; break;
            }
        }
        if (flag) {cnt+= 1;}
    }
    cout <<  S_box * (double)cnt / n;
    return 0;
}
