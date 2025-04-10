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

    char** language = malloc(0 * sizeof(char));
    int* range = malloc(0 * sizeof(int));
    int wordCounter = 0;

    char word[128] = {0}; //BUG: possible buffer overflow
    int letterCounter = 0;
    
    //Reading file character by character
    char ch;
    while ((ch = fgetc(input_file)) != EOF) {
        if (ch != '\n') {
            word[letterCounter] = ch;
            letterCounter++;
            continue;
        }
        // Clean up, add terminating char
        word[letterCounter] = '0';
        letterCounter++;

        // Store the word in the heap, get a pointer to that word
        char *heap_word = malloc(letterCounter);
        memcpy(heap_word, &word, letterCounter);

        // Allocate
        wordCounter++;
        language = relloc(language, sizeof(char *) * (wordCounter));
        range = relloc(range, (wordCounter) * sizeof(int));

        // Assign the word to the language
        language[wordCounter - 1] = word;
        range[wordCounter - 1] = wordCounter - 1;

        letterCounter = 0;
    }

    //Allocate a null to the the language so that we don't have to store wordCounter
    language = relloc(language, sizeof(char *) * (wordCounter + 1));
    language[wordCounter - 1] = NULL;

    //Close
    fclose(input_file);

    // create a map
    Map map = map_init(words, shuffle);
    
    //Dealloc
    free(range);
    for (int i = 0; i < wordCounter; i++) {
        free(language[i]);
    }
    free(language);
    return 0;
}
