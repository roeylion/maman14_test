#include "pre_processor.h"

/*
 * Finds a macro by name in the given macro list.
 *
 * @param name: The name of the macro to find.
 * @param macroList: An array of macro structures representing the macro list.
 *
 * @return The index of the macro in the list if found, or -1 if not found.
 */
int find_macro(string name, macro *macroList);



string pre_proccess(string sourceName) {
    /*declarations*/
    int i, wordCount = 0;
    string *wordsInLine;
    string destName, currentLine;
    int macroCount = 0, macroCapacity = 10, currentMacro;
    bool inMacro = false;
    FILE *source, *dest;

    /*memory allocations*/
    BLOCK_ALLOCATION(macro *macroList,macro,macroCapacity);
    CHECK_NULL(macroList, PRINT_ALLOCATION_FAILED_MSG; return NULL;)
    BLOCK_ALLOCATION( destName,char, strlen(sourceName)+4);
    CHECK_NULL(destName, PRINT_ALLOCATION_FAILED_MSG; free(macroList); return NULL;)
    BLOCK_ALLOCATION( currentLine, char , LINE_LENGTH);
    CHECK_NULL(currentLine, PRINT_ALLOCATION_FAILED_MSG; free(macroList); free(destName);  return NULL;)

    /*set the input and output files name*/
    strcpy(destName,sourceName);
    strcat(destName,".am");
    strcat(sourceName,".as");

    /*open the files*/
     source = fopen(sourceName, "r");
     CHECK_NULL(source, PRINT_FOPEN_FAILED_MSG(sourceName); free(macroList); free(destName); free(destName); return NULL;)
     dest = fopen(destName, "w");
    CHECK_NULL(dest, PRINT_FOPEN_FAILED_MSG(destName); free(macroList); free(destName); free(currentLine); fclose(source);  return NULL;)
    printf("after declarations\n");
    macroList[0].name = NULL;
    printf("macro start: %s , macro end: %s",MACRO_START,MACRO_END);

    /*go over the file line by line*/
    while (fgets(currentLine,LINE_LENGTH,source)!=NULL){
        int start = 0,i; /*the first non blank char of the line*/
        if (currentLine[strlen(currentLine) - 1] != '\n') {
            fprintf(stderr,"Line exceeded maximum length: %s\n", currentLine);
            remove(destName);
            return NULL;
        }
        CLEAR_SPACES(currentLine, start)
        printf("\n%s", (currentLine + start));
        if (*(currentLine + start) != COMMENT_CHAR && !IS_END(*(currentLine+start))) {/*check for comment or empty line*/
           wordsInLine = split_to_words((currentLine+start)," ",&wordCount);
            /*printf("first 2 words in splitted line:-%s-%s\n",wordsInLine[0],wordsInLine[1]);*/

            /*make sure each word is free of whitespaces*/
            for ( i = 0; i <wordCount ; ++i) {
                trim(wordsInLine[i]);
            }

           /*if a real macro found*/
              if ((currentMacro = find_macro(wordsInLine[0], macroList)) != -1) {
            printf("-found macro\n");
            printf("-printing to file: %s",macroList[currentMacro].content);
            fprintf(dest,"%s",macroList[currentMacro].content);/*place macro content*/

        }
              /*reading a macro*/
              else if (inMacro) {
            printf("-in macro\n");
            printf("%s\n",wordsInLine[0]);
            /*check if endmcro reached*/
            if (strcmp(wordsInLine[0], MACRO_END)==0) {
                inMacro = false;
                printf("-macro end. name:%s content:\n%s",(*(macroList + macroCount)).name,(*(macroList + macroCount)).content);
                macroCount++;
                continue;
            } else {
                /*add the line the content of the macro*/
                strcat((*(macroList + macroCount)).content, (currentLine + start));

                printf( "-new macro line.\nname:%s, content:\n%s\n", (*(macroList + macroCount)).name,(*(macroList + macroCount)).content); /*remove later*/
            }
        } else

            /*start of macro definition */
        if (strcmp(wordsInLine[0], MACRO_START)==0) {
            inMacro = true;
            if (macroCount == macroCapacity - 1) { /*resize the macro list*/
                macroCapacity += 5;
                macroList = (macro *) realloc(macroList, sizeof(macro) * macroCapacity);
                CHECK_NULL(macroList, PRINT_ALLOCATION_FAILED_MSG; free(destName); fclose(source); fclose(dest); return NULL;)
            }
            /*only mcro without a macro name*/
            if (wordCount < 2) {
                fprintf(stderr, "-no macro name \n");
            }
            /*allocate memory for the name*/
            BLOCK_ALLOCATION((*(macroList + macroCount)).name, char, MAX_MACRO_NAME_SIZE);
            CHECK_NULL((*(macroList + macroCount)).name, PRINT_ALLOCATION_FAILED_MSG;
                       free(macroList); free(destName); fclose(source); fclose(dest); return NULL;)
            /*add the macro name to the list*/
            strcpy((*(macroList + macroCount)).name, wordsInLine[1]);
            printf("-new macro name: %s\n", (*(macroList + macroCount)).name);
            /*allocate memory and initialize the content*/
            BLOCK_ALLOCATION((*(macroList + macroCount)).content, char, LINE_LENGTH * 3);
            CHECK_NULL((*(macroList + macroCount)).content, PRINT_ALLOCATION_FAILED_MSG;
                       free((*(macroList + macroCount)).name); free(macroList); free(destName); fclose(source); fclose(
                               dest); return NULL;)
            strcpy((*(macroList + macroCount)).content, "");
            /*mark the last macro */
            (*(macroList + macroCount + 1)).name = NULL;
        }
         /*regular line*/
         else {
            printf("-printing to file regular line: %s",(currentLine + start));
            /*print the line to file*/
            fprintf( dest,"%s",(currentLine + start));
        }

            free_string_array(wordsInLine,wordCount);
    }

}
printf("all macros:\n");
for (
i = 0;
macroList[i].name!=NULL; ++i) {
printf("name: %s\ncontent: %s\n",macroList[i].name,macroList[i].content);
}

    return destName;
}

int find_macro(string name, macro *macroList) {
    int i;
    for (i = 0; (*(macroList + i)).name != NULL; ++i) {
        if (!strcmp(macroList[i].name, name)) {
            printf("macro exist!\n");
            return i;
        }
    }

    return -1;
}