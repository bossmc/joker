#include <malloc.h>
#include <ruby.h>
#include "CArray.h"


void *
CArray_enlarge_(array, entry_size, old_size)
    void **   array;
    int       entry_size;
    long int  old_size;
{
    void *    new_array;

    new_array = realloc(*array, entry_size * (old_size + 1));
    *array = new_array;
    return new_array + old_size;
}



