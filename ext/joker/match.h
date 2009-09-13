#ifndef MATCH_H_GUARD
#define MATCH_H_GUARD

#include "Wildcard.h"


int Wildcard_match(
    Wildcard *      wildcard,
    const char *    cstring,
    const long int  length,
    const int       casefold
);


#endif

