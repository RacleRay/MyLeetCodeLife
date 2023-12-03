#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


using namespace std;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord,
                                       vector<string>& wordList) {
        vector<vector<string>> ans;
        unordered_set<string>  dict;
        for (const string& w : wordList) {
            dict.insert(w);
        }

        if (!dict.count(endWord)) {
            return ans;
        }
        dict.erase(beginWord);
        dict.erase(endWord);

        // record the traversal path in opposite directions
        unordered_set<string>                 q1{beginWord}, q2{endWord};
        unordered_map<string, vector<string>> next;  // for search

        bool reversed = false, found = false;
        while (!q1.empty()) {
            unordered_set<string>
                q;  // record the nodes have been used in current BFS level
            for (const string& w : q1) {
                string s = w;                            // for traversal
                for (size_t i = 0; i < s.size(); ++i) {  // char wise bfs
                    char ch = s[i];
                    for (int j = 0; j < 26; ++j) {  // char wise bfs
                        s[i] = j + 'a';
                        if (q2.count(s)) {  // 双向交汇
                            reversed ? next[s].push_back(w)
                                     : next[w].push_back(s);
                            found = true;
                        }
                        if (dict.count(s)) {
                            reversed ? next[s].push_back(w)
                                     : next[w].push_back(s);
                            q.insert(s);
                        }
                    }
                    s[i] = ch;
                }
            }

            if (found) break;

            for (const string& w : q)
                dict.erase(w);  // update reachable node
                
            if (q.size() <= q2.size()) {  // 继续从节点较少的一侧进行遍历 666
                q1 = q;
            }
            else {  // 交换遍历方向，666
                reversed = !reversed;
                q1       = q2;
                q2       = q;
            }
        }

        if (found) {
            vector<string> path = {beginWord};
            backtracking(beginWord, endWord, next, path, ans);
        }

        return ans;
    }

    void backtracking(const string& src, const string& dst,
                      unordered_map<string, vector<string>>& next,
                      vector<string>& path, vector<vector<string>>& ans) {
        if (src == dst) {
            ans.push_back(path);
            return;
        }

        for (const string& s : next[src]) {
            path.push_back(s);
            backtracking(s, dst, next, path, ans);
            path.pop_back();
        }
    }
};


int main() {
    Solution sl = Solution();

    vector<string> wordlist{"hot", "dot", "dog", "lot", "log", "cog"};
    sl.findLadders("hit", "hog", wordlist);

    return 0;
}