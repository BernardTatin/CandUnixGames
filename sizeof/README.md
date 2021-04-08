# sizeof.c

A good exercise which recall me that integers are only 32 bits, and not 64 as I thought - on my machine.

Here are some results:

| Processor | Intel(R) Core(TM) i5-3320M |
| --------- | -------------------------: |
| Compiler  |                 gcc 10.2.0 |



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

