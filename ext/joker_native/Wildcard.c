#include <malloc.h>
#include <stddef.h>
#include <Wildcard.h>


void Wildcard_init(wildcard) // {{{1
    Wildcard *  wildcard;
{
    wildcard->length = 0;
    wildcard->first  = NULL;
    wildcard->last   = NULL;
}


void Wildcard_free(wildcard) // {{{1
    Wildcard *  wildcard;
{
    free(wildcard->first);
}


void Wildcard_enlarge(wildcard) // {{{1
    Wildcard *  wildcard;
{
    wildcard->length += 2;
    wildcard->first   = realloc(wildcard->first, wildcard->length);
    wildcard->last    = wildcard->first + wildcard->length - 2;
}

