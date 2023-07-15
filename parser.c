#include "parser.h"
#include "helpers.h"
#include "globals.h"
/*

Retrieves an instruction structure based on the provided name.

@param name The name of the instruction to retrieve.

@return The instruction structure matching the name, or a default non-existing instruction if not found.
*/
string next_word(string line, string *restOfLine);
bool is_instruction(string name);

/*
 *
static const struct instruction instructions[16] = {{"mov",  mov_opcode,  {immediate_addressing, direct_addressing, register_addressing}, direct_addressing, register_addressing},
                                                    {"cmp",  cmp_opcode,  {immediate_addressing, direct_addressing, register_addressing}, {immediate_addressing, direct_addressing, register_addressing}},
                                                    {"add",  add_opcode,  {immediate_addressing, direct_addressing, register_addressing}, {direct_addressing,    register_addressing}},
                                                    {"sub",  sub_opcode,  {immediate_addressing, direct_addressing, register_addressing}, {direct_addressing,    register_addressing}},
                                                    {"not",  not_opcode,  {no_addressing,no_addressing,no_addressing}, {direct_addressing,register_addressing}},
                                                    {"clr",  clr_opcode,  {no_addressing,no_addressing,no_addressing}, {direct_addressing,register_addressing}},
                                                    {"lea",  lea_opcode,  {direct_addressing}, {direct_addressing,register_addressing}},
                                                    {"inc",  inc_opcode,  {no_addressing,no_addressing,no_addressing}, {direct_addressing,register_addressing}},
                                                    { "dec",  dec_opcode, {no_addressing,no_addressing,no_addressing}, {direct_addressing,register_addressing}},
                                                    {"jmp",  jmp_opcode,  {no_addressing,no_addressing,no_addressing}, {direct_addressing,register_addressing}},
                                                    {"bne",  bne_opcode,  {no_addressing,no_addressing,no_addressing}, {direct_addressing,register_addressing}},
                                                    {"red",  red_opcode,  {no_addressing,no_addressing,no_addressing}, {direct_addressing,    register_addressing}},
                                                    {"prn",  prn_opcode,  {no_addressing,no_addressing,no_addressing}, {immediate_addressing, direct_addressing, register_addressing}},
                                                    {"jsr",  jsr_opcode,  {no_addressing,no_addressing,no_addressing}, {direct_addressing,    register_addressing}},
                                                    {"rts",  rts_opcode,  {no_addressing,no_addressing,no_addressing}, {no_addressing,no_addressing,no_addressing}},
                                                    {"stop", stop_opcode, {no_addressing,no_addressing,no_addressing}, {no_addressing,no_addressing,no_addressing}}};
                                                    */


int line_to_AST(string line){
    int wordCount, start;
    string *words;
    string temp, first_word, restOfLine;
    BLOCK_ALLOCATION(temp,char, strlen(line)+1);
    CHECK_NULL(temp, PRINT_ALLOCATION_FAILED_MSG; return -1;)
  temp = strcpy(temp,line);
    CLEAR_SPACES(temp , start)
    printf("after decalrations\n");
    /*check if this is a label definition*/
    /*if (first_word[strlen(first_word)-1]==LABEL_END){
        printf("label ");
    } else*/
    first_word = strtok_r((temp)," ",&restOfLine);
    words = split_to_words((temp+start+strlen(restOfLine)), " ,", &wordCount);
    printf("line: %s\n",line);
    printf("first word: %s-\n",first_word);

   if(is_instruction(first_word)){
       printf("instruction found: %s\n",first_word);
   } else
       printf("instruction not found\n");
    return 0;
}

string next_word(string line, string *restOfLine){

}

int next_char(string str , const char character){
    int index;
    for ( index = 0; index < strlen(str); index++) {
        if(*(str+index)==character){
            memmove(str,(str+index), strlen(str)-index);
            return 0;
        }
    }
    return -1;
}

bool is_legal_label(string label) {
    int i;
    /*label doesnt start with a letter*/
    if (!isalpha(label[0])) {
        return false;
    }
    /*check if label contains only letters and numbers*/
    for (i = 1; i < strlen(label); i++) {
        if (!(isalpha(label[i]) || isdigit(label[i]))) {
            return false;
        }
    }
    /*check if the label is a keyword*/
    return is_keyword(label);
}

bool is_instruction(string name){
    int i;
    for ( i = 0; i <16 ; ++i) {
        if(strcmp(name,instructions[i])==0){
            return true;
        }
    }

    return false;
}