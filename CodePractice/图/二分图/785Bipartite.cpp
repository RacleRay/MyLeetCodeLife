#include "../../header.h"


class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int nedges = graph.size();
        if (nedges == 0) {
            return false;
        }

        vector<int> colors(nedges, 0);  // 0 not visited
        queue<int> q;
        for (int i = 0; i < nedges; ++i) {
            if (!colors[i]) {
                q.push(i);
                colors[i] = 1;
            }
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                for (const int& nei : graph[node]) {
                    if (!colors[nei]) {
                        q.push(nei);
                        colors[nei] = -colors[node];
                    } else if (colors[nei] == colors[node]) {
                        return false;  // 相邻两个node有相同颜色，不属于两个部分
                    }
                }
            }
        }

        return true;
    }
};