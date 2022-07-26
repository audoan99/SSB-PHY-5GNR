#ifndef __NR_5G_PHY_POLAR_ENCODING_H__
#define __NR_5G_PHY_POLAR_ENCODING_H__

#include "nr5gPhyCRC.h"
#include "nr5gPhyPolarDefs.h"

void nr5gPhyPolarEncode();
uint32_t nr5gPhyPolarOutputLength(uint16_t K, uint16_t E, uint8_t n_max);
void nr5gPhyPolarInterleaving(uint16_t K, uint8_t I_IL, uint8_t *output);
void nr5gPhyMatrixMultiplicationUint81DUint82D(uint8_t *matrix1, uint8_t **matrix2, uint8_t *output, uint16_t row, uint16_t col);
void nr5gPhyPolarBitInsertion(uint8_t *input, uint8_t *output, uint16_t N, uint16_t K, int16_t *Q_I_N, int16_t *Q_PC_N, uint8_t n_PC);
void nr5gPhyPolarInfoBitPattern(int16_t *Q_I_N, int16_t *Q_F_N, uint16_t *J, const uint16_t *Q_0_Nminus1, uint16_t K, uint16_t N, uint16_t E, uint8_t n_PC);
void nr5gPhyPolarRateMatchingPattern(uint16_t *J, const uint8_t *P_i_, uint16_t K, uint16_t N, uint16_t E);

extern uint8_t outputPolarEncode[512];
extern uint16_t N; //polar_code_output_length

#endif /*__NR_5G_PHY_POLAR_ENCODING_H__*/