#include "nr5gPhyRateMatching.h"

uint8_t f[NR_POLAR_PBCH_E] = {0};

void nr5gPhyRateMatching()
{
    uint8_t y[512] = {0};

    //Sub-block Interleaving: d_N -> y_N
    nr5gPhySubBlockInterleaving(y, nr5gPhyPolarSubblockInterleaverPattern, NR_POLAR_K_LENGTH, N, NR_POLAR_PBCH_E);
    
    //Bit selection
    uint8_t e[NR_POLAR_PBCH_E] = {0};
    nr5gPhyBitSelection(y, e, NR_POLAR_K_LENGTH, N, NR_POLAR_PBCH_E);

    //Interleaving
    nr5gPhyInterleavingOfCodedBits(e, f, NR_POLAR_PBCH_I_BIL, NR_POLAR_PBCH_E);
    fprintf(flog, "\n======> Ratematching Output sequence: 864\n");
    for(int n = 0; n < NR_POLAR_PBCH_E; n++)
    {
        fprintf(flog, "%d", f[n]);
    }
}

void nr5gPhySubBlockInterleaving(uint8_t *y, const uint8_t *P_i_, uint16_t K, uint16_t N, uint16_t E)
{
    uint8_t i;
    uint16_t *J;

    J = (uint16_t *)malloc(sizeof(uint16_t) * N);

    for (int n = 0; n <= N-1; n++)
    {
        i = floor((32*n)/N);
        J[n] = (P_i_[i]*(N/32)) + (n%(N/32));
        y[n] = outputPolarEncode[J[n]];
    }
    
    free(J);
}

void nr5gPhyBitSelection(uint8_t *y, uint8_t *e, uint16_t K, uint16_t N, uint16_t E)
{
    if(E >= N) //repetition
    {
        for(int k = 0; k <= E-1 ; k++)
        {
            e[k] = y[(k%N)];
        }
    }
    else
    {
        if((K / (double) E) <= (7.0 / 16)) //puncturing
        {
            for(int k = 0; k <= E-1 ; k++)
            {
                e[k] = y[(k + N - E)];
            }
        }
        else //shortening
        {
            for(int k = 0; k <= E-1 ; k++)
            {
                e[k] = y[k];
            }
        }
    }
}
void nr5gPhyInterleavingOfCodedBits(uint8_t *e, uint8_t *f, uint16_t I_BIL, uint16_t E)
{
    if(I_BIL == 1)
    {
        /*
        */
    }
    else
    {
        for(int i = 0; i <= E - 1; i++)
        {
            f[i] = e[i];
        }
    }
}