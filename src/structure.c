#include "structure.h"


DataMap data_init(char **words, int *shuffle) {
    DataMap map = {0};
    int* value = shuffle;
    Word* head = NULL;

    //Construct linked list
    for (char** word = words; *word; word = word + 1, value = value + 1) {
        Word* current = malloc(sizeof(Word));
        current->word = word; 
        current->value = *value;
        current->nextWord = head; 

        head = current;

        map.wordCount++;
    }
        
    map.words = head;

    return map;
}

DataError data_opt(DataMap *map) {
    for (Word* word = map->words; word; word = word->nextWord) {
        for (char* ch = *word->word; *ch; ++ch) {
            map->ranges[(int) (*ch)].prob++;
            map->charCount++;
        }
    }

    for (int i = 0; i < 256; i++) {
        if (map->ranges[i].prob != 0) map->uniqueChars++;
    }

    if (map->uniqueChars == 0) {
        return DATA_ERR_ZEROCHARS;
    }

    for (int i = 0; i < 256; i++) {
        map->ranges[i].prob /= map->charCount;
        printf("%c %f\n", i, map->ranges[i].prob);
    } 

    //Begin character assignment to interval of [0, wordCount)
    float lowInterval = 0;

    //Many will be 0
    for (int i = 0; i < 256; i++) {
        //ignore empty values they don't have a character
        if (map->ranges[i].prob == 0) continue;
        
        //set the ranges
        map->ranges[i].low = lowInterval;
        map->ranges[i].high = lowInterval + map->ranges[i].prob;

        //reset the lowest available interval value
        lowInterval = lowInterval + map->ranges[i].prob;
    }

    //Encode each word to a unique value for sub cipher
    for (Word* word = map->words; word; word = word->nextWord) {
        //Set the max range of the word
        Range wordRange = {
            .low = 0, 
            .high = 1
        }; 
    
        for (char* ch = *word->word; *ch; ++ch) {
            int currentRange = wordRange.high - wordRange.low;
            Range chRange = map->ranges[(int) (*ch)];
    
            //Shrink the range
            wordRange.high = wordRange.low + (currentRange * chRange.high);
            wordRange.low = wordRange.low + (currentRange * chRange.low); 
        }

        word->low = wordRange.low;
        word->high = wordRange.high;

        //Dummy printout for testing
        printf("%s || [%f, %f)\n", *word->word, word->low, word->high);
        
    }

    return DATA_OK;
}

DataError data_store(DataMap *const map, FILE *stream) {

}

// runtime fns
DataMap data_load(FILE *stream) {

}

char const *data_access(DataMap *const map, char *const input) {

}

// shared
void data_deinit(DataMap *const map) {
    
}


