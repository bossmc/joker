#ifndef WILDCARD_H_GUARD
#define WILDCARD_H_GUARD


typedef enum {
    Fixed   = 1,
    Group   = 2,
    Wild    = 4,
    Kleene  = 8,
    EOW     = 16,
} WildcardType;

/*
 * Represents a Wildcard.
 * Used for matching.
 *
 */
typedef struct {
    char *   first;
    char *   last;
    long int length;
} Wildcard;


/*
 * Initializes a Wildcard.
 *
 */
void Wildcard_init(Wildcard * wildcard);


/*
 * Frees a Wildcard.
 *
 */
void Wildcard_free(Wildcard * wildcard);


/*
 * Adds two additional characters at the end
 * and adjusts all the pointers.
 *
 */
void Wildcard_enlarge(Wildcard * wildcard);


#endif

