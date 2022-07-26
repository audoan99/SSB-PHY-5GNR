/********************************************************************
*
* FILE NAME :
*
* DESCRIPTION :
*
* FUNCTIONS:
*
* Revision: 	VERSION 			DATE 			AUTHOR 			CONTENT
* 				L1 v00.01.00 		2022-03-01 		trinh_thang 	Create
*
* Copyright (c) 2022, HCL.
*
*******************************************************************/

#ifndef NR_5G_PHY_STATIC_SYS_CFG_H_
#define NR_5G_PHY_STATIC_SYS_CFG_H_

/* ------------------------------------------------------------------------------------------ 
   -------------------------------- NR 5G define --------------------------------------------
   ---------------------------------------------------------------------------------------- */
/***************** System **************/
#define NR_5G_MAX_ANT						   2
#define NR_5G_MAX_NUM_BWP 					   4
#define NR_5G_MAX_NUM_SUBCARRIER_SPACING 	5
#define NR_5G_MAX_NB_RB 					   273
#define NR_5G_NB_SC_PER_RB 					12
#define NR_5G_NB_REG_PER_CCE 				   6
#define NR_5G_SYMBOLS_PER_SLOT 				14
#define NR_5G_SLOT_PER_SF_30k				   2
#define NR_5G_MAX_NUM_RE_PER_SYMBOL			4096
#define NR_5G_MAX_NUM_RE_PER_PER_SLOT		61440

#define NR_5G_PSS_LENGTH 					   127
#define NR_5G_SSS_LENGTH 					   127
#define NR_5G_PBCH_DMRS_LENGTH 				144 //in mod symbols
#define NR_5G_PBCH_DMRS_CN_LENGTH 			288
#define NR_5G_MAX_PDCCH_DMRS_INIT_LENGTH 	((NR_5G_MAX_NB_RB<<1)*3) //3symbols*2(QPSK)
#define NR_5G_MAX_PDCCH_DMRS_LENGTH 		576 //16(L)*2(QPSK)*3(3 DMRS symbs per REG)*6(REG per CCE)
#define NR_5G_MAX_PDSCH_DMRS_LENGTH 		3300 //275*6(k)*2(QPSK)

/***************** PBCH ****************/ 
#define NR_5G_POLAR_PBCH_AGGREGATION_LEVEL 	0
#define NR_5G_POLAR_PBCH_MESSAGE_TYPE 		   0
#define NR_5G_POLAR_PBCH_PAYLOAD_BITS 		   32
#define NR_5G_POLAR_PBCH_CRC_PARITY_BITS 	   24
//Sec. 7.1.4: Channel Coding
#define NR_5G_POLAR_PBCH_N_MAX 				   9
#define NR_5G_POLAR_PBCH_I_IL 				   1
#define NR_5G_POLAR_PBCH_I_SEG 				   0
#define NR_5G_POLAR_PBCH_N_PC 				   0
#define NR_5G_POLAR_PBCH_N_PC_WM 			   0
#define NR_5G_POLAR_PBCH_N 					   512
//Sec. 7.1.5: Rate Matching
#define NR_5G_POLAR_PBCH_I_BIL 				   0
#define NR_5G_POLAR_PBCH_E		   			   864

/***************** PDCCH ****************/ 
#define NR_5G_MAX_DCI_PAYLOAD_SIZE 			64
#define NR_5G_MAX_DCI_SIZE 					1728 //16(L)*2(QPSK)*9(12 RE per REG - 3(DMRS))*6(REG per CCE)
#define NR_5G_MAX_PDCCH_AGG_LEVEL 			16
#define NR_5G_MAX_CSET_DURATION 			   3
#define NR_5G_MAX_PDCCH_PER_TTI				16

/***************** PDSCH ****************/
#define NR_5G_MAX_PDSCH_PER_TTI				16
#define NR_5G_MAX_NUM_UE_GROUP				255
#define	NR_5G_MAX_UE_PER_GROUP				12
#define	NR_5G_MAX_NUM_CODEWORD				2
#define NR_5G_MAX_PRG_SPANNING				8
#define NR_5G_MAX_DIGITAL_BEAM				8

/***************** TDD ****************/
#define	NR_5G_MAX_TDD_PERIODICITY			7
#define NR_5G_MAX_NUM_SYMB_PER_SLOT			14

/***************** UPLINK ****************/
#define NR_5G_MAX_PUSCH_PDU_PER_TTI			16
#define NR_5G_MAX_UCI_PDU_PER_TTI			16
#define NR_5G_MAX_SRS_PDU_PER_TTI			16
#define NR_5G_MAX_RACH_PDU_PER_TTI			16

#define NR_5G_MAX_PUSCH_CODEBLOCK			16
#define NR_5G_MAX_NUM_HARQ_PDU				16
#define NR_5G_MAX_SR_PAYLOAD_BIT			   16
#define NR_5G_MAX_HARQ_PAYLOAD_BIT			16
#define NR_5G_MAX_CSI_PART1_PAYLOAD_BIT	16
#define NR_5G_MAX_CSI_PART2_PAYLOAD_BIT	16

#endif /* */
