#include <cstdio>
#include <cstdlib>
#include <cstring>


using namespace std;


char *replace(char* s, char* old, char* nw)
{
    char *sub = strstr(s, old);
    if (sub == nullptr) {
        return s;
    }

    char *res = (char *)calloc(100, sizeof(char));
    while (sub != nullptr) {
        sub[0] = '\0';
        strcat(res, s);
        strcat(res, nw);

        s = sub + strlen(old);
        sub = strstr(s, old);
    }

    strcat(res, s);
    return res;
}


int main() {
    char *s = (char *)calloc(100, sizeof(char));
    fgets(s, 100, stdin);

    for (int i = 26; i >= 1; i--) {
        char key[4];
        sprintf(key, "%d", i);

        if (i > 9) {
            strcat(key, "*");
        }

        char val[2];
        sprintf(val, "%c", i + 97 - 1);

        s = replace(s, key, val);
    }

    puts(s);

    return 0;
}