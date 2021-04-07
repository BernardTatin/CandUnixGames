/*
 * sizeof.c
 */

#include <stdio.h>

#define SHOW_TYPE(type)     printf("%6s | %8ld|\n", #type, 8 * sizeof(type))

int main(void) {
    printf("Size of all in C\n");
    printf("-------+-------------+\n");
    printf("Type   | Size (bits) |\n");
    printf("-------+-------------+\n");
    SHOW_TYPE(char);
    SHOW_TYPE(short);
    SHOW_TYPE(int);
    SHOW_TYPE(long);
    printf("-------+-------------+\n");
}
