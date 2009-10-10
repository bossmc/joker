#include <malloc.h>
#include <stddef.h>
#include "Wildcard.h"


void Wildcard_init(wildcard)
    Wildcard *  wildcard;
{
    wildcard->length = 0;
    wildcard->first  = NULL;
    wildcard->last   = NULL;
}


void Wildcard_free(wildcard)
    Wildcard *  wildcard;
{
    free(wildcard->first);
}


void Wildcard_enlarge(wildcard)
    Wildcard *  wildcard;
{
    wildcard->length += 2;
    realloc(wildcard->first, wildcard->length);
    wildcard->last = wildcard->first + length - 2;
}

