#include <malloc.h>
#include <stddef.h>
#include "Wildcard.h"


void
Wildcard_free(wildcard)
    Wildcard *  wildcard;
{
    int i;

    for(i = 0; i < wildcard->length; i++) {
        if (wildcard->parts[i].data != NULL) {
            free(wildcard->parts[i].data);
        }
    }
    free(wildcard->parts);
    free(wildcard);
}

