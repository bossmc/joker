#ifndef ARRAY_H_GUARD
#define ARRAY_H_GUARD


/*
 * Enlarges a dynamic C array by one entry.
 *
 *  const char * array = NULL;
 *  CArray_enlarge(&array, char, 0);
 *  array[0] = 'c';
 *
 */
#define CArray_enlarge(array, type, old_size) CArray_enlarge_((void**)array, sizeof(type), old_size)
void * CArray_enlarge_(
    void **   array,        // A pointer to the array
    int       entry_size,   // The size of one entry
    long int  old_size      // The old array size
);


#endif

