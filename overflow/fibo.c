/*
 * fibo.c
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "safe-int-arithmetic.h"
#include "compiler-version.h"

#if defined(with_builtins)
static char *has_builtin_add = "with builtins";
#else
static char *has_builtin_mul = "NO builtins";
#endif

static bool compute_fibo(ULONG N, ULONG *result) {
    ULONG N1 = 0, N2 = 1;
    // ULONG index = 1;

    *result = 1;
    for (ULONG i=2; i<N; i++) {
        if (!safe_add_lu(N1, N2, result)) {
            return false;
        }
        N1 = N2;
        N2 = *result;
    }
    return true;
}

static void show_all_fibos(void) {
    ULONG N = 0;
    ULONG result;
    bool end = false;

    do {
          if (!compute_fibo(N, &result)) {
            printf("KO " UL_FORMAT " " UL_FORMAT "\n", N, result);
            end = true;
        } else {
            printf("OK " UL_FORMAT " " UL_FORMAT "\n", N, result);
            N++;
        }
    } while (!end);
}


int main(void) {
    printf("%s\n", get_compiler_name(has_builtin_mul));
    for (int i=0; i<50000; i++) {
        show_all_fibos();
    }
    return 0;
}
