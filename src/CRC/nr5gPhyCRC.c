#include "nr5gPhyCRC.h"

#define CRC_SEQUENCE                    24

uint8_t crcSequence[] = {1,1,0,1,1,0,0,1,0,1,0,1,1,0,0,0,1,0,0,0,1,0,1,1,1};
uint8_t outputCRC[56] = {0};

void nr5gPhyCRC()
{
    uint8_t inputCRC[56] = {0};
    uint16 status = 1;

    //Get InputCRC
    for(uint16 i = 0; i < 32; i++)
    {
        inputCRC[i] = outputScrambling[i];
    }

    //XOR inputCRC and crcSequence
    for(uint16 i = 0; i < CRC_SEQUENCE + 8; i++)
    {
        
        if(inputCRC[i] == 0) status = 0;
        else status = 1;

        for(uint16 j = 0; j <= CRC_SEQUENCE; j++)
        {
            
            if(status == 1)
            {
                inputCRC[j+i] ^= crcSequence[j];
            }
            else
            {
                inputCRC[j+i] ^= 0;
            }
        }
    }

    fprintf(flog, "\n======> CRC Output sequence: 56\n");
    for(uint16 i = 0; i < 56; i++)
    {
        if(i < 32)
        {
            outputCRC[i] = outputScrambling[i];
        }
        else
        {
            outputCRC[i] = inputCRC[i];
        }

        //print
        fprintf(flog, "%d", outputCRC[i]);
    }
}