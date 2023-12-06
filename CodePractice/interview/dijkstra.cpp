/*************************************************************************
    > File Name: dijkstra.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// 最短路径时间复杂度对比
// 1. Dijkstra O((E + V)logV)
// 2. Bellman-Ford O(E*V)
// 3. Floyd O(V^3)  (多源)

// 遍历点，记录并更新当前可达的最短路径
// 用于单源最短路径

struct node {
    int  pos, dist;
    bool operator<(const node& other) const {
        return this->dist > other.dist;  // 小顶堆
    }
};

struct edge {
    int end_node, weight;
};

// nnodes node; medges edges; start_node start node; dist_from_st distance from source node
int nnodes, medges, start_node;
int dist_from_st[1005];

int main(int argc, char* argv[]) {

    // 邻接表存储
    // 初始每个字节的值位 3f 那么一个 int 为 0x3f3f3f3f
    memset(dist_from_st, 0x3f, sizeof(dist_from_st));
    cin >> nnodes >> medges >> start_node;
    vector<vector<edge>> edgs(nnodes + 1, vector<edge>());
    for (int i = 0; i < medges; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        edgs[a].push_back((edge){b, c});
        edgs[b].push_back((edge){a, c});
    }
    
    // 每次更新当前路径最短的结点，及其相邻的节点
    priority_queue<node> que;
    que.push((node){start_node, 0});
    dist_from_st[start_node] = 0;
    while (!que.empty()) {
        node tmp = que.top();
        que.pop();

        // 无需更新，有更优解
        if (tmp.dist > dist_from_st[tmp.pos]) continue;  // no need for updating by this node
        
        // 更新当前节点的所有邻接点的最短路径，并将更新的节点，加入队列中
        for (int i = 0; i < edgs[tmp.pos].size(); ++i) {
            int end_node = edgs[tmp.pos][i].end_node;
            int weight = edgs[tmp.pos][i].weight;

            if (dist_from_st[end_node] > dist_from_st[tmp.pos] + weight) {
                dist_from_st[end_node] = dist_from_st[tmp.pos] + weight;
                que.push((node){end_node, dist_from_st[end_node]});
            }
        }
    }

    for (int i = 1; i <= nnodes; i++) {
        if (dist_from_st[i] == 0x3f3f3f3f)
            cout << -1 << endl;
        else
            cout << dist_from_st[i] << endl;
    }

    return 0;
}
