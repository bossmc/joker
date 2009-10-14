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
generic_test(cstring, length, expected)
    const char *  cstring;
    const int     length;
    const char *  expected;
{
    Wildcard *    wildcard;
    int           i;

    wildcard = Wildcard_compile(cstring, strlen(cstring));
    assert_int_not_equal( (int)NULL, (int)wildcard        );
    assert_int_not_equal( (int)NULL, (int)wildcard->first );
    assert_int_not_equal( (int)NULL, (int)wildcard->last  );
    assert_int_equal(     length,    wildcard->length     );

    for (i = 0; i < length; i += 2) {
        assert_int_equal((int)*(expected + i), (int)*(wildcard->first + i));
    }

    Wildcard_free(wildcard);
}


static void
test_empty(state)
    void ** state;
{
    Wildcard *    wildcard;
    int           i;

    wildcard = Wildcard_compile("", 0);
    assert_int_not_equal( (int)NULL, (int)wildcard        );
    assert_int_equal(     (int)NULL, (int)wildcard->first );
    assert_int_equal(     (int)NULL, (int)wildcard->last  );
    assert_int_equal(     0,         wildcard->length     );
}


static void
test_fixed(state)
    void ** state;
{
    const char expected[8] = {
        Fixed, 'u',
        Fixed, 'i',
        Fixed, 'a',
        Fixed, 'e',
    };

    generic_test("uiae", 8, expected);
}


static void
test_group(state)
    void ** state;
{
    const char expected[4] = {
        Group, 'i',
        Group, 'a',
    };

    generic_test("[ia]", 4, expected);
}


static void
test_wild(state)
    void ** state;
{
    const char expected[2] = {
        Wild, '?',
    };

    generic_test("?", 2, expected);
}


static void
test_kleene(state)
    void ** state;
{
    const char expected[2] = {
        Kleene, '*',
    };

    generic_test("*",    2, expected);
    generic_test("**",   2, expected);
    generic_test("****", 2, expected);
}


static void
test_mixed(state)
    void ** state;
{
    const char expected[10] = {
        Fixed,  'u',
        Wild,   '?',
        Kleene, '*',
        Group,  'e',
        Group,  '?',
    };

    generic_test("u?*[e?]", 10, expected);
}


int
main() {
    const UnitTest tests[] = {
        unit_test(test_empty),
        unit_test(test_fixed),
        unit_test(test_group),
        unit_test(test_wild),
        unit_test(test_kleene),
        unit_test(test_mixed),
    };
    return run_tests(tests);
}

