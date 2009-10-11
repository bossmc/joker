#ifndef WILDCARD_H_GUARD
#define WILDCARD_H_GUARD


/*
 * The different kinds of Wildcard components.
 *
 */
typedef enum {
    Fixed   = 1,
    Group   = 2,
    Wild    = 4,
    Kleene  = 8,
    EOW     = 16,   // only used in matching
} WildcardType;

/*
 * Represents a Wildcard internally.
 *
 */
typedef struct {
    char *   first;     // The first Wildcard part
    char *   last;      // The last Wildcard part
    long int length;    // How many chars there are (not parts!)
} Wildcard;


void Wildcard_init(Wildcard * wildcard);
void Wildcard_free(Wildcard * wildcard);


/*
 * Adds two additional characters at the end
 * and adjusts all the pointers.
 *
 */
void Wildcard_enlarge(Wildcard * wildcard);


#endif

