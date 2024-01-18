#include <iostream>
#include <vector>
#include <climits>

// https://blog.csdn.net/qfc_128220/article/details/134383665


using namespace std;


struct Rect {
    int minRow{INT_MAX};
    int maxRow{INT_MIN};
    int minCol{INT_MAX};
    int maxCol{INT_MIN};
};


constexpr int SIZE = 500;

void solution() {
    int nrow, ncol;
    cin >> nrow >> ncol;

    Rect *rects[SIZE] = {nullptr};

    for (int i = 0; i < nrow; ++i) {
        for (int j = 0; j < ncol; ++j) {
            int num;
            cin >> num;
            
            if (num > 0) {
                if (rects[num] == nullptr) {
                    rects[num] = new Rect();
                }

                rects[num]->minRow = min(rects[num]->minRow, i);
                rects[num]->maxRow = max(rects[num]->maxRow, i);

                rects[num]->minCol = min(rects[num]->minCol, j);
                rects[num]->maxCol = max(rects[num]->maxCol, j);
            }
        }
    }

    int res = 0;
    for (int i = 0; i < SIZE; ++i) {
        Rect *rect = rects[i];

        if (rect != nullptr) {
            int tmp = (rect->maxRow - rect->minRow + 1) * (rect->maxCol - rect->minCol + 1);
            res = max(res, tmp);
        }
    }

    cout << res << endl;

    return;
}


int main() {
    solution();

    return 0;
}