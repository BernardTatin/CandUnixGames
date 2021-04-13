/*
 * overflow.c
 *
 * testing overflow of multiplication with GNU builtins
 * or - if not available as with Watcom C - a simple
 * function
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#include "compiler-version.h"

// if no builtins or the wanted builtin
// is not accessible, we undef with_builtins
# if defined(with_builtins)
#if defined(__has_builtin)
#    if !(__has_builtin(__builtin_umull_overflow))
#       undef with_builtins
#    else
#       warning "With builtins"
#    endif
#else
//   __has_builtin is not defined in Watcom C and
//   is not defined in gcc 9 but is defined in gcc 10 and clang 9 and 10
#    if defined(__WATCOMC__) \
            || (defined(__GNUC__) \
            && !defined(__clang__) \
            && (__GNUC__ > 9))
#       undef with_builtins
#    endif
#endif
#endif

#if defined(with_builtins)
static char *has_builtin_mul = "with builtins";
#else
static char *has_builtin_mul = "NO builtins";
#endif


#if defined(__WATCOMC__)
//  the only integer type with 64 bits
#   define LONG                long long
//  printing format for unsigned long long
#   define UL_FORMAT           "%20I64u"
//  max unsigned long long value
#   define ULMAX               ULONGLONG_MAX
#else
//  first type with 64 bits
#   define LONG                long
//  printing format for unsigned long
#   define UL_FORMAT           "%20lu"
//  max unsigned long value
#   define ULMAX               ULONG_MAX
#endif
// because we test factorial which is only defined
// for positive integers, we use unsigned values
#define ULONG               unsigned LONG

// *result = m1 * m2
// if there is overflow, return false, else return true
static inline bool safe_mul_lu(ULONG m1, ULONG m2, ULONG *result) {
#if defined(with_builtins)
    return !__builtin_umull_overflow(m1, m2, result);
#else
    *result = m1 * m2;
    if (m1 > ULMAX / m2) {
        return false;
    } else {
        return true;
    }
#endif
}

int main(void) {
    ULONG N = 1, M = 1;
    ULONG result = 1;
    bool end = false;

    printf("%s\n", get_compiler_name(has_builtin_mul));
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
