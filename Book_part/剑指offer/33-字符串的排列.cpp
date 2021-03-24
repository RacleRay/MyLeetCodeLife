#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <set>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <limits.h>

using namespace std;

class Solution
{
public:
    vector<string> permutation(string s)
    {
        if (s.size() == 0)
            return vector<string>();

        vector<string> result;
        sort(s.begin(), s.end());

        do
        {
            result.push_back(s);
        } while (next_permutation(s.begin(), s.end()));

        return result;
    }

    vector<string> ret;

    vector<string> permutation(string s) {
        // DFS
        vector<bool> visited(s.size(), false);
        string path = "";
        // 排序后使得相同元素前后排列方便去重
        sort(s.begin(), s.end());
        dfs(path, s, visited);
        return ret;
    }

    void dfs(string &path, string &s, vector<bool> &visited){
        if(path.size()==s.size()){
            ret.push_back(path);
            return;
        }

        for(int i=0; i<s.size(); i++){
            // 当前位置已访问，已在当前path中
            if(visited[i]) continue;
            // !visited[i-1] 和 visited[i-1]是一致的，都是跳过相同的
            if(i>0 && s[i-1]==s[i] && !visited[i-1]) continue;

            visited[i] = true;
            path += s[i];

            dfs(path, s, visited);
            path.pop_back();
            visited[i] = false;
        }
    }


    vector<string> permutation(string s)
    {
        vector<string> res;
        int n = s.length();

        if (n == 0)
            return res;

        // vector<int> used(n);
        unordered_map<int,int> used;
        // vector<int> path;

        function<void(int)> dfs = [&](int begin) {
            if (begin == n-1)
            {
                res.push_back(s);
                return;
            }

            unordered_map<int,int> used;
            for (int i = begin; i <= n - 1; i++)
            {
                if (used[s[i]])
                    continue;
                used[s[i]] = 1;
                swap(s[i], s[begin]);
                dfs(begin + 1);
                swap(s[i], s[begin]);
                // used[s[i]] = 0;
            }
        };

        dfs(0);
        sort(res.begin(), res.end());
        return res;
    }
};

// next_permutation
int main(){
    int n;

    while (scanf("%d", &n) && n) {
        int a[100];

        for (int i = 0; i < n; ++i){
            scanf("%d", &a[i]);
        }

        sort(a, a+n);

        do {
            for (int i = 0; i < n; ++i){
                printf("%d", a[i]);
            }
            printf("\n");
        } while (next_permutation(a, a+n));
    }
}