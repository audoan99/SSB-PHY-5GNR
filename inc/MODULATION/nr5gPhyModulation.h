#ifndef __NR_5G_PHY_MODULATION_H__
#define __NR_5G_PHY_MODULATION_H__

#include "nr5gPhyScrambling.h"
#include "nr5gPhyRateMatching.h"

typedef struct
{
	int re;
	int im;
} IQComplex;


void nr5gPhyModulation();
void modulationConvert(uint8_t* input, IQComplex* output);

extern IQComplex output[NR_POLAR_PBCH_E/2];

#endif /*__NR_5G_PHY_MODULATION_H__*/