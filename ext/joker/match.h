#ifndef MATCH_H_GUARD
#define MATCH_H_GUARD

#include "Wildcard.h"


/*
 * Matches the given Wildcard against the given string.
 * If casefold is true, ignores the case of the string
 * and wildcard.
 *
 * Returns true iff the Wildcard matches the string.
 *
 */
int Wildcard_match(
    Wildcard *      wildcard,   /* The wildcard to match         */
    const char *    cstring,    /* The string to match against   */
    const long int  length,     /* The length of the string      */
    const int       casefold    /* Whether or not to ignore case */
);


#endif

