#ifndef MATCHING_FUNCTIONS_H_GUARD
#define MATCHING_FUNCTIONS_H_GUARD

#include "MatchData.h"


/*
 * Matches a single Wildpart of type Wild from the right
 * end against the given match data. The part must be
 * the current right part in the match data.
 *
 * The input of the match data must not be consumed.
 *
 * Always succeeds.
 *
 */
void
match_Wild_rev(
    MatchData *  match_data);   /* The match data to modify */


/*
 * Matches a single Wildpart of type Wild from the left
 * end against the given match data. The part must be
 * the current left part in the match data.
 *
 * The input of the match data must not be consumed.
 *
 * Always succeeds.
 *
 */
void
match_Wild(
    MatchData *  match_data);   /* The match data to modify */


/*
 * Matches a single Wildpart of type Group from the right
 * end against the given match data. The part must be
 * the current right part in the match data.
 *
 * wild determines whether the part must occurr at the
 * end of the input (false) or anywhere in the input (true).
 *
 * The input of the match data must not be consumed.
 *
 * Returns true on success and false otherwise.
 *
 */
int
match_Group_rev(
    MatchData *  match_data,    /* The match data to modify                */
    int          wild);         /* Determines where to search for the part */


/*
 * Matches a single Wildpart of type Group from the left
 * end against the given match data. The part must be
 * the current left part in the match data.
 *
 * wild determines whether the part must occurr at the
 * beginning of the input (false) or anywhere in the
 * input (true).
 *
 * The input of the match data must not be consumed.
 *
 * Returns true on success and false otherwise.
 *
 */
int
match_Group(
    MatchData *  match_data,    /* The match data to modify                */
    int          wild);         /* Determines where to search for the part */


/*
 * Matches a single Wildpart of type Fixed from the right
 * end against the given match data. The part must be
 * the current right part in the match data.
 *
 * wild determines whether the part must occurr at the
 * end of the input (false) or anywhere in the input (true).
 *
 * The input of the match data must not be consumed.
 *
 * Returns true on success and false otherwise.
 *
 */
int
match_Fixed_rev(
    MatchData *  match_data,    /* The match data to modify                */
    int          wild);         /* Determines where to search for the part */


/*
 * Matches a single Wildpart of type Fixed from the left
 * end against the given match data. The part must be
 * the current left part in the match data.
 *
 * wild determines whether the part must occurr at the
 * beginning of the input (false) or anywhere in the
 * input (true).
 *
 * The input of the match data must not be consumed.
 *
 * Returns true on success and false otherwise.
 *
 */
int
match_Fixed(
    MatchData *  match_data,    /* The match data to modify                */
    int          wild);         /* Determines where to search for the part */


#endif
