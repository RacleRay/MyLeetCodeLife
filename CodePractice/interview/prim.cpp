/*************************************************************************
    > File Name: prim.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include<iostream>
#include<bits/stdc++.h>
using namespace std;


struct node {
    int e, v;
    bool operator< (const node& b) const {
        return this->v > b.v;
    }
};

struct edge {
    int e, v, next;
};

edge edg[200005];
int n, m, edg_cnt, ans, mark[100005], cnt, head[100005];

void add_edge(int a, int b, int c) {
    edg[edg_cnt].e = b;
    edg[edg_cnt].v = c;
    edg[edg_cnt].next = head[a];
    head[a] = edg_cnt++;
}

int main(int argc, char *argv[]) {
    memset(head, -1, sizeof(head));
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a, b, c);
        add_edge(b, a, c);
    }

    priority_queue<node> que;
    que.push((node){(n/4 == 0 ? 1: n/4), 0});
    while (!que.empty()) {
        node tmp = que.top();
        que.pop();
        if (mark[tmp.e] == 1) continue;
        mark[tmp.e] = 1;
        ans += tmp.v;
        cnt++;
        if (cnt == n) {
            cout << ans << endl;
            return 0;
        }
        for (int i = head[tmp.e]; i != -1; i = edg[i].next) {
            int e = edg[i].e, v = edg[i].v;
            if (mark[e] == 0)
                que.push((node){e, v});
        }
    }
    
    cout << -1 << endl;
    return 0;
}
