#include <malloc.h>
#include "Joker.h"
#include "Wildcard.h"
#include "compile.h"
#include "match.h"


void
Init_joker(void)  // {{{1
{
    class_Wildcard = rb_define_class("Wildcard", rb_cObject);
    rb_define_singleton_method(class_Wildcard, "new", class_method_new, -2);
    rb_define_method(class_Wildcard, "=~",  instance_operator_match, 1);
    rb_define_method(class_Wildcard, "===", instance_operator_case, 1);
}


/*
 * call-seq:
 *   wildcard =~ 'string' -> true or false
 *   'string' =~ wildcard -> true or false
 *
 * Matches the Wildcard against the given string.
 *
 * NOTE: Since a wildcard has to match the whole string,
 * this method only returns true or false, not the position
 * of the match.
 *
 *   Wildcard['*fairy*'] =~ 'I love fairycake'   #=> true
 *   'I love fairycake' =~ Wildcard['*dairy*']   #=> false
 *
 */
VALUE
instance_operator_match(self, string)  // {{{1
    VALUE  self;
    VALUE  string;
{
    Wildcard *    wildcard;
    const char *  cstring;
    long int      length;
    int           casefold;

    Data_Get_Struct(self, Wildcard, wildcard);
    cstring   = rb_str2cstr(string, &length);
    casefold  = RTEST(rb_iv_get(self, "@casefold"));

    if (Wildcard_match(wildcard, cstring, length, casefold)) {
        return Qtrue;
    } else {
        return Qfalse;
    }
}


/*
 * call-seq:
 *   wildcard === 'string' -> true or false
 *
 * The case operator. Allows you to use Wildcards in case
 * expressions:
 *
 *   case 'I love fairycake'
 *   when Wildcard['*fairy*'] then puts 'fairy!'
 *   else puts 'no fairy...'
 *   end
 *
 */
VALUE
instance_operator_case(self, object)  // {{{1
    VALUE  self;
    VALUE  object;
{
    Wildcard *    wildcard;
    const char *  cstring;
    long int      length;
    int           casefold;

    Check_Type(object, T_STRING);
    Data_Get_Struct(self, Wildcard, wildcard);
    cstring  = rb_str2cstr(object, &length);
    casefold  = RTEST(rb_iv_get(self, "@casefold"));

    if (Wildcard_match(wildcard, cstring, length, casefold)) {
        return Qtrue;
    } else {
        return Qfalse;
    }
}


/*
 * call-seq:
 *   Wildcard.new(wildcard_string, casefold = false) -> Wildcard
 *
 * Creates a new Wildcard from the given string.
 * If casefold is true, the Wildcard will ignore case.
 *
 * Raisess a SyntaxError if the given string could not
 * be interpreted as a Wildcard.
 *
 * Issues warnings to the console if the given Wildcard
 * was malformed.
 *
 * TODO: Wildcard.warn = false
 *
 */
VALUE
class_method_new(argc, argv, klass)  // {{{1
    int      argc;
    VALUE *  argv;
    VALUE    klass;
{
    VALUE         wildcard_string;
    VALUE         casefold;
    VALUE         new_object;
    Wildcard *    new_wildcard;
    const char *  wildcard_cstring;
    long int      string_length;

    rb_scan_args(argc, argv, "11", &wildcard_string, &casefold);
    if (NIL_P(casefold)) {
        casefold = Qfalse;
    }

    wildcard_cstring = rb_str2cstr(wildcard_string, &string_length);
    new_wildcard     = Wildcard_init();
    Wildcard_compile(wildcard_cstring, string_length, new_wildcard);
    new_object       = Data_Wrap_Struct(klass, 0, Wildcard_free, new_wildcard); 

    rb_iv_set(new_object, "@casefold", casefold);

    return new_object;
}

