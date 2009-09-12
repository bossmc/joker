#include "ruby.h"

VALUE class_Wildcard = Qnil;
void Init_joker(void);

VALUE class_method_new(int argc, VALUE * argv, VALUE klass);

VALUE instance_operator_match(VALUE self, VALUE string);
VALUE instance_operator_case(VALUE self, VALUE object);

