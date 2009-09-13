#ifndef ARRAY_H_GUARD
#define ARRAY_H_GUARD


#define CArray_enlarge(array, type, old_size) CArray_enlarge_((void**)array, sizeof(type), old_size)

void * CArray_enlarge_(
    void **   array,
    int       entry_size,
    long int  old_size
);


#endif

