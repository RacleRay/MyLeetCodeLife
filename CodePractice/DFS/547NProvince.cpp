#include <iostream>
#include <vector>


using namespace std;


class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        if (isConnected.size() == 0) return 0;

        int n = isConnected.size(), count = 0;
        vector<bool> visited(n, false);
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                ++count;
                dfs(isConnected, i, visited);
            }
        }
        return count;
    }

    void dfs(vector<vector<int>>& isConnected, int i, vector<bool>& visited) {
        visited[i] = true;
        for (int k = 0; k < isConnected.size(); ++k) {
            if (isConnected[i][k] == 1 && !visited[k]) {
                dfs(isConnected, k, visited);
            }
        }
    }
};


int main() {
    Solution sl = Solution();
    vector<vector<int>> a = {{1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}};

    sl.findCircleNum(a);

    return 0;
}