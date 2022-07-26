#include "nr5gPhySyncSignal.h"
#include "nr5gPhyLog.h"

//Create Object of Struct nr5gPhySyncSignal_t
nr5gPhyAttributeSyncSignal_t nr5gPhyAttributeSyncSignal;
nr5gPhySyncSignal_t nr5gPhySyncSignal[127];
nr5gPhyDmrs_t nr5gPhyDmrsOfSSB[144];

/*!
 * This lookup table is used by PSS and SSS.
 */
//PSS
const int32 x[] = {0,1,1,0,1,1,1,1,0,0,1,1,1,0,0,1,0,1,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,0,1,1,1,0,1,0,0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,1,0,1,0,0,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,1,0,0,0,1,0,1,0,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,0,0,0,1};
//SSS
const int32 x0[] = {1,0,0,0,0,0,0,1,0,0,1,0,0,1,1,0,1,0,0,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,1,0,0,0,1,0,1,0,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1,1,0,1,1,1,1,0,0,1,1,1,0,0,1,0,1,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,0,1,1,1,0,1,0,0,0,1,1,0,0,1,0,0,0};
const int32 x1[] = {1,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,1,0,1,0,0,0,1,1,1,1,0,0,1,0,0,0,1,0,1,1,0,0,1,1,1,0,1,0,1,0,0,1,1,1,1,1,0,1,0,0,0,0,1,1,1,0,0,0,1,0,0,1,0,0,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1,0,1,1,0,0,0,1,1,0,1,0,0,1,0,1,1,1,0,1,1,1,0,0,1,1,0,0,1,0,1,0,1,0,1,1,1,1,1,1};

void nr5gPhyPssSequence(int32 N_2_id)
{
    // Find pss(n) = 1 -2*x(m) with 0 <= n < 127
    fprintf(flog, "\n====== PSS Bit: 127bit ======\n");
    for(int32 n = 0; n < NR_5G_PSS_LENGTH; n++)
    {
        nr5gPhySyncSignal[n].pssSequence = 1 - 2 * x[((n + 43*N_2_id) % 127)];
        fprintf(flog, "%d", nr5gPhySyncSignal[n].pssSequence);
    }
    fprintf(flog, "\n");
}

void nr5gPhySssSequence(int32 N_1_id, int32 N_2_id)
{
    // Find sss(n) = [1 - 2*x0((n+m0)mod127)]*[1 - 2*x1((n+m1)mod127)] with 0 <= n < 127
    fprintf(flog, "\n====== SSS Bit: 127bit ======\n");
    int32 m0 = 15 * (N_1_id/112) + 5 * N_2_id;
    int32 m1 = N_1_id % 112;

    for(int32 n = 0; n < NR_5G_SSS_LENGTH; n++)
    {
        nr5gPhySyncSignal[n].sssSequence = (1-2*x0[((n + m0)%127)])*(1-2*x1[((n + m1)%127)]);
        fprintf(flog, "%d", nr5gPhySyncSignal[n].sssSequence);
    }
    fprintf(flog, "\n");
}

void nr5gPhyDmRsSequence(int32 N_1_id, int32 N_2_id, int32 dlFrequency, int32 ssbBlockIndex)
{
    int32 N_cell_id;

    //Find N_cell_id = 3*N_1_id + N_2_id
    N_cell_id = 3 * N_1_id + N_2_id;
    nr5gPhyAttributeSyncSignal.N_cell_id = N_cell_id;

    int32 i_ssb;
    uint32_t cinit;
    uint8_t outputCnByte[36] = {0};
    uint8_t outputCnBit[288] = {0}; // The number of bit = 36 * 8 = 288 bit;
    
    //Find i_ssb = i_ssb + 4*n_hf
    i_ssb = ssbBlockIndex + 4*0; // n_hr of first half frame is 0

    //Find Cinit = 2^11 * (i_ssb + 1) * ((N_cell_id/4) + 1) + 2^6 * (i_ssb + 1) + N_cell_id mod 4
    cinit = pow(2,11)*(i_ssb + 1)*((N_cell_id/4) + 1) + pow(2,6)*(i_ssb + 1) + (N_cell_id % 4);

    //Find C(n) sequence
    nr5gPhyPrsProc(cinit, NR_5G_PBCH_DMRS_CN_LENGTH, CN_PRS_BITS_ORDER_REVERSED, outputCnByte);
    for(int16 i = 0; i < 36; i++)
    {
        for(int16 j = 0; j < 8; j++)
        {
            outputCnBit[((i*8)+7-j)] = (outputCnByte[i] >> j) & 0x01;
        }
    }

    //Print C(n) sequence
    fprintf(flog, "\n====== C(n) sequence: 288bit ======\n");
    for(int16 i =0; i < 288; i++)
    {
        fprintf(flog, "%d", outputCnBit[i]);
    }
    fprintf(flog, "\n");

    //Find R(m) = (1/sqrt(2))*(1-2*c(2m)) + j*(1/sqrt(2))*(1-2*c(2m+1)) with 0 < m < 144
    for(int16 i = 0; i < 144; i++)
    {
        if(outputCnBit[2*i] == 0 && outputCnBit[2*i +1] == 0)
        {
            nr5gPhyDmrsOfSSB[i].re = 5792; // (1/sqrt(2)) = 0.70710678118 ==> x2^13 ~ 5792
            nr5gPhyDmrsOfSSB[i].im = 5792;
        }
        else if(outputCnBit[2*i] == 0 && outputCnBit[2*i +1] == 1)
        {
            nr5gPhyDmrsOfSSB[i].re = 5792; // (1/sqrt(2)) = 0.70710678118 ==> x2^13 ~ 5792
            nr5gPhyDmrsOfSSB[i].im = -5792;
        }
        else if(outputCnBit[2*i] == 1 && outputCnBit[2*i +1] == 0)
        {
            nr5gPhyDmrsOfSSB[i].re = -5792; // (1/sqrt(2)) = 0.70710678118 ==> x2^13 ~ 5792
            nr5gPhyDmrsOfSSB[i].im = 5792;
        }
        else
        {
            nr5gPhyDmrsOfSSB[i].re = -5792; // (1/sqrt(2)) = 0.70710678118 ==> x2^13 ~ 5792
            nr5gPhyDmrsOfSSB[i].im = -5792;
        }
    }
}