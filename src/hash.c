#include "hash.h"

struct HashNode {
  HashNode *next;
  char *data;
};

Hash hash_init(char **words, int *shuffle) {
    Hash result = {0};

    return result;
}

// there are no possible optimizations
HashError hash_opt(Hash *hash) {}

HashError hash_store(Hash *const hash, FILE *stream) {
    
}

