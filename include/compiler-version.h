/*
 * compiler-version.h
 */

#if !defined(__compiler_version_h__)
#define __compiler_version_h__

#include <stdbool.h>

static char *get_compiler_name(char *more) {
    static char compiler_name[256];
    static bool done = false;

    if (!done) {
#if defined(__clang__)
        sprintf(compiler_name, "clang %s",
                __clang_version__);
#elif defined(__NVCOMPILER)
        sprintf(compiler_name, "NVidia Compiler %d.%d.%d",
                __NVCOMPILER_MAJOR__,
                __NVCOMPILER_MINOR__,
                __NVCOMPILER_PATCHLEVEL__);
#elif defined(__GNUC__)
        sprintf(compiler_name, "gcc %d.%d.%d",
                __GNUC__,
                __GNUC_MINOR__,
                __GNUC_PATCHLEVEL__);
#elif defined(__WATCOMC__)
        sprintf(compiler_name, "Open Watcom %2d.%02d",
                __WATCOMC__/100,
                __WATCOMC__%100);
#else
        strcpy(compiler_name, "Unknown compiler");
#endif
        if (more != NULL) {
            strcat(compiler_name, " ");
            strcat(compiler_name, more);
        }
        done = true;
    }
    return compiler_name;
}

#endif // __compiler_version_h__
