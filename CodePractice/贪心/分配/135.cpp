#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        if (ratings.size() == 1) return 1;

        vector<int> cookies(ratings.size(), 1);

        for (size_t i = 1; i < ratings.size(); ++i) {
            if (ratings[i - 1] < ratings[i])
                cookies[i] = cookies[i - 1] + 1;
        }

        for (size_t j = ratings.size() - 1; j > 0; --j) {
            if (ratings[j - 1] > ratings[j])
                cookies[j - 1] = max(cookies[j - 1], cookies[j] + 1);
        }

        return accumulate(cookies.begin(), cookies.end(), 0);
    }
};

