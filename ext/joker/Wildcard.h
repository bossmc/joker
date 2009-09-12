#ifndef WILDCARD_H_GUARD
#define WILDCARD_H_GUARD


typedef enum {
    Fixed, Wild, Kleene, Group, None
} WildpartType;


typedef struct {
    WildpartType  type;
    int           length; // The lenght of fixed or group
    char *        data;   // The data for fixed and group
} Wildpart;


typedef struct {
    int           length;
    WildpartType  last;
    Wildpart *    parts;
} Wildcard;


Wildcard * Wildcard_init(void);
void Wildcard_free(Wildcard * wildcard);


#endif

