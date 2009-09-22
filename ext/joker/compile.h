#ifndef COMPILE_H_GUARD
#define COMPILE_H_GUARD

#include "Wildcard.h"


/*
 * Compiles an input string to the internal Wildcard
 * represenation.
 *
 * The Wildcard instance must be preallocated by the
 * caller, but does not need to be prefilled with
 * any values.
 *
 */
void Wildcard_Compile(
        const char * cstring,   /* The string to parse                        */
        const long int len,     /* The length of the string                   */
        Wildcard * wildcard);   /* The Wildcard struct to store the result in */


#endif

