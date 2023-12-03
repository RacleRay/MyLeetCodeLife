/*************************************************************************
    > File Name: kruskal.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct edge {
    int s, e, v;
    bool operator<(const edge& b) const {
        return this->v < b.v;
    }
};

int n, m, ans, e_union[100005], cnt;
edge edg[100005];

void init() {
    for (int i = 1; i <= n; ++i) {
        e_union[i] = i;
    }
}

int find_(int x) {
    if (e_union[x] == x) {
        return x;
    }
    return e_union[x] = find_(e_union[x]);
}

int main(int argc, char *argv[]) {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> edg[i].s >> edg[i].e >> edg[i].v;
    }

    init();
    sort(edg, edg + m);
    for (int i = 0; i < m; i++) {
        int pa = find_(edg[i].s), pb = find_(edg[i].e);
        if (pa != pb) {
            e_union[pa] = pb;
            ans += edg[i].v;
            cnt++;
            if (cnt == n - 1) {
                cout << ans << endl;
                return 0;
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
