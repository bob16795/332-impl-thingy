#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>

#define MAP_SIZE 2048

typedef struct DataMap DataMap;
typedef struct Word Word;
typedef struct Range Range;

struct DataMap {
   Word* words;
   Range ranges[256]; 

   int uniqueChars;
   int wordCount;
   int charCount;
};

struct Word {
    char** word;
    int value;
    Word* nextWord;
    //Store the range that can encode the word
    float low;
    float high;
};

struct Range {
    float prob;
    float low;
    float high;
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
