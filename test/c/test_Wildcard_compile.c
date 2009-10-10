#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <setjmp.h>
#include <google/cmockery.h>
#include <stdio.h>
#include <string.h>
#include "compile.h"

//
// Possible scenarios:
// *    string empty
//      string not empty
// *    contains group
//      contains fixed
//      contains wildcard
//      contains kleene
// *    contains "**"
//


static void
test_empty(state)
    void ** state;
{
    Wildcard *    wildcard;
    const char *  cstring;

    cstring  = "";
    printf("gggggggggggggggggg\n");
    wildcard = Wildcard_compile(cstring, strlen(cstring));
    printf("gggggggggggggggggg\n");
    assert_int_equal(0,          wildcard->length);
    assert_int_equal((int)NULL, (int)wildcard->parts);
}


static void
test_group(state)
    void ** state;
{
}


static void
test_fixed(state)
    void ** state;
{
}


static void
test_wildcard(state)
    void ** state;
{
}


static void
test_kleene(state)
    void ** state;
{
}


static void
test_double_kleene(state)
    void ** state;
{
}


static void
test_mixed(state)
    void ** state;
{
}


int
main() {
    const UnitTest tests[] = {
        unit_test(test_empty),
        unit_test(test_group),
        unit_test(test_fixed),
        unit_test(test_wildcard),
        unit_test(test_kleene),
        unit_test(test_double_kleene),
        unit_test(test_mixed),
    };
    return run_tests(tests);
}

