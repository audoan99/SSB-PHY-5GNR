#ifndef __NR_5G_PHY_RESOURCE_ELEMENT_MAPPING_H__
#define __NR_5G_PHY_RESOURCE_ELEMENT_MAPPING_H__

#include "nr5gPhyModulation.h"
#include "nr5gPhySyncSignal.h"

void nr5gPhyMapping1st(int ssbIdxOfslot);
void nr5gPhyMapping2nd(int Lmax, int OFDMSymboln, uint16 subcarrierSpacing, int ssbBlockIndex, uint16 ssbOffsetPointA, uint16 ssbSubcarrierOffset);

#endif /*__NR_5G_PHY_RESOURCE_ELEMENT_MAPPING_H__*/