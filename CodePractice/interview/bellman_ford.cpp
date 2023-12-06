/*************************************************************************
    > File Name: bellman_ford.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// 原版写这段代码的人，写的真的烂

// next 保存相同 start node 起点的下一条边
struct edge {
    int end, weight, next;
};

edge edg[200005];
int nnodes, medges, start, edg_cnt;
int dist_from_st[100005], head[100005], mark[100005];

// 链式前向星存储：相同 head（begin node）的边连成一个链表存储，head 中存储头节点（头插法生成的链表）
// edg_cnt 作为在 edg 数组中找到边的 index
void add_edg(int begin, int end, int weight) {
    edg[edg_cnt].end = end;
    edg[edg_cnt].weight = weight;
    edg[edg_cnt].next = head[begin];
    head[begin] = edg_cnt++;
}

// 基于队列优化的bellmanford
// 完全随机条件下，效果和 dijikstra 相当，但是最坏情况下和原始bellmanford一样
// 可以处理负权边的单源最短路径，但是只能处理有向图
// 使用邻接表和链式前向星结构储存图
int main(int argc, char *argv[]) {
    memset(dist_from_st, 0x3F, sizeof(dist_from_st));
    memset(head, -1, sizeof(head));
    
    cin >> nnodes >> medges >> start;
    for (int i = 0; i < medges; ++i) {
        int begin, end, weight;
        cin >> begin >> end >> weight;
        add_edg(begin, end, weight);
        add_edg(end, begin, weight);
    }

    queue<int> que;
    que.push(start);
    dist_from_st[start] = 0;

    while (!que.empty()) {
        int tmp_st = que.front();
        que.pop();
        mark[tmp_st] = 0;
    
        for (int i = head[tmp_st]; i != -1; i = edg[i].next) {
            int end = edg[i].end;
            int weight = edg[i].weight;

            if (dist_from_st[end] > dist_from_st[tmp_st] + weight) {
                dist_from_st[end] = dist_from_st[tmp_st] + weight;
                // 标记 该次循环中，relax 的节点，并加入下一轮更新中
                // 并在下一次作为起点后，再次变为 mark = 0 的 可 relax 节点
                // 也就是说，mark 标记后续将会进行 relex 的起点，relax 后将会再次可用
                if (mark[end] == 0) {
                    mark[end] = 1;
                    que.push(end);
                }
            }
        }
    }

    for (int i = 1; i <= nnodes; i++) {
        if (dist_from_st[i] == 0x3f3f3f3f) {
            cout << -1 << endl;
        } else {
            cout << dist_from_st[i] << endl;
        }
    }

    return 0;
}
