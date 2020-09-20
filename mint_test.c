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

byte rand_b()
{
    int byte_bit = sizeof(byte) * 8;
    int random = 0;
    for (size_t i = 0; i < byte_bit; i++)
    {
        random <<= 1;
        random |= rand() % 2;
    }
    return random;
}

void test_basic_math()
{
    //full random testing
    for (size_t i = 0; i < 32; i++)
    {
        long long a = rand_i();
        long long b = rand_i();
        mint ma = i2m(a);
        mint mb = i2m(b);

        printf("TESTING SUM WITH %lld, %lld = %lld\n", a, b, m2ll(summ(ma, mb)));
        if (a + b != m2ll(summ(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while sum, should be %lld but %lld\n", a, b, a + b, m2ll(summ(ma, mb)));
            exit(1);
        }
        printf("TESTING SUB WITH %lld, %lld = %lld\n", a, b, m2ll(subm(ma, mb)));
        if (a - b != m2ll(subm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while sub, should be %lld but %lld\n", a, b, a - b, m2ll(subm(ma, mb)));
            exit(1);
        }
        printf("TESTING MUL WITH %lld, %lld = %lld\n", a, b, m2ll(mulm(ma, mb)));
        if (a * b != m2ll(mulm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while mul, should be %lld but %lld\n", a, b, a * b, m2ll(mulm(ma, mb)));
            exit(1);
        }
        printf("TESTING DIV WITH %lld, %lld = %lld\n", a, b, m2ll(divm(ma, mb)));
        if (a / b != m2ll(divm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while div, should be %lld but %lld\n", a, b, a / b, m2ll(divm(ma, mb)));
            exit(1);
        }
    }
    //smaller a testing
    for (size_t i = 0; i < 32; i++)
    {
        long long a = rand_b();
        long long b = rand_i();
        mint ma = ll2m(a);
        mint mb = ll2m(b);

        printf("TESTING SUM WITH %lld, %lld = %lld\n", a, b, m2ll(summ(ma, mb)));
        if (a + b != m2ll(summ(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while sum, should be %lld but %lld\n", a, b, a + b, m2ll(summ(ma, mb)));
            exit(1);
        }
        printf("TESTING SUB WITH %lld, %lld = %lld\n", a, b, m2ll(subm(ma, mb)));
        if (a - b != m2ll(subm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while sub, should be %lld but %lld\n", a, b, a - b, m2ll(subm(ma, mb)));
            exit(1);
        }
        printf("TESTING MUL WITH %lld, %lld = %lld\n", a, b, m2ll(mulm(ma, mb)));
        if (a * b != m2ll(mulm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while mul, should be %lld but %lld\n", a, b, a * b, m2ll(mulm(ma, mb)));
            exit(1);
        }
        printf("TESTING DIV WITH %lld, %lld = %lld\n", a, b, m2ll(divm(ma, mb)));
        if (a / b != m2ll(divm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while div, should be %lld but %lld\n", a, b, a / b, m2ll(divm(ma, mb)));
            exit(1);
        }
    }
    //smaller b testing
    for (size_t i = 0; i < 32; i++)
    {
        long long a = rand_i();
        long long b = rand_b();
        mint ma = i2m(a);
        mint mb = i2m(b);

        printf("TESTING SUM WITH %lld, %lld = %lld\n", a, b, m2ll(summ(ma, mb)));
        if (a + b != m2ll(summ(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while sum, should be %lld but %lld\n", a, b, a + b, m2ll(summ(ma, mb)));
            exit(1);
        }
        printf("TESTING SUB WITH %lld, %lld = %lld\n", a, b, m2ll(subm(ma, mb)));
        if (a - b != m2ll(subm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while sub, should be %lld but %lld\n", a, b, a - b, m2ll(subm(ma, mb)));
            exit(1);
        }
        printf("TESTING MUL WITH %lld, %lld = %lld\n", a, b, m2ll(mulm(ma, mb)));
        if (a * b != m2ll(mulm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while mul, should be %lld but %lld\n", a, b, a * b, m2ll(mulm(ma, mb)));
            exit(1);
        }
        printf("TESTING DIV WITH %lld, %lld = %lld\n", a, b, m2ll(divm(ma, mb)));
        if (a / b != m2ll(divm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while div, should be %lld but %lld\n", a, b, a / b, m2ll(divm(ma, mb)));
            exit(1);
        }
    }
    //a=0 testing
    for (size_t i = 0; i < 32; i++)
    {
        long long a = 0;
        long long b = rand_i();
        mint ma = i2m(a);
        mint mb = i2m(b);

        printf("TESTING SUM WITH %lld, %lld = %lld\n", a, b, m2ll(summ(ma, mb)));
        if (a + b != m2ll(summ(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while sum, should be %lld but %lld\n", a, b, a + b, m2ll(summ(ma, mb)));
            exit(1);
        }
        printf("TESTING SUB WITH %lld, %lld = %lld\n", a, b, m2ll(subm(ma, mb)));
        if (a - b != m2ll(subm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while sub, should be %lld but %lld\n", a, b, a - b, m2ll(subm(ma, mb)));
            exit(1);
        }
        printf("TESTING MUL WITH %lld, %lld = %lld\n", a, b, m2ll(mulm(ma, mb)));
        if (a * b != m2ll(mulm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while mul, should be %lld but %lld\n", a, b, a * b, m2ll(mulm(ma, mb)));
            exit(1);
        }
        printf("TESTING DIV WITH %lld, %lld = %lld\n", a, b, m2ll(divm(ma, mb)));
        if (a / b != m2ll(divm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while div, should be %lld but %lld\n", a, b, a / b, m2ll(divm(ma, mb)));
            exit(1);
        }
    }
    //b=0 testing
    for (size_t i = 0; i < 32; i++)
    {
        long long a = rand_i();
        long long b = 0;
        mint ma = i2m(a);
        mint mb = i2m(b);

        printf("TESTING SUM WITH %lld, %lld = %lld\n", a, b, m2ll(summ(ma, mb)));
        if (a + b != m2ll(summ(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while sum, should be %lld but %lld\n", a, b, a + b, m2ll(summ(ma, mb)));
            exit(1);
        }
        printf("TESTING SUB WITH %lld, %lld = %lld\n", a, b, m2ll(subm(ma, mb)));
        if (a - b != m2ll(subm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while sub, should be %lld but %lld\n", a, b, a - b, m2ll(subm(ma, mb)));
            exit(1);
        }
        printf("TESTING MUL WITH %lld, %lld = %lld\n", a, b, m2ll(mulm(ma, mb)));
        if (a * b != m2ll(mulm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while mul, should be %lld but %lld\n", a, b, a * b, m2ll(mulm(ma, mb)));
            exit(1);
        }
        // printf("TESTING DIV WITH %lld, %lld = %lld\n", a, b, m2ll(divm(ma, mb)));
        // if (a / b != m2ll(divm(ma, mb)))
        // {
        //     printf("ERROR WITH %lld, %lld while div, should be %lld but %lld\n", a, b, a / b, m2ll(divm(ma, mb)));
        //     exit(1);
        // }
    }
    //a=b testing
    for (size_t i = 0; i < 32; i++)
    {
        long long a = rand_i();
        long long b = a;
        mint ma = i2m(a);
        mint mb = i2m(b);

        printf("TESTING SUM WITH %lld, %lld = %lld\n", a, b, m2ll(summ(ma, mb)));
        if (a + b != m2ll(summ(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while sum, should be %lld but %lld\n", a, b, a + b, m2ll(summ(ma, mb)));
            exit(1);
        }
        printf("TESTING SUB WITH %lld, %lld = %lld\n", a, b, m2ll(subm(ma, mb)));
        if (a - b != m2ll(subm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while sub, should be %lld but %lld\n", a, b, a - b, m2ll(subm(ma, mb)));
            exit(1);
        }
        printf("TESTING MUL WITH %lld, %lld = %lld\n", a, b, m2ll(mulm(ma, mb)));
        if (a * b != m2ll(mulm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while mul, should be %lld but %lld\n", a, b, a * b, m2ll(mulm(ma, mb)));
            exit(1);
        }
        printf("TESTING DIV WITH %lld, %lld = %lld\n", a, b, m2ll(divm(ma, mb)));
        if (a / b != m2ll(divm(ma, mb)))
        {
            printf("ERROR WITH %lld, %lld while div, should be %lld but %lld\n", a, b, a / b, m2ll(divm(ma, mb)));
            exit(1);
        }
    }
    printf("DONE!\n");
}

int main()
{
    test_basic_math();
}