/*************************************************************************
    > File Name: floyd.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int n, m, s, arr[1005][1005];

int main(int argc, char *argv[]) {

    memset(arr, 0x3F, sizeof(arr));
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (arr[a][b] > c) {
            arr[a][b] = c;
            arr[b][a] = c; 
        }
    }
    for (int i = 1; i <= n; i++) { // 最外层进行中转
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                arr[j][k] = min(arr[j][k], arr[j][i] + arr[i][k]);
            }
        }
    }

    arr[s][s] = 0;
    for (int i = 1; i <= n; i++) {
        if (arr[s][i] == 0x3f3f3f3f)
            cout << -1 << endl;
        else
            cout << arr[s][i] << endl;
    }

    return 0;
}
