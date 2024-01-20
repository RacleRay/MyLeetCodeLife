#include <iostream>
#include <stack>
#include <string>
#include <cctype>


long compute(const std::string& str) {
    std::stack<long> st;  // for operands

    int i = 0;
    while (i < str.length()) {
        char ch = str[i];
        if (isdigit(ch)) {
            int start = i;
            while (i < str.length() && isdigit(str[i])) {
                i++;
            }
            long num = std::stol(str.substr(start, i - start));
            st.push(num);
        } else {
            if (ch == '$') {
                long y = st.top();
                st.pop();
                i++;
                // new number
                int start = i;
                while (i < str.length() && isdigit(str[i])) {
                    i++;
                }
                long x = std::stol(str.substr(start, i - start));
                
                // compute
                st.push(3 * y + x + 2);
            } else if (ch == '#') {
                i++;
            }
        }
    }

    std::stack<long> reverse_st;
    while (!st.empty()) {
        reverse_st.push(st.top());
        st.pop();
    }

    long result = reverse_st.top();
    reverse_st.pop();
    while (!reverse_st.empty()) {
        long x = reverse_st.top();
        reverse_st.pop();
        result = 2 * result + 3 * x + 4;
    }

    return result;
}


int main() {
    std::string str;
    std::cin >> str;

    std::cout << compute(str) << std::endl;

    return 0;
}