#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <google/cmockery.h>
#include <stdio.h>
#include "string_functions.h"


static void
test_strnstr(state)
    void ** state;
{
    assert_int_equal(     0, (int)strnstr("roses", "r",    0));
    assert_int_not_equal( 0, (int)strnstr("roses", "r",    3));
    assert_int_equal(     0, (int)strnstr("roses", "x",    3));
    assert_int_equal(     0, (int)strnstr("roses", "e",    3));
    assert_int_not_equal( 0, (int)strnstr("roses", "s",    3));
    assert_int_equal(     0, (int)strnstr("roses", "x",    5));
    assert_int_equal(     0, (int)strnstr("roses", "ross", 5));
    assert_int_equal(     0, (int)strnstr("roses", "sess", 5));
    assert_int_not_equal( 0, (int)strnstr("roses", "ose",  5));
    assert_int_not_equal( 0, (int)strnstr("roses", "ro",   5));
    assert_int_not_equal( 0, (int)strnstr("roses", "es",   5));
}


static void
test_strncasestr(state)
    void ** state;
{
    assert_int_equal(     0, (int)strncasestr("roses", "r",    0));
    assert_int_not_equal( 0, (int)strncasestr("roses", "r",    3));
    assert_int_not_equal( 0, (int)strncasestr("roses", "R",    3));
    assert_int_equal(     0, (int)strncasestr("roses", "x",    3));
    assert_int_equal(     0, (int)strncasestr("roses", "e",    3));
    assert_int_not_equal( 0, (int)strncasestr("roses", "s",    3));
    assert_int_not_equal( 0, (int)strncasestr("roses", "S",    3));
    assert_int_equal(     0, (int)strncasestr("roses", "x",    5));
    assert_int_equal(     0, (int)strncasestr("roses", "ross", 5));
    assert_int_equal(     0, (int)strncasestr("roses", "sess", 5));
    assert_int_not_equal( 0, (int)strncasestr("roses", "ose",  5));
    assert_int_not_equal( 0, (int)strncasestr("roses", "oSe",  5));
    assert_int_not_equal( 0, (int)strncasestr("roses", "OSE",  5));
    assert_int_not_equal( 0, (int)strncasestr("roses", "ro",   5));
    assert_int_not_equal( 0, (int)strncasestr("roses", "es",   5));
}


static void
test_strrnstr(state)
    void ** state;
{
    const char * roses;

    roses = "roses";
    roses += strlen(roses) - 1;
    assert_int_equal(     0, (int)strrnstr(roses, "s",    0));
    assert_int_not_equal( 0, (int)strrnstr(roses, "s",    3));
    assert_int_equal(     0, (int)strrnstr(roses, "x",    3));
    assert_int_equal(     0, (int)strrnstr(roses, "o",    3));
    assert_int_not_equal( 0, (int)strrnstr(roses, "e",    3));
    assert_int_equal(     0, (int)strrnstr(roses, "x",    5));
    assert_int_equal(     0, (int)strrnstr(roses, "ross", 5));
    assert_int_equal(     0, (int)strrnstr(roses, "sess", 5));
    assert_int_not_equal( 0, (int)strrnstr(roses, "ose",  5));
    assert_int_not_equal( 0, (int)strrnstr(roses, "oses", 5));
}


static void
test_strrncasestr(state)
    void ** state;
{
    const char * roses;

    roses = "roses";
    roses += strlen(roses) - 1;
    assert_int_equal(     0, (int)strrncasestr(roses, "s",    0));
    assert_int_not_equal( 0, (int)strrncasestr(roses, "s",    3));
    assert_int_not_equal( 0, (int)strrncasestr(roses, "S",    3));
    assert_int_equal(     0, (int)strrncasestr(roses, "x",    3));
    assert_int_equal(     0, (int)strrncasestr(roses, "o",    3));
    assert_int_not_equal( 0, (int)strrncasestr(roses, "e",    3));
    assert_int_not_equal( 0, (int)strrncasestr(roses, "E",    3));
    assert_int_equal(     0, (int)strrncasestr(roses, "x",    5));
    assert_int_equal(     0, (int)strrncasestr(roses, "ross", 5));
    assert_int_equal(     0, (int)strrncasestr(roses, "sess", 5));
    assert_int_not_equal( 0, (int)strrncasestr(roses, "ose",  5));
    assert_int_not_equal( 0, (int)strrncasestr(roses, "oSe",  5));
    assert_int_not_equal( 0, (int)strrncasestr(roses, "OSE",  5));
    assert_int_not_equal( 0, (int)strrncasestr(roses, "oses", 5));
}


static void
test_strcasechr(state)
    void ** state;
{
    assert_int_equal(     0, (int)strcasechr("roses",   'x'));
    assert_int_equal(     0, (int)strcasechr("lillies", 'o'));
    assert_int_not_equal( 0, (int)strcasechr("Daisies", 'd'));
    assert_int_not_equal( 0, (int)strcasechr("Daisies", 'D'));
    assert_int_not_equal( 0, (int)strcasechr("daisies", 'd'));
    assert_int_not_equal( 0, (int)strcasechr("daisies", 'D'));
}


int
main() {
    const UnitTest tests[] = {
        unit_test( test_strcasechr   ),
        unit_test( test_strnstr      ),
        unit_test( test_strncasestr  ),
        unit_test( test_strrnstr     ),
        unit_test( test_strrncasestr ),
    };
    return run_tests(tests);
}

