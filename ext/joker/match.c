#include "match.h"
#include "string_functions.h"
#include "matching_functions.h"
#include "MatchData.h"
#include "Wildcard.h"


static int
match_from_left(match_data, wild) // {{{1
    MatchData *  match_data;
    int          wild;
{
    while (match_data->left_part <= match_data->right_part) {
        switch (match_data->left_part->type) {
            case Group:
                if (match_Group(match_data, wild) == 0) {
                    return 0;
                }
                wild = 0;
                break;
            case Wild:
                match_Wild(match_data);
                break;
            case Fixed:
                if (match_Fixed(match_data, wild) == 0) {
                    return 0;
                }
                wild = 0;
                break;
            case Kleene:
                return 1;
        }
        match_data->left_part += 1;
    }
}


static int
match_from_right(match_data, wild) // {{{1
    MatchData *  match_data;
    int          wild;
{
    while (match_data->left_part <= match_data->right_part) {
        switch (match_data->right_part->type) {
            case Group:
                if (match_Group_rev(match_data, wild) == 0) {
                    return 0;
                }
                wild = 0;
                break;
            case Wild:
                match_Wild_rev(match_data);
                break;
            case Fixed:
                if (match_Fixed_rev(match_data, wild) == 0) {
                    return 0;
                }
                wild = 0;
                break;
            case Kleene:
                return 1;
        }
        match_data->right_part -= 1;
        wild = 0;
    }
}


void
match_kleenes(match_data) // {{{1
    MatchData *  match_data;
{
    if (match_data->left_part <= match_data->right_part) {
        match_data->left_part += 1;
    }
    if (match_data->left_part <= match_data->right_part) {
        match_data->right_part -= 1;
    }
}


int
Wildcard_match(wildcard, cstring, length, casefold) // {{{1
    Wildcard *      wildcard;
    const char *    cstring;
    const long int  length;
    const int       casefold;
{
    MatchData       match_data;
    int             wild;
    int             input_end;
    int             parts_end;

    match_data.left_input   = cstring;
    match_data.right_input  = cstring + length - 1;
    match_data.left_part    = wildcard->parts;
    match_data.right_part   = wildcard->parts + wildcard->length - 1;

    if (casefold) {
        match_data.rev_find_string_in_string  = strrncasestr;
        match_data.find_string_in_string      = strncasestr;
        match_data.find_char_in_string        = strcasechr;
        match_data.string_compare             = strncasecmp;
    } else {
        match_data.rev_find_string_in_string  = strrnstr;
        match_data.find_string_in_string      = strnstr;
        match_data.find_char_in_string        = strchr;
        match_data.string_compare             = strncmp;
    }

    wild = 0;
    while (1) {
        input_end = (match_data.left_input > match_data.right_input);
        parts_end = (match_data.left_part  > match_data.right_part );

        if (input_end && parts_end) {
            return 1;
        } else if (input_end || parts_end) {
            return 0;
        }

        if (match_from_left(&match_data, wild) == 0) {
            return 0;
        }
        if (match_from_right(&match_data, wild) == 0) {
            return 0;
        }
        match_kleenes(&match_data);
        wild = 1;
    }
}

