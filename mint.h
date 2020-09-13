#ifndef MINT_H
#define MINT_H

#define MINT_LENGTH 128

typedef unsigned char byte;
const byte BYTE_MAX = 0b11111111;
const byte BYTE_MIN = 0b00000000;
const int BYTE_DIGIT = 256;

struct mint_struct
{
    bool positive;
    byte data[MINT_LENGTH];
};

typedef struct mint_struct mint;

mint new_mint();
mint ll2m(long long ll);
long long m2ll(mint m);
mint i2m(int i);
int m2i(mint m);
bool is_zero(mint m);
bool eq(mint a, mint b);
bool gt(mint a, mint b);
bool lt(mint a, mint b);
mint sum(mint a, mint b);
mint sub(mint a, mint b);

#endif