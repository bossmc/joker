#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <setjmp.h>
#include <cmockery.h>
#include <stdio.h>
#include <string.h>
#include "compile.h"
#include "Wildcard.h"

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
    wildcard = Wildcard_compile(cstring, strlen(cstring));
    assert_int_not_equal( (int)NULL, (int)wildcard        );
    assert_int_equal(     (int)NULL, (int)wildcard->first );
    assert_int_equal(     (int)NULL, (int)wildcard->last  );
    assert_int_equal(     0,         wildcard->length     );

    Wildcard_free(wildcard);
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

