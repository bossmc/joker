#include <stddef.h>
#include <stdbool.h>
#include "matching_functions.h"


void
match_Wild_rev(match_data)
    MatchData *  match_data;
{
    match_data->right_input -= 1;
}


void
match_Wild(match_data)
    MatchData *  match_data;
{
    match_data->left_input += 1;
}


int
match_Group_rev(match_data, wild)
    MatchData *  match_data;
    int          wild;
{
    Wildpart *   part;
    const char * ptr;

    part = match_data->right_part;
    if (wild) {
        ptr = match_data->right_input + 1;
        do {
            ptr -= 1;
            if ((*match_data->find_char_in_string)(part->data, *ptr) != NULL) {
                match_data->right_input = ptr - 1;
                return true;
            }
        } while(ptr != match_data->left_input);
        return false;
    } else {
        if ((*match_data->find_char_in_string)(part->data, *match_data->right_input) != NULL) {
            match_data->right_input -= 1;
            return true;
        } else {
            return false;
        }
    }
}


int
match_Group(match_data, wild)
    MatchData *  match_data;
    int          wild;
{
    Wildpart *   part;
    const char * ptr;

    part = match_data->left_part;
    if (wild) {
        ptr = match_data->left_input - 1;
        do {
            ptr += 1;
            if ((*match_data->find_char_in_string)(part->data, *ptr) != NULL) {
                match_data->left_input = ptr + 1;
                return true;
            }
        } while(ptr != match_data->right_input);
        return false;
    } else {
        if ((*match_data->find_char_in_string)(part->data, *match_data->left_input) != NULL) {
            match_data->left_input += 1;
            return true;
        } else {
            return false;
        }
    }
}


int
match_Fixed_rev(match_data, wild)
    MatchData *  match_data;
    int          wild;
{
    Wildpart *   part;
    const char * match;
    int          length;

    part = match_data->right_part;
    if (wild) {
        length = match_data->right_input - match_data->left_input + 1;
        match = (*match_data->rev_find_string_in_string)(match_data->right_input, part->data, length);
        if (match == NULL) {
            return false;
        } else {
            match_data->right_input = match - 1;
            return true;
        }
    } else {
        if ((*match_data->string_compare)(match_data->right_input - part->length + 1, part->data, part->length) == 0) {
            match_data->right_input -= part->length;
            return true;
        } else {
            return false;
        }
    }
}


int
match_Fixed(match_data, wild)
    MatchData *  match_data;
    int          wild;
{
    Wildpart *   part;
    const char * match;
    int          length;

    part = match_data->left_part;
    if (wild) {
        length = match_data->right_input - match_data->left_input + 1;
        match = (*match_data->find_string_in_string)(match_data->left_input, part->data, length);
        if (match == NULL) {
            return false;
        } else {
            match_data->left_input = match + part->length;
            return true;
        }
    } else {
        if ((*match_data->string_compare)(match_data->left_input, part->data, part->length) == 0) {
            match_data->left_input += part->length;
            return true;
        } else {
            return false;
        }
    }
}

