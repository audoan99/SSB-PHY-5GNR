/*
 * (C) Copyright 2020 Vinsmart - VinGroup.
 *
 * Module: *****
 *
 * Author: THANGTV8
 *
 */

#ifndef CN_NR5GPHYPRS_H_
#define CN_NR5GPHYPRS_H_

#include "nr5gPhyCnInc.h"
#include "nr5gPhyTypes.h"

//! The value of first sequence registers after being shifted 1600 times, the initial value was 0x00000001
#define NR5G_PHY_PRS_SEQUENCE_1_VALUE      0x24D84B2A
//! The size of the lookup table used to calculate the value of the shift register after 1600 iterations
#define NR5G_PHY_PRS_SEQUENCE_2_MASKS_SIZE  31

typedef enum EnPrsBitsOrder
{
	CN_PRS_BITS_ORDER_NORMAL = 0, 	 //!< B7 will be stored at the MSB location while B0 will be stored at LSB
	CN_PRS_BITS_ORDER_REVERSED = 1   //!< B0 will be stored at the MSB location while B7 will be stored at LSB
} EnPrsBitsOrder;

/* Pseudo random sequence generator process function */
int nr5gPhyPrsProc(
		IN uint32_t cinit,
		IN uint32_t numOutputBits,
		IN EnPrsBitsOrder bitsOrder,
		OUT uint8_t* pOutput
		);

#endif
