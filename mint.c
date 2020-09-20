#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "mint.h"

#define max(a, b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#define min(a, b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })


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

// Util Functions

int valid_bytes(mint m)
{
    int vb = MINT_BYTES;
    for (int i = MINT_BYTES; i-- > 0;)
    {
        if (m.data[i] == BYTE_MIN)
            vb--;
        else
            break;
    }
    return vb;
}

mint absm(mint m)
{
    m.positive = true;
    return m;
}

mint negatem(mint m)
{
    m.positive = !m.positive;
    return m;
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
        if (gt(absm(a), absm(b)) || eq(absm(a), absm(b)))
        {
            mint sub = newm();

            sub.positive = a.positive;
            int carry = 0;
            for (size_t i = 0; i < MINT_BYTES; i++)
            {
                int byte_sub = BYTE_RADIX + (int)a.data[i] - (int)b.data[i] + carry;
                sub.data[i] = byte_sub % BYTE_RADIX;
                carry = (byte_sub / BYTE_RADIX) - 1;
            }
            return sub;
        }
        else
        {
            return negatem(subm(b, a));
        }
    }
    else
    {
        mint sub = summ(absm(a), absm(b));
        sub.positive = a.positive;
        return sub;
    }
}

mint mulm(mint a, mint b)
{
    if (valid_bytes(a) + valid_bytes(b) > MINT_BYTES)
    {
        printf("MULM OVERFLOW");
        exit(1);
    }

    mint product = newm();
    int p = valid_bytes(a);
    int q = valid_bytes(b);

    for (int bi = 0; bi < p + q + 1; bi++)
    {
        mint mcarry = newm();
        int carry = 0;
        for (int ai = 0; ai < p + 1; ai++)
        {
            int mul_temp = a.data[ai] * b.data[bi] + carry;
            carry = mul_temp / BYTE_RADIX;
            mcarry.data[bi + ai] = mul_temp % BYTE_RADIX;
        }
        product = summ(product, mcarry);
    }
    product.positive = a.positive == b.positive;
    return product;
}

mint divm(mint n, mint d)
{
    if (is_zero(d))
    {
        printf("DIVM BYZERO");
        exit(1);
    }

    mint q = newm();
    mint r = newm();
    for (size_t i = valid_bytes(n) * 8; i-- > 0;)
    {
        r = left_shift(r, 1);
        r = set_bit(r, 0, get_bit(n, i));
        if (gt(r, absm(d)) || eq(r, absm(d)))
        {
            r = subm(r, absm(d));
            q = set_bit(q, i, 1);
        }
    }

    q.positive = n.positive == d.positive;
    return q;
}
