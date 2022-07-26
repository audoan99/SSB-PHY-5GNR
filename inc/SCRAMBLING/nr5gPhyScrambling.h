#ifndef __NR_5G_PHY_SCRAMBLING_H__
#define __NR_5G_PHY_SCRAMBLING_H__

#include "nr5gPhyPayloadGeneration.h"

void nr5gPhyScrambling(const uint16 Lmax, uint16 index,int16 SSBidx);

extern uint8_t outputScrambling[32];
extern uint8_t outputScrambling2nd[864];

#endif /*__NR_5G_PHY_SCRAMBLING_H__*/