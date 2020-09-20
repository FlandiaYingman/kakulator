#ifndef MINT_H
#define MINT_H

#include <stdbool.h>

#define MINT_BYTES 128
#define MINT_BITS (MINT_BYTES * 8)

typedef unsigned char byte;

static const byte BYTE_MIN = 0b00000000;
static const byte BYTE_MAX = 0b11111111;
static const int BYTE_RADIX = 256;

struct mint
{
    bool positive;
    byte data[MINT_BYTES];
};
typedef struct mint mint;

// Initialization Functions
mint newm();

// Conversation Functions

mint ll2m(long long ll);
long long m2ll(mint m);
mint i2m(int i);
int m2i(mint m);

// Bitwise Functions
bool get_bit(mint m, int i);
mint set_bit(mint m, int i, bool bit);
mint left_shift(mint m, int index);
mint right_shift(mint m, int index);

// Comparing Functions
bool eq(mint a, mint b);
bool gt(mint a, mint b);
bool lt(mint a, mint b);

// Basic Math Funcions
mint summ(mint a, mint b);
mint subm(mint a, mint b);
mint muli(mint a, int b);
mint mulm(mint a, mint b);
mint divm(mint n, mint d);

#endif