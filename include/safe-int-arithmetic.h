/*
 * safe-int-arithmetic.h
 */

#if !defined(__safe_int_arithmetic_h__)

#include <stdint.h>
#include <limits.h>

// if no builtins or the wanted builtin
// is not accessible, we undef with_builtins
# if defined(with_builtins)
#if defined(__has_builtin)
#    if !(__has_builtin(__builtin_umull_overflow))
#       undef with_builtins
#    else
#       warning "With builtins"
#    endif
#else   // __has_builtin
//   __has_builtin is not defined in Watcom C and
//   is not defined in gcc 9 but is defined in gcc 10 and clang 9 and 10
#    if defined(__WATCOMC__) \
            || (defined(__GNUC__) \
            && !defined(__clang__) \
            && (__GNUC__ > 9))
#       undef with_builtins
#    endif
#endif   // __has_builtin
#endif   // with_builtins

#if defined(__WATCOMC__)
//  printing format for unsigned long long
#   define UL_FORMAT           "%20I64u"
//  max unsigned long long value
#   define ULMAX               ULONGLONG_MAX
#else   // __WATCOMC__
//  printing format for unsigned long
#   define UL_FORMAT           "%20lu"
//  max unsigned long value
#   define ULMAX               ULONG_MAX
#endif
// because we test factorial/fibonacci which is only defined
// for positive integers, we use unsigned values
#define ULONG               uint64_t

#if defined(with_builtins)
// *result = m1 + m2
// if there is overflow, return false, else return true
static inline bool safe_add_lu(ULONG m1, ULONG m2, ULONG *result) {
    return !__builtin_uaddl_overflow(m1, m2, result);
}
// *result = m1 * m2
// if there is overflow, return false, else return true
static inline bool safe_mul_lu(ULONG m1, ULONG m2, ULONG *result) {
    return !__builtin_umull_overflow(m1, m2, result);
}
#else   // with_builtins
// *result = m1 + m2
// if there is overflow, return false, else return true
static inline bool safe_add_lu(ULONG m1, ULONG m2, ULONG *result) {
    *result = m1 + m2;
    if (m1 > ULMAX - m2) {
        return false;
    } else {
        return true;
    }
}

// *result = m1 * m2
// if there is overflow, return false, else return true
static inline bool safe_mul_lu(ULONG m1, ULONG m2, ULONG *result) {
    *result = m1 * m2;
    if (m1 > ULMAX / m2) {
        return false;
    } else {
        return true;
    }
}
#endif   // with_builtins

#endif // safe-int-arithmetic.h
