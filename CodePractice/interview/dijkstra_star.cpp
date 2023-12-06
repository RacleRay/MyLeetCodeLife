/*************************************************************************
    > File Name: dijkstra_star.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct node {
    int pos, dist;
    bool operator< (const node& end) const {
        return this->dist > end.dist;
    }
};

struct edge {
    int end, weight, next;
};

int nnodes, medges, startnode, edg_cnt, head[100005], dist_from_st[100005];
edge edg[200005];

// 使用邻接表和链式前向星结构储存图
// 链式前向星存储：相同 head（begin node）的边连成一个链表存储，head 中存储头节点（头插法生成的链表）
// edg_cnt 作为在 edg 数组中找到边的 index
void add_edg(int start, int end, int weight) {
    edg[edg_cnt].end = end;
    edg[edg_cnt].weight = weight;
    // 记录共用一个start节点的边，如何何回溯找到上一条边
    edg[edg_cnt].next = head[start];
    head[start] = edg_cnt++;
}

int main(int argc, char *argv[]) {
    memset(head, -1, sizeof(head));
    memset(dist_from_st, 0x3F, sizeof(dist_from_st));
    cin >> nnodes >> medges >> startnode;
    for (int i = 0; i < medges; i++) {
        int start, end, weight;
        cin >> start >> end >> weight;
        add_edg(start, end, weight);
        add_edg(end, start, weight);
    }

    priority_queue<node> que;
    que.push((node){startnode, 0});
    dist_from_st[startnode] = 0;

    while (!que.empty()) {
        node tmp = que.top();
        que.pop();

        if (dist_from_st[tmp.pos] < tmp.dist) continue;
        
        // 只遍历有相同start节点的边，避免重复遍历
        for (int i = head[tmp.pos]; i != -1; i = edg[i].next) {
            int end = edg[i].end;
            int weight = edg[i].weight;

            if (dist_from_st[end] > tmp.dist + weight) {
                dist_from_st[end] = tmp.dist + weight;
                que.push((node){end, dist_from_st[end]});
            }
        }
    }

    for (int i = 1; i <= nnodes; i++) {
        if (dist_from_st[i] == 0x3F3f3f3f) {
            cout << -1 << endl;
        } else {
            cout << dist_from_st[i] << endl;
        }
    }
 
    return 0;
}
