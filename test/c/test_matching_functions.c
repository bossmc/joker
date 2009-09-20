#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <google/cmockery.h>
#include <stdio.h>
#include <string.h>
#include "string_functions.h"
#include "matching_functions.h"


static void
setup(state)
    void ** state;
{
    MatchData *  match_data;
    Wildcard *   wildcard;
    Wildpart *   wildpart;
    char *       input;

    match_data = test_malloc(sizeof(MatchData));
    wildpart   = test_malloc(sizeof(Wildpart));
    input      = test_malloc(sizeof(char)*7);
    memcpy(input, "orchid", 7);

    match_data->rev_find_string_in_string = strrnstr;
    match_data->find_string_in_string     = strnstr;
    match_data->find_char_in_string       = strchr;
    match_data->string_compare            = strncmp;

    match_data->right_input               = input + strlen(input) - 1;
    match_data->left_input                = input;
    match_data->right_part                = wildpart;
    match_data->left_part                 = wildpart;

    wildpart->data                        = input;
    wildpart->length                      = 6;

    *state                                = match_data;
}


static void
teardown(state)
    void ** state;
{
    MatchData * match_data;

    match_data = *state;
    test_free(match_data->left_part->data);
    test_free(match_data->left_part);
    test_free(match_data);
}


static void
test_match_Wild(state)
    void ** state;
{
    MatchData * match_data;
    
    match_data = *state;
}


static void
test_match_Wild_rev(state)
    void ** state;
{
}


static void
test_match_Fixed(state)
    void ** state;
{
}


static void
test_match_Fixed_rev(state)
    void ** state;
{
}


static void
test_match_Group(state)
    void ** state;
{
}


static void
test_match_Group_rev(state)
    void ** state;
{
}

int
main() {
    const UnitTest tests[] = {
        // string_functions
        unit_test_setup_teardown( test_match_Wild,      setup, teardown ),
        unit_test_setup_teardown( test_match_Wild_rev,  setup, teardown ),
        unit_test_setup_teardown( test_match_Fixed,     setup, teardown ),
        unit_test_setup_teardown( test_match_Fixed_rev, setup, teardown ),
        unit_test_setup_teardown( test_match_Group,     setup, teardown ),
        unit_test_setup_teardown( test_match_Group_rev, setup, teardown ),
    };
    return run_tests(tests);
}

