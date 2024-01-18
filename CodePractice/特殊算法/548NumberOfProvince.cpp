#include "../header.h"

#include <numeric>


class UnionFind {
public:
    UnionFind(int n) : size(n) {
        roots = std::move(vector<int>(n, 0));
        std::iota(roots.begin(), roots.end(), 0);
    }

    int find(int target) {
        if (roots[target] == target) {
            return target;
        }
        return roots[target] = find(roots[target]);
    }

    void uni(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty) {
            roots[rootx] = rooty;
            size--;
        }
    }

    int get_n_roots() const {
        return size;
    }

private:
    vector<int> roots;
    int size;
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        size_t n_province = isConnected.size();

        vector<bool> visited(n_province + 1, 0);
        visited.reserve(n_province + 1);

        int count = 0;
        for (int i = 0; i < n_province; ++i) {
            if (visited[i] == 0) {
                count++;
                dfs(i, isConnected, visited);
            }
        }

        return count;
    }

    void dfs(int i, vector<vector<int>>& isConnected, vector<bool>& visited) {
        visited[i] = true;

        for (int j = 0; j < isConnected.size(); ++j) {
            if (isConnected[i][j] == true && !visited[j]) {
                dfs(j, isConnected, visited);
            }
        }
    }


    int findCircleNum2(vector<vector<int>>& isConnected) {
        size_t n_province = isConnected.size();
        vector<bool> visited(n_province + 1, false);
        
        int count = 0;
        queue<int> q;

        for (size_t i = 0; i < n_province; ++i) {
            if (visited[i] == false) {
                count++;
                q.push(i);
                visited[i] = true;
                while (!q.empty()) {
                    int cur = q.front();
                    q.pop();

                    for (size_t j = 0; j < n_province; ++j) {
                        if (isConnected[cur][j] == 1 && visited[j] == false) {
                            visited[j] = true;
                            q.push(j);
                        }
                    }
                }
            }
        }

        return count;
    }


    int findCircleNum3(vector<vector<int>>& isConnected) {
        size_t n_province = isConnected.size();

        UnionFind uf(n_province);

        for (int i = 0; i < n_province; ++i) {
            for (int j = 0; j < n_province; ++j) {
                if (isConnected[i][j] == 1) {
                    uf.uni(i, j);
                }
            }
        }

        return uf.get_n_roots();
    }
};


