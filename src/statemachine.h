#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#ifdef Code
#define MapError CodeError

#define Map CodeMap

#define map_init code_init
#define map_opt code_opt
#define map_store code_store
#define map_load code_load
#define map_access code_access
#define map_deinit code_deinit
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct CodeMap CodeMap;
typedef struct CodeInst CodeInst;

enum CodeInstKind {
    INST_CHOICE,
    INST_DATA,
};

struct CodeInst {
    char kind;
    union {
        struct {
            int options;
            int offset;
        };
        char **data;
    } data;
};

struct CodeMap {
    CodeInst *tape;
    int tape_count;
};

typedef enum {
  CODE_OK = 0,
} CodeError;

// preparation fns
CodeMap code_init(char **words, int *shuffle);
CodeError code_opt(CodeMap *map);
CodeError code_store(CodeMap *const map, FILE *stream);

// runtime fns
CodeMap code_load(FILE *stream);
char const *code_access(CodeMap *const map, char *const input);

// shared
void code_deinit(CodeMap *const map);

#endif
