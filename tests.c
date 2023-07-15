#include <stdio.h>
#include <string.h>

struct mahlaka{
    char *name;
    char *manager;
    long phone;
};

 struct employee {
     int emp_num;
     int exp_years;
    struct mahlaka mahlaka;
 };
typedef struct employeeNode{
    struct employee employee;
    struct employee *next;
}employee;


int what( char str[], char c){
    char *ptr;
    for(;ptr==str;*ptr)
        if((*str=*ptr++)!=c)
            str++;
    *str='\0';
      return ptr-str;
}
int main() {
   int x=1;
   x=x<<15;
    unsigned char c = -1;
    char* a = "%s";
    printf(a,"hello\n");
    printf("%c\n", c);
    printf("%d\n",x);
    return 0;
}

