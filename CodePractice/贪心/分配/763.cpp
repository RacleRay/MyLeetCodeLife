#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

// https://leetcode.cn/problems/partition-labels/solutions/

class Solution {
public:
    vector<int> partitionLabels(string s) {
        // size_t last_present[26];
        // for (size_t i = 0; i < s.size(); ++i) {
        //     last_present[s[i] - 'a'] = i;
        // }

        // size_t cur_end = 0, first_idx = 0;
        // vector<int> result;
        // for (size_t i = 0; i < s.size(); ++i) {
        //     if (last_present[s[i] - 'a'] > cur_end)
        //         cur_end = last_present[s[i] - 'a'];
        //     if (cur_end == i) {
        //         result.push_back(cur_end - first_idx + 1);
        //         first_idx = i + 1;
        //     }
        // }

        // return result;

        size_t last_index[26];
        for (size_t i = 0; i < s.size(); ++i) {
            last_index[s.at(i) - 'a'] = i;
        }

        size_t slice_end = 0, slice_begin = 0;
        vector<int> result;
        for (int i = 0; i < s.size(); ++i) {
            if (last_index[s.at(i) - 'a'] > slice_end) {
                slice_end = last_index[s.at(i) - 'a'];
            }
            if (i == slice_end) {
                result.push_back(slice_end - slice_begin + 1);
                slice_begin = slice_end + 1;
            }
        }

        return result;
    }
};


int main() {
    std::string s = "ntswuqqbidunnixxpoxxuuupotaatwdainsotwvpxpsdvdbwvbtdiptwtxnnbtqbdvnbowqitudutpsxsbbsvtipibqpvpnivottsxvoqqaqdxiviidivndvdtbvadnxboiqivpusuxaaqnqaobutdbpiosuitdnopoboivopaapadvqwwnnwvxndpxbapixaspwxxxvppoptqxitsvaaawxwaxtbxuixsoxoqdtopqqivaitnpvutzchkygjjgjkcfzjzrkmyerhgkglcyffezmehjcllmlrjghhfkfylkgyhyjfmljkzglkklykrjgrmzjyeyzrrkymccefggczrjflykclfhrjjckjlmglrmgfzlkkhffkjrkyfhegyykrzgjzcgjhkzzmzyejycfrkkekmhzjgggrmchkeclljlyhjkchmhjlehhejjyccyegzrcrerfzczfelzrlfylzleefgefgmzzlggmejjjygehmrczmkrc";
    Solution sl;
    vector<int> res = sl.partitionLabels(s);
    for (auto& r: res)
        std::cout << r << std::endl;
    return 0;
}