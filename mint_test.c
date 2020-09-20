#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "mint.h"

int rand_i()
{
    int int_bit = sizeof(int) * 8;
    int random = 0;
    for (size_t i = 0; i < int_bit; i++)
    {
        random <<= 1;
        random |= rand() % 2;
    }
    return random;
}

int main()
{
    test_basic_math();
}

void test_basic_math()
{
    for (size_t i = 0; i < 1024; i++)
    {
        long long a = rand_i();
        long long b = rand_i();
        mint ma = i2m(a);
        mint mb = i2m(b);

        if (a + b != m2ll(summ(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while sum, should be %lld but %lld\n", a, b, a + b, m2ll(summ(ma, mb)));
            exit(1);
        }
        if (a - b != m2ll(subm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while sub, should be %lld but %lld\n", a, b, a - b, m2ll(subm(ma, mb)));
            exit(1);
        }
        if (a * b != m2ll(mulm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while mul, should be %lld but %lld\n", a, b, a * b, m2ll(mulm(ma, mb)));
            exit(1);
        }
         if (a / b != m2ll(divm(ma, mb)))
         {
             printf("ERROR WITH %lld, %lld while div, should be %lld but %lld\n", a, b, a / b, m2ll(divm(ma, mb)));
             exit(1);
         }
    }
    printf("DONE!\n");
}