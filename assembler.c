/*#include <stdio.h>
#include "pre_processor.h"
#include "parser.h"
#define ROUND(x)  (((x)-((int)x)>0.5)? (int)((x)+1):(int)(x))
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
void round_arr(float arr[],int length);

struct a{
    int a:1;
    int b:1;
};
struct type{
    char a;
    int b;
    char c;
    float d;
} t;


int main(int argc, char **argv) {
    int i, capacity=10 ,len;
    struct a temp[12];
    void fun(int[]);
    char e;
    float h[]={1.2,12.8,3.4,4.5,5.6,6.7,7.8};
    char g;
    unsigned int x = -4;
    printf("%d\n",x);
    round_arr(h,7);
    for ( i = 0; i < 5; ++i)
        printf("hello\n");

    printf("%f\n%f\n%f\n",h[0],h[1],h[2]);


    return 0;
}



void round_arr(float *arr, int length) {
    int i;
    for ( i = 0; i < length; ++i) {
        arr[i] = ROUND(arr[i]);

    }
}

void fun(int a[]){
    a[0]=3;
}
int find_c(char *str, char c){
    int i,count=0;
    size_t len = strlen(str);
    for ( i = 0; i <len ; ++i) {
        if(str[i]==c)
            count++;
    }
    return count;
}*/