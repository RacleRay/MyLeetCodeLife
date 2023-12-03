#include <cstring>
#include <iostream>
#include <vector>

typedef int Position;
#define NotFound -1

using namespace std;


// brute force
int matchString(string pattern, string text) {
    int m = pattern.size();
    int n = text.size();
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (pattern[j] != text[i + j]) break;
        }
        if (j == m) return i;
    }
    return -1;
}


// ============================================================================
// kmp, dp  --  不那么容易懂
int kmp(string pattern, string text) {
    int m = pattern.size();
    int n = text.size();

    // dp[i][j] 表示模式串中第i个状态匹配字符j时，pattern中的状态会转移到哪个index
    vector<vector<int>> dp(m, vector<int>(256, 0));
    int                 prev = 0;  // prev 始终为 i 的影子状态（有相同前缀字串）
    dp[0][pattern[0]]        = 1;  // 第0位置匹配成功，下一个位置idx
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < 256; j++) {
            if (pattern[i] == j) {  // ascii
                dp[i][j] = i + 1;
            }
            else {  // 不匹配时，从影子（有相同前缀字串）状态开始，尝试匹配
                dp[i][j] = dp[prev][j];
            }
        }
        // cout << prev << endl;
        prev = dp[prev][pattern[i]];  // [prev][pattern[i]] --
                                      // 填充过，有相同子串，成为prev状态，回退状态
                                      // [prev][pattern[i]] --
                                      // 未填充过，没有相同子串，重置为0，prev状态
    }

    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < 256; j++) {
    //         if (j >= 'a' && j <= 'd')
    //             cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    int i = 0;
    for (int j = 0; j < n; j++) {
        i = dp[i][text[j]];
        if (i == m) return j - m + 1;
    }

    return -1;
}


// =============================================================================
// KMP match
//             |--> 满足 p0, p1, ..., pi = pj-i, pj-i+1, ..., pj 的最大的i
// match[j] = -|
//             |--> -1 这样的 i 不存在
void buildMatch(const char* pattern, int* match) {
    int i, j;
    int m = strlen(pattern);

    match[0] = -1;
    for (j = 1; j < m; ++j) {  // O(m)
        i = match[j - 1];      // for concise representation.
        // i 回退总次数，不会超过 match[j] 中 i + 1 的总次数
        // 即，以下while循环，不会超过m次
        while (i >= 0 && (pattern[i + 1] != pattern[j]))
            i = match[i];

        if (pattern[i + 1] == pattern[j])
            match[j] = i + 1;
        else
            match[j] = -1;
    }
}


Position KMP(const char* pattern, const char* string) {
    int n = strlen(string);
    int m = strlen(pattern);
    int s = 0, p = 0;

    if (n < m) return NotFound;

    int* match = (int*)malloc(sizeof(int) * m);
    buildMatch(pattern, match);

    // s is always forwarding. O(n)
    while (s < n && p < m) {
        if (string[s] == pattern[p]) {
            ++s;
            ++p;
        }
        else if (p > 0)
            p = match[p - 1] + 1;  // match[p - 1] is legal.
        else
            ++s;  // p == 0, the first char is not match.
    }

    return (p == m) ? s - m : NotFound;
}


// ============================================================================
// 
int sunday(const char* pattern, const char* text) {
    int n = strlen(text), m = strlen(pattern), last_present[256];

    for (int i = 0; i < 256; i++) {
        last_present[i] = -1;
    }

    // 最后一次出现某个字符的 index
    for (int i = 0; i < m; i++) {
        last_present[pattern[i]] = i;
    }

    // m - last_present[text[i + m]]：将 pattern 中最后一个和 text[i + m] 相同的字符，与 text 对齐，需要移动的长度
    for (int i = 0; i + m <= n; i += (m - last_present[text[i + m]])) {
        // 匹配
        int flag = 1;
        for (int j = 0; pattern[j]; j++) {
            if (text[i + j] == pattern[j]) continue;
            flag = 0;
            break;
        }
        if (flag) return i;
    }

    return -1;
}


int main() {
    cout << matchString("abab", "abacabab") << endl;
    cout << kmp("ababc", "abacababc") << endl;
    cout << kmp("aaaa", "abacaaaab") << endl;
    cout << KMP("abab", "abacabab") << endl;
    cout << KMP("aaaa", "abacaaaab") << endl;

    cout << sunday("abab", "abacabab") << endl;
    return 0;
}