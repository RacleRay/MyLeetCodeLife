#include <stdio.h>
#include <string.h>


int main() {
    char s[11];
    scanf("%s", s);

    int counts[26] = {0};
    int len = strlen(s);
    int cumu = 1;        
    for (int i = 0; i < len; ++i) {
        int val = s[i] - 'A';
        cumu *= (i + 1);
        counts[val]++;
    }

    for (int i = 0; i < 26; ++i) {
        if (counts[i] > 0) {
            for (int j = 2; j <= counts[i]; ++j) {
                cumu /= j;
            }
        }
    }

    printf("%d\n", cumu);

    return 0;
}