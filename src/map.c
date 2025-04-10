#include "map.h"

struct MapNode {
  MapNode *next;
  char *data;
};

Map map_init(char **words, int *shuffle) {
    Map result = {0};

    return result;
}

// there are no possible optimizations
MapError map_opt(Map *map) {}

MapError map_store(Map *const map, FILE *stream) {
    
}

