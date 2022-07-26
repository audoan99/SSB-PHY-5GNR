#include "nr5gPhyPolarEncode.h"
#include "nr5gPhyKroneckerMatrix.h"
#include "nr5gPhyPolarSequencePattern.h"

//Lookup Table for Interleaving
uint8_t interleaving_pattern_table[164] = { 0, 2, 4, 7, 9, 14, 19, 20, 24, 25, 26, 28, 31, 34,
                                            42, 45, 49, 50, 51, 53, 54, 56, 58, 59, 61, 62, 65, 66,
                                            67, 69, 70, 71, 72, 76, 77, 81, 82, 83, 87, 88, 89, 91,
                                            93, 95, 98, 101, 104, 106, 108, 110, 111, 113, 115, 118, 119, 120,
                                            122, 123, 126, 127, 129, 132, 134, 138, 139, 140, 1, 3, 5, 8,
                                            10, 15, 21, 27, 29, 32, 35, 43, 46, 52, 55, 57, 60, 63,
                                            68, 73, 78, 84, 90, 92, 94, 96, 99, 102, 105, 107, 109, 112,
                                            114, 116, 121, 124, 128, 130, 133, 135, 141, 6, 11, 16, 22, 30,
                                            33, 36, 44, 47, 64, 74, 79, 85, 97, 100, 103, 117, 125, 131,
                                            136, 142, 12, 17, 23, 37, 48, 75, 80, 86, 137, 143, 13, 18,
                                            38, 144, 39, 145, 40, 146, 41, 147, 148, 149, 150, 151, 152, 153,
                                            154, 155, 156, 157, 158, 159, 160, 161, 162, 163 };

uint8_t outputPolarEncode[512] = {0};
uint8_t n;
uint16_t N; //polar_code_output_length

void nr5gPhyPolarEncode()
{
    //Find N output length
    N = nr5gPhyPolarOutputLength(NR_POLAR_K_LENGTH, NR_POLAR_PBCH_E, NR_POLAR_N_MAX);
    n = log2(N);

    //Interleaving
    uint8_t outputInterleaving[NR_POLAR_K_LENGTH];
    nr5gPhyPolarInterleaving(NR_POLAR_K_LENGTH, NR_POLAR_I_IL, outputInterleaving);

    //Find Kronecker Matrix G(n)
    uint8_t **G_N; // G_N matrix
    G_N = nr5gPhyPolarKroneckerPowerMatrices(n);

    //Find J(n) sequence
    uint16_t J[N];
    nr5gPhyPolarRateMatchingPattern(J, nr5gPhyPolarSubblockInterleaverPattern, NR_POLAR_K_LENGTH, N, NR_POLAR_PBCH_E);
    
    //Find Q_I_N
    const uint16_t *Q_0_Nminus1;

    uint8_t *nrPolarU = malloc(sizeof(uint8_t) * N); //Decoder: nr_polar_u
    int16_t *Q_I_N = malloc(sizeof(int16_t) * (NR_POLAR_K_LENGTH + NR_POLAR_N_PC));
    int16_t *Q_F_N = malloc( sizeof(int16_t) * (N + 1)); // Last element shows the final array index assigned a value.
    int16_t *Q_PC_N = malloc( sizeof(int16_t) * (NR_POLAR_N_PC));

    Q_0_Nminus1 = nr5gPhyPolarSequencePattern(n);
    
    nr5gPhyPolarInfoBitPattern(Q_I_N, Q_F_N, J, Q_0_Nminus1, NR_POLAR_K_LENGTH, N, NR_POLAR_PBCH_E, NR_POLAR_N_PC);

    //Find U(N)
    nr5gPhyPolarBitInsertion(outputInterleaving, nrPolarU, N, NR_POLAR_K_LENGTH, Q_I_N, Q_PC_N, NR_POLAR_N_PC);

    //Find d(N) = U * G_N
    nr5gPhyMatrixMultiplicationUint81DUint82D(nrPolarU, G_N, outputPolarEncode, N, N);

    fprintf(flog, "\n======> Polar Output sequence: 512\n");
    for(int i = 0; i < 512; i++)
    {
        fprintf(flog, "%d", outputPolarEncode[i]);
    }

    //Free memory
    free(Q_I_N);
    free(Q_F_N);
    free(Q_PC_N);
    free(nrPolarU);
}

uint32_t nr5gPhyPolarOutputLength(uint16_t K, uint16_t E, uint8_t n_max)
{
    uint8_t n_1;
    uint8_t n_2;
    uint8_t n_min = 5;
    uint8_t n;
  
    if ( (E <= (9.0/8)*pow(2,ceil(log2(E))-1)) && (K/E < 9.0/16) )
    {
        n_1 = ceil(log2(E))-1;
    }
    else
    {
        n_1 = ceil(log2(E));
    }
  
    double R_min = 1.0/8;

    n_2 = ceil(log2(K/R_min));

    //n = max{min{n_1, n_2, n_max}, n_min}
    n = n_max;
    if (n > n_1) n = n_1;
    if (n > n_2) n = n_2;
    if (n < n_min) n = n_min;

    return ((uint32_t) pow(2.0,n)); //=polar_code_output_length: N = 2^n
}

void nr5gPhyPolarInterleaving(uint16_t K, uint8_t I_IL, uint8_t *output)
{
    uint8_t PI_k_[NR_POLAR_K_LENGTH];
	uint8_t K_IL_max = 164;
	
	if (I_IL == 0)
    {
		for(uint8_t k = 0; k <= K-1; k++)
        {
			PI_k_[k] = k;
        }
	} 
    else
    {
        uint8_t k = 0;

		for(uint16 m = 0; m <= (K_IL_max-1); m++)
        {
			if (interleaving_pattern_table[m] >= (K_IL_max-K))
            {
				PI_k_[k] = interleaving_pattern_table[m]-(K_IL_max-K);
				k++;
			}
		}
	}

    for (int i = 0; i < K; i++)
    {
        output[i] = outputCRC[PI_k_[i]];
    }
}

void nr5gPhyPolarBitInsertion(uint8_t *input, uint8_t *output, uint16_t N, uint16_t K, int16_t *Q_I_N, int16_t *Q_PC_N, uint8_t n_PC)
{
    uint16_t k = 0;
    uint8_t flag;

    if (n_PC > 0) 
    {
        /*
        *
        */
    }
    else
    {
        for (int n = 0; n <= N-1; n++)
        {
            flag = 0;
            for (int m = 0; m <= (K+n_PC) - 1; m++)
            {
	            if (n == Q_I_N[m])
                {
	                flag = 1;
	                break;
	            }
            }
            if (flag == 1)  // n ϵ Q_I_N
            {
	            output[n] = input[k];
	            k++;
            }
            else
            {
	            output[n] = 0;
            }
        }
    }
}

void nr5gPhyPolarInfoBitPattern(int16_t *Q_I_N, int16_t *Q_F_N, uint16_t *J, const uint16_t *Q_0_Nminus1, uint16_t K, uint16_t N, uint16_t E, uint8_t n_PC)
{
    int16_t *Q_Ftmp_N = malloc(sizeof(int16_t) * (N + 1)); // Last element shows the final
    int16_t *Q_Itmp_N = malloc(sizeof(int16_t) * (N + 1)); // array index assigned a value.

    for (int i = 0; i <= N; i++) 
    {
        Q_Ftmp_N[i] = -1; // Empty array.
        Q_Itmp_N[i] = -1;
    }

    uint8_t flag;
    uint16_t limit, ind;

    if (E < N)
    {
        if ((K / (double) E) <= (7.0 / 16))  //puncturing
        {
            for (int n = 0; n <= N - E - 1; n++)
            {
                ind = Q_Ftmp_N[N] + 1;
                Q_Ftmp_N[ind] = J[n];
                Q_Ftmp_N[N] = Q_Ftmp_N[N] + 1;
            }

            if ((E / (double) N) >= (3.0 / 4))
            {
                limit = ceil((double) (3 * N - 2 * E) / 4);
                for (int n = 0; n <= limit - 1; n++)
                {
                    ind = Q_Ftmp_N[N] + 1;
                    Q_Ftmp_N[ind] = n;
                    Q_Ftmp_N[N] = Q_Ftmp_N[N] + 1;
                }
            }
            else
            {
                limit = ceil((double) (9 * N - 4 * E) / 16);
                for (int n = 0; n <= limit - 1; n++)
                {
                    ind = Q_Ftmp_N[N] + 1;
                    Q_Ftmp_N[ind] = n;
                    Q_Ftmp_N[N] = Q_Ftmp_N[N] + 1;
                }
            }
        }
        else  //shortening 
        {
            for (int n = E; n <= N - 1; n++)
            {
                ind = Q_Ftmp_N[N] + 1;
                Q_Ftmp_N[ind] = J[n];
                Q_Ftmp_N[N] = Q_Ftmp_N[N] + 1;
            }
        }
    }

    //Q_I,tmp_N = Q_0_N-1 \ Q_F,tmp_N
    for (int n = 0; n <= N - 1; n++)
    {
        flag = 1;

        for (int m = 0; m <= Q_Ftmp_N[N]; m++)
        {
            if (Q_0_Nminus1[n] == Q_Ftmp_N[m])
            {
                flag = 0;
                break;
            }
        }

        if (flag)
        {
            Q_Itmp_N[Q_Itmp_N[N] + 1] = Q_0_Nminus1[n];
            Q_Itmp_N[N]++;
        }
    }

    //Q_I_N comprises (K+n_PC) most reliable bit indices in Q_I,tmp_N
    for (int n = 0; n <= (K + n_PC) - 1; n++)
    {
        ind = Q_Itmp_N[N] + n - ((K + n_PC) - 1);
        Q_I_N[n] = Q_Itmp_N[ind];
    }

    //Q_F_N = Q_0_N-1 \ Q_I_N
    for (int n = 0; n <= N - 1; n++)
    {
        flag = 1;
        for (int m = 0; m <= (K + n_PC) - 1; m++)
        {
            if (Q_0_Nminus1[n] == Q_I_N[m])
            {
                flag = 0;
                break;
            }
        }
        
        if (flag)
        {
            Q_F_N[Q_F_N[N] + 1] = Q_0_Nminus1[n];
            Q_F_N[N]++;
        }
    }

    free(Q_Ftmp_N);
    free(Q_Itmp_N);
}

void nr5gPhyPolarRateMatchingPattern(uint16_t *J, const uint8_t *P_i_, uint16_t K, uint16_t N, uint16_t E)
{
    uint8_t i;
    uint16_t ind;

    for (int n = 0; n <= N-1; n++)
    {
        i = floor((32*n)/N);
        J[n] = (P_i_[i]*(N/32)) + (n%(N/32));
    }
}

void nr5gPhyMatrixMultiplicationUint81DUint82D(uint8_t *matrix1, uint8_t **matrix2, uint8_t *output, uint16_t row, uint16_t col)
{
	for (uint16_t i = 0; i < col; i++)
    {
		output[i] = 0;
		for (uint16_t j = 0; j < row; j++)
        {
			output[i] ^= (matrix1[j] & matrix2[j][i]);
		} 
	}
}