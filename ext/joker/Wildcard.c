#include <malloc.h>
#include "Wildcard.h"

Wildcard *
Wildcard_init(void)
{
    Wildcard * wildcard;

    wildcard = malloc(sizeof(Wildcard));
    wildcard->length = 0;
    wildcard->parts  = 0;
    wildcard->last   = None;

    return wildcard;
}

void
Wildcard_free(wildcard)
    Wildcard *  wildcard;
{
    free(wildcard->parts);
    free(wildcard);
}

