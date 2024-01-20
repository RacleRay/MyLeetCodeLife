#include <iostream>
#include <vector>

using namespace std;

int nrow, ncol, k;
vector<vector<bool>> visited;


int sumOfDigits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}


int dfs(int x, int y) {
    if (x < 0 || x >= nrow || y < 0 || y >= ncol || visited[x][y] || sumOfDigits(x) + sumOfDigits(y) > k) {
        return 0;
    }

    visited[x][y] = true;

    return 1 + dfs(x + 1, y) + dfs(x - 1, y) + dfs(x, y + 1) + dfs(x, y - 1);
}


int main() {

    cin >> nrow >> ncol >> k;
    visited.resize(nrow, vector<bool>(ncol, false));

    cout << dfs(0, 0) << endl;

    return 0;    
}