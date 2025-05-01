#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>

#ifdef Data
#define MapError DataError

#define Map DataMap

#define map_init data_init
#define map_opt data_opt
#define map_store data_store
#define map_load data_load
#define map_access data_access
#define map_deinit data_deinit
#endif

#define MAP_SIZE 2048

typedef struct DataMap DataMap;
typedef struct Word Word;
typedef struct Range Range;

struct Range {
    float prob;
    float low;
    float high;
};

struct Word {
    char** word;
    int value;
    char** outputWord; 
    Word* nextWord;
    //Store the range that can encode the word
    float low;
    float high;
};

struct DataMap {
   Word* words;
   Range ranges[256]; 

   int uniqueChars;
   int wordCount;
   int charCount;
};


typedef enum {
  DATA_OK = 0,
  DATA_ERR_ZEROCHARS,
} DataError;

// preparation fns
DataMap data_init(char **words, int *shuffle);
DataError data_opt(DataMap *map);
DataError data_store(DataMap *const map, FILE *stream);

// runtime fns
DataMap data_load(FILE *stream);
char const *data_access(DataMap *const map, char *const input);

// shared
void data_deinit(DataMap *const map);

#endif
