#ifndef __NR_5G_PHY_PAYLOAD_GENERATION_H__
#define __NR_5G_PHY_PAYLOAD_GENERATION_H__

#include "nr5gPhyDef.h"
#include "nr5gPhyCnInc.h"
#include "nr5gPhyStaticSysCfg.h"
#include "nr5gPhyTypes.h"
#include "nr5gPhyLog.h"

#define INPUT_LENGTH                    24

void nr5gPhyGeneratePbch(const uint16* inputSequence, const uint16 * sfnSequence, const uint16 hrf, const uint16 * ssbIndexSequence, const uint16 kssb, const uint16 Lmax);
void nr5gPhyInterleave(uint16* inputInterleave, const uint16 Lmax);

extern uint8_t outputInterleave[INPUT_LENGTH + 8];
extern uint16 nr5gPhyAddbitsIndex[8];
extern uint16 nr5gPhyAddbitsPayload[8];

#endif /*__NR_5G_PHY_PAYLOAD_GENERATION_H__*/