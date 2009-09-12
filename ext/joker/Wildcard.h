
typedef struct {
    char        type;   // 0 => '*', 1 => '?', 2 => string, 3 => group
    int         len;    // The lenght of the string or group
    char *      data;   // The data for the strings and groups
} Wildpart;

typedef struct {
    int         len;
    Wildpart *  parts;
} Wildcard;

