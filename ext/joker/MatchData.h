#ifndef MATCH_DATA_GUARD
#define MATCH_DATA_GUARD

#include <string.h>
#include "Wildcard.h"


typedef struct {
    const char * ( *rev_find_string_in_string )( const char * haystack, const char * needle, size_t n );
    const char * ( *find_string_in_string     )( const char * haystack, const char * needle, size_t n );
    char *       ( *find_char_in_string       )( const char * string,   int          chr              );
    int          ( *string_compare            )( const char * s1,       const char * s2,     size_t n );
    const char *    left_input;
    const char *    right_input;
    Wildpart *      left_part;
    Wildpart *      right_part;
} MatchData;        


#endif
