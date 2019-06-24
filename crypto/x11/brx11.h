// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Copyright (c) 2014-2017 The Dash Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_HASH_H
#define BITCOIN_HASH_H

#include "sph_blake.h"
#include "sph_bmw.h"
#include "sph_groestl.h"
#include "sph_jh.h"
#include "sph_keccak.h"
#include "sph_skein.h"
#include "sph_luffa.h"
#include "sph_cubehash.h"
#include "sph_shavite.h"
#include "sph_simd.h"
#include "sph_echo.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef GLOBALDEFINED
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL sph_blake512_context z_blake;
GLOBAL sph_bmw512_context z_bmw;
GLOBAL sph_groestl512_context z_groestl;
GLOBAL sph_jh512_context z_jh;
GLOBAL sph_keccak512_context z_keccak;
GLOBAL sph_skein512_context z_skein;
GLOBAL sph_luffa512_context z_luffa;
GLOBAL sph_cubehash512_context z_cubehash;
GLOBAL sph_shavite512_context z_shavite;
GLOBAL sph_simd512_context z_simd;
GLOBAL sph_echo512_context z_echo;

#define fillz() do { \
    sph_blake512_init(&z_blake); \
    sph_bmw512_init(&z_bmw); \
    sph_groestl512_init(&z_groestl); \
    sph_jh512_init(&z_jh); \
    sph_keccak512_init(&z_keccak); \
    sph_skein512_init(&z_skein); \
    sph_luffa512_init(&z_luffa); \
    sph_cubehash512_init(&z_cubehash); \
    sph_shavite512_init(&z_shavite); \
    sph_simd512_init(&z_simd); \
    sph_echo512_init(&z_echo); \
} while (0)

#define ZBLAKE (memcpy(&ctx_blake, &z_blake, sizeof(z_blake)))
#define ZBMW (memcpy(&ctx_bmw, &z_bmw, sizeof(z_bmw)))
#define ZGROESTL (memcpy(&ctx_groestl, &z_groestl, sizeof(z_groestl)))
#define ZJH (memcpy(&ctx_jh, &z_jh, sizeof(z_jh)))
#define ZKECCAK (memcpy(&ctx_keccak, &z_keccak, sizeof(z_keccak)))
#define ZSKEIN (memcpy(&ctx_skein, &z_skein, sizeof(z_skein)))


/* ----------- Dash Hash ------------------------------------------------ */
void BRX11(void *md32, const void *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif // BITCOIN_HASH_H
