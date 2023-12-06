/*************************************************************************
    > File Name: prim.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// 最小生成树：从源点开始，从源点到其他点的距离最小，并且不连通
// Prim 结合二叉堆优化 O((E + V)logV)，斐波那契堆可以更优化
// 适合稠密图


struct node {
    int end, weight;
    bool operator< (const node& oth) const {
        return this->weight > oth.weight;
    }
};

struct edge {
    int end, weight, next;
};

edge edg[200005];
int nnodes, medges, edg_cnt, ans, cnt;
int mark[100005], head[100005];

// 链式前向星存储：相同 head（begin node）的边连成一个链表存储，head 中存储头节点（头插法生成的链表）
// edg_cnt 作为在 edg 数组中找到边的 index
void add_edge(int begin, int end, int weight) {
    edg[edg_cnt].end = end;
    edg[edg_cnt].weight = weight;
    edg[edg_cnt].next = head[begin];
    head[begin] = edg_cnt++;
}

int main(int argc, char *argv[]) {
    memset(head, -1, sizeof(head));

    cin >> nnodes >> medges;
    for (int i = 0; i < medges; i++) {
        int begin, end, weight;
        cin >> begin >> end >> weight;
        add_edge(begin, end, weight);
        add_edge(end, begin, weight);
    }

    // 每次取当前可遍历但是未遍历的边中，权值最小的边（实际上是遍历点）
    priority_queue<node> que;
    // 选择初始起点
    que.push((node){(nnodes / 4 == 0 ? 1: nnodes / 4), 0});
    
    while (!que.empty()) {
        node tmp = que.top();
        que.pop();

        if (mark[tmp.end] == 1) continue;  // 只关心未遍历的可达节点
        
        mark[tmp.end] = 1;
        ans += tmp.weight;
        cnt++;
        
        if (cnt == nnodes) {
            cout << ans << endl;
            return 0;
        }
        
        for (int i = head[tmp.end]; i != -1; i = edg[i].next) {
            int end = edg[i].end;
            int weight = edg[i].weight;
            if (mark[end] == 0)
                que.push((node){end, weight});
        }
    }
    
    cout << -1 << endl;
    return 0;
}
