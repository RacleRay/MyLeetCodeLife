/*************************************************************************
    > File Name: kruskal.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// MST 最小生成树，解法。
// 结合并查集优化
// 适合边较多的MST，O(E*logE + E*A(V) + V)

struct edge {
    int begin, end, weight;
    bool operator<(const edge& b) const {
        return this->weight < b.weight;
    }
};

int nnodes, medges, ans, cnt;
int graph_union[100005];
edge edg[100005];

// 每个节点，初始化一个集合
void init() {
    for (int i = 1; i <= nnodes; ++i) {
        graph_union[i] = i;
    }
}

// 找到所属集合的根节点
int find_root(int x) {
    if (graph_union[x] == x) {
        return x;
    }
    return graph_union[x] = find_root(graph_union[x]);
}

int main(int argc, char *argv[]) {
    cin >> nnodes >> medges;
    for (int i = 0; i < medges; i++) {
        cin >> edg[i].begin >> edg[i].end >> edg[i].weight;
    }

    init();
    
    // 升序
    sort(edg, edg + medges);

    for (int i = 0; i < medges; i++) {
        int root_begin = find_root(edg[i].begin);
        int root_end = find_root(edg[i].end);

        // 不在一个集合中，加入这条还未遍历的最优的边，并加入并查集
        // 直到所有点都在集合中
        if (root_begin != root_end) {
            graph_union[root_begin] = root_end;  // begin -> end
            ans += edg[i].weight;
            cnt++;
            if (cnt == nnodes - 1) {
                cout << ans << endl;
                return 0;
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
