#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <google/cmockery.h>
#include <stdio.h>
#include "string_functions.h"


void test_strnstr(void ** state) {
    assert_int_equal(     0, (int)strnstr("roses", "r",    0));
    assert_int_not_equal( 0, (int)strnstr("roses", "r",    3));
    assert_int_equal(     0, (int)strnstr("roses", "x",    3));
    assert_int_equal(     0, (int)strnstr("roses", "e",    3));
    assert_int_not_equal( 0, (int)strnstr("roses", "s",    3));
    assert_int_equal(     0, (int)strnstr("roses", "x",    9));
    assert_int_equal(     0, (int)strnstr("roses", "ross", 9));
    assert_int_equal(     0, (int)strnstr("roses", "sess", 9));
    assert_int_not_equal( 0, (int)strnstr("roses", "ose",  9));
    assert_int_not_equal( 0, (int)strnstr("roses", "ro",   9));
    assert_int_not_equal( 0, (int)strnstr("roses", "es",   9));
}


void test_strncasestr(void ** state) {
    assert_int_equal(     0, (int)strncasestr("roses", "r",    0));
    assert_int_not_equal( 0, (int)strncasestr("roses", "r",    3));
    assert_int_not_equal( 0, (int)strncasestr("roses", "R",    3));
    assert_int_equal(     0, (int)strncasestr("roses", "x",    3));
    assert_int_equal(     0, (int)strncasestr("roses", "e",    3));
    assert_int_not_equal( 0, (int)strncasestr("roses", "s",    3));
    assert_int_not_equal( 0, (int)strncasestr("roses", "S",    3));
    assert_int_equal(     0, (int)strncasestr("roses", "x",    9));
    assert_int_equal(     0, (int)strncasestr("roses", "ross", 9));
    assert_int_equal(     0, (int)strncasestr("roses", "sess", 9));
    assert_int_not_equal( 0, (int)strncasestr("roses", "ose",  9));
    assert_int_not_equal( 0, (int)strncasestr("roses", "oSe",  9));
    assert_int_not_equal( 0, (int)strncasestr("roses", "OSE",  9));
    assert_int_not_equal( 0, (int)strncasestr("roses", "ro",   9));
    assert_int_not_equal( 0, (int)strncasestr("roses", "es",   9));
}


void test_strrnstr(void ** state) {
    const char * roses;

    roses = "roses";
    roses += strlen(roses) - 1;
    assert_int_equal(     0, (int)strrnstr(roses, "s",    0));
    assert_int_not_equal( 0, (int)strrnstr(roses, "s",    3));
    assert_int_equal(     0, (int)strrnstr(roses, "x",    3));
    assert_int_equal(     0, (int)strrnstr(roses, "o",    3));
    assert_int_not_equal( 0, (int)strrnstr(roses, "e",    3));
    assert_int_equal(     0, (int)strrnstr(roses, "x",    9));
    assert_int_equal(     0, (int)strrnstr(roses, "ross", 9));
    assert_int_equal(     0, (int)strrnstr(roses, "sess", 9));
    assert_int_not_equal( 0, (int)strrnstr(roses, "ose",  9));
    assert_int_not_equal( 0, (int)strrnstr(roses, "oses", 9));
}


void test_strrncasestr(void ** state) {
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
    assert_int_equal(     0, (int)strrncasestr(roses, "x",    9));
    assert_int_equal(     0, (int)strrncasestr(roses, "ross", 9));
    assert_int_equal(     0, (int)strrncasestr(roses, "sess", 9));
    assert_int_not_equal( 0, (int)strrncasestr(roses, "ose",  9));
    assert_int_not_equal( 0, (int)strrncasestr(roses, "oSe",  9));
    assert_int_not_equal( 0, (int)strrncasestr(roses, "OSE",  9));
    assert_int_not_equal( 0, (int)strrncasestr(roses, "oses", 9));
}


void test_strcasechr(void ** state) {
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
        // string_functions
        unit_test( test_strcasechr   ),
        unit_test( test_strnstr      ),
        unit_test( test_strncasestr  ),
        unit_test( test_strrnstr     ),
        unit_test( test_strrncasestr )
    };
    return run_tests(tests);
}

