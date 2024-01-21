#include <iostream>
#include <vector>
#include <stack>
#include <sstream>


using namespace std;

int main() {
    string line;
    getline(cin, line);
    istringstream iss(line);

    vector<int> prices;
    int price;
    while (iss >> price) {
        prices.push_back(price);
    }    

    int n = prices.size();

    vector<int> res(n, 0);
    stack<int> st;

    for (int j = 0; j < n * 2 - 1; j++) {
        int idx = j % n;
        while (!st.empty() && prices[st.top()] > prices[idx]) {
            int topidx = st.top();
            st.pop();
            res[topidx] = prices[topidx] + prices[idx];
        }
        if (j < n) {
            st.push(idx);
        }
    }

    while (!st.empty()) {
        int topidx = st.top();
        st.pop();
        res[topidx] = prices[topidx];
    }

    for (int num : res) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}