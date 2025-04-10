#include "stdio.h"
#include "map.h"
#include "structure.h"
#include "statemachine.h"

const char *const INPUT_PATH = "dat/google-10000-english-usa.txt";
const char *const OUTPUT_PATH = "out/file.map";

int main(void) {
    // read input data
    int word_cap = 1, word_len = 0;

    char **words;
    int *shuffle;

    FILE *input_file = fopen(INPUT_PATH, "r");
    if (!input_file)
        return 1;

    fclose(input_file);

    // generate the shuffle
    // 1. range 
    // 2. shuffle

    // create a map
    Map map = map_init(words, shuffle);

    map_opt(map);
    
    FILE *output_file = fopen(OUTPUT_PATH, "w");
    if (!output_file)
        return 1;

    // stores the map
    map_store(map, output_file);

    return 0;
}
