#ifndef STRING_H_GUARD
#define STRING_H_GUARD

#include <string.h>


const char *
strrncasestr(
    const char *  haystack,
    const char *  needle,
    size_t  n);


const char *
strrnstr(
    const char *  haystack,
    const char *  needle,
    size_t        n);


const char *
strncasestr(
    const char *  haystack,
    const char *  needle,
    size_t        n);


const char *
strnstr(
    const char *  haystack,
    const char *  needle,
    size_t        n);


char *
strcasechr(
    const char *  string,
    int           character);


#endif
