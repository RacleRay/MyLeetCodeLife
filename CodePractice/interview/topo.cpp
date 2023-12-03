/*************************************************************************
    > File Name: topo.cpp
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

edge edg[100005];
int n, m, mark[100005], cnt, head[100005], indegree[100005];
int res[100005];

int main(int argc, char *argv[]) {

    memset(head, -1, sizeof(head));
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        indegree[b]++;
        edg[i].e = b;
        edg[i].next = head[a];
        head[a] = i;
    }

    queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            que.push(i);
        }
    }

    while (!que.empty()) {
        int tmp = que.front();
        que.pop();
        res[cnt] = tmp;
        cnt++;
        for (int i = head[tmp]; i != -1; i = edg[i].next) {
            int e = edg[i].e;
            indegree[e]--;
            if (indegree[e] == 0)
                que.push(e);
        }
    }

    if (cnt != n) {
        cout << "no" << endl;
        return 0;
    }

    for (int i = 0; i < cnt; i++) {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}
