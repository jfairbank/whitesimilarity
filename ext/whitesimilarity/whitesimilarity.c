#include "ruby.h"
#include "white_similarity.h"

// Ruby stuff
// ----------

// Contracts
VALUE WhiteSimilarity = Qnil;
void Init_whitesimilarity();
VALUE method_white_similarity(VALUE self, VALUE str1, VALUE str2);

// Defs
void Init_whitesimilarity() {
  WhiteSimilarity = rb_define_module("WhiteSimilarity");
  rb_define_singleton_method(WhiteSimilarity, "similarity", method_white_similarity, 2);

  rb_require("whitesimilarity/version");
}

VALUE method_white_similarity(VALUE self, VALUE rstr1, VALUE rstr2) {
  char *str1;
  char *str2;
  double d;

  str1 = StringValueCStr(rstr1);
  str2 = StringValueCStr(rstr2);

  d = white_similarity(str1, str2);
  return rb_float_new(d);
}
