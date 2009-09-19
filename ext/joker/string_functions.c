#include <ctype.h>
#include "string_functions.h"

char *
strcasechr(string, character)
    const char *  string;
    int           character;
{
    char * result;

    result = strchr(string, tolower(character));
    if (result == 0) {
        return strchr(string, toupper(character));
    } else {
        return result;
    }
}


const char *
strnstr(haystack, needle, n)
    const char *  haystack;
    const char *  needle;
    size_t        n;
{
    int           needle_len;
    const char *  ptr;
    const char *  end;

    needle_len = strlen(needle);
    if (needle_len > n) {
        return 0;
    }
    ptr = haystack - 1;
    end = haystack + n - needle_len;
    do {
        ptr += 1;
        if (strncmp(ptr, needle, needle_len) == 0) {
            return ptr;
        }
    } while (ptr != end);
    return 0;
}


const char *
strncasestr(haystack, needle, n)
    const char *  haystack;
    const char *  needle;
    size_t        n;
{
    int           needle_len;
    const char *  ptr;
    const char *  end;

    needle_len = strlen(needle);
    if (needle_len > n) {
        return 0;
    }
    ptr = haystack - 1;
    end = haystack + n - needle_len;
    do {
        ptr += 1;
        if (strncasecmp(ptr, needle, needle_len) == 0) {
            return ptr;
        }
    } while (ptr != end);
    return 0;
}


const char *
strrnstr(haystack, needle, n)
    const char *  haystack;
    const char *  needle;
    size_t        n;
{
    int           needle_len;
    const char *  ptr;

    needle_len = strlen(needle);
    if (needle_len > n) {
        return 0;
    }
    ptr = haystack + n - needle_len + 1;
    do {
        ptr -= 1;
        if (strncmp(ptr, needle, needle_len) == 0) {
            return ptr;
        }
    } while (ptr != haystack);
    return 0;
}


const char *
strrncasestr(haystack, needle, n)
    const char *  haystack;
    const char *  needle;
    size_t  n;
{
    int           needle_len;
    const char *  ptr;

    needle_len = strlen(needle);
    if (needle_len > n) {
        return 0;
    }
    ptr = haystack + n - needle_len + 1;
    do {
        ptr -= 1;
        if (strncasecmp(ptr, needle, needle_len) == 0) {
            return ptr;
        }
    } while (ptr != haystack);
    return 0;
}

