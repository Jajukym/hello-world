/*******************************************************************************
* File Name: adcVFan_AMux.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_adcVFan_AMux_H)
#define CY_AMUX_adcVFan_AMux_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void adcVFan_AMux_Start(void) ;
#define adcVFan_AMux_Init() adcVFan_AMux_Start()
void adcVFan_AMux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void adcVFan_AMux_Stop(void); */
/* void adcVFan_AMux_Select(uint8 channel); */
/* void adcVFan_AMux_Connect(uint8 channel); */
/* void adcVFan_AMux_Disconnect(uint8 channel); */
/* void adcVFan_AMux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define adcVFan_AMux_CHANNELS  2u
#define adcVFan_AMux_MUXTYPE   1
#define adcVFan_AMux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define adcVFan_AMux_NULL_CHANNEL 0xFFu
#define adcVFan_AMux_MUX_SINGLE   1
#define adcVFan_AMux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if adcVFan_AMux_MUXTYPE == adcVFan_AMux_MUX_SINGLE
# if !adcVFan_AMux_ATMOSTONE
#  define adcVFan_AMux_Connect(channel) adcVFan_AMux_Set(channel)
# endif
# define adcVFan_AMux_Disconnect(channel) adcVFan_AMux_Unset(channel)
#else
# if !adcVFan_AMux_ATMOSTONE
void adcVFan_AMux_Connect(uint8 channel) ;
# endif
void adcVFan_AMux_Disconnect(uint8 channel) ;
#endif

#if adcVFan_AMux_ATMOSTONE
# define adcVFan_AMux_Stop() adcVFan_AMux_DisconnectAll()
# define adcVFan_AMux_Select(channel) adcVFan_AMux_FastSelect(channel)
void adcVFan_AMux_DisconnectAll(void) ;
#else
# define adcVFan_AMux_Stop() adcVFan_AMux_Start()
void adcVFan_AMux_Select(uint8 channel) ;
# define adcVFan_AMux_DisconnectAll() adcVFan_AMux_Start()
#endif

#endif /* CY_AMUX_adcVFan_AMux_H */


/* [] END OF FILE */
