#ifndef __NR_5G_PHY_POLAR_DEFS__H__
#define __NR_5G_PHY_POLAR_DEFS__H__

//Sec. 7.3.3: Channel Coding
#define NR_POLAR_N_MAX              9   //uint8_t
#define NR_POLAR_I_IL               1   //uint8_t
#define NR_POLAR_I_SEG              0   //uint8_t
#define NR_POLAR_N_PC               0   //uint8_t
#define NR_POLAR_N_PC_WM            0   //uint8_t
#define NR_POLAR_K_LENGTH           56

//Sec. 7.1.5: Rate Matching
#define NR_POLAR_PBCH_I_BIL 0 //uint8_t
#define NR_POLAR_PBCH_E 864   //uint16_t
#define NR_POLAR_PBCH_E_DWORD 27 // NR_POLAR_PBCH_E/32

static const uint8_t nr5gPhyPolarSubblockInterleaverPattern[32] = {0,1,2,4,3,5,6,7,8,16,9,17,10,18,11,19,12,20,13,21,14,22,15,23,24,25,26,28,27,29,30,31};

#endif /*__NR_5G_PHY_POLAR_DEFS__H__*/
