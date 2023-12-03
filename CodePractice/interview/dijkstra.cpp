/*************************************************************************
    > File Name: dijkstra.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct node {
    int now, dist;
    bool operator< (const node& other) const {
        return this->dist > other.dist; // 小顶堆
    }
};

struct edge {
    int e, w;
};

// n node; m edges; s start node; ans distance from source node
int n, m, s, ans[1005];

int main(int argc, char *argv[]) {

    memset(ans, 0x3f, sizeof(ans));
    cin >> n >> m >> s;
    vector<vector<edge> > edgs(n + 1, vector<edge>());
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        edgs[a].push_back((edge){b, c});
        edgs[b].push_back((edge){a, c});
    }

    priority_queue<node> que;
    que.push((node){s, 0});
    ans[s] = 0;
    while (!que.empty()) {
        node tmp = que.top();
        que.pop();
        if (tmp.dist > ans[tmp.now]) continue;  // no need for updating by this node
        for (int i = 0; i < edgs[tmp.now].size(); ++i) {
            int e = edgs[tmp.now][i].e, w = edgs[tmp.now][i].w;
            if (ans[e] > ans[tmp.now] + w) {
                ans[e] = ans[tmp.now] + w;
                que.push((node){e, ans[e]});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (ans[i] == 0x3f3f3f3f) cout << -1 << endl;
        else cout << ans[i] << endl;
    }
    
    return 0;
}
