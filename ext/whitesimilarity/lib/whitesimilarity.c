#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "whitesimilarity.h"

#define _empty_char(c) (c == ' ')
#define _null_char(c) (c == '\0')
#define will_make_bad_pair(str, i) \
  (_empty_char(*(str + i)) || _empty_char(*(str + i + 1)) || _null_char(*(str + i + 1)))

#define pairs_equal(a, b) (strcmp(a, b) == 0)

// Pairs struct
typedef struct {
  char **array;
  int count;
} t_pairs;

// Free up a pair
void destroy_pair(char *pair) {
  if (pair != NULL) {
    free(pair);
  }
}

// Remove a pair struct from a pairs struct at the index p
void remove_pair_at(t_pairs *pairs, int p) {
  int i = 0;

  // Free up the pair
  destroy_pair(pairs->array[p]);
  pairs->array[p] = NULL;

  // Decrease the pair count
  pairs->count--;

  // Reassign positions of other pairs in struct
  for (i = p; i < pairs->count; i++) {
    pairs->array[i] = pairs->array[i + 1];
  }
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
  char *pair     = NULL;

  pairs->count = num_pairs;
  pairs->array = calloc(num_pairs, sizeof(char *));

  for (i = 0; i < l; i++) {
    if (will_make_bad_pair(str, i)) {
      continue;
    }

    // Create and add pair
    pair = calloc(3, sizeof(char));
    strncpy(pair, str + i, 2);
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
      if (pairs_equal(pairs1->array[i], pairs2->array[j])) {
        intersection++;
        remove_pair_at(pairs2, j);
        break;
      }
    }
  }

  destroy_letter_pairs(pairs1);
  destroy_letter_pairs(pairs2);

  return (2.0 * intersection) / sum;
}

int main(int argc, char *argv[]) {
  double d;
  
  if (argc < 3) {
    printf("Please supply two strings to compare.\n");
    return 1;
  }

  d = white_similarity(argv[1], argv[2]);
  printf("white similarity for '%s' and '%s' is %f\n", argv[1], argv[2], d);

  return 0;
}
