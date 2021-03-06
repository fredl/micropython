#include <stdint.h>
#include "std.h"

void *memcpy(void *dest, const void *src, size_t n) {
    // TODO align and copy 32 bits at a time
    uint8_t *d = dest;
    const uint8_t *s = src;
    for (; n > 0; n--) {
        *d++ = *s++;
    }
    return dest;
}

void *memmove(void *dest, const void *src, size_t n) {
    if (src < dest && dest < src + n) {
        // need to copy backwards
        uint8_t *d = dest + n - 1;
        const uint8_t *s = src + n - 1;
        for (; n > 0; n--) {
            *d-- = *s--;
        }
        return dest;
    } else {
        // can use normal memcpy
        return memcpy(dest, src, n);
    }
}

void *memset(void *s, int c, size_t n) {
    uint8_t *s2 = s;
    for (; n > 0; n--) {
        *s2++ = c;
    }
    return s;
}

int strlen(const char *str) {
    int len = 0;
    for (const char *s = str; *s; s++) {
        len += 1;
    }
    return len;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = *s1++; // XXX UTF8 get char, next char
        char c2 = *s2++; // XXX UTF8 get char, next char
        if (c1 < c2) return -1;
        else if (c1 > c2) return 1;
    }
    if (*s2) return -1;
    else if (*s1) return 1;
    else return 0;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    while (*s1 && *s2 && n > 0) {
        char c1 = *s1++; // XXX UTF8 get char, next char
        char c2 = *s2++; // XXX UTF8 get char, next char
        n--;
        if (c1 < c2) return -1;
        else if (c1 > c2) return 1;
    }
    if (n == 0) return 0;
    else if (*s2) return -1;
    else if (*s1) return 1;
    else return 0;
}

char *strndup(const char *s, size_t n) {
    size_t len = strlen(s);
    if (n > len) {
        n = len;
    }
    char *s2 = malloc(n + 1);
    memcpy(s2, s, n);
    s2[n] = '\0';
    return s2;
}

char *strcpy(char *dest, const char *src) {
    char *d = dest;
    while (*src) {
        *d++ = *src++;
    }
    *d = '\0';
    return dest;
}

// needed because gcc optimises strcpy + strcat to this
char *stpcpy(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return dest;
}

char *strcat(char *dest, const char *src) {
    char *d = dest;
    while (*d) {
        d++;
    }
    while (*src) {
        *d++ = *src++;
    }
    *d = '\0';
    return dest;
}
