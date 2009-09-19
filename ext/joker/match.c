#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include "match.h"
#include "Wildcard.h"


typedef struct {
    char *  (*rev_find_string_in_string)(const char * haystack, const char * needle);
    char *  (*find_string_in_string)(const char * haystack, const char * needle);
    char *  (*find_char_in_string)(const char * string, int chr);
    int     (*string_compare)(const char * s1, const char * s2);
    int     (*string_n_compare)(const char * s1, const char * s2, size_t n);
    const char *  left_input;
    const char *  right_input;
    Wildpart *    left_part;
    Wildpart *    right_part;
} MatchData;


// basic string functions {{{1
static int
strcasechr(string, character)
    const char *  string;
    int           character;
{
    return strchr(string, tolower(character)) || strchr(string, toupper(character));
}


static char *
strrstr(haystack, needle)
    const char *  haystack;
    const char *  needle;
{
    int  haystack_len;
    int  needle_len;

    haystack_len  = strlen(haystack);
    needle_len    = strlen(needle);
    if (needle_len > haystack_len) {
        return 0;
    }
    const char *  ptr = haystack + haystack_len - needle_len + 1;
    do {
        ptr -= 1;
        if (strncmp(ptr, needle, needle_len) == 0) {
            return 1;
        }
    } while (ptr != haystack)
    return 0;
}


static char *
strrcasestr(haystack, needle)
    const char *  haystack;
    const char *  needle;
{
    int  haystack_len;
    int  needle_len;

    haystack_len  = strlen(haystack);
    needle_len    = strlen(needle);
    if (needle_len > haystack_len) {
        return 0;
    }
    const char *  ptr = haystack + haystack_len - needle_len + 1;
    do {
        ptr -= 1;
        if (strncasecmp(ptr, needle, needle_len) == 0) {
            return 1;
        }
    } while (ptr != haystack)
    return 0;
}


int
Wildcard_match(wildcard, cstring, length, casefold)  // {{{1
    Wildcard *      wildcard;
    const char *    cstring;
    const long int  length;
    const int       casefold;
{
    MatchData       match_data;

    match_data.left_input   = cstring;
    match_data.right_input  = cstring + lenght - 1;
    match_data.left_part    = wildcard->parts;
    match_data.right_part   = wildcard->parts + wildcard->length - 1;

    if (casefold) {
        match_data.rev_find_string_in_string  = strrcasestr;
        match_data.find_string_in_string      = strcasestr;
        match_data.find_char_in_string        = strcasechr;
        match_data.string_compare             = strcasecmp;
        match_data.string_n_compare           = strncasecmp;
    } else {
        match_data.rev_find_string_in_string  = strrstr;
        match_data.find_string_in_string      = strstr;
        match_data.find_char_in_string        = strchr;
        match_data.string_compare             = strcmp;
        match_data.string_n_compare           = strncmp;
    }
}

