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
static char *has_builtin_add = "NO builtins";
#endif

static bool compute_fibo(ULONG N, ULONG *result) {
    ULONG N1 = 1, N2 = 1;

    if (N < 3) {
        int littlen = (int)N;
        switch (littlen)
        {
        case 0:
            *result = 0;
            return true;
        case 1:
        case 2:
            *result = 1;
            return true;
        }
    }
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
#if !defined(test_timing)
            printf("OK " UL_FORMAT " " UL_FORMAT "\n", N, result);
#endif            
            N++;
        }
    } while (!end);
}


int main(void) {
    printf("%s\n", get_compiler_name(has_builtin_add));
#if defined(test_timing)
    for (int i=0; i<500000; i++) {
        show_all_fibos();
    }
#else
    show_all_fibos();
#endif    
    return 0;
}
