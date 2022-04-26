#include <stdio.h>
#include <stdlib.h>
#include "test.h"

int main()
{
    Test *i, *j;
    i = test_init(), j = test_init();
    i->version = 1;
    char *k = malloc(sizeof(Test));
    test_encode(k, i);
    test_decode(k, j);
    printf("%d\n", j->version);
    test_free(i); 
    printf("%d\n", i->version);
    return 0;
}
