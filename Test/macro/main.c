#include <stdio.h>
#include <assert.h>
#include <string.h>

#define POW(n, p, i, r)       \
    r = 1;                    \
    for (i = 0; i < p; ++i) { \
        r *= n;               \
    }\

#define GET_SIZE(type) sizeof(type)

#define message_for(a, b) \
    printf(#a " and " #b ": We love you!\n")

#define token_pasting(num) \
    printf("%s\n", key##num)

#if !defined(TRUE)
#define TRUE (1)
#define FALSE (0)
#endif

#if defined(NDEBUG)
#undef NDEBUG
#endif

int main(void)
{
    const char* key1 = "Valkyrie";
    const char* key2 = "Oracle";
    char time[] = __TIME__;
    int i;
    int result;

    printf("%d\n", strcmp(key1, key2));
    printf("Now time: %s\n", time);

    token_pasting(1);
    token_pasting(2);
    message_for(Rakan, Xayah);

    POW(2, 8, i, result);
    printf("result: %d\n", result);

    printf("Size of short: %d\n", GET_SIZE(short));
    printf("Size of int: %d\n", GET_SIZE(int));
    printf("Size of float: %d\n", GET_SIZE(float));
    printf("Size of double: %d\n", GET_SIZE(double));
    printf("Size of pointer: %d\n", GET_SIZE(void*));

    puts("No prob");

    return 0;
}
