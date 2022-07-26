#include "nr5gPhyResourceElementMapping.h"

//Mapping to Resource grid
StrIComplex16 subFrameFreDataOutGuard[NR_5G_MAX_ANT][NR_5G_SYMBOLS_PER_SLOT * NR_5G_MAX_NUM_RE_PER_SYMBOL] = {0};

//Mapping SS Block to grid for each slot
StrIComplex16 ssbPayloadScratch[NR5G_PBCH_SSBMAX][NR5G_PBCH_SSB_SYMBOL_LEN][NR5G_PBCH_SSB_RE_LEN] = {0};

void nr5gPhyMapping1st(int ssbIdxOfslot)
{
    int32 v;
    int32 count;

    //Find v = N_cell_id mod 4;
    v = nr5gPhyAttributeSyncSignal.N_cell_id % 4;

    //Mapping PSS Sequence
    for(int32 SSBReLen = 56; SSBReLen <= 182; SSBReLen++)
    {
        ssbPayloadScratch[ssbIdxOfslot][0][SSBReLen].re = nr5gPhySyncSignal[SSBReLen-56].pssSequence * 8192; // 2^13 = 8192
    }

    //Mapping SSS Sequence
    for(int32 SSBReLen = 56; SSBReLen <= 182; SSBReLen++)
    {
        ssbPayloadScratch[ssbIdxOfslot][2][SSBReLen].re = nr5gPhySyncSignal[SSBReLen-56].sssSequence * 8192; // 2^13 = 8192
    }

    //Mapping DMRS Sequence and Mapping PBCH and DMRS
    int countPBCH = 0; 
    int countDMRS = 0;
    int status = 0;

    for(int32 SSBReLen1 = 0; SSBReLen1 <= 239; SSBReLen1++)
    {
        // +) Mapping 60 elements of DMRS on OFDM symbol 1
        // +) Mapping 180 elements of PBCH on OFDM symbol 1
        for(int16 SSBReLen2 = 0 + v; SSBReLen2 <= 236 + v; SSBReLen2 +=4)
        {
            if(SSBReLen1 == SSBReLen2)
            {
                status = 1;
                ssbPayloadScratch[ssbIdxOfslot][1][SSBReLen1].re = nr5gPhyDmrsOfSSB[countDMRS].re;
                ssbPayloadScratch[ssbIdxOfslot][1][SSBReLen1].im = nr5gPhyDmrsOfSSB[countDMRS].im;
                countDMRS++; //count = 60
                break;
            }
        }

        if(status == 0)
        {
            ssbPayloadScratch[ssbIdxOfslot][1][SSBReLen1].re = output[countPBCH].re;
            ssbPayloadScratch[ssbIdxOfslot][1][SSBReLen1].im = output[countPBCH].im;
            countPBCH++; //count = 180
        }

        status = 0;
    }

    for(int32 SSBReLen1 = 0; SSBReLen1 <= 47; SSBReLen1++)
    {
        // +) Mapping 12 elements of DMRS on OFDM symbol 2
        // +) Mapping 36 elements of PBCH on OFDM symbol 2
        for(int16 SSBReLen2 = 0 + v; SSBReLen2 <= 44 + v; SSBReLen2 +=4)
        {
            if(SSBReLen1 == SSBReLen2)
            {
                status = 1;
                ssbPayloadScratch[ssbIdxOfslot][2][SSBReLen1].re = nr5gPhyDmrsOfSSB[countDMRS].re;
                ssbPayloadScratch[ssbIdxOfslot][2][SSBReLen1].im = nr5gPhyDmrsOfSSB[countDMRS].im;
                countDMRS++; //count = 72
                break;
            }
        }

        if(status == 0)
        {
            ssbPayloadScratch[ssbIdxOfslot][2][SSBReLen1].re = output[countPBCH].re;
            ssbPayloadScratch[ssbIdxOfslot][2][SSBReLen1].im = output[countPBCH].im;
            countPBCH++; //count = 216
        }

        status = 0;
    }

    for(int32 SSBReLen1 = 192; SSBReLen1 <= 239; SSBReLen1++)
    {
        // +) Mapping 12 elements of DMRS on OFDM symbol 2
        // +) Mapping 36 elements of PBCH on OFDM symbol 2
        for(int16 SSBReLen2 = 192 + v; SSBReLen2 <= 236 + v; SSBReLen2 +=4)
        {
            if(SSBReLen1 == SSBReLen2)
            {
                status = 1;
                ssbPayloadScratch[ssbIdxOfslot][2][SSBReLen1].re = nr5gPhyDmrsOfSSB[countDMRS].re;
                ssbPayloadScratch[ssbIdxOfslot][2][SSBReLen1].im = nr5gPhyDmrsOfSSB[countDMRS].im;
                countDMRS++; //count = 84
                break;
            }
        }

        if(status == 0)
        {
            ssbPayloadScratch[ssbIdxOfslot][2][SSBReLen1].re = output[countPBCH].re;
            ssbPayloadScratch[ssbIdxOfslot][2][SSBReLen1].im = output[countPBCH].im;
            countPBCH++; //count = 252
        }

        status = 0;
    }

    for(int32 SSBReLen1 = 0; SSBReLen1 <= 239; SSBReLen1++)
    {
        // +) Mapping 60 elements of DMRS on OFDM symbol 2
        // +) Mapping 180 elements of PBCH on OFDM symbol 2
        for(int16 SSBReLen2 = 0 + v; SSBReLen2 <= 236 + v; SSBReLen2 +=4)
        {
            if(SSBReLen1 == SSBReLen2)
            {
                status = 1;
                ssbPayloadScratch[ssbIdxOfslot][3][SSBReLen1].re = nr5gPhyDmrsOfSSB[countDMRS].re;
                ssbPayloadScratch[ssbIdxOfslot][3][SSBReLen1].im = nr5gPhyDmrsOfSSB[countDMRS].im;
                countDMRS++; //count = 144
                break;
            }
        }
        
        if(status == 0)
        {
            ssbPayloadScratch[ssbIdxOfslot][3][SSBReLen1].re = output[countPBCH].re;
            ssbPayloadScratch[ssbIdxOfslot][3][SSBReLen1].im = output[countPBCH].im;
            countPBCH++; //count = 432
        }

        status = 0;
    }

    fprintf(flog, "\n======> SSSB Payload 144, PBCH 432\n");

    for(int i = 0; i < NR5G_PBCH_SSB_RE_LEN; i++)
    {
        for(int j = 0; j < NR5G_PBCH_SSB_SYMBOL_LEN; j++)
        {
            if(j == 0)
            {
                fprintf(flog,"     %5d", ssbPayloadScratch[ssbIdxOfslot][j][i].re);
                fprintf(flog,"  %5d", ssbPayloadScratch[ssbIdxOfslot][j][i].im);
            }
            else
            {
                fprintf(flog," |  %5d", ssbPayloadScratch[ssbIdxOfslot][j][i].re);
                fprintf(flog,"  %5d", ssbPayloadScratch[ssbIdxOfslot][j][i].im);
            }
        }
        fprintf(flog, "\n");
    }
}

void nr5gPhyMapping2nd(int Lmax, int OFDMSymboln, uint16 subcarrierSpacing, int ssbBlockIndex, uint16 ssbOffsetPointA, uint16 ssbSubcarrierOffset)
{
    //NULL
    for(int i = 0; i < NR_5G_MAX_ANT; i++)
    {
        for(int j = 0; j < (NR_5G_SYMBOLS_PER_SLOT * NR_5G_MAX_NUM_RE_PER_SYMBOL); j++)
        {
            subFrameFreDataOutGuard[i][j].re = 0;
            subFrameFreDataOutGuard[i][j].im = 0;
        }
    }

    //Case 1 antenna
    int k = 0;

    if(subcarrierSpacing == 15) 
    {
        //Case A
        k = (ssbOffsetPointA * 12) + ssbSubcarrierOffset;
        if(Lmax == 4) // OFDM symbol: 2,8,16,22
        {
            if(ssbBlockIndex == 2)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((2 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((2 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((8 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((8 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
            if(ssbBlockIndex == 4)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((16 - 14 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((16 - 14 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((22 - 14 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((22 - 14 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
        }
        else if(Lmax == 8) // OFDM symbol: 2,8,16,22,30,36,44,50
        {
            if(ssbBlockIndex == 2)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((2 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((2 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((8 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((8 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
            if(ssbBlockIndex == 4)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((16 - 14 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((16 - 14 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((22 - 14 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((22 - 14 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
            if(ssbBlockIndex == 6)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((30 - 14*2 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((30 - 14*2 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((36 - 14*2 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((36 - 14*2 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
            if(ssbBlockIndex == 8)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((44 - 14*3 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((44 - 14*3 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((50 - 14*3 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((50 - 14*3 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
        }
        else
        {
            //N/A;
        }
    }
    else if(subcarrierSpacing == 30 && OFDMSymboln == 28)
    {
        //Case B
        k = (ssbOffsetPointA * 12)/2 + ssbSubcarrierOffset;

        if(Lmax == 4) // OFDM symbol: 4,8,16,20
        {
            if(ssbBlockIndex == 2)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((4 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((4 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((8 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((8 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
            if(ssbBlockIndex == 4)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((16 - 14 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((16 - 14 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((20 - 14 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((20 - 14 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
        }
        else if(Lmax == 8) //OFDM symbol: 4,8,16,20,32,36,44,48
        {
            if(ssbBlockIndex == 2)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((4 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((4 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((8 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((8 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
            if(ssbBlockIndex == 4)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((16 - 14 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((16 - 14 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((20 - 14 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((20 - 14 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
            if(ssbBlockIndex == 6)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((32 - 14*2 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((32 - 14*2 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((36 - 14*2 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((36 - 14*2 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
            if(ssbBlockIndex == 8)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((44 - 14*3 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((44 - 14*3 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((48 - 14*3 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((48 - 14*3 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
        }
        else
        {
            //N/A;
        }
    }
    else if(subcarrierSpacing == 30 && OFDMSymboln == 14)
    {
        //Case C
        k = (ssbOffsetPointA * 12)/2 + ssbSubcarrierOffset;

        if(Lmax == 4) // OFDM symbol: 2,8,16,22
        {
            if(ssbBlockIndex == 2)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((2 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((2 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((8 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((8 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
            if(ssbBlockIndex == 4)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((16 - 14 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((16 - 14 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((22 - 14 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((22 - 14 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
        }
        else if(Lmax == 8) // OFDM symbol: 2,8,16,22,30,36,44,50
        {
            if(ssbBlockIndex == 2)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((2 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((2 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((8 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((8 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
            if(ssbBlockIndex == 4)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((16 - 14 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((16 - 14 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((22 - 14 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((22 - 14 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
            if(ssbBlockIndex == 6)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((30 - 14*2 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((30 - 14*2 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((36 - 14*2 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((36 - 14*2 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
            if(ssbBlockIndex == 8)
            {
                for(int m = 0; m < 4; m++)
                {
                    for(int n = 0; n < 240; n++)
                    {
                        subFrameFreDataOutGuard[0][(((44 - 14*3 + m) * 4096) + k + n)].re = ssbPayloadScratch[0][m][n].re;
                        subFrameFreDataOutGuard[0][(((44 - 14*3 + m) * 4096) + k + n)].im = ssbPayloadScratch[0][m][n].im;
                        subFrameFreDataOutGuard[0][(((50 - 14*3 + m) * 4096) + k + n)].re = ssbPayloadScratch[1][m][n].re;
                        subFrameFreDataOutGuard[0][(((50 - 14*3 + m) * 4096) + k + n)].im = ssbPayloadScratch[1][m][n].im;
                    }
                }
            }
        }
        else
        {
            //N/A;
        }
    }

    fprintf(flog, "\n======> Frequency Payload\n");
    for(int j = 0; j < NR_5G_MAX_NUM_RE_PER_SYMBOL; j++)
    {
        fprintf(flog, "%6d ", j);
        for(int i = 0; i < NR_5G_SYMBOLS_PER_SLOT + 1; i++)
        {
            fprintf(flog, "|     %6d", subFrameFreDataOutGuard[0][(i * 4096) + j].re);
            fprintf(flog, "  %6d", subFrameFreDataOutGuard[0][(i * 4096) + j].im);
        }
        fprintf(flog, "\n");
    }
}