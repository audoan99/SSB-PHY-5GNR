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

#ifndef NR_5G_PHY_CONFIG_H_
#define NR_5G_PHY_CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "nr5gPhyDef.h"

extern FILE* logFile;

#define TRUE 0
#define FALSE -1

#define PRINTFCMD(STR...)  		printf(STR) //fprintf(logFile, STR)
#define PRINTFCMD_DATA(STR...) 	printf(STR)
#define GET_VARIABLE_NAME(Var) 	(#Var)

#define OS_STATUS_ASSERT(status)	return status

// FRAMEWORK Define
#define NR5GPHY_LOG_DEFAULT				NR5GPHY_LOG_INFO
#define NR5GPHY_MAIN_PROC_CORE_ID		0
#define NR5GPHY_DRV_MAC_MSG_CORE_ID		0 //1
#define NR5GPHY_SSB_THREAD_CORE_ID		0 //2
#define NR5GPHY_PDCCH_THREAD_CORE_ID	0 //3
#define NR5GPHY_PDSCH_THREAD_CORE_ID	0 //4
#define NR5GPHY_PRACH_THREAD_CORE_ID	0 //5
#define NR5GPHY_PUCCH_THREAD_CORE_ID	0 //6
#define NR5GPHY_PUSCH_THREAD_CORE_ID	0 //7


#define NR5GPHY_MAX_FAPI_MES_LEN		4096 //FIXME: change it
#define NR5GPHY_FAPI_PORT     			8080

#endif
