// Copyright (c) 2013-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "brx11.h"


void BRX11(void *md32, const void *data, size_t len)

{
    sph_blake512_context     ctx_blake;
    sph_bmw512_context       ctx_bmw;
    sph_groestl512_context   ctx_groestl;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;
    sph_skein512_context     ctx_skein;
    sph_luffa512_context     ctx_luffa;
    sph_cubehash512_context  ctx_cubehash;
    sph_shavite512_context   ctx_shavite;
    sph_simd512_context      ctx_simd;
    sph_echo512_context      ctx_echo;
    static unsigned char pblank[1];

    char hash[11][80];

    sph_blake512_init(&ctx_blake);
    sph_blake512 (&ctx_blake, len == 0 ? pblank : data, len);
    sph_blake512_close(&ctx_blake, (&hash[0]));

    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, (&hash[0]), 64);
    sph_bmw512_close(&ctx_bmw, (&hash[1]));

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, (&hash[1]), 64);
    sph_groestl512_close(&ctx_groestl, (&hash[2]));

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, (&hash[2]), 64);
    sph_skein512_close(&ctx_skein, (&hash[3]));

    sph_jh512_init(&ctx_jh);
    sph_jh512 (&ctx_jh, (&hash[3]), 64);
    sph_jh512_close(&ctx_jh, (&hash[4]));

    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, (&hash[4]), 64);
    sph_keccak512_close(&ctx_keccak, (&hash[5]));

    sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, (&hash[5]), 64);
    sph_luffa512_close(&ctx_luffa, (&hash[6]));

    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, (&hash[6]), 64);
    sph_cubehash512_close(&ctx_cubehash, (&hash[7]));

    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, (&hash[7]), 64);
    sph_shavite512_close(&ctx_shavite, (&hash[8]));

    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, (&hash[8]), 64);
    sph_simd512_close(&ctx_simd, (&hash[9]));

    sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, (&hash[9]), 64);
    sph_echo512_close(&ctx_echo, (&hash[10]));

    for (unsigned int i = 0; i < 32; i++) {
        ((char *) md32)[i] = hash[10][i];
    }
}

