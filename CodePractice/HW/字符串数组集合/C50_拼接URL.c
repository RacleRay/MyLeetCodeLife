#include <stdio.h>
#include <string.h>


int main() {
    char s[205] = {0};

    fgets(s, 205, stdin);

    char* pos = strchr(s, ',');
    pos[0] = '\0';

    char* prefix_last = pos - 1;
    char* suffix_first = pos + 1;

    while (prefix_last[0] == '/') {
        prefix_last[0] = '\0';
        prefix_last--;
    }

    while (suffix_first[0] == '/') {
        suffix_first[0] = '\0';
        suffix_first++;
    }

    int i = 0;
    while (s[i] == '/' && s[i + 1] == '/') {
        i++;
    }

    printf("%s/%s", &s[i], suffix_first);

    return 0;
}