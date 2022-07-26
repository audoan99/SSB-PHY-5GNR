#include "nr5gPhyScrambling.h"
#include "nr5gPhySyncSignal.h"
#include "nr5gPhyRateMatching.h"

#define NR_5H_PBCH_CN_SCRAMBLING_BIT_LENGTH 				864 // c(j+v*M)
#define NR_5H_PBCH_CN_SCRAMBLING_BYTE_LENGTH                108 //120/8bit

uint8_t outputScrambling[32];
uint8_t outputScrambling2nd[864];

void nr5gPhyScrambling(const uint16 Lmax, uint16 index, int16 SSBidx)
{
    int16 j = 0;
    int16 v = 0;
    int16 byteLength = 0;
    int16 bitLength = 0;

    uint8_t outputCnByte[NR_5H_PBCH_CN_SCRAMBLING_BYTE_LENGTH * 8] = {0};
    uint8_t outputCnBit[NR_5H_PBCH_CN_SCRAMBLING_BIT_LENGTH * 8] = {0}; // The number of bit = 36 * 8 = 288 bit;

    //Find v;
    if(nr5gPhyAddbitsPayload[2] == 0 && nr5gPhyAddbitsPayload[1] == 0)
    {
        v = 0;
    }
    if(nr5gPhyAddbitsPayload[2] == 0 && nr5gPhyAddbitsPayload[1] == 1)
    {
        v = 1;
    }
    if(nr5gPhyAddbitsPayload[2] == 1 && nr5gPhyAddbitsPayload[1] == 0)
    {
        v = 2;
    }
    if(nr5gPhyAddbitsPayload[2] == 1 && nr5gPhyAddbitsPayload[1] == 0)
    {
        v = 3;
    }

    //Find C(n) with C_init = N_cell_id
    nr5gPhyPrsProc(nr5gPhyAttributeSyncSignal.N_cell_id, NR_5H_PBCH_CN_SCRAMBLING_BIT_LENGTH * 8, CN_PRS_BITS_ORDER_REVERSED, outputCnByte); //C_init = N_cell_id

    for(int16 i = 0; i < NR_5H_PBCH_CN_SCRAMBLING_BYTE_LENGTH * 8; i++) //108 Bytes * Lmax
    {
        for(int16 m = 0; m < 8; m++) //864 bits * Lmax
        {
            outputCnBit[((i*8)+7-m)] = (outputCnByte[i] >> m) & 0x01;
        }
    }

    //Find S(i) and Scrambling
    if(index == 1) //scrambling 1st
    {
        fprintf(flog, "\n======> Scramble Output sequence: 32\n");

        if(Lmax == 64)
        {
            for(int16 i = 0; i < 32; i++)
            {
                if(i == nr5gPhyAddbitsIndex[1] || i == nr5gPhyAddbitsIndex[2] || i == nr5gPhyAddbitsIndex[4] || i == nr5gPhyAddbitsIndex[5] || i == nr5gPhyAddbitsIndex[6] || i == nr5gPhyAddbitsIndex[7])
                {
                    outputScrambling[i] = (outputInterleave[i] + 0) % 2; //S_i = 0;
                    fprintf(flog, "%d", outputScrambling[i]);
                }
                else
                {
                    outputScrambling[i] = (outputInterleave[i] + outputCnBit[j + v * (32-3)]) % 2; //S_i = C(j + v*M) with M = A - 3 where Lmax = 4 or Lmax =8;
                    fprintf(flog, "%d", outputScrambling[i]);
                    j++; 
                }
            }
        }
        else
        {
            for(int16 i = 0; i < 32; i++)
            {
                if(i == nr5gPhyAddbitsIndex[1] || i == nr5gPhyAddbitsIndex[2] || i == nr5gPhyAddbitsIndex[4])
                {
                    outputScrambling[i] = (outputInterleave[i] + 0) % 2; //S_i = 0;
                    fprintf(flog, "%d", outputScrambling[i]);
                }
                else
                {
                    outputScrambling[i] = (outputInterleave[i] + outputCnBit[j + v * (32-3)]) % 2; //S_i = C(j + v*M) with M = A - 3 where Lmax = 4 or Lmax =8;
                    fprintf(flog, "%d", outputScrambling[i]);
                    j++; 
                }
            }
        }
    }
    else //scrambling 2nd
    {   

        fprintf(flog, "\nPRS for scrambling 2:\n");
        for(int i = 0; i < (NR_5H_PBCH_CN_SCRAMBLING_BIT_LENGTH * Lmax); i++)
        {
            fprintf(flog, "%d", outputCnBit[i]);
        }

        fprintf(flog, "\n======> 2nd Scramble Output sequence: 864 with SSB index is %d\n", SSBidx);

        for(int16 i = 0; i < NR_POLAR_PBCH_E; i++)
        {
            outputScrambling2nd[i] = (f[i] + outputCnBit[(i + SSBidx*NR_POLAR_PBCH_E)]) % 2; //b~_i = (b(i) + c(i+ v*M_bit))mod2;
            fprintf(flog, "%d", outputScrambling2nd[i]);
        }
    }
}