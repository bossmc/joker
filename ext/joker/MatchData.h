#ifndef MATCH_DATA_GUARD
#define MATCH_DATA_GUARD

#include <string.h>
#include "Wildcard.h"


/*
 * Stores all low level functions needed for compiling,
 * as well as the current input and current Wildparts.
 *
 */
typedef struct {
    const char * ( *rev_find_string_in_string )( const char * haystack, const char * needle, size_t n );
    const char * ( *find_string_in_string     )( const char * haystack, const char * needle, size_t n );
    char *       ( *find_char_in_string       )( const char * string,   int          chr              );
    int          ( *string_compare            )( const char * s1,       const char * s2,     size_t n );
    const char *    left_input;     /* The current left input character  */
    const char *    right_input;    /* The current right input character */
    Wildpart *      left_part;      /* The current left Wildpart         */
    Wildpart *      right_part;     /* The current right Wildpart        */
} MatchData;        


#endif
