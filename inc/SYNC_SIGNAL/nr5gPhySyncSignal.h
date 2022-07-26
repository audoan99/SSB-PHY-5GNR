#ifndef __NR_5G_PHY_PSS_SSS_H__
#define __NR_5G_PHY_PSS_SSS_H__

#include "nr5gPhyPrs.h"
#include "nr5gPhyDef.h"
#include "nr5gPhyCnInc.h"
#include "nr5gPhyStaticSysCfg.h"

#define NR5G_PBCH_SSBMAX            2 //case B
#define NR5G_PBCH_SSB_SYMBOL_LEN    4 // The number of OFDM in SSB
#define NR5G_PBCH_SSB_RE_LEN        240 //240 subcarriers

typedef struct
{
    int32 pssSequence;
    int32 sssSequence;  
} nr5gPhySyncSignal_t;

typedef struct
{
    int32 re;
    int32 im;
} nr5gPhyDmrs_t;

typedef struct
{
    //Attributes
    int32 N_1_id_t;
    int32 N_2_id_t;
    int32 N_cell_id;

} nr5gPhyAttributeSyncSignal_t;

//Methods
void nr5gPhyPssSequence(int32 N_2_id);
void nr5gPhySssSequence(int32 N_1_id, int32 N_2_id);
void nr5gPhyDmRsSequence(int32 N_1_id, int32 N_2_id, int32 dlFrequency, int32 ssbBlockIndex);
void nr5gPhyMapping();

extern nr5gPhyAttributeSyncSignal_t nr5gPhyAttributeSyncSignal;
extern nr5gPhySyncSignal_t nr5gPhySyncSignal[127];
extern nr5gPhyDmrs_t nr5gPhyDmrsOfSSB[144];

#endif /*__NR_5G_PHY_PSS_SSS_H__*/