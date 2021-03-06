/*
 * sizeof.c
 *
 * Open Watcom v2:
 *      owcc -o sizeof.ow -Wall -Wextra -std=c99 sizeof.c && ./sizeof.ow
 * gcc:
 *      gcc -Wall -Wextra -std=c11 sizeof.c -o sizeof && ./sizeof
 * clang:
 *      clang -Wall -Wextra -std=c11 sizeof.c -o sizeof && ./sizeof
 */

#include <stdio.h>
#include <string.h>

#include "compiler-version.h"

#define SHOW_TYPE(type)     printf("%-13s | %6ld | %7ld |\n", \
    #type, 8 * sizeof(type), sizeof(type))
#define SHOW_2TYPE(t1, t2)   printf("%-6s %-6s | %6ld | %7ld |\n", \
    #t1, #t2, 8 * sizeof(t1 t2), sizeof(t1 t2))

int main(void) {
    printf("--------------+--------+---------+\n");
    printf("Size of all in C\n");
    printf("%s\n", get_compiler_name(NULL));
    printf("--------------+--------+---------+\n");
    printf("%-13s | %16s |\n", "Type", "Size");
    printf("%-13s | %6s | %7s |\n", "", "bits", "bytes");
    printf("--------------+--------+---------+\n");
    SHOW_TYPE(char);
    SHOW_TYPE(short);
    SHOW_TYPE(int);
    SHOW_TYPE(long);
    SHOW_2TYPE(long, long);
    SHOW_2TYPE(char, *);
    SHOW_TYPE(float);
    SHOW_TYPE(double);
    SHOW_2TYPE(long, double);
    printf("--------------+--------+---------+\n");
    return 0;
}
