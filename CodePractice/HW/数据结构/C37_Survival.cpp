#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <sstream>


using namespace std;


int solution(vector<int>& nums, int jump, int left) {
    if (left >= nums.size()) {
        return accumulate(nums.begin(), nums.end(), 0);
    }

    int idx = 1;
    while (nums.size() > left) {
        idx = (idx + jump) % nums.size();
        nums.erase(nums.begin() + idx);
        // idx = (idx + nums.size() - 1) % nums.size();
    }

    return accumulate(nums.begin(), nums.end(), 0);
}


int main() {
    string line;
    getline(cin, line);

    vector<int> nums;
    stringstream ss(line);
    string num;
    while (getline(ss, num, ',')) {
        nums.push_back(stoi(num));
    } 

    int jump, left;
    cin >> jump >> left;

    cout << solution(nums, jump, left) << endl;

    return 0;
}