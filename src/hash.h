#ifndef MAP_H
#define MAP_H

#include <stdio.h>

#ifdef Hash
#define MapError HashError

#define Map Hash
#define map_init hash_init
#define map_opt hash_opt
#define map_store hash_store
#define map_load hash_load
#define map_access hash_access
#define map_deinit hash_deinit
#endif

#define HASH_CAPACITY 2048

typedef struct HashNode HashNode;
typedef struct Hash Hash;

struct Hash {
  HashNode *nodes[HASH_CAPACITY]; 
};

typedef enum {
  HASH_OK = 0,
} HashError;

// preparation fns
Hash hash_init(char **words, int *shuffle);
HashError hash_opt(Hash *hash);
HashError hash_store(Hash *const hash, FILE *stream);

// runtime fns
Hash hash_load(FILE *stream);
char const *hash_access(Hash *const hash, char *const input);

// shared
void hash_deinit(Hash *const hash);

#endif
