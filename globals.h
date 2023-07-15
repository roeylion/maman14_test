/*ARE:
 * A - number
 * R - label
 * E- extern label
 * */
#ifndef GLOBALS_H
#define GLOBALS_H
/*maximun length of a line (including \n)*/
#define LINE_LENGTH 81
#define MAX_LABEL_LENGTH 31
#define LABEL_END ':'
/*error messages*/
#define PRINT_ALLOCATION_FAILED_MSG fprintf(stderr, "Memory allocation failed at %s:%d\n", __FILE__, __LINE__)
#define PRINT_FOPEN_FAILED_MSG(filename) fprintf(stderr, "Failed to open file: %s\n", filename)

#define WORD_SIZE 12
#define MEMORY 1024
#define SYSTEM_USED_MEMORY 100
typedef enum {
    false, true
} bool;
typedef char *string;
enum registers {
    r1 = 0, r2, r3, r4, r5, r6, r7, INAVLID_REG = -1
};
enum opcode {
    mov_opcode = 0,
    cmp_opcode,
    add_opcode,
    sub_opcode,
    not_opcode,
    clr_opcode,
    lea_opcode,
    inc_opcode,
    dec_opcode,
    jmp_opcode,
    bne_opcode,
    red_opcode,
    prn_opcode,
    jsr_opcode,
    rts_opcode,
    stop_opcode,
    illegal_opcode
};
typedef struct {
    string name;
    string content;
} macro;
enum addressing_types {
    immediate_addressing = 1,/*number*/
    direct_addressing = 3,/*label*/
    register_addressing = 5,/*register*/
    no_addressing = -1
};
enum A_R_E{
    A = 0,
    R=2,
    E=1

};
struct first_word {
    unsigned int A_R_E: 2;
    unsigned int target_oprnd: 3;
    unsigned int opcode: 4;
    unsigned int source_oprnd: 3;
};

struct instruction {
    string name;
    unsigned int opcode;
    unsigned int source_addrressing[3];
    unsigned int target_addrressing[3];
};
typedef struct operand{
    /*the addressing type 1 ,3 ,5*/
    int type;
   /* the value of the operand
    * for number - the number itself
    * for label - the address
    *for register - the register number */
    int value;
}operand;
const operand nullOperand = {0,-1.1};
static const string keywords[] = {"@r0", "@r1", "@r2", "@r3", "@r4", "@r5", "@r6", "@r7",
                                  "mov", "cmp", "add", "sub", "not", "clr", "lea",
                                  "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};

struct label{
    unsigned int address;

};
static const string instructions[16] = {
        "mov",
        "cmp",
        "add",
        "sub",
        "not",
        "clr",
        "lea",
        "inc",
        "dec",
        "jmp",
        "bne",
        "red",
        "prn",
        "jsr",
        "rts",
        "stop"
};
#endif
