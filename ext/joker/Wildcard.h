#ifndef WILDCARD_H_GUARD
#define WILDCARD_H_GUARD


/*
 * All the types of Wildparts.
 *
 * None is only used during compilation.
 *
 */
typedef enum {
    Fixed, Wild, Kleene, Group, None
} WildpartType;


/*
 * Represents one unit in a Wildcard.
 * Can represent any of the four WildpartTypes.
 *
 */
typedef struct {
    WildpartType  type;     /* The Wildpart's type          */
    int           length;   /* The length of Fixed or Group */
    char *        data;     /* The data for Fixed and Group */
} Wildpart;


/*
 * Represents a Wildcard.
 * Used for matching.
 *
 */
typedef struct {
    int           length;   /* The number of parts in this Wildcard */
    WildpartType  last;
    Wildpart *    parts;    /* A CArray of parts */
} Wildcard;


/*
 * Frees a Wildcard and all it's associated parts.
 *
 */
void Wildcard_free(Wildcard * wildcard);


#endif

