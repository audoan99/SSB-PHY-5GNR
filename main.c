/********************************************************************
*
* FILE NAME : Develop Physical Broadcast Channel
*
*
* Revision: 	DATE 			AUTHOR 			CONTENT
* 				2022-03-28 	    au.doan      	Create
*
* Copyright (c) 2022, HCL.
*
*******************************************************************/

#include "nr5gPhySyncSignal.h"
#include "nr5gPhyPayloadGeneration.h"
#include "nr5gPhyScrambling.h"
#include "nr5gPhyCRC.h"
#include "nr5gPhyPolarEncode.h"
#include "nr5gPhyRateMatching.h"
#include "nr5gPhyModulation.h"
#include "nr5gPhyResourceElementMapping.h"
#include "nr5gPhyLog.h"

const uint16 inputSequence[] = {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1};
const uint16 sfnSequence[] = {0,0,0,0};
const uint16 hrf = 0;
const uint16 ssbIndexSequence[] = {0,0,0};
const uint16 kssb = 0;
const uint16 Frequence = 3000; //3000MHz = 3GHz
const uint16 subcarrierSpacing = 30; //30KHz
const uint16 ssbOffsetPointA = 86; //15KHz
const uint16 ssbSubcarrierOffset = 0;
const int OFDMSymboln = 28;
static int ssbBlockIndex = 0;

int main()
{
    int Lmax = 0;
    
    Loginit();

    fprintf(flog, "========================================================\n");
    fprintf(flog, "INPUT:\n");
    fprintf(flog, "-) Input sequence: ");
    for(int i = 0; i < 24; i++)
    {
        fprintf(flog, "%d", inputSequence[i]);
    }
    fprintf(flog, "\n  +) sfb Sequence: ");
    for(int i = 0; i < 4; i++)
    {
        fprintf(flog, "%d", sfnSequence[i]);
    }
    fprintf(flog, "\n  +) hrf Sequence: %d", hrf);
    fprintf(flog, "\n  +) ssbIndex Sequence: %d", hrf);
    for(int i = 0; i < 3; i++)
    {
        fprintf(flog, "%d", ssbIndexSequence[i]);
    }
    fprintf(flog, "\n  +) Kssb: %d", kssb);
    fprintf(flog, "\n-) Frequence: %dMHz", Frequence);
    fprintf(flog, "\n-) subcarrierSpacing: %dKHz", subcarrierSpacing);
    fprintf(flog, "\n-) numTxAnt: %d", 1);
    fprintf(flog, "\n-) phyCellId: %d", 1);
    fprintf(flog, "\n-) ssbOffsetPointA: %d", ssbOffsetPointA);
    fprintf(flog, "\n-) ssbSubcarrierOffset : %d", ssbSubcarrierOffset);
    fprintf(flog, "\n========================================================\n");

    fprintf(flog, "\nOUTPUT:\n");
    if(Frequence <= 3000)
    {
        Lmax = 4; //Case A,B,C
    }
    else if(Frequence > 3000 && Frequence <= 6000)
    {
        Lmax = 8; //Case A,B,C
    }
    else
    {
        //Case D and E => Lmax =64
    }

    for(int i = 0; i < (Lmax/2); i++)
    {
        fprintf(flog, "\n******************** SLOT NUM %d ********************\n", i);

        for(int j = 0; j < 2; j++)
        {
            fprintf(flog, "\n*** SSBidx %d ***\n", ssbBlockIndex);

            //Sync Signal
            nr5gPhyDmRsSequence(0, 1, 1500, ssbBlockIndex);
            nr5gPhyPssSequence(1); // N_2_id = 1
            nr5gPhySssSequence(0,1); // N_1_id = 0
            /*PBCH
            */
            //Generate
            nr5gPhyGeneratePbch(inputSequence, sfnSequence, hrf, ssbIndexSequence, kssb, Lmax);
            //scrambling 1st
            nr5gPhyScrambling(Lmax, 1, ssbBlockIndex);
            //CRC
            nr5gPhyCRC();
            //Channel Coding - Polar code
            nr5gPhyPolarEncode();
            //Rate Matching
            nr5gPhyRateMatching();
            //scrambling 2nd
            nr5gPhyScrambling(Lmax, 2, ssbBlockIndex);
            //Modulation - QPSK
            nr5gPhyModulation();
            //Mapping
            nr5gPhyMapping1st(j); //MHz

            ssbBlockIndex++;
        }
        nr5gPhyMapping2nd(Lmax, OFDMSymboln, subcarrierSpacing, ssbBlockIndex,ssbOffsetPointA, ssbSubcarrierOffset);
    }

    Logstop();
    return 0;
}

