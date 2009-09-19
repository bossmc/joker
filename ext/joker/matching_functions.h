#ifndef MATCHING_FUNCTIONS_H_GUARD
#define MATCHING_FUNCTIONS_H_GUARD

#include "MatchData.h"


void
match_Wild_rev(
    MatchData *  match_data);


void
match_Wild(
    MatchData *  match_data);


int
match_Group_rev(
    MatchData *  match_data,
    int          wild);


int
match_Group(
    MatchData *  match_data,
    int          wild);


int
match_Fixed_rev(
    MatchData *  match_data,
    int          wild);


int
match_Fixed(
    MatchData *  match_data,
    int          wild);


#endif
