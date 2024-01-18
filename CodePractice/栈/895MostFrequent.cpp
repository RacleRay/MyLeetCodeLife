#include "../header.h"


class FreqStack {
public:
    FreqStack() = default;
    
    void push(int val) {
        if (freq.find(val) == freq.end()) {
            freq[val] = 0;
        }
        freq[val]++;

        if (umap.find(freq[val]) == umap.end()) {
            umap[freq[val]] = std::move(vector<int>());
        }
        umap[freq[val]].push_back(val);

        most_freq = std::max(most_freq, freq[val]);
    }
    
    int pop() {
        auto res = umap[most_freq].back();
        umap[most_freq].pop_back();

        freq[res]--;

        if (umap[most_freq].empty()) {
            most_freq--;
        }

        return res;
    }

private:
    int most_freq {0};

    std::unordered_map<int, vector<int>> umap;
    std::unordered_map<int, int> freq;
};