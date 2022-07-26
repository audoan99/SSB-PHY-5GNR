#include "nr5gPhyPayloadGeneration.h"
#include "nr5gPhyLog.h"

/*!
 * This lookup table is used by PBCH payload Interleaver.
*/
const int32 pbchPayloadTable[32] = {16, 23 , 18, 17, 8,  30, 10, 6,
                                    24, 7,   0,  5,  3,  2,  1,  4,
                                    9,  11,  12, 13, 14, 15, 19, 20,
                                    21, 22,  25, 26, 27, 28, 29, 31 };

uint16 inputInterleave[INPUT_LENGTH + 8] = {0};
uint8_t outputInterleave[INPUT_LENGTH + 8] = {0};
uint16 nr5gPhyAddbitsIndex[8] = {0};
uint16 nr5gPhyAddbitsPayload[8] = {0};

void nr5gPhyGeneratePbch(const uint16* inputSequence, const uint16 * sfnSequence, const uint16 hrf, const uint16 * ssbIndexSequence, const uint16 kssb, const uint16 Lmax)
{
    //data
    for(uint16 i = 0; i < 24; i++)
    {
        inputInterleave[i] = inputSequence[i];
    }

    //sfn sequence
    for(uint16 i = 0; i < 4; i++)
    {
        inputInterleave[INPUT_LENGTH + i] = sfnSequence[i];
    }

    //hrf
    inputInterleave[INPUT_LENGTH + 4] = hrf;

    //ssb sequence or kssb
    if(Lmax == 64)
    {
        for(uint16 i = 0; i < 3; i++)
        {
            inputInterleave[INPUT_LENGTH + i + 5] = ssbIndexSequence[i];
        }
    }
    else
    {
        inputInterleave[INPUT_LENGTH + 5] = kssb;
    }

    fprintf(flog, "\n======> Interleave Input sequence: 32\n");
    for(int i =0; i < 32; i++)
    {
        fprintf(flog, "%d", inputInterleave[i]);
    }

    //interleave
    nr5gPhyInterleave(inputInterleave, Lmax);
    
}

void nr5gPhyInterleave(uint16* inputInterleave, const uint16 Lmax)
{
    uint32 inputLengthInterleave = INPUT_LENGTH + 8;
    uint32 j_FSN = 0;
    uint32 j_HRF = 10;
    uint32 j_SSB = 11;
    uint32 j_other = 14;
    
    for(int16 index = 0; index < inputLengthInterleave; index++)
    {
        if((index >= (INPUT_LENGTH) && index <= (INPUT_LENGTH + 3)) || (index >= 1 && index <= 6)) // 4 bits LSB of SFN + 6 bits SFN of INPUT
        {
            outputInterleave[(pbchPayloadTable[j_FSN])] = inputInterleave[index];

            if(index >= (INPUT_LENGTH) && index <= (INPUT_LENGTH + 3))
            {
                nr5gPhyAddbitsIndex[index-24] = pbchPayloadTable[j_FSN];
                nr5gPhyAddbitsPayload[index-24] = inputInterleave[index];
            }
            j_FSN++;
        }
        else if(index == (INPUT_LENGTH + 4)) // 1 bit of HRF
        {
            outputInterleave[(pbchPayloadTable[j_HRF])] = inputInterleave[index];
            nr5gPhyAddbitsIndex[index-24] = pbchPayloadTable[j_HRF];
            nr5gPhyAddbitsPayload[index-24] = inputInterleave[index];
        }
        else if(index >= (INPUT_LENGTH + 5) && index <= (INPUT_LENGTH + 7)) //3 bits of SSB
        {
            outputInterleave[(pbchPayloadTable[j_SSB])] = inputInterleave[index];
            if(Lmax == 64)
            {
                nr5gPhyAddbitsIndex[index-24] = pbchPayloadTable[j_SSB];
                nr5gPhyAddbitsPayload[index-24] = inputInterleave[index];
            }
            j_SSB++;
        }
        else //Bits Data
        {
            outputInterleave[(pbchPayloadTable[j_other])] = inputInterleave[index];
            j_other++;
        }
    }

    //print Interleace sequence
    fprintf(flog, "\n======> Interleave Output sequence: 32\n");

    for(int16 index = 0; index < inputLengthInterleave; index++)
    {
        fprintf(flog, "%d", outputInterleave[index]);
    }
}