
#ifndef PREPROCESSOR_H

#define PREPROCESSOR_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "helpers.h"
/*macro definitions*/
#define MACRO_START "mcro"
#define MACRO_END "endmcro"
#define MAX_MACRO_NAME_SIZE 30
#define COMMENT_CHAR ';'



/*
 * Generates an .am file containing the code after macro expansion and comment removal.
 *
 * @param sourceName: The name of the source file to be preprocessed.
 *
 * @return A pointer to the output file on success. Returns NULL if any error occurs.
 *
 * Memory Management: The caller is responsible for closing and freeing the returned file pointer.
 */
string pre_proccess(string sourceName);
#endif
