#ifndef WILDCARD_H_GUARD
#define WILDCARD_H_GUARD


typedef enum {
    Fixed, Wild, Kleene, Group, None
} WildpartType;


typedef struct {
    WildpartType  type;
    int           length; // The lenght of Fixed or Group
    char *        data;   // The data for Fixed and Group
} Wildpart;


typedef struct {
    int           length;
    WildpartType  last;   // TODO: move out of there
    Wildpart *    parts;
} Wildcard;


Wildcard * Wildcard_init(void);
void Wildcard_free(Wildcard * wildcard);


#endif

