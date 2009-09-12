#include "Joker.h"
#include "compile.h"
#include "stdlib.h"


static void
Wildcard_free(p)
    void *  p;
{
    Wildcard *  wildcard;

    wildcard = p;
    // TODO dispose of parts
    free(wildcard);
}


void
Init_joker(void)
{
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
instance_operator_match(self, string)
    VALUE  self;
    VALUE  string;
{
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
instance_operator_case(self, object)
    VALUE  self;
    VALUE  object;
{
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
class_method_new(argc, argv, klass)
    int      argc;
    VALUE *  argv;
    VALUE    klass;
{
    VALUE         wildcard_string;
    VALUE         casefold;
    VALUE         new_object;
    Wildcard *    new_wildcard;
    const char *  wildcard_cstring;
    long int      wildcard_len;

    rb_scan_args(argc, argv, "11", &wildcard_string, &casefold);
    if (NIL_P(casefold)) {
        casefold = Qfalse;
    }

    wildcard_cstring = rb_str2cstr(wildcard_string, &wildcard_len);
    new_wildcard     = malloc(sizeof(Wildcard));
    Wildcard_compile(wildcard_cstring, wildcard_len, new_wildcard);
    new_object       = Data_Wrap_Struct(klass, 0, Wildcard_free, new_wildcard); 

    return new_object;
}

