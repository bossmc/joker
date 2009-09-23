#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <setjmp.h>
#include <google/cmockery.h>
#include <stdio.h>
#include <string.h>
#include "string_functions.h"
#include "matching_functions.h"


static void
test_match_Wild(state)
    void ** state;
{
    MatchData *   match_data;
    const char *  left_input;
    const char *  right_input;
    
    match_data  = *state;
    left_input  = match_data->left_input;
    right_input = match_data->right_input;
    match_Wild(match_data);
    assert_int_equal((int)left_input+1, (int)match_data->left_input);
    assert_int_equal((int)right_input,  (int)match_data->right_input);
}


static void
test_match_Wild_rev(state)
    void ** state;
{
    MatchData *   match_data;
    const char *  left_input;
    const char *  right_input;
    
    match_data  = *state;
    left_input  = match_data->left_input;
    right_input = match_data->right_input;
    match_Wild_rev(match_data);
    assert_int_equal((int)left_input,    (int)match_data->left_input);
    assert_int_equal((int)right_input-1, (int)match_data->right_input);
}


static void
test_match_Fixed(state)
    void ** state;
{
    MatchData *   match_data;
    const char *  left_input;
    const char *  right_input;

    //
    // possible scenarios:
    // *    empty input                  impossible (prohibited by specification)
    //      non-empty input              possible
    // *    empty part                   impossible (prohibited by compilation process)
    //      non-empty part               possible
    // *    part matches at beginning    possible
    //      part matches, but later      possible
    //      part does not match          possible
    //      part matches, but is longer  possible
    //
    // => 1*1*4 = 4 scenarios
    //
    
    match_data                     = *state;
    left_input                     = match_data->left_input;
    right_input                    = match_data->right_input;
    match_data->left_part->data    = "orc";
    match_data->left_part->length  = 3;
    assert_true(match_Fixed(match_data, false));
    assert_int_equal((int)left_input+3, (int)match_data->left_input);
    assert_int_equal((int)right_input,  (int)match_data->right_input);

    match_data->left_input         = left_input;
    match_data->left_part->length  = 3;
    match_data->left_part->data    = "ork";
    assert_false(match_Fixed(match_data, false));
    assert_int_equal((int)left_input,  (int)match_data->left_input);
    assert_int_equal((int)right_input, (int)match_data->right_input);

    match_data->left_input         = left_input;
    match_data->left_part->length  = 3;
    match_data->left_part->data    = "rch";
    assert_false(match_Fixed(match_data, false));
    assert_int_equal((int)left_input,  (int)match_data->left_input);
    assert_int_equal((int)right_input, (int)match_data->right_input);

    match_data->left_input         = left_input;
    match_data->left_part->length  = 17;
    match_data->left_part->data    = "orchids are great";
    assert_false(match_Fixed(match_data, false));
    assert_int_equal((int)left_input,  (int)match_data->left_input);
    assert_int_equal((int)right_input, (int)match_data->right_input);
}


static void
test_match_Fixed_wild(state)
    void ** state;
{
    MatchData *   match_data;
    const char *  left_input;
    const char *  right_input;

    //
    // possible scenarios:
    // *    empty input                  impossible (prohibited by specification)
    //      non-empty input              possible
    // *    empty part                   impossible (prohibited by compilation process)
    //      non-empty part               possible
    // *    part matches at beginning    possible
    //      part matches, but later      possible
    //      part does not match          possible
    //      part matches, but is longer  possible
    //
    // => 1*1*4 = 4 scenarios
    //
    
    match_data                     = *state;
    left_input                     = match_data->left_input;
    right_input                    = match_data->right_input;
    match_data->left_part->data    = "orc";
    match_data->left_part->length  = 3;
    assert_true(match_Fixed(match_data, true));
    assert_int_equal((int)left_input+3, (int)match_data->left_input);
    assert_int_equal((int)right_input,  (int)match_data->right_input);

    match_data->left_input         = left_input;
    match_data->left_part->length  = 3;
    match_data->left_part->data    = "ork";
    assert_false(match_Fixed(match_data, true));
    assert_int_equal((int)left_input,  (int)match_data->left_input);
    assert_int_equal((int)right_input, (int)match_data->right_input);

    match_data->left_input         = left_input;
    match_data->left_part->length  = 3;
    match_data->left_part->data    = "rch";
    assert_true(match_Fixed(match_data, true));
    assert_int_equal((int)left_input+4, (int)match_data->left_input);
    assert_int_equal((int)right_input,  (int)match_data->right_input);

    match_data->left_input         = left_input;
    match_data->left_part->length  = 17;
    match_data->left_part->data    = "orchids are great";
    assert_false(match_Fixed(match_data, true));
    assert_int_equal((int)left_input,  (int)match_data->left_input);
    assert_int_equal((int)right_input, (int)match_data->right_input);
}


static void
test_match_Fixed_rev(state)
    void ** state;
{
    MatchData *   match_data;
    const char *  left_input;
    const char *  right_input;

    //
    // possible scenarios:
    // *    empty input                  impossible (prohibited by specification)
    //      non-empty input              possible
    // *    empty part                   impossible (prohibited by compilation process)
    //      non-empty part               possible
    // *    part matches at beginning    possible
    //      part matches, but later      possible
    //      part does not match          possible
    //      part matches, but is longer  possible
    //
    // => 1*1*4 = 4 scenarios
    //
    
    match_data                      = *state;
    left_input                      = match_data->left_input;
    right_input                     = match_data->right_input;
    match_data->right_part->data    = "hid";
    match_data->right_part->length  = 3;
    assert_true(match_Fixed_rev(match_data, false));
    assert_int_equal((int)left_input,    (int)match_data->left_input);
    assert_int_equal((int)right_input-3, (int)match_data->right_input);

    match_data->right_input         = right_input;
    match_data->right_part->length  = 3;
    match_data->right_part->data    = "kid";
    assert_false(match_Fixed_rev(match_data, false));
    assert_int_equal((int)left_input,  (int)match_data->left_input);
    assert_int_equal((int)right_input, (int)match_data->right_input);

    match_data->right_input         = right_input;
    match_data->right_part->length  = 3;
    match_data->right_part->data    = "rch";
    assert_false(match_Fixed_rev(match_data, false));
    assert_int_equal((int)left_input,  (int)match_data->left_input);
    assert_int_equal((int)right_input, (int)match_data->right_input);

    match_data->right_input         = right_input;
    match_data->right_part->length  = 16;
    match_data->right_part->data    = "i love my orchid";
    assert_false(match_Fixed_rev(match_data, false));
    assert_int_equal((int)left_input,  (int)match_data->left_input);
    assert_int_equal((int)right_input, (int)match_data->right_input);
}


static void
test_match_Fixed_rev_wild(state)
    void ** state;
{
    MatchData *   match_data;
    const char *  left_input;
    const char *  right_input;

    //
    // possible scenarios:
    // *    empty input                  impossible (prohibited by specification)
    //      non-empty input              possible
    // *    empty part                   impossible (prohibited by compilation process)
    //      non-empty part               possible
    // *    part matches at beginning    possible
    //      part matches, but later      possible
    //      part does not match          possible
    //      part matches, but is longer  possible
    //
    // => 1*1*4 = 4 scenarios
    //
    
    match_data                      = *state;
    left_input                      = match_data->left_input;
    right_input                     = match_data->right_input;
    match_data->right_part->data    = "hid";
    match_data->right_part->length  = 3;
    assert_true(match_Fixed_rev(match_data, true));
    assert_int_equal((int)left_input,    (int)match_data->left_input);
    assert_int_equal((int)right_input-3, (int)match_data->right_input);

    match_data->right_input         = right_input;
    match_data->right_part->length  = 3;
    match_data->right_part->data    = "kid";
    assert_false(match_Fixed_rev(match_data, true));
    assert_int_equal((int)left_input,  (int)match_data->left_input);
    assert_int_equal((int)right_input, (int)match_data->right_input);

    match_data->right_input         = right_input;
    match_data->right_part->length  = 3;
    match_data->right_part->data    = "rch";
    assert_true(match_Fixed_rev(match_data, true));
    assert_int_equal((int)left_input,    (int)match_data->left_input);
    assert_int_equal((int)right_input-5, (int)match_data->right_input);

    match_data->right_input         = right_input;
    match_data->right_part->length  = 16;
    match_data->right_part->data    = "i love my orchid";
    assert_false(match_Fixed_rev(match_data, true));
    assert_int_equal((int)left_input,  (int)match_data->left_input);
    assert_int_equal((int)right_input, (int)match_data->right_input);
}


static void
test_match_Group(state)
    void ** state;
{
}


static void
test_match_Group_wild(state)
    void ** state;
{
}


static void
test_match_Group_rev(state)
    void ** state;
{
}


static void
test_match_Group_rev_wild(state)
    void ** state;
{
}


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

    *state                                = match_data;
}


static void
teardown(state)
    void ** state;
{
    MatchData * match_data;

    match_data = *state;
    while (*match_data->left_input != 'o') {
        match_data->left_input -= 1;
    }
    test_free((char*)match_data->left_input);
    test_free(match_data->left_part);
    test_free(match_data);
}

int
main() {
    const UnitTest tests[] = {
        // string_functions
        unit_test_setup_teardown( test_match_Wild,           setup, teardown ),
        unit_test_setup_teardown( test_match_Wild_rev,       setup, teardown ),
        unit_test_setup_teardown( test_match_Fixed,          setup, teardown ),
        unit_test_setup_teardown( test_match_Fixed_wild,     setup, teardown ),
        unit_test_setup_teardown( test_match_Fixed_rev,      setup, teardown ),
        unit_test_setup_teardown( test_match_Fixed_rev_wild, setup, teardown ),
        unit_test_setup_teardown( test_match_Group,          setup, teardown ),
        unit_test_setup_teardown( test_match_Group_wild,     setup, teardown ),
        unit_test_setup_teardown( test_match_Group_rev,      setup, teardown ),
        unit_test_setup_teardown( test_match_Group_rev_wild, setup, teardown ),
    };
    return run_tests(tests);
}

