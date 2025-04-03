#include "stdio.h"
#include "map.h"
#include "structure.h"
#include "statemachine.h"

const char *const INPUT_PATH = "dat/google-10000-english-usa.txt";

int main(void) {
    // read input data
    int word_cap = 1, word_len = 0;

    char **words;
    int *shuffle;

    FILE *input_file = fopen(INPUT_PATH, "r");
    if (!input_file)
        return 1;

    char *read;
    while ((read = getline(words[word_en ++], )))

    fclose(input_file);

    // create a map
    Map map = map_init(words, shuffle);
    return 0;
}
