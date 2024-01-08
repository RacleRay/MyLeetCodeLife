#include <map>
#include <vector>

using namespace std;

// 求同一段的最大重叠次数
class MyCalendarThree {
private:
    map<int, int> milestone_map;

public:
    MyCalendarThree() {}
    
    int book(int start, int end) {
        // 只需要看那一段有最大的 milestone
        milestone_map[start]++;
        milestone_map[end]--;  

        int ans = 0, cur = 0;
        for (auto&[a, b] : milestone_map) {
            cur += b;
            ans = max(ans, cur);
        }         

        return ans;
    }
};



int main() {
    MyCalendarThree cal;

    vector<vector<int>> inputs = {{10,20},{50,60},{10,40},{5,15},{5,10},{25,55}};

    for (auto&input : inputs) {
        cal.book(input[0], input[1]);
    }

    return 0;
}