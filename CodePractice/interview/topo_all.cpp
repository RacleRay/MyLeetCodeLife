/*************************************************************************
    > File Name: topo_all.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include<iostream>
#include<bits/stdc++.h>
#include <mutex>
using namespace std;

struct edge {
    int e, v, next;
};

edge edg[100005];
int n, m, mark[100005], cnt, head[100005], indegree[100005];
int res[100005];
int flag = 0;

void recursive_trival(int now, vector<vector<int> >& edg) {
    if (now == n + 1) {
        for (int i = 1; i <= n; i++) {
            cout << res[i] << " ";
        }
        cout << endl;
        flag = 1;
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0 && mark[i] == 0) {
            res[now] = i;
            mark[i] = 1;
            for (int j = 0; j < edg[i].size(); j++) {
                indegree[edg[i][j]]--;
            }
            recursive_trival(now + 1, edg);
            mark[i] = 0;
            for (int j = 0; j < edg[i].size(); j++) {
                indegree[edg[i][j]]++;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    cin >> n >> m;
    vector<vector<int> > edg(n + 1, vector<int>());
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        indegree[b]++;
        edg[a].push_back(b);
    }

    recursive_trival(1, edg);

    if (flag == 0) {
        cout << "no" << endl;
    }

    return 0;
}
