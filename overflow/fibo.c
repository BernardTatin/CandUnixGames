/*
 * fibo.c
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "safe-int-arithmetic.h"
#include "compiler-version.h"

#if defined(with_builtins)
static char *has_builtin_mul = "with builtins";
#else
static char *has_builtin_mul = "NO builtins";
#endif

static void fibo(void) {
    ULONG N1 = 0, N2 = 1;
    ULONG result = 1;
    int index = 1;
    bool end = false;

    do {
        if (!safe_add_lu(N1, N2, &result)) {
            printf("KO %3d -" UL_FORMAT " " UL_FORMAT "\n", index, N2, result);
            end = true;
        } else {
            printf("OK %3d -" UL_FORMAT " " UL_FORMAT "\n", index, N2, result);
            N1 = N2;
            N2 = result;
            index++;
        }
    } while (!end);
}


int main(void) {
    printf("%s\n", get_compiler_name(has_builtin_mul));
    fibo();
    return 0;
}
