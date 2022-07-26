#include "nr5gPhyModulation.h"

const int modQPSK_re[4] = { 5792, 5792, -5792, -5792 };
const int modQPSK_im[4] = { 5792, -5792, 5792, -5792 };

IQComplex output[NR_POLAR_PBCH_E/2];

void nr5gPhyModulation()
{
    fprintf(flog, "\n======> Modulation Output sequence: 432\n");

    //QPSK
    modulationConvert(outputScrambling2nd, output);
}

void modulationConvert(uint8_t* input, IQComplex* output)
{
	for (int idx = 0; idx < NR_POLAR_PBCH_E/2; idx++)
	{
        //QPSK modulation 2 bit/1 symbol
        if(input[(idx*2)] == 0 && input[((idx*2) + 1)] == 0)
        {
            output[idx].re = modQPSK_re[0];
		    output[idx].im = modQPSK_im[0];
		    fprintf(flog, "%d %d\n", output[idx].re,output[idx].im);
        }
        else if(input[(idx*2)] == 0 && input[((idx*2) + 1)] == 1)
        {
            output[idx].re = modQPSK_re[1];
		    output[idx].im = modQPSK_im[1];
		    fprintf(flog, "%d %d\n", output[idx].re,output[idx].im);
        }
        else if(input[(idx*2)] == 1 && input[((idx*2) + 1)] == 0)
        {
            output[idx].re = modQPSK_re[2];
		    output[idx].im = modQPSK_im[2];
		    fprintf(flog, "%d %d\n", output[idx].re,output[idx].im);            
        }
        else
        {
            output[idx].re = modQPSK_re[3];
		    output[idx].im = modQPSK_im[3];
		    fprintf(flog, "%d %d\n", output[idx].re,output[idx].im);
        }
	}
}

// void modulationGenerator()
// {
// 	int i = 0, j = 0;
// 	unsigned int bit[2];
// 	IQComplex out[4];

// 	for (i = 0; i < 4; i++)
// 	{
// //		memset()
// 		for (j = 0; j < 2; j++)
// 		{
// 			bit[j] = (i >> j) & 0x1;
// 		}
// 		out[i].re = 5792 * (1 - 2 * bit[1]);
// 		out[i].im = 5792 * (1 - 2 * bit[0]);
// 	}

// 	for (i = 0; i < 4; i++)
// 	{
// 		printf("%d, ", out[i].re);
// 	}
// 	printf("\n");
// 	for (i = 0; i < 4; i++)
// 	{
// 		printf("%d, ", out[i].im);
// 	}
// 	printf("\n");
// }