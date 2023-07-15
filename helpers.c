#include "helpers.h"

string *split_to_words(string line, string separator, int *wordCount) {
    int length = strlen(line);
    int wordCapacity = 3; /*holds the maximum amount of words, used to extend the size*/
    string *words;
    string temp;
    string token;
    *wordCount = 0;
    BLOCK_ALLOCATION(words, string, 10);
    CHECK_NULL(words, PRINT_ALLOCATION_FAILED_MSG; return NULL;)
    BLOCK_ALLOCATION(temp, char, length + 1);
    CHECK_NULL(temp, PRINT_ALLOCATION_FAILED_MSG; free(words); return NULL;)
    strcpy(temp, line);
    REMOVE_NEWLINE(temp)
    token = strtok(temp, separator);
    /* walk through other tokens */
    while (token != NULL) {
        if (*wordCount == wordCapacity) {
            wordCapacity += 10;/*add 10 possible words */
            words = (string *) realloc(words, sizeof(string) * wordCapacity);
            CHECK_NULL(words, PRINT_ALLOCATION_FAILED_MSG; return NULL;)
        }
        words[*wordCount] = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(words[*wordCount], token);
        (*wordCount)++;
        token = strtok(NULL, separator);
    }
    free(temp);
    return words;

}


void free_string_array(string *string_array, int count) {
    int i;
    for (i = 0; i < count; i++) {
        free(string_array[i]);
    }
    free(string_array);
}


void trim(string str) {
    string start = str;
    string end;

    /*find the first non space character*/
    while (isspace(*start)) {
        ++start;
    }

    /*find the last non space character*/
    end = str + strlen(str) - 1;
    while (end > start && isspace(*end)) {
        --end;
    }

    /*Null-terminate the trimmed string*/
    *(end + 1) = '\0';

    /*Move the trimmed string to the beginning of the original string*/
    if (str != start) {
        memmove(str, start, end - start + 2);
    }
}

bool is_keyword(string word) {
    static const string keywords[] = {"@r0", "@r1", "@r2", "@r3", "@r4", "@r5", "@r6", "@r7",
                                      "mov", "cmp", "add", "sub", "not", "clr", "lea",
                                      "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop",".data",".string"};
    static const int keywordCount = 26;
    int i;
    for(i=0;i<keywordCount;i++){
        if(strcmp(word,keywords[i])==0){
            return true;
        }
    }
    return false;
}
