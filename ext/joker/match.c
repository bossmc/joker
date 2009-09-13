#include <malloc.h>
#include <string.h>
#include "match.h"
#include "Wildcard.h"
#include "Stack.h"

typedef int (*WildcardStringCompare)(const char *, const char *);


int
Wildcard_match(wildcard, cstring, length, casefold)  // {{{1
    Wildcard *      wildcard;
    const char *    cstring;
    const long int  length;
    const int       casefold;
{
    WildcardStringCompare  compare;
    int                    input_pointer;
    int                    wildpart_pointer;
    Wildpart *             current_part;
    const char *           current_input;

    if (casefold) {
      compare = strcasecmp;
    } else {
      compare = strcmp;
    }

    input_pointer     = 0;
    current_input     = cstring;
    wildpart_pointer  = 0;
    current_part      = wildcard->parts;

    while (1) {
        switch (current_part->type) {
        }
    }
}

