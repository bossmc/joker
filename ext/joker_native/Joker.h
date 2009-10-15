#ifndef JOKER_H_GUARD
#define JOKER_H_GUARD

#include "ruby.h"


VALUE class_Wildcard;
void Init_joker(void);


/*
 * This function will become the Wildcard::new method.
 *
 */
VALUE class_method_new(int argc, VALUE * argv, VALUE klass);


/*
 * This function will become the =~ and === methods.
 *
 */
VALUE instance_operator_match(VALUE self, VALUE string);


#endif

