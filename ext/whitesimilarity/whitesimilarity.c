#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ruby.h"

#define _empty_char(c) (c == ' ')
#define _null_char(c) (c == '\0')
#define will_make_bad_pair(str, i) \
  (_empty_char(*(str + i)) || _empty_char(*(str + i + 1)) || _null_char(*(str + i + 1)))

#define _pairs_equal(a, b) (strcmp(a->string, b->string) == 0)
#define _compare_pairs(a, b) (a->compare == 1 && b->compare == 1)
#define compare_pairs(a, b) (_compare_pairs(a, b) && _pairs_equal(a, b))

// Pair struct
typedef struct {
  char *string;
  int compare;
} t_pair;

// Pairs struct
typedef struct {
  t_pair **array;
  int count;
} t_pairs;

// Free up a pair
void destroy_pair(t_pair *pair) {
  free(pair->string);
  pair->string = NULL;
  free(pair);
}

// Get the total number of pairs in string
int get_num_pairs(char *str) {
  int i = 0;
  int num_pairs = 0;

  while (*(str + i) != '\0') {
    if (!will_make_bad_pair(str, i)) {
      num_pairs++;
    }

    i++;
  }

  return num_pairs;
}

// Create the pairs from the string
t_pairs *letter_pairs(char *str) {
  int i          = 0;
  int l          = strlen(str);
  int counter    = 0;
  int num_pairs  = get_num_pairs(str);
  t_pairs *pairs = malloc(sizeof(t_pairs));
  t_pair *pair   = NULL;

  pairs->count = num_pairs;
  pairs->array = calloc(num_pairs, sizeof(t_pair *));

  for (i = 0; i < l; i++) {
    if (will_make_bad_pair(str, i)) {
      continue;
    }

    // Create and add pair
    pair                  = malloc(sizeof(t_pair));
    pair->string          = calloc(3, sizeof(char));
    strncpy(pair->string, str + i, 2);
    pair->string[0]       = toupper(pair->string[0]);
    pair->string[1]       = toupper(pair->string[1]);
    pair->compare         = 1;
    pairs->array[counter] = pair;

    // Increment the counter for adding the pair to the pairs struct
    counter++;
  }

  return pairs;
}

void destroy_letter_pairs(t_pairs *pairs) {
  int i = 0;
  int num_pairs = pairs->count;

  // Free each pair
  for (i = 0; i < num_pairs; i++) {
    destroy_pair(pairs->array[i]);
  }

  // Free the pairs array
  free(pairs->array);

  // Free the pairs struct
  free(pairs);
}

double white_similarity(char *str1, char *str2) {
  t_pairs *pairs1 = letter_pairs(str1);
  t_pairs *pairs2 = letter_pairs(str2);

  int i = 0;
  int j = 0;
  int intersection = 0;
  int sum = pairs1->count + pairs2->count;

  for (i = 0; i < pairs1->count; i++) {
    for (j = 0; j < pairs2->count; j++) {
      if (compare_pairs(pairs1->array[i], pairs2->array[j])) {
        intersection++;

        // "remove" pair from pairs2
        pairs2->array[j]->compare = 0;
        break;
      }
    }
  }

  destroy_letter_pairs(pairs1);
  destroy_letter_pairs(pairs2);

  return (2.0 * intersection) / sum;
}

int main(void) { return 0; }

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
