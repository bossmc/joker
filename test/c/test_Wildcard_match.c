#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <setjmp.h>
#include <google/cmockery.h>
#include <stdio.h>
#include <string.h>
#include "compile.h"
#include "match.h"

//
// Possible scenarios:
// *    input empty
//      input not empty
// *    Wildcard empty
//      Wildcard not empty
// *    Wildcard matches
//      Wildcard does not match at all
//      Wildcard doesn't match at beginning
//      Wildcard doesn't match at end
//      Wildcard doesn't match at middle
// *    Wildcard == '*'
//


static void
test_empty(state)
    void * state;
{
}


static void
test_match(state)
    void * state;
{
}


static void
test_non_match(state)
    void * state;
{
}


static void
test_non_match_end(state)
    void * state;
{
}


static void
test_non_match_beg(state)
    void * state;
{
}


static void
test_non_match_mid(state)
    void * state;
{
}


static void
test_kleene(state)
    void * state;
{
}


static void
setup(state)
    void ** state;
{
}


static void
teardown(state)
    void ** state;
{
}

int
main() {
    const UnitTest tests[] = {
        unit_test_setup_teardown( test_empty,           setup, teardown ),
        unit_test_setup_teardown( test_match,           setup, teardown ),
        unit_test_setup_teardown( test_non_match,       setup, teardown ),
        unit_test_setup_teardown( test_non_match_end,   setup, teardown ),
        unit_test_setup_teardown( test_non_match_beg,   setup, teardown ),
        unit_test_setup_teardown( test_non_match_mid,   setup, teardown ),
        unit_test_setup_teardown( test_kleene,          setup, teardown ),
    };
    return run_tests(tests);
}

