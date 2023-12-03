#include "selfstring.hpp"


int main() {
    char        dest[10];
    const char* src = "1203lop";
    cout << selfmade::strlen(src) << endl;
    cout << strlen(src) << endl;
    selfmade::strcpy(dest, src);
    cout << dest << endl;

    src = "1223";
    selfmade::memcpy(dest, src, strlen(src));
    cout << dest << endl;  // 可以看到遇到str\0不结束

    cout << selfmade::strlen(src) << endl;

    const char* s1 = "abcdegdefghi";
    const char* s2 = "def";
    cout << "============" << endl;
    cout << selfmade::strstr(s1, s2) << endl;
    cout << strstr(s1, s2) << endl;

    char s3[100] = {'1', '2', '3', 0};
    cout << s3 << endl;
    cout << strcat(s3, s1) << endl;
    cout << selfmade::strcat(s3, s1) << endl;
    const char* ss1 = "a";
    const char* ss2 = "b";
    cout << strcmp(ss1, ss2) << endl;
    cout << selfmade::strcmp(ss1, ss2) << endl;

    return 0;
}