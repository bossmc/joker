#include <stdlib.h>
#include <stdio.h>
#include "jkCompiler.h"


static void
jkwarn(message)
    const char *  message;
{
    printf("%s\n", message);
    // TODO
}


static int
hash(cchar)
    const char  cchar;
{
    switch (cchar) {
        case '\\':
            return 0;
        case '[':
            return 1;
        case ']':
            return 2;
        case '*':
            return 3;
        case '?':
            return 4;
        default:
            return 5;
    }
}


static void
push_fixed(cchar, wildcard)
    const char  cchar;
    Wildcard *  wildcard;
{
    printf("-> fixed: %c\n", cchar);
}


static void
push_wild(wildcard)
    Wildcard *  wildcard;
{
    printf("-> wild\n");
}


static void
push_kleene(wildcard)
    Wildcard *  wildcard;
{
    printf("-> kleene\n");
}


static void
push_group(cchar, wildcard)
    const char  cchar;
    Wildcard *  wildcard;
{
    printf("-> group: %c\n", cchar);
}


static void
do_transition(transition, input, state, wildcard)
    const char  transition;
    const char  input;
    int *       state;
    Wildcard *  wildcard;
{
    switch (transition) {
        case 0:
            *state = 1;
            break;
        case 1:
            *state = 2;
            break;
        case 2:
            push_fixed(input, wildcard);
            jkwarn("Unescaped ]");
            break;
        case 3:
            push_kleene(wildcard);
            break;
        case 4:
            push_wild(wildcard);
            break;
        case 5:
            push_fixed(input, wildcard);
            break;
        case 6:
            *state = -1;
            break;
        case 7:
            *state = 0;
            push_fixed(input, wildcard);
            break;
        case 8:
            *state = 0;
            push_fixed('\\', wildcard);
            push_fixed(input, wildcard);
            break;
        case 9:
            *state = -1;
            push_fixed('\\', wildcard);
            break;
        case 10:
            *state = 3;
            break;
        case 11:
            push_group(input, wildcard);
            jkwarn("Unescaped [ in group");
            break;
        case 12:
            *state = 0;
            break;
        case 13:
            push_group(input, wildcard);
            break;
        case 14:
            *state = -1;
            jkwarn("Unfinished group");
            // throw ruby error
            break;
        case 15:
            *state = 2;
            push_group(input, wildcard);
            break;
        case 16:
            *state = 2;
            push_group('\\', wildcard);
            push_group(input, wildcard);
            break;
    }
}


int
Wildcard_Compile(cstring, len, wildcard)
    const char *    cstring;
    const long int  len;
    Wildcard *      wildcard;
{
    // the table that maps (state x input) -> transition
    const char transitiontable[4][7] = {
    //    \   [   ]   *   ? any EOS
        { 0,  1,  2,  3,  4,  5,  6},
        { 7,  7,  7,  7,  7,  8,  9},
        {10, 11, 12, 13, 13, 13, 14},
        {15, 15, 15, 16, 16, 16, 14}
    };
    int state = 0;
    long int p;

    for (p = 0; p < len; p++) {
        char input = cstring[p];
        int hashed = hash(input);
        char transition = transitiontable[state][hashed];
        do_transition(transition, input, &state, wildcard);
    }

    char transition = transitiontable[state][6];
    do_transition(transition, '\0', &state, wildcard);
    return 1;
}

