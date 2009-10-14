#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <setjmp.h>
#include <cmockery.h>
#include <stdio.h>
#include <string.h>
#include <ruby.h>
#include "compile.h"
#include "Wildcard.h"

//
// Possible scenarios:
// *    empty
//      not empty
// *    contains group
//      contains fixed
//      contains wildcard
//      contains kleene
// *    casefold
//      not casefold
//


static void
generic_test(wildcard_string, cstring, casefold, should_match)
    const char *  wildcard_string;
    const char *  cstring;
    bool          casefold;
    bool          should_match;
{
    Wildcard *    wildcard;
    bool          matches;

    wildcard = Wildcard_compile(wildcard_string, strlen(wildcard_string));
    matches  = Wildcard_match(wildcard, cstring, strlen(cstring), casefold);
    assert_int_equal((int)should_match, (int)matches);

    Wildcard_free(wildcard);
}


static void
test_empty(state)
    void ** state;
{
    generic_test("", "",  false, true);
    generic_test("", "",  true,  true);
    generic_test("", "a", false, false);
    generic_test("", "a", true,  false);
}


static void
test_fixed(state)
    void ** state;
{
    generic_test("uiae", "uiae",  false, true);
    generic_test("uiae", "UIAE",  true,  true);
    generic_test("uiae", "UIAE",  false, false); // bad case
    generic_test("uiae", "",      false, false); // empty
    generic_test("uiae", "u",     false, false); // too short
    generic_test("uiae", "uiaeo", false, false); // too long
}


static void
test_group(state)
    void ** state;
{
    generic_test("[uiae]", "u",  false, true);
    generic_test("[uiae]", "U",  true,  true);
    generic_test("[uiae]", "U",  false, false); // bad case
    generic_test("[uiae]", "",   false, false); // empty
    generic_test("[uiae]", "o",  false, false); // wrong character
    generic_test("[uiae]", "ui", false, false); // too long
}


static void
test_wild(state)
    void ** state;
{
}


static void
test_kleene(state)
    void ** state;
{
}


int
main() {
    const UnitTest tests[] = {
        unit_test(test_empty),
        unit_test(test_fixed),
        unit_test(test_group),
        unit_test(test_wild),
        unit_test(test_kleene),
    };
    return run_tests(tests);
}

