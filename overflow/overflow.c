/*
 * overflow.c
 *
 * testing overflow of multiplication with GNU builtins
 * or - if not available as with Watcom C - a simple
 * function
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "safe-int-arithmetic.h"
#include "compiler-version.h"

#if defined(with_builtins)
static char *has_builtin_mul = "with builtins";
#else
static char *has_builtin_add = "NO builtins";
#endif



int main(void) {
    ULONG N = 1, M = 1;
    ULONG result = 1;
    bool end = false;

    printf("%s\n", get_compiler_name(has_builtin_add));
    do {
        if (!safe_mul_lu(N, M, &result)) {
            printf("KO " UL_FORMAT " " UL_FORMAT "\n", N, result);
            end = true;
        } else {
            printf("OK " UL_FORMAT "! " UL_FORMAT "\n", N, result);
            M = result;
            N++;
        }
    } while (!end);
    printf("\nLast N: " UL_FORMAT "\n", N - 1);

    return 0;
}
