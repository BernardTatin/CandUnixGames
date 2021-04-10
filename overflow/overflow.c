/*
 * overflow.c
 *
 * testing overflow of multiplication with GNU builtins
 * or - if not available as with Watcom C - a simple
 * function
 */

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#if defined(__WATCOMC__)
// the only integer type with 64 bits
#define LONG                long long
// printing format for unsigned long long
#define UL_FORMAT           "%20I64u"
// max unsigned long long value
#define ULMAX               ULONGLONG_MAX
#if defined(with_builtins)
// Watcom does not have builtins for multiplication
#undef with_builtins
#endif
#else
// first type with 64 bits
#define LONG                long
#define UL_FORMAT           "%20lu"
// printing format for unsigned long
#define ULMAX               ULONG_MAX
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

    printf("\n");
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
