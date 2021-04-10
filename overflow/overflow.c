/*
 * overflow.c
 */

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#if defined(__WATCOMC__)
#define __UINT64_MAX__ (unsigned long long)-1
#define LONG    long long
#define UL_FORMAT   "%20I64u"
#define ULMAX ULONGLONG_MAX
#if defined(with_builtins)
#undef with_builtins
#endif
#else
#define LONG    long
#define UL_FORMAT   "%20lu"
#define ULMAX ULONG_MAX
#endif
#define ULONG   unsigned LONG

#if defined(with_builtins)
static inline bool safe_mul_lu(ULONG m1, ULONG m2, ULONG *result) {
    return !__builtin_umull_overflow(m1, m2, result);
}
#else
static inline bool safe_mul_lu(ULONG m1, ULONG m2, ULONG *result) {
    if (m1 > ULMAX / m2) {
        *result = ULMAX;
        return false;
    } else {
        *result = m1 * m2;
        return true;
    }
}
#endif

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
            printf("OK " UL_FORMAT " " UL_FORMAT "\n", N, result);
            M = result;
            N++;
        }
    } while (!end);
    printf("\nLast N: " UL_FORMAT "\n", N - 1);

    return 0;
}
