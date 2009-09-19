#include "match.h"
#include "string_functions.h"
#include "Wildcard.h"


typedef struct {
    const char * (*rev_find_string_in_string)(const char * haystack, const char * needle, size_t n);
    const char * (*find_string_in_string    )(const char * haystack, const char * needle, size_t n);
    char *       (*find_char_in_string      )(const char * string,   int          chr             );
    int          (*string_compare           )(const char * s1,       const char * s2              );
    int          (*string_n_compare         )(const char * s1,       const char * s2,     size_t n);
    const char *   left_input;
    const char *   right_input;
    Wildpart *     left_part;
    Wildpart *     right_part;
} MatchData;


// basic matching functions {{{1
int
match_Wild_rev(match_data)
    MatchData *  match_data;
{
}


int
match_Wild(match_data)
    MatchData *  match_data;
{
}


int
match_Group_rev(match_data, wild)
    MatchData *  match_data;
    int          wild;
{
}


int
match_Group(match_data, wild)
    MatchData *  match_data;
    int          wild;
{
}


int
match_Fixed_rev(match_data, wild)
    MatchData *  match_data;
    int          wild;
{
}


int
match_Fixed(match_data, wild)
    MatchData *  match_data;
    int          wild;
{
    Wildpart *   part;
    const char * match;

    part = match_data->left_part;
    if (wild) {
        match = (*match_data->find_string_in_string)(match_data->left_input, part->data, part->length);
        if (match == 0) {
            return 0;
        } else {
            match_data->left_input = match;
            return 1;
        }
    } else {
        return (*match_data->string_n_compare)(match_data->left_input, part->data, part->length) == 0;
    }
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
    match_data.right_input  = cstring + length - 1;
    match_data.left_part    = wildcard->parts;
    match_data.right_part   = wildcard->parts + wildcard->length - 1;

    if (casefold) {
        match_data.rev_find_string_in_string  = strrncasestr;
        match_data.find_string_in_string      = strncasestr;
        match_data.find_char_in_string        = strcasechr;
        match_data.string_compare             = strcasecmp;
        match_data.string_n_compare           = strncasecmp;
    } else {
        match_data.rev_find_string_in_string  = strrnstr;
        match_data.find_string_in_string      = strnstr;
        match_data.find_char_in_string        = strchr;
        match_data.string_compare             = strcmp;
        match_data.string_n_compare           = strncmp;
    }
}

