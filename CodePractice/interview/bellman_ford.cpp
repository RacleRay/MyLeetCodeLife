/*************************************************************************
    > File Name: bellman_ford.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct edge {
    int e, v, next;
};

edge edg[200005];
int n, m, s, edg_cnt, ans[100005], head[100005], mark[100005];

void add_edg(int a, int b, int c) {
    edg[edg_cnt].e = b;
    edg[edg_cnt].v = c;
    edg[edg_cnt].next = head[a];
    head[a] = edg_cnt++;
}

// 基于队列优化的bellmanford
// 完全随机条件下，效果和dijikstra相当，但是最坏情况下和原始bellmanford一样
// 可以处理负权边的单源最短路径
// 使用邻接表和链式前向星结构储存图
int main(int argc, char *argv[]) {
    memset(ans, 0x3F, sizeof(ans));
    memset(head, -1, sizeof(head));
    cin >> n >> m >> s;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edg(a, b, c);
        add_edg(b, a, c);
    }

    queue<int> que;
    que.push(s);
    ans[s] = 0;
    while (!que.empty()) {
        int tmp = que.front();
        que.pop();
        mark[tmp] = 0;
        for (int i = head[tmp]; i != -1; i = edg[i].next) {
            int e = edg[i].e, v = edg[i].v;
            if (ans[e] > ans[tmp] + v) {
                ans[e] = ans[tmp] + v;
                if (mark[e] == 0) {
                    mark[e] = 1;
                    que.push(e);
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (ans[i] == 0x3f3f3f3f) {
            cout << -1 << endl;
        } else {
            cout << ans[i] << endl;
        }
    }

    return 0;
}
