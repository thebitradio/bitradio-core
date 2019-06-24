//
//  BRChainParams.h
//
//  Created by Aaron Voisine on 1/10/18.
//  Copyright (c) 2019 breadwallet LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#ifndef BRChainParams_h
#define BRChainParams_h

#include "BRMerkleBlock.h"
#include <assert.h>

typedef struct {
    uint32_t height;
    UInt256 hash;
    uint32_t timestamp;
    uint32_t target;
} BRCheckPoint;

typedef struct {
    const char * const *dnsSeeds; // NULL terminated array of dns seeds
    uint16_t standardPort;
    uint32_t magicNumber;
    uint64_t services;
    int (*verifyDifficulty)(const BRMerkleBlock *block, const BRMerkleBlock *previous, uint32_t transitionTime);
    const BRCheckPoint *checkpoints;
    size_t checkpointsCount;
} BRChainParams;

static const char *BRMainNetDNSSeeds[] = {
	"seed1.bitrad.io",
	"seed2.bitrad.io",
	"seed3.bitrad.io",
    NULL
};

static const char *BRTestNetDNSSeeds[] = {
    "seed1.bitrad.io",
	"seed2.bitrad.io",
	"seed3.bitrad.io",
    NULL
};

// blockchain checkpoints - these are also used as starting points for partial chain downloads, so they must be at
// difficulty transition boundaries in order to verify the block difficulty at the immediately following transition
static const BRCheckPoint BRMainNetCheckpoints[] = {
    //{          0, uint256("000000b908cffc5d22993b936e81deda15a5b7b566a80f3972df4d5c1e5b8c7d"), 1557523857, 0x1e0fffff},
    //{        100, uint256("00000044a2162047fd8b47eb2b391be35c20777f88499639d739df4176c12a61"), 1558170091, 0x1e00f94e},
    //{        500, uint256("1ddd9bea2c5e23d315b8da3f6ff54c9b334d944aa229d9a0b8523094876ae322"), 1558219622, 0x1d493c2c},
    {       1000, uint256("7d552267bf56c85c9e49c47422ad0b311c76505a5239daa4ef14fff3a4b4cad3"), 1558273768, 0x1c16913d},
    {       5000, uint256("68111ad601c0c9494ea132434d7998497e2131b65e16eddc8e763fae6c2c9394"), 1558769875, 0x1b05c33a},
    {      10000, uint256("cdf2f806b0ba8a247db06cb04859a00ee7be451ff7469e04a4803a3e805ca346"), 1559395315, 0x1b05721f},
    {      15000, uint256("dab18b0b7e09e739676940a4d747f4908294f61f37c893ef8ddcf96d05a58874"), 1560019596, 0x1b020bea},
    {      17000, uint256("682e301f77fc3f0eea62d1a25b4f491d5cb307847c80468734655078b15bd11e"), 1560272290, 0x1b034066}
};

static const BRCheckPoint BRTestNetCheckpoints[] = {
    //{          0, uint256("000000b908cffc5d22993b936e81deda15a5b7b566a80f3972df4d5c1e5b8c7d"), 1557523857, 0x1e0fffff},
    //{        100, uint256("00000044a2162047fd8b47eb2b391be35c20777f88499639d739df4176c12a61"), 1558170091, 0x1e00f94e},
    //{        500, uint256("1ddd9bea2c5e23d315b8da3f6ff54c9b334d944aa229d9a0b8523094876ae322"), 1558219622, 0x1d493c2c},
    {       1000, uint256("7d552267bf56c85c9e49c47422ad0b311c76505a5239daa4ef14fff3a4b4cad3"), 1558273768, 0x1c16913d},
    {       5000, uint256("68111ad601c0c9494ea132434d7998497e2131b65e16eddc8e763fae6c2c9394"), 1558769875, 0x1b05c33a},
    {      10000, uint256("cdf2f806b0ba8a247db06cb04859a00ee7be451ff7469e04a4803a3e805ca346"), 1559395315, 0x1b05721f},
    {      15000, uint256("dab18b0b7e09e739676940a4d747f4908294f61f37c893ef8ddcf96d05a58874"), 1560019596, 0x1b020bea},
    {      17000, uint256("682e301f77fc3f0eea62d1a25b4f491d5cb307847c80468734655078b15bd11e"), 1560272290, 0x1b034066}
};

static int BRTestNetVerifyDifficulty(const BRMerkleBlock *block, const BRMerkleBlock *previous, uint32_t transitionTime)
{
    int r = 1;
    
    assert(block != NULL);
    
    if (! previous || !UInt256Eq(block->prevBlock, previous->blockHash) || block->height != previous->height + 1)
        r = 0;
    
    return r;
}

static const BRChainParams BRMainNetParams = {
    BRMainNetDNSSeeds,
    33455,       // standardPort
    0xe43d1ad3, // magicNumber
    0,          // services
    BRMerkleBlockVerifyDifficulty,
    BRMainNetCheckpoints,
    sizeof(BRMainNetCheckpoints)/sizeof(*BRMainNetCheckpoints)
};

static const BRChainParams BRTestNetParams = {
    BRTestNetDNSSeeds,
    33455,      // standardPort
    0xe43d1ad3, // magicNumber
    0,          // services
    BRTestNetVerifyDifficulty,
    BRTestNetCheckpoints,
    sizeof(BRTestNetCheckpoints)/sizeof(*BRTestNetCheckpoints)
};

#endif // BRChainParams_h
