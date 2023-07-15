
#include "translator.h"
#include "helpers.h"


string intToBinary(int number, int bits) {

    BLOCK_ALLOCATION(string binary, char , bits+1);
    CHECK_NULL(binary,PRINT_ALLOCATION_FAILED_MSG; return NULL;)
    int mask = 1 << (bits - 1);
    int i;
    for (i = 0; i < bits; ++i) {
        binary[i] = (number & mask) ? '1' : '0';
        mask >>= 1;
    }
    binary[bits] = '\0';

    return binary;
}

string stringToBinary(string str){
    int i;
    string binary;
    BLOCK_ALLOCATION(binary,char , (WORD_SIZE* strlen(str)+1));
    CHECK_NULL(binary,PRINT_ALLOCATION_FAILED_MSG; return NULL;)
    binary = strcpy(binary,"");
    for ( i = 0; i < strlen(str); ++i) {
        strcat(binary, intToBinary(str[i],WORD_SIZE));
        strcat(binary,"\n");

    }
}

string firstWordToBinary(struct first_word fw) {
    int numBits = 12;
    string binary;
    BLOCK_ALLOCATION(binary, char , numBits + 1);
    CHECK_NULL(binary,PRINT_ALLOCATION_FAILED_MSG; return NULL;)
    /*initialize binary*/
    strcpy(binary,"");

    /*Convert the fields to binary*/
    strcat(binary, intToBinary(fw.source_oprnd,3));
    strcat(binary, intToBinary(fw.opcode,4));
    strcat(binary, intToBinary(fw.target_oprnd,3));
    strcat(binary, intToBinary(fw.A_R_E,2));
    return binary;
}


/*work out the issue of source register and target something else, source register should fill a word*/
string instruction_to_binary(unsigned int opcode, operand targetOperand, operand sourceOperand ){
    struct first_word firstWord;
    string binary, nextWords;
    int lines=3, nextWordsCount=0;

    /*initialize binary*/
    BLOCK_ALLOCATION(binary,char,(WORD_SIZE+1)*lines);
    strcpy(binary,"");

    /*initialize first firstWord*/
    firstWord.opcode = opcode;
    firstWord.source_oprnd = sourceOperand.type;
    firstWord.target_oprnd = targetOperand.type;

    strcat(binary, firstWordToBinary(firstWord));
    strcat(binary,"\n");

    if(targetOperand.type!=nullOperand.type&&sourceOperand.type!=nullOperand.type) {
        /*initialize nextWords*/
        BLOCK_ALLOCATION(nextWords, char, WORD_SIZE + 1);
        CHECK_NULL(nextWords, PRINT_ALLOCATION_FAILED_MSG; return NULL;)
        strcpy(nextWords, "");

        if(sourceOperand.type!=nullOperand.type) {
            /*handle private case of both source and target registers are operands*/
            if (sourceOperand.type == register_addressing && targetOperand.type == register_addressing) {
                /*digits 7-11 are source register, digits 2-6 are target register, digits 0-2 are A_R_E - A*/
                strcat(nextWords, intToBinary(sourceOperand.value, 5));
                strcat(nextWords, intToBinary(targetOperand.value, 5));
                strcat(nextWords, intToBinary(A, 2));
                nextWordsCount++;
            }
/*source operand analysis*/
            switch (sourceOperand.type) {
                case immediate_addressing:
                    /*the whole word is the number*/
                    strcat(nextWords, intToBinary(sourceOperand.value, WORD_SIZE));
                    break;
                case direct_addressing:
                    /*last 10 bits are the address, first 2 bits are A_R_E */
                    strcat(nextWords, intToBinary(sourceOperand.value, 10));
                    strcat(nextWords, intToBinary(R, 2));
                    break;
                    /*only the source operand is register*/
                case register_addressing:
                    /*digits 7-11 are source register, digits 2-6 are 0, digits 0-2 are A_R_E - A */
                    strcat(nextWords, intToBinary(sourceOperand.value, 5));
                    strcat(nextWords, intToBinary(0, 5));
                    strcat(nextWords, intToBinary(A, 2));
                    break;
            }
            /*if a word was created (there is a source operand)*/
            if (strlen(nextWords) == WORD_SIZE) {
                strcat(nextWords, "\n");
                nextWordsCount++;
            }
        }
        switch (targetOperand.type) {
            case immediate_addressing:
                /*the whole word is the number*/
                strcat(nextWords, intToBinary(targetOperand.value, WORD_SIZE));
                break;
            case direct_addressing:
                /*last 10 bits are the address, first 2 bits are A_R_E */
                strcat(nextWords, intToBinary(targetOperand.value, 10));
                strcat(nextWords, intToBinary(R, 2));
                break;
            case register_addressing:
                strcat(nextWords, intToBinary(targetOperand.value, 5));
                strcat(nextWords, intToBinary(A, 2));
                break;
        }

        strcat(binary,nextWords);
        /*check if the last word is complete - happens
        if ((strlen(nextWords) - nextWordsCount) % WORD_SIZE != 0) {
            strcat(nextWords, intToBinary(A, 2));
        }*/
    }


}