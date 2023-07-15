

#ifndef HELPERS_H
#define HELPERS_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "globals.h"


/*Macro definitions*/
/*
 * Returns true if the character is EOF, newline, or null character.
 *
 * @param chr: The character to check.
 * @return true if the character is EOF, newline, or null character, false otherwise.
 */
#define IS_END(chr) (chr == '\n' || chr == EOF || chr == '\0')

/*
 * Allocates memory using malloc.
 *
 * @param pointer: The pointer variable to assign the allocated memory.
 * @param type: The type of the allocated memory.
 * @param size: The number of elements of the specified type to allocate.
 */
#define BLOCK_ALLOCATION(pointer, type ,size)  pointer = (type*) malloc(sizeof(type)*(size))

/*
 * Checks if a pointer is NULL, and performs the provided actions if it is.
 *
 * @param ptr: The pointer to check.
 * @param message: The error message to display if the pointer is NULL.
 * @param action: The action to perform if the pointer is NULL.
 */
#define CHECK_NULL(ptr,  action) \
  if ((ptr)==NULL) { \
                action                         \
  }

/*
 * Makes the index point to the first non-white character in the string.
 *
 * @param string: The input string.
 * @param index: The index variable to update.
 */
#define CLEAR_SPACES(string, index) \
        while ((string)[(index)] && (isspace((string)[index]))){\
         (++(index));               \
         }

/*
 * Removes the newline character from a string.
 *
 * @param str: The input string.
 */
#define REMOVE_NEWLINE(str) (str)[strcspn((str), "\n")] = '\0';

/*
 * Extracts the first word of a line using strtok.
 *
 * @param line The input line from which to extract the first word.
 *
 * @return A pointer to the first word of the line, or NULL if no word is found.
 *
 * @note The input line is modified by strtok, replacing the delimiter with a null character.
 *       If you need to preserve the original line, make a copy of it before using this macro.
 */
#define FIRST_WORD_OF(line) strtok_r((line)," ",&)

/*function declarations*/
/*
 * Splits a string into individual words based on specified delimiters.
 *
 * @param line: The input string to be split into words.
 * @param delimiters: The delimiters used to separate words in the input string.
 * @param wordCount: A pointer to an integer that will store the count of words found in the input string.
 *
 * @returns: On success, a dynamically allocated array of strings representing the individual words.
 *           On failure returns NULL.
 *
 * Memory Management: The returned array of strings and the memory allocated for each individual word
 * should be freed by the caller using free_string_array when they are no longer needed.
 */string * split_to_words(string line, const string separtor , int *wordCount );



/*
* Frees an array of strings.
*
* @param string_array: The array of strings to be freed.
* @param count: The number of words in the array.
*/
void free_string_array(string *string_array, int count);

/*
 * Removes leading and trailing whitespace characters from the given string.
 *
 * @param str The string to trim (will be modified in place).
 */
void trim(string str);

bool is_keyword(string word);
#endif
