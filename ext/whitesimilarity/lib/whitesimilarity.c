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

// Free up a pair
void destroy_pair(char *pair) {
  if (pair != NULL) {
    free(pair);
  }
}

// Remove a pair struct from a pairs struct at the index p
void remove_pair_at(int num_pairs, char **pairs, int p) {
  int i = 0;

  // Free up the pair
  destroy_pair(pairs[p]);
  pairs[p] = NULL;

  // Reassign positions of other pairs
  for (i = p; i < num_pairs; i++) {
    pairs[i] = pairs[i + 1];
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
char **letter_pairs(int num_pairs, char *str) {
  int i        = 0;
  int l        = strlen(str);
  int counter  = 0;
  char **pairs = calloc(num_pairs, sizeof(char *));
  char *pair   = NULL;

  for (i = 0; i < l; i++) {
    if (will_make_bad_pair(str, i)) {
      continue;
    }

    // Create and add pair
    pair = calloc(3, sizeof(char));
    strncpy(pair, str + i, 2);
    pairs[counter] = pair;

    // Increment the counter for adding the pair to the pairs struct
    counter++;
  }

  return pairs;
}

void destroy_letter_pairs(int num_pairs, char **pairs) {
  int i = 0;

  // Free each pair
  for (i = 0; i < num_pairs; i++) {
    destroy_pair(pairs[i]);
  }

  // Free the array
  free(pairs);
}

double white_similarity(char *str1, char *str2) {
  int num_pairs1 = get_num_pairs(str1);
  int num_pairs2 = get_num_pairs(str2);

  char **pairs1 = letter_pairs(num_pairs1, str1);
  char **pairs2 = letter_pairs(num_pairs2, str2);

  int i            = 0;
  int j            = 0;
  int intersection = 0;
  int sum          = num_pairs1 + num_pairs2;

  for (i = 0; i < num_pairs1; i++) {
    for (j = 0; j < num_pairs2; j++) {
      if (pairs_equal(pairs1[i], pairs2[j])) {
        intersection++;

        // Removing pair, so make sure to decrement `num_pairs2`
        num_pairs2--;
        remove_pair_at(num_pairs2, pairs2, j);
        break;
      }
    }
  }

  destroy_letter_pairs(num_pairs1, pairs1);
  destroy_letter_pairs(num_pairs2, pairs2);

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
