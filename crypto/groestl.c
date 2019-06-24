#include "groestl.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "sha3/sph_groestl.h"
#include "sha256.h"


// This is myriadgroestl
void groestl_hash(const char* input, char* output)
{
    uint32_t len = 80;
    char temp[64];
    
    sph_groestl512_context ctx_groestl;
    sph_groestl512_init(&ctx_groestl);
    sph_groestl512(&ctx_groestl, input, len);
    sph_groestl512_close(&ctx_groestl, &temp);
    
    SHA256_CTX ctx_sha256;
    SHA256_Init(&ctx_sha256);
    SHA256_Update(&ctx_sha256, &temp, 64);
    SHA256_Final((unsigned char*) output, &ctx_sha256);
}