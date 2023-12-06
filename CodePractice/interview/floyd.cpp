/*************************************************************************
    > File Name: floyd.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int nnodes, medges, start_node, dist_from_st[1005][1005];

// 多源最短路径，支持负权边和无向图，适合稠密图，动态规划插点

int main(int argc, char *argv[]) {

    memset(dist_from_st, 0x3F, sizeof(dist_from_st));
    
    cin >> nnodes >> medges >> start_node;
    for (int i = 0; i < medges; i++) {
        int begin, end, weight;
        cin >> begin >> end >> weight;
        if (dist_from_st[begin][end] > weight) {
            dist_from_st[begin][end] = weight;
            dist_from_st[end][begin] = weight; 
        }
    }

    for (int i = 1; i <= nnodes; i++) { // 最外层作为插点，排列插点，动态规划
        for (int j = 1; j <= nnodes; j++) {
            for (int k = 1; k <= nnodes; k++) {
                dist_from_st[j][k] = min(dist_from_st[j][k], dist_from_st[j][i] + dist_from_st[i][k]);
            }
        }
    }

    dist_from_st[start_node][start_node] = 0;
    for (int i = 1; i <= nnodes; i++) {
        if (dist_from_st[start_node][i] == 0x3f3f3f3f)
            cout << -1 << endl;
        else
            cout << dist_from_st[start_node][i] << endl;
    }

    return 0;
}
