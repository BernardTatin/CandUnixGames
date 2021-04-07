/*
 * sizeof.c
 */

#include <stdio.h>

#if defined(__GNUC__) && !defined(__clang__)
#define COMPILER "gcc"
#elif defined(__clang__)
#define COMPILER "clang-" __clang_version__
#elif defined(__WATCOMC__)
#define COMPILER "open watcom"
#else
#define COMPILER "Unknown compiler"
#endif

#define SHOW_TYPE(type)     printf("%-13s | %6ld | %7ld |\n", \
    #type, 8 * sizeof(type), sizeof(type))
#define SHOW_2TYPE(t1, t2)   printf("%-6s %-6s | %6ld | %7ld |\n", \
    #t1, #t2, 8 * sizeof(t1 t2), sizeof(t1 t2))

int main(void) {
    printf("--------------+--------+---------+\n");
    printf("Size of all in C\n");
    printf("%s\n", COMPILER);
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
