#include <iostream>
#include <stack>
#include <string>


using namespace std;

// https://blog.csdn.net/qfc_128220/article/details/134454085

static inline void solution() {
    string inputs;
    cin >> inputs;

    string outputs;
    int n_upper = 0;
    int n_lower = 0;
    int n_num = 0;
    int n_other = 0;

    for (auto& ch: inputs) {
        char operand;
        int count;

        if (ch == '<') {
            if (outputs.size() > 0) {
                operand = outputs[outputs.size() - 1];
                count = -1;
                outputs.pop_back();
            } else [[unlikely]] {
                continue;
            }
        } else {
            operand = ch;
            count = 1;
            outputs.push_back(ch);
        }

        if (operand >= 'a' && operand <= 'z') {
            n_lower += count;
        } else if (operand >= 'A' && operand <= 'Z') {
            n_upper += count;
        } else if (operand >= '0' && operand <= '9') {
            n_num += count;
        } else {
            n_other += count;
        }
    }

    if (outputs.size() >= 8 && n_lower >= 1 && n_upper >= 1 && n_num >= 1 && n_other >= 1) {
        outputs.append(",true");
    } else {
        outputs.append(",false");
    }

    cout << outputs << endl;

    return;
}


int main() {
    solution();

    return 0;
}