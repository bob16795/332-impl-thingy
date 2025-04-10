#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "map.h"
#include "structure.h"
#include "statemachine.h"

//Fisher-Yates shuffle algorithm
void shuffle(int *array, int size) {
    srand(time(NULL));  //seed the random number generator
    
    for (int i = size - 1; i > 0; i--) {
        //generate a random index between 0 and i (inclusive)
        int j = rand() % (i + 1);
        
        //swap array[i] and array[j]
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

const char *const INPUT_PATH = "dat/google-10000-english-usa.txt";
const char *const OUTPUT_PATH = "out/file.map";

int main(void) {
    //read input data
    FILE *input_file = fopen(INPUT_PATH, "r");
    if (!input_file)
        return 1;
        
    char** language = malloc(0 * sizeof(char*));
    int* range = malloc(0 * sizeof(int));
    int wordCounter = 0;
    char word[128] = {0};  // BUG: possible buffer overflow
    int letterCounter = 0;
    
    //Reading file character by character
    char ch;
    while ((ch = fgetc(input_file)) != EOF) {
        if (ch != '\n') {
            word[letterCounter] = ch;
            letterCounter++;
            continue;
        }
        
        //Clean up, add terminating char
        word[letterCounter] = '\0'; 
        
        // Store the word in the heap, get a pointer to that word
        char *heap_word = malloc(letterCounter + 1); 
        memcpy(heap_word, word, letterCounter + 1); 
        
        // Allocate
        wordCounter++;
        language = realloc(language, sizeof(char*) * wordCounter);  
        range = realloc(range, wordCounter * sizeof(int));  
        
        // Assign the word to the language
        language[wordCounter - 1] = heap_word; 
        range[wordCounter - 1] = wordCounter - 1;
        letterCounter = 0;
    }
    
    //Allocate a null to the language so that we don't have to store wordCounter
    language = realloc(language, sizeof(char*) * (wordCounter + 1)); 
    language[wordCounter] = NULL;
    
    //Close
    fclose(input_file);
    
    //Just shuffle the range array, keeping the language array in original order
    shuffle(range, wordCounter);
    
    //For demonstration, let's print a few words and their shuffled indices
    printf("First 5 words with their shuffled indices:\n");
    for (int i = 0; i < 5 && i < wordCounter; i++) {
        printf("Word: %s, Shuffled Index: %d\n", language[i], range[i]);
    }
    
    //create a map with the original language array and shuffled range
    Map map = map_init(language, range);
    
    //Dealloc
    free(range);
    for (int i = 0; i < wordCounter; i++) {
        free(language[i]);
    }
    free(language);
    
    return 0;
}