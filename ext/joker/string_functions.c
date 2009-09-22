#include <ctype.h>
#include <stddef.h>
#include "string_functions.h"

char *
strcasechr(string, character)
    const char *  string;
    int           character;
{
    char * result;

    result = strchr(string, tolower(character));
    if (result == NULL) {
        return strchr(string, toupper(character));
    } else {
        return result;
    }
}


static const char *
strngenstr(haystack, needle, n, compare)
    const char *  haystack;
    const char *  needle;
    size_t        n;
    int (*compare)(const char *, const char *, size_t);
{
    int           needle_len;
    const char *  ptr;
    const char *  end;

    needle_len = strlen(needle);
    if (needle_len > n) {
        return NULL;
    }
    ptr = haystack - 1;
    end = haystack + n - needle_len;
    do {
        ptr += 1;
        if ((*compare)(ptr, needle, needle_len) == 0) {
            return ptr;
        }
    } while (ptr != end);
    return NULL;
}


const char *
strnstr(haystack, needle, n)
    const char *  haystack;
    const char *  needle;
    size_t        n;
{
    return strngenstr(haystack, needle, n, strncmp);
}


const char *
strncasestr(haystack, needle, n)
    const char *  haystack;
    const char *  needle;
    size_t        n;
{
    return strngenstr(haystack, needle, n, strncasecmp);
}


static const char *
strrngenstr(haystackr, needle, n, compare)
    const char *  haystackr;
    const char *  needle;
    size_t        n;
    int (*compare)(const char *, const char *, size_t);
{
    int           needle_len;
    const char *  ptr;
    const char *  end;

    needle_len = strlen(needle);
    if (needle_len > n) {
        return NULL;
    }
    end = haystackr - n + needle_len;
    ptr = haystackr + 1;
    do {
        ptr -= 1;
        if ((*compare)(ptr, needle, needle_len) == 0) {
            return ptr;
        }
    } while (ptr != end);
    return NULL;
}


const char *
strrnstr(haystackr, needle, n)
    const char *  haystackr;
    const char *  needle;
    size_t        n;
{
    return strrngenstr(haystackr, needle, n, strncmp);
}


const char *
strrncasestr(haystackr, needle, n)
    const char *  haystackr;
    const char *  needle;
    size_t  n;
{
    return strrngenstr(haystackr, needle, n, strncasecmp);
}

