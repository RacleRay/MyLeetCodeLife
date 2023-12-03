/*************************************************************************
    > File Name: dijkstra_star.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include<iostream>
#include <queue>
#include <cstring>
using namespace std;

struct node {
    int now, dist;
    bool operator< (const node& b) const {
        return this->dist > b.dist;
    }
};

struct edge {
    int e, v, next;
};

int n, m, s, edg_cnt, head[100005], ans[100005];
edge edg[200005];

void add_edg(int a, int b, int c) {
    edg[edg_cnt].e = b;
    edg[edg_cnt].v = c;
    edg[edg_cnt].next = head[a];
    head[a] = edg_cnt++;
}

int main(int argc, char *argv[]) {
    memset(head, -1, sizeof(head));
    memset(ans, 0x3F, sizeof(ans));
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edg(a, b, c);
        add_edg(b, a, c);
    }

    priority_queue<node> que;
    que.push((node){s, 0});
    ans[s] = 0;
    while (!que.empty()) {
        node tmp = que.top();
        que.pop();
        if (ans[tmp.now] < tmp.dist) continue;
        for (int i = head[tmp.now]; i != -1; i = edg[i].next) {
            int e = edg[i].e, v = edg[i].v;
            if (ans[e] > tmp.dist + v) {
                ans[e] = tmp.dist + v;
                que.push((node){e, ans[e]});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (ans[i] == 0x3F3f3f3f) {
            cout << -1 << endl;
        } else {
            cout << ans[i] << endl;
        }
    }
 
    return 0;
}
