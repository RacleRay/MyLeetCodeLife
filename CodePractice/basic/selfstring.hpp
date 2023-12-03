#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;


namespace selfmade {
void memcpy(void* dest, const void* src, size_t n) {
    if (!dest || !src || n == 0) {
        // printf("%s: %s: %d: input error.", __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
        printf("input error");
        return;
    }
    
    char* d = (char *)dest;
    char* s = (char *)src;
    // ========= WRONG IMPLEMENT ==========
    // while (src && n--) {
    //     *d++ = *s++;
    // }

    // Think about overlap
    if (s < d && s + n > d) {
        d = d + n - 1;
        s = s + n - 1;
        while (n--) {
            *d-- = *s--;
        }
        return;
    }

    while (src && n--) {
        *d++ = *s++;
    }

    return;
}

char* strcpy(char* dest, const char* src) {
    if (!dest || !src) return nullptr;
    char *d = dest;
    while ((*d++ = *src++) != '\0') {}; // boring
    return dest;
}

char* strncpy(char* dest, const char* src, size_t n) {
    if (!dest || !src || n == 0) return nullptr;

    size_t i = 0;
    for (; i < n && (*src != '\0'); ++i) {
        dest[i] = src[i];
    }

    for (; i < n; ++i) {
        dest[i] = '\0';  // same as 0
    }

    return dest;
}

size_t strlen(const char* s) {
    if (!s) return 0;
    size_t len = 0;
    while ((*s++) != '\0') {++len;}
    return len;
}

char* strstr(const char* haystack, const char* needle) {
    if (!haystack || !needle) return nullptr;

    size_t hlen = strlen(haystack);
    size_t nlen = strlen(needle);
    if (nlen > hlen) return nullptr;

    char* hs = (char *) haystack;
    for (size_t i = 0; i < hlen - nlen; ++i) {
        size_t j = 0;
        for (; j < nlen; ++j) {
            if (haystack[i + j] != needle[j]) break;
        }
        if (j == nlen) return hs + i;
    }

    return nullptr;
}

char* strcat(char* dest, const char* src) {
    if (!dest || !src) return nullptr;

    char *d = dest;
    while ((*d++) != '\0') {};
    while ((*src) != '\0') {
        *d++ = *src++;
    }
    *d = '\0';

    return dest;
}

int strcmp(const char* s1, const char* s2) {
    while (*s1 == *s2) {
        if (*s1 == '\0') break;
        ++s1;
        ++s2;
    }
    return *s1 - *s2;
}

}