#ifndef MAP_H
#define MAP_H

#include <stdio.h>

typedef struct {

} Map;

typedef enum {
  MAP_OK = 0,
} MapError;

// preparation fns
Map map_init(char **words, int *shuffle);
MapError map_opt(Map *map);
MapError map_store(Map *const map, FILE *stream);

// runtime fns
Map map_load(FILE *stream);
char const *map_access(Map *const map, char *const input);

// shared
void map_deinit(Map *const map);

#endif
