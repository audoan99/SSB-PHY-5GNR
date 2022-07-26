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

#ifndef NR_5G_PHY_DEF_H_
#define NR_5G_PHY_DEF_H_

#include "nr5gPhyTypes.h"

/*Macro*/

#define MAC_CFG_MSG_MAX_BYTES            250
#define MAC_DL_CFG_MSG_MAX_BYTES        6600
#define MAC_HIDCI0_MSG_MAX_BYTES        3208
#define MAC_TX_MSG_MAX_BYTES            2400
#define MAC_UL_CFG_MSG_MAX_BYTES        5000

#define MAC_TX_DATA_MAX_BYTES           20000

#define MAC_MSG_MAX_BYTES    			0x800

/** Message Buffers, which are all 32 bits align, shared with MAC **/
#define NR_PHY_DRV_FAPI_MSG_SIZE       					128 // FIXME: That is hardcode for IPC Queue, need change

/* Uplink data message Buffer */
#define NR_PHY_RX_DATA_IND_MSG_SIZE                     128
#define NR_PHY_RX_DATA_IND_MSG_BUF_NUM                  (1) // FIXME: Need change > 1

/* HARQ indication buffer. It should keep as multiple of 5, since the buffer is chosen by subframe index */
#define NR_PHY_CRC_IND_MSG_SIZE                         128
#define NR_PHY_CRC_IND_MSG_BUF_NUM                      (1)

#define NR_PHY_UCI_IND_MSG_SIZE                         128
#define NR_PHY_UCI_IND_MSG_BUF_NUM                      (1)

/* CQI indication buffer. It should keep as multiple of 5, since the buffer is chosen by subframe index */
#define NR_PHY_SRS_IND_MSG_SIZE                         128
#define NR_PHY_SRS_IND_MSG_BUF_NUM                      (1)

#define NR_PHY_RACH_IND_MSG_SIZE                        128
#define NR_PHY_RACH_IND_MSG_BUF_NUM                     (1)

#define NR_PHY_ERROR_IND_BUF_SIZE                       (128)
#define NR_PHY_ERROR_IND_MSG_BUF_NUM                    (1)

#define NR_PHY_DRV_SFM_IND_SIZE                         (128)

#define NR_MAX_SUBFRAME_IDX_SPT        10
#define NR_MAX_FRAME_IDX_SPT           1024

#define NR_PHY_DRV_MSGSCALE_TABLE_Q       (11)
#define NR_PHY_DRV_MSGSCALE_OUT_Q         (11)

typedef enum {
	NR_5G_TDD_SLOT_D,		//!< D Slot
	NR_5G_TDD_SLOT_S,		//!< S Slot
	NR_5G_TDD_SLOT_U		//!< U Slot
}nr5gSlotType_e;

//IPC channnel number define. allocation ipc channnel number to each FAPI message
typedef enum
{
	MAC_TO_PHY_PARAM_REQUEST_CH = 1,
	MAC_TO_PHY_CONFIG_REQUEST_CH,
	MAC_TO_PHY_START_REQUEST_CH,
	MAC_TO_PHY_STOP_REQUEST_CH,
	MAC_TO_PHY_DLCONF_REQUEST_CH,
	MAC_TO_PHY_TX_REQUEST_CH,
	MAC_TO_PHY_ULCONF_REQUEST_CH,
	MAC_TO_PHY_UL_DCI_REQUEST_CH,

	MAX_IPC_MAC_PHY_CH_NUM,

	PHY_TO_MAC_INIT_CH = MAX_IPC_MAC_PHY_CH_NUM,
	PHY_TO_MAC_PARAM_RESPONSE_CH,
	PHY_TO_MAC_CONFIG_RESPONSE_CH,
	PHY_TO_MAC_STOP_INDICATION_CH,
	PHY_TO_MAC_ERROR_INDICATION_CH,
	PHY_TO_MAC_SLOT_INDICATION_CH,

	PHY_TO_MAC_RX_DATA_INDICATION_CH,
	PHY_TO_MAC_CRC_INDICATION_CH,
	PHY_TO_MAC_UCI_INDICATION_CH,
	PHY_TO_MAC_SRS_INDICATION_CH,
	PHY_TO_MAC_RACH_INDICATION_CH,

	TOTAL_FAPI_CH_NUM,
	MAX_IPC_PHY_MAC_CH_NUM = TOTAL_FAPI_CH_NUM - MAX_IPC_MAC_PHY_CH_NUM,

}nr5gPhyIpcChannelIdx;

typedef enum
{
	DLCONF_BUF_ID = 0,
	TX_BUF_ID,

	DL_CH_BUF_NUM
}nr5gPhyIpcDlChannelIdx;

typedef struct
{
	// Cell
	uint8 frameDuplexType;
	uint16 phyCellId;

	//Carrier
	uint8 frequencyShift7p5KHz;
    uint16 dlBandwidth;
    uint16 dlk0; //k0 for each numerolegy
    uint16 dlGridSize;
	uint16 numTxAnt;
    uint32 dlFrequency; //dlFreq SCF define 32 bit but convert to 16 bit
    uint16 ulBandwidth;
    uint16 ulk0; //k0 for each numerolegy
    uint16 ulGridSize;
	uint16 numRxAnt;
    uint32 ulFrequency; //ulFreq SCF define 32 bit but convert to 16 bit

	//SSB
	uint8 pbchPayload;
	uint8 scsCommon;
	uint16 ssbOffsetPointA;
	uint32 ssPbchPower;
	uint32 MIB;
	uint8 betaPss;
	uint8 SsbPeriod;
	uint8 ssbSubcarrierOffset;
	uint8 ssPbchMultipleCarriersInABand;
	uint8 multipleCellsSsPbchInACarrier;
	uint8 unused[3];

    //PDCCH

	//PDSCH

} nr5gPhySysConfig_t;

typedef struct
{
	uint8	ssbEnable;
	uint16	phyCellId;
	uint8	betaPss;
	uint8	ssbBlockIndex;
	uint8   ssbPattern;
	uint8	ssbSubcarrierOffset;
	uint16	ssbOffsetPointA;
	uint8	bchPayloadFlag;
	uint32	bchPayload;
} nr5gPhySSBConfig_t;

typedef struct
{
	uint8	pdcchEnable;
} nr5gPhyPDCCHConfig_t;

typedef struct
{
	uint8	pdschEnable;
} nr5gPhyPDSCHConfig_t;

#endif
