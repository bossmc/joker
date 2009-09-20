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
            if ((*match_data->find_char_in_string)(part->data, *ptr) != 0) {
                match_data->right_input = ptr;
                return 1;
            }
        } while(ptr != match_data->left_input);
        return 0;
    } else {
        if ((*match_data->find_char_in_string)(part->data, *match_data->right_input) != 0) {
            match_data->right_input -= 1;
            return 1;
        } else {
            return 0;
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
            if ((*match_data->find_char_in_string)(part->data, *ptr) != 0) {
                match_data->left_input = ptr;
                return 1;
            }
        } while(ptr != match_data->right_input);
        return 0;
    } else {
        if ((*match_data->find_char_in_string)(part->data, *match_data->left_input) != 0) {
            match_data->left_input += 1;
            return 1;
        } else {
            return 0;
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
        match = (*match_data->rev_find_string_in_string)(match_data->left_input, part->data, length);
        if (match == 0) {
            return 0;
        } else {
            match_data->right_input = match - 1;
            return 1;
        }
    } else {
        if ((*match_data->string_compare)(match_data->right_input - part->length + 1, part->data, part->length) == 0) {
            match_data->right_input -= 1;
            return 1;
        } else {
            return 0;
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
        if (match == 0) {
            return 0;
        } else {
            match_data->left_input = match;
            return 1;
        }
    } else {
        if ((*match_data->string_compare)(match_data->left_input, part->data, part->length) == 0) {
            match_data->left_input += 1;
            return 1;
        } else {
            return 0;
        }
    }
}

