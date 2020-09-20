#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "mint.h"


// Initialization Functions

mint newm()
{
    mint new_mint;
    new_mint.positive = true;
    memset(new_mint.data, BYTE_MIN, MINT_BYTES);
    return new_mint;
}


// Conversation Functions

mint ll2m(long long ll)
{
    mint m = newm();
    m.positive = ll >= 0;
    ll = ll >= 0 ? ll : -ll;
    size_t index = 0;
    while (ll != 0)
    {
        if (index >= MINT_BYTES)
        {
            printf("MINT LL2M OVERFLOW");
        }

        m.data[index++] = ll % BYTE_RADIX;
        ll = ll / BYTE_RADIX;
    }
    return m;
}

long long m2ll(mint m)
{
    long long ll = 0;
    for (size_t index = MINT_BYTES; index-- > 0;)
    {
        if (m.data[index] == BYTE_MIN)
        {
            continue;
        }
        else
        {
            if (ll > ll + m.data[index] * powl(BYTE_RADIX, index))
            {
                printf("MINT M2LL OVERFLOW");
            }

            ll += m.data[index] * powl(BYTE_RADIX, index);
        }
    }
    return ll * (m.positive ? 1 : -1);
}

mint i2m(int i)
{
    return ll2m(i);
}

int m2i(mint m)
{
    return m2ll(m);
}


// Bitwise Functions

bool get_bit(mint m, int i)
{
    return (m.data[i / 8] >> (i % 8)) & 1U;
}

mint set_bit(mint m, int i, bool bit)
{
    m.data[i / 8] ^= (-bit ^ m.data[i / 8]) & (1U << (i % 8));
    return m;
}

mint left_shift(mint m, int index)
{
    for (size_t i = MINT_BITS; i-- > index;)
    {
        m = set_bit(m, i, get_bit(m, i - index));
    }
    for (size_t i = 0; i < index; i++)
    {
        m = set_bit(m, i, 0);
    }
    return m;
}

mint right_shift(mint m, int index)
{
    for (size_t i = 0; i < MINT_BITS - index; i++)
    {
        set_bit(m, i, get_bit(m, i + index));
    }
    for (size_t i = MINT_BITS - index; i < MINT_BITS; i++)
    {
        set_bit(m, i, 0);
    }
    return m;
}


// Comparing Functions

bool is_zero(mint m)
{
    for (size_t i = 0; i < MINT_BYTES; i++)
    {
        if (m.data[i] != BYTE_MIN)
        {
            return false;
        }
    }
    return true;
}

bool eq(mint a, mint b)
{
    if (is_zero(a) && is_zero(b))
    {
        return true;
    }
    else if (a.positive != b.positive)
    {
        return false;
    }
    else
    {
        for (size_t i = 0; i < MINT_BYTES; i++)
        {
            if (a.data[i] != b.data[i])
            {
                return false;
            }
        }
        return true;
    }
}

bool gt(mint a, mint b)
{
    if (is_zero(a) && is_zero(b))
    {
        return false;
    }
    if (a.positive && !b.positive)
    {
        return true;
    }
    if (!a.positive && b.positive)
    {
        return false;
    }

    for (size_t i = MINT_BYTES; i-- > 0;)
    {
        if (a.data[i] > b.data[i])
        {
            return true;
        }
        if (a.data[i] < b.data[i])
        {
            return false;
        }
    }
    return false;
}

bool lt(mint a, mint b)
{
    if (is_zero(a) && is_zero(b))
    {
        return false;
    }
    if (a.positive && !b.positive)
    {
        return false;
    }
    if (!a.positive && b.positive)
    {
        return true;
    }

    for (size_t i = MINT_BYTES; i-- > 0;)
    {
        if (a.data[i] < b.data[i])
        {
            return true;
        }
        if (a.data[i] > b.data[i])
        {
            return false;
        }
    }
    return false;
}


// Basic Math Funcions

mint summ(mint a, mint b)
{
    if (a.positive == b.positive)
    {
        mint sum = newm();
        sum.positive = a.positive;
        byte carry = BYTE_MIN;
        for (size_t i = 0; i < MINT_BYTES; i++)
        {
            int byte_sum = (int)a.data[i] + (int)b.data[i] + carry;
            sum.data[i] = byte_sum % BYTE_RADIX;
            carry = byte_sum / BYTE_RADIX;
        }
        if (carry != 0)
        {
            printf("MINT SUM OVERFLOW!");
            exit(1);
        }
        return sum;
    }
    else
    {
        if (a.positive)
        {
            b.positive = true;
            mint sum = subm(a, b);
            b.positive = false;
            return sum;
        }
        if (b.positive)
        {
            a.positive = true;
            mint sum = subm(b, a);
            a.positive = false;
            return sum;
        }
    }
}

mint subm(mint a, mint b)
{
    if (a.positive == b.positive)
    {
        mint sub = newm();
        sub.positive = gt(a, b);
        int carry = 0;
        for (size_t i = 0; i < MINT_BYTES; i++)
        {
            int byte_sub = BYTE_RADIX + (int)a.data[i] - (int)b.data[i] + carry;
            sub.data[i] = byte_sub % BYTE_RADIX;
            carry = (byte_sub / BYTE_RADIX) - 1;
        }
        if (carry != 0)
        {
            printf("MINT SUB OVERFLOW!");
            exit(1);
        }
        return sub;
    }
    else
    {
        b.positive = !(b.positive);
        mint sub = summ(a, b);
        b.positive = !(b.positive);
        return sub;
    }
}

mint muli(mint a, int b)
{
    mint product = newm();
    product.positive = a.positive;

    unsigned long long carry = 0;
    for (size_t i = 0; i < MINT_BYTES; i++)
    {
        unsigned long long byte_product = a.data[i] * b + carry;
        product.data[i] = byte_product % BYTE_RADIX;
        carry = byte_product / BYTE_RADIX;
    }

    if (carry != 0)
    {
        printf("MINT MULI OVERFLOW");
        exit(1);
    }

    return product;
}

mint mulm(mint a, mint b)
{
    mint product = newm();
    product.positive = a.positive == b.positive;

    mint temp_array[MINT_BYTES];
    for (size_t i = 0; i < MINT_BYTES; i++)
    {
        mint byte_product = muli(a, b.data[i]);
        for (size_t j = 0; j < i; j++)
        {
            byte_product = muli(byte_product, BYTE_RADIX);
        }
        temp_array[i] = byte_product;
    }

    for (size_t i = 0; i < MINT_BYTES; i++)
    {
        product = summ(product, temp_array[i]);
    }
    return product;
}

mint divm(mint n, mint d)
{
    if (is_zero(d))
    {
        printf("DIV BY ZERO");
        exit(1);
    }

    mint q = newm();
    mint r = newm();
    for (size_t i = MINT_BITS; i-- > 0;)
    {
        r = left_shift(r, 1);
        r = set_bit(r, 0, get_bit(n, i));
        if (gt(r, d) || eq(r, d))
        {
            r = subm(r, d);
            q = set_bit(q, i, 1);
        }
    }

    return q;
}
