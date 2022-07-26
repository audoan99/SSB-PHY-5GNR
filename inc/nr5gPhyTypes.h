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

#ifndef NR_5G_PHY_TYPES_H_
#define NR_5G_PHY_TYPES_H_

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#ifndef ON
#define ON    1
#endif 

#ifndef OFF
#define OFF    0
#endif

#ifndef NULL
    #define NULL                 ((void*)0)
#endif

/*Macro and type define*/
#ifndef int8
typedef         signed char             int8;
#endif

#ifndef int16
typedef         short                   int16;
#endif

#ifndef int32
typedef         int                     int32;
#endif

#ifndef uint8
typedef         unsigned char           uint8;
#endif 

#ifndef uint16
typedef         unsigned short          uint16;
#endif

#ifndef uint32
typedef         unsigned int            uint32;
#endif

/*****************************************************************************/
/*Define for checking the sizes of the typedefs */
#define nr_check_sizeof_error(cond) \
       extern char size_error[(cond) ? 1 : -1]


#define NUM_BYTES_IN_INT8               (sizeof(int8))

#define NUM_BYTES_IN_INT16              (sizeof(int16))

#define NUM_BYTES_IN_INT32              (sizeof(int32))

#define NUM_BYTES_IN_INT40              (sizeof(int40))

#define NUM_BYTES_IN_INT64              (sizeof(int64))

#define NUM_BITS_IN_BYTE                8

#ifdef _WIN32
   #pragma pack(1)
   #define STRUCTURE_PACK
#else
   #define STRUCTURE_PACK  __attribute__((packed))
#endif

/************************************* MEMORY *******************************/

#ifndef ALIGN_SIZE
#define ALIGN_SIZE(SIZE, ALIGNMENT)                 \
        ((((unsigned int)(SIZE)) + ((unsigned int)(ALIGNMENT)) - 1) & (~(((unsigned int)(ALIGNMENT)) - 1)))
#endif

#ifndef ALIGN_ADDRESS
	#define ALIGN_ADDRESS(ADDRESS, ALIGNMENT)                 \
			(uint8*)((((unsigned long long)(ADDRESS)) + ((unsigned long long)(ALIGNMENT)) - 1) & (~(((unsigned long long)(ALIGNMENT)) - 1)))
#endif


#ifndef ALIGN_PADDING_SIZE
#define ALIGN_PADDING_SIZE(SIZE, ALIGNMENT)         \
        (((((unsigned int)(SIZE)) + ((unsigned int)(ALIGNMENT)) - 1) & (~(((unsigned int)(ALIGNMENT)) - 1))) - ((unsigned int)(SIZE)))
#endif

#define ALIGN_8_BYTE                     8

#define ALIGN_16_BYTE                    16

#define ALIGN_64_BYTE                    64

#define ALIGN_128_BYTE                   128

#define ALIGN_256_BYTE                   256

#define ALIGN_4096_BYTE                  4096

#define NR_8_BYTE_ALIGN  __attribute__ ((aligned (ALIGN_8_BYTE)))

#define NR_16_BYTE_ALIGN  __attribute__ ((aligned (ALIGN_16_BYTE)))

#define NR_64_BYTE_ALIGN  __attribute__ ((aligned (ALIGN_64_BYTE)))

#define NR_128_BYTE_ALIGN  __attribute__ ((aligned (ALIGN_128_BYTE)))

#define NR_256_BYTE_ALIGN  __attribute__ ((aligned (ALIGN_256_BYTE)))

/************************ Struct Common ***************************************/

/*
 * Data type for complex of integer type. Used for fixed point calculation.
 */
typedef struct {
	int16 re;
	int16 im;
} StrIComplex16;
    
#endif
