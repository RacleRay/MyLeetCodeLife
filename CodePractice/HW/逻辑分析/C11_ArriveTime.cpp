#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
    int n_car, distance;
    cin >> n_car >> distance;

    double arrived = 0.0;
    for (int i = 0; i < n_car; i++) {
        double speed;
        cin >> speed;

        arrived = std::max(arrived, distance / speed + i);
    }

    double res = arrived - (n_car - 1);

    // cout << std::fixed << std::setprecision(2) << res << endl;
    char out[100];
    sprintf(out, "%.3f", res);
    printf("%g", atof(out));

    return 0;
}