#include <malloc.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <string.h>
#include <ruby.h>
#include "compile.h"
#include "CArray.h"


static int
hash(cchar)  // {{{1
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
push_fixed(cchar, wildcard)  // {{{1
    const char  cchar;
    Wildcard *  wildcard;
{
    char *      new_char;
    Wildpart *  part;

    switch (wildcard->last) {
        case Fixed:  // add to current string
            part        = wildcard->parts + wildcard->length - 1;
            new_char = CArray_enlarge(&part->data, char, part->length);
            part->length += 1;
            *(new_char - 1)  = cchar;
            *new_char        = '\0';
            break;
        default:     // add new array entry
            part = CArray_enlarge(&wildcard->parts, Wildpart, wildcard->length);
            wildcard->length += 1;
            part->type     = Fixed;
            part->length   = 1;
            part->data     = malloc(sizeof(char)*2);
            part->data[0]  = cchar;
            part->data[1]  = '\0';
            break;
    }
}


static void
push_wild(wildcard)  // {{{1
    Wildcard *  wildcard;
{
    Wildpart *  part;

    switch (wildcard->last) {
        default:      // add new array entry
            part = CArray_enlarge(&wildcard->parts, Wildpart, wildcard->length);
            wildcard->length += 1;
            part->type = Wild;
            break;
    }
}


static void
push_kleene(wildcard)  // {{{1
    Wildcard *  wildcard;
{
    Wildpart *  part;

    switch (wildcard->last) {
        case Kleene:  // transform ** --> *
            break;
        default:      // add new array entry
            part = CArray_enlarge(&wildcard->parts, Wildpart, wildcard->length);
            wildcard->length += 1;
            part->type = Kleene;
            break;
    }
}


static void
push_group(cchar, wildcard)  // {{{1
    const char  cchar;
    Wildcard *  wildcard;
{
    char *      new_char;
    Wildpart *  part;

    switch (wildcard->last) {
        case Group:  // add to current group
            part      = wildcard->parts + wildcard->length - 1;
            new_char  = CArray_enlarge(&part->data, char, part->length);
            part->length += 1;
            *(new_char - 1)  = cchar;
            *new_char        = '\0';
            break;
        default:     // add new array entry
            part = CArray_enlarge(&wildcard->parts, Wildpart, wildcard->length);
            wildcard->length += 1;
            part->type     = Group;
            part->length   = 1;
            part->data     = malloc(sizeof(char)*2);
            part->data[0]  = cchar;
            part->data[1]  = '\0';
            break;
    }
}


static void
do_transition(transition, input, state, wildcard)  // {{{1
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
            rb_warn("wildcard has `]' without escape");
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
            rb_warn("character class has `[' without escape");
            break;
        case 12:
            *state = 0;
            break;
        case 13:
            push_group(input, wildcard);
            break;
        case 14:
            *state = -1;
            rb_raise(rb_eSyntaxError, "premature end of wildcard");
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


Wildcard *
Wildcard_compile(cstring, len)  // {{{1
    const char *    cstring;
    const long int  len;
{
    // the table that maps (state x input) -> transition
    const char transition_table[4][7] = {
    //    \   [   ]   *   ? any EOS
        { 0,  1,  2,  3,  4,  5,  6},
        { 7,  7,  7,  7,  7,  8,  9},
        {10, 11, 12, 13, 13, 13, 14},
        {15, 15, 15, 16, 16, 16, 14}
    };
    int state = 0;

    Wildcard * wildcard;
    long int   p;
    char       input;
    int        hashed;
    char       transition;

    wildcard         = malloc(sizeof(Wildcard));
    wildcard->parts  = NULL;
    wildcard->length = 0;
    wildcard->last   = None;

    for (p = 0; p < len; p++) {
        input = cstring[p];
        hashed = hash(input);
        transition = transition_table[state][hashed];
        do_transition(transition, input, &state, wildcard);
    }

    transition = transition_table[state][6];
    do_transition(transition, '\0', &state, wildcard);
}

