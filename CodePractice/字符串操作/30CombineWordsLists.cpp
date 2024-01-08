#include <string>
#include <vector>
#include <unordered_map>


using namespace std;


class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n_words = words.size();
        if (n_words == 0 or s.empty()) return {};

        int str_len = s.size();
        int word_len = words[0].size();
        int target_len = word_len * n_words;
        if (target_len > str_len) {
            return {};
        }

        vector<int> res;
        // i < word_len 防止重复遍历
        for (int i = 0; i < word_len && i + target_len <= str_len; i++) {
            unordered_map<string, int> word_count_map;
            for (int j = i; j < i + target_len; j += word_len) {
                word_count_map[s.substr(j, word_len)]++;
            }

            for (auto& word: words) {
                if (--word_count_map[word] == 0) {
                    word_count_map.erase(word);
                }
            }
            // count > 0 表示 s 中存在多余的 word
            // count < 0 表示 words 中存在多余的 word

            if (word_count_map.empty()) {
                res.push_back(i);
            }

            for (int k = i + word_len; k + target_len <= str_len; k += word_len) { 
                string to_remove = s.substr(k - word_len, word_len);
                if (--word_count_map[to_remove] == 0) {
                    word_count_map.erase(to_remove);
                }

                string to_add = s.substr(k + target_len - word_len, word_len);
                if (++word_count_map[to_add] == 0) {
                    word_count_map.erase(to_add);
                }

                if (word_count_map.empty()) {
                    res.push_back(k);
                }
            }
        }

        return res;
    }
};


int main() {
    string s = "barfoothefoobarman";

    Solution sol;
    std::vector<string> words = {"foo", "bar"};
    sol.findSubstring(s, words);

    return 0;
}