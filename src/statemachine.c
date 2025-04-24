#include "statemachine.h"

typedef struct GenNode {
    struct GenNode *children[256]; 
    
    char **word;
    char **output;
} GenNode;

void node_deinit(GenNode *root) {
    for (int i = 0; i < 256; i++)
        if (root->children[i]) {
            node_deinit(root->children[i]);
            free(root->children[i]);
        }
}

void print_node(GenNode *root) {
    if (root->output)
        printf("%s %s\n", *root->word, *root->output);

    for (int i = 0; i < 256; i++)
        if (root->children[i])
            print_node(root->children[i]);
}

CodeError add_node(GenNode *root, char **word, int ofs, char **output) {
    char ch;

    if (!(ch = (*word)[ofs])) {
        root->output = output;
        root->word = word;
        return CODE_OK;
    }

    if (root->children[ch] == NULL) {
        root->children[ch] = calloc(sizeof(GenNode), 1);
    }

    return add_node(root->children[ch], word, ofs + 1, output);
}

CodeMap code_init(char **words, int *shuffle) {
    GenNode root = {0}; 

    int *index = shuffle;
    for (char **word = words; *word; word++, index++) {
        char **output = &words[*index];

        add_node(&root, word, 0, output);
    }

    print_node(&root);

    node_deinit(&root);
}

CodeError code_opt(CodeMap *map) {}
CodeError code_store(CodeMap *const map, FILE *stream) {}

// runtime fns
CodeMap code_load(FILE *stream) {}
char const *code_access(CodeMap *const map, char *const input) {}

// shared
void code_deinit(CodeMap *const map) {}
