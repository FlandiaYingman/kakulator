#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "mint.h"

mint new_mint()
{
    mint new_mint;
    new_mint.positive = true;
    memset(new_mint.data, BYTE_MIN, MINT_LENGTH);
    return new_mint;
}

mint ll2m(long long ll)
{
    mint m = new_mint();
    m.positive = ll >= 0;
    ll = ll >= 0 ? ll : -ll;
    size_t index = 0;
    while (ll != 0)
    {
        if (index >= MINT_LENGTH)
        {
            printf("MINT LL2M OVERFLOW");
        }

        m.data[index++] = ll % BYTE_DIGIT;
        ll = ll / BYTE_DIGIT;
    }
    return m;
}

long long m2ll(mint m)
{
    long long ll = 0;
    for (size_t index = MINT_LENGTH; index-- > 0;)
    {
        if (m.data[index] == BYTE_MIN)
        {
            continue;
        }
        else
        {
            if (ll > ll + m.data[index] * powl(BYTE_DIGIT, index))
            {
                printf("MINT M2LL OVERFLOW");
            }

            ll += m.data[index] * powl(BYTE_DIGIT, index);
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

bool is_zero(mint m)
{
    for (size_t i = 0; i < MINT_LENGTH; i++)
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
        for (size_t i = 0; i < MINT_LENGTH; i++)
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

    for (size_t i = MINT_LENGTH; i-- > 0;)
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

    for (size_t i = MINT_LENGTH; i-- > 0;)
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

mint sumi(mint a, int b)
{
    return sum(a, i2m(b));
}

mint subi(mint a, int b)
{
    return sub(a, i2m(b));
}

mint sum(mint a, mint b)
{
    if (a.positive == b.positive)
    {
        mint sum = new_mint();
        sum.positive = a.positive;
        byte carry = BYTE_MIN;
        for (size_t i = 0; i < MINT_LENGTH; i++)
        {
            int byte_sum = (int)a.data[i] + (int)b.data[i] + carry;
            sum.data[i] = byte_sum % BYTE_DIGIT;
            carry = byte_sum / BYTE_DIGIT;
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
            mint sum = sub(a, b);
            b.positive = false;
            return sum;
        }
        if (b.positive)
        {
            a.positive = true;
            mint sum = sub(b, a);
            a.positive = false;
            return sum;
        }
    }
}

mint sub(mint a, mint b)
{
    if (a.positive == b.positive)
    {
        mint sub = new_mint();
        sub.positive = gt(a, b);
        int carry = 0;
        for (size_t i = 0; i < MINT_LENGTH; i++)
        {
            int byte_sub = BYTE_DIGIT + (int)a.data[i] - (int)b.data[i] + carry;
            sub.data[i] = byte_sub % BYTE_DIGIT;
            carry = (byte_sub / BYTE_DIGIT) - 1;
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
        mint sub = sum(a, b);
        b.positive = !(b.positive);
        return sub;
    }
}

mint muli(mint a, int b)
{
    mint product = new_mint();
    product.positive = a.positive;

    unsigned long long carry = 0;
    for (size_t i = 0; i < MINT_LENGTH; i++)
    {
        unsigned long long byte_product = a.data[i] * b + carry;
        product.data[i] = byte_product % BYTE_DIGIT;
        carry = byte_product / BYTE_DIGIT;
    }

    if (carry != 0)
    {
        printf("MINT MULI OVERFLOW");
        exit(1);
    }

    return product;
}

mint mul(mint a, mint b)
{
    mint product = new_mint();
    product.positive = a.positive == b.positive;

    mint temp_array[MINT_LENGTH];
    for (size_t i = 0; i < MINT_LENGTH; i++)
    {
        mint byte_product = muli(a, b.data[i]);
        for (size_t j = 0; j < i; j++)
        {
            byte_product = muli(byte_product, BYTE_DIGIT);
        }
        temp_array[i] = byte_product;
    }

    for (size_t i = 0; i < MINT_LENGTH; i++)
    {
        product = sum(product, temp_array[i]);
    }
    return product;
}

mint mdiv(mint n, mint d)
{
    if (is_zero(d))
    {
        printf("DIV BY ZERO");
        exit(1);
    }

    mint q = new_mint();
    mint r = new_mint();
    for (size_t i = MINT_BITS; i-- > 0;)
    {
        r = left_shift(r, 1);
        r = set_bit(r, 0, get_bit(n, i));
        if (gt(r, d) || eq(r, d))
        {
            r = sub(r, d);
            q = set_bit(q, i, 1);
        }
    }

    return q;
}

int main()
{
    mint m_1000 = i2m(1000);
    mint m_n1000 = i2m(-1000);
    mint m_2147483647 = i2m(2147483647);

    int i_1000 = m2i(i2m(1000));
    int i_n1000 = m2i(i2m(-1000));
    int i_2147483647 = m2i(i2m(2147483647));

    bool get_bit_255_4 = get_bit(ll2m(255), 4);
    bool get_bit_255_7 = get_bit(ll2m(255), 7);
    bool get_bit_2147483647_30 = get_bit(ll2m(2147483647), 30);

    mint set_bit_255_4 = set_bit(ll2m(255), 4, 0);
    mint set_bit_255_7 = set_bit(ll2m(255), 7, 0);
    mint set_bit_2147483647_30 = set_bit(ll2m(2147483647), 30, 0);

    bool gt_2147483647_2147483646 = gt(i2m(2147483647), i2m(2147483646));
    bool gt_32767_2147483647 = gt(i2m(32767), i2m(2147483647));

    bool lt_2147483647_2147483646 = lt(i2m(2147483647), i2m(2147483646));
    bool lt_32767_2147483647 = lt(i2m(32767), i2m(2147483647));

    bool eq_2147483647_2147483646 = eq(i2m(2147483647), i2m(2147483646));
    bool eq_2147483647_2147483647 = eq(i2m(2147483647), i2m(2147483647));

    mint sum_1000_1000 = sum(i2m(1000), i2m(1000));
    mint sum_n1000_1000 = sum(i2m(-1000), i2m(1000));
    mint sum_2147483647_2147483647 = sum(i2m(2147483647), i2m(2147483647));

    mint sub_1000_500 = sub(i2m(1000), i2m(500));
    mint sub_n1000_500 = sub(i2m(-1000), i2m(500));
    mint sub_2147483647_32767 = sub(i2m(2147483647), i2m(32767));

    mint mulb_9_81 = muli(i2m(9), 81);
    mint mulb_1234567_177 = muli(i2m(1234567), 177);

    mint mul_123_321 = mul(i2m(123), i2m(321));
    mint mul_1234567_7654321 = mul(i2m(1234567), i2m(7654321));

    mint div_1024_256 = mdiv(ll2m(1024), ll2m(256));
    mint div_32768_256 = mdiv(ll2m(32768), ll2m(256));
    mint div_2147483648_256 = mdiv(ll2m(2147483648), ll2m(256));

    return 0;
}