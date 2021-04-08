/*
 * overflow.c
 */

#include <stdio.h>
#include <stdbool.h>

int main(void) {
    unsigned long N = 1, M = 1;
    unsigned long result = 1;
    bool end = false;

    printf("\n");
    do {
        if (__builtin_umull_overflow(N, M, &result)) {
            printf("KO %10lu\r", N);
            end = true;
        } else {
            printf("OK %10lu %10lu\r", N, M);
            M = result;
            N++;
        }
    } while (!end);
    printf("Last N: %lu\n", N - 1);

    return 0;
}
