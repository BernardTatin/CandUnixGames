# sizeof.c

A good exercise which recall me that integers are only 32 bits, and not 64 as I thought - on my machine.

Here are some results:

| Processor | OS            | Intel(R) Core(TM) i5-3320M |
| --------- | ------------- | -------------------------: |
| Compiler  | Linux 64 bits |                 gcc 10.2.0 |
| Compiler  | Linux 64 bits |               clang 10.0.0 |


| Data Type   | Size (bits) | Size (bytes) |
| ----------- | ----------: | -----------: |
| char        |           8 |            1 |
| short       |          16 |            2 |
| int         |          32 |            4 |
| long        |          64 |            8 |
| long long   |          64 |            8 |
| char *      |          64 |            8 |
| float       |          32 |            4 |
| double      |          64 |            8 |
| long double |         128 |           16 |


| Processor | OS            | Intel(R) Core(TM) i5-3320M |
| --------- | ------------- | -------------------------: |
| Compiler  | Linux 64 bits |                Open Watcom |

| Data Type   | Size (bits) | Size (bytes) |
| ----------- | ----------: | -----------: |
| char        |           8 |            1 |
| short       |          16 |            2 |
| int         |          32 |            4 |
| long        |          32 |            4 |
| long   long |          64 |            8 |
| char   *    |          32 |            4 |
| float       |          32 |            4 |
| double      |          64 |            8 |
| long double |          64 |            8 |

Compilation was done with these command line:

| Compiler    | Command line                                      |
| ----------- | ------------------------------------------------- |
| gcc         | `gcc -Wall -Wextra -std=c11 sizeof.c -o sizeof`   |
| clang       | `clang -Wall -Wextra -std=c11 sizeof.c -o sizeof` |
| Open watcom | `owcc -o sizeof -Wall -Wextra -std=c99 sizeof.c`  |

