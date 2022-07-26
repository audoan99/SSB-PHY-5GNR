#ifndef __NR_5G_PHY_RATE_MATCHING_H__
#define __NR_5G_PHY_RATE_MATCHING_H__

#include "nr5gPhyPolarEncode.h"

void nr5gPhyRateMatching();
void nr5gPhySubBlockInterleaving(uint8_t *y, const uint8_t *P_i_, uint16_t K, uint16_t N, uint16_t E);
void nr5gPhyBitSelection(uint8_t *y, uint8_t *e, uint16_t K, uint16_t N, uint16_t E);
void nr5gPhyInterleavingOfCodedBits(uint8_t *e, uint8_t *f, uint16_t I_BIL, uint16_t E);

extern uint8_t f[NR_POLAR_PBCH_E];

#endif /*__NR_5G_PHY_RATE_MATCHING_H__*/