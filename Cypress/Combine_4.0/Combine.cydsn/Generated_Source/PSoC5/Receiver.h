/*******************************************************************************
* File Name: Receiver.h
* Version 2.10
*
* Description:
*  This header file contains definitions associated with the Shift Register
*  component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#ifndef CY_SHIFTREG_Receiver_H
#define CY_SHIFTREG_Receiver_H

#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component ShiftReg_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Receiver_FIFO_SIZE                (4u)
#define Receiver_USE_INPUT_FIFO           (0u)
#define Receiver_USE_OUTPUT_FIFO          (1u)
#define Receiver_SR_SIZE                  (8u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */

typedef struct _Receiver_backupStruct
{    
    uint8 enableState;
    
    uint8 saveSrA0Reg;
    uint8 saveSrA1Reg;

    #if(CY_UDB_V0) /* CY_UDB_V0 */
        uint8 saveSrIntMask;
    #endif /* CY_UDB_V0 */

} Receiver_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  Receiver_Start(void) ;
void  Receiver_Stop(void) ; 
void  Receiver_Init(void) ;
void  Receiver_Enable(void) ; 
void  Receiver_RestoreConfig(void) ;
void  Receiver_SaveConfig(void) ;
void  Receiver_Sleep(void) ;
void  Receiver_Wakeup(void) ; 
void  Receiver_EnableInt(void) ;
void  Receiver_DisableInt(void) ;
void  Receiver_SetIntMode(uint8 interruptSource) ;
uint8 Receiver_GetIntStatus(void) ;
void  Receiver_WriteRegValue(uint8 shiftData) \
                    ;
uint8 Receiver_ReadRegValue(void) ;
uint8    Receiver_GetFIFOStatus(uint8 fifoId) ;

#if (Receiver_USE_INPUT_FIFO == 1u)
    uint8 Receiver_WriteData(uint8 shiftData)\
                    ;
#endif/*(Receiver_USE_INPUT_FIFO == 1u)*/
#if (Receiver_USE_OUTPUT_FIFO == 1u)
    uint8 Receiver_ReadData(void) ;
#endif/*(Receiver_USE_OUTPUT_FIFO == 1u)*/


/***************************************
*           API Constants
***************************************/

#define Receiver_LOAD                     (0x01u)
#define Receiver_STORE                    (0x02u)
#define Receiver_RESET                    (0x04u)

#define Receiver_IN_FIFO                  (0x01u)
#define Receiver_OUT_FIFO                 (0x02u)

#define Receiver_RET_FIFO_FULL            (0x00u)
#define Receiver_RET_FIFO_NOT_EMPTY       (0x01u)
#define Receiver_RET_FIFO_EMPTY           (0x02u)

#define Receiver_RET_FIFO_NOT_DEFINED     (0xFEu)
#define Receiver_RET_FIFO_BAD_PARAM       (0xFFu)

/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Receiver__LEFT 0
#define Receiver__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define Receiver_SR_MASK                  (0xFFu)
#define Receiver_INT_SRC                  (2u)
#define Receiver_DIRECTION                (0u)


/***************************************
*             Registers
***************************************/

/* Shift Register control register */

#define Receiver_SR_CONTROL_REG       (* (reg8 *) \
    Receiver_bSR_AsyncCtl_CtrlReg__CONTROL_REG)
#define Receiver_SR_CONTROL_PTR       (  (reg8 *) \
    Receiver_bSR_AsyncCtl_CtrlReg__CONTROL_REG)

/* Obsolete control reg name*/
#define Receiver_SR_CONTROL               Receiver_SR_CONTROL_REG

/* Shift Regisster interupt status register */

#define Receiver_SR_STATUS_REG            (* (reg8 *) Receiver_bSR_StsReg__STATUS_REG)
#define Receiver_SR_STATUS_PTR            (  (reg8 *) Receiver_bSR_StsReg__STATUS_REG)
#define Receiver_SR_STATUS_MASK_REG       (* (reg8 *) Receiver_bSR_StsReg__MASK_REG)
#define Receiver_SR_STATUS_MASK_PTR       (  (reg8 *) Receiver_bSR_StsReg__MASK_REG)
#define Receiver_SR_AUX_CONTROL_REG       (* (reg8 *) Receiver_bSR_StsReg__STATUS_AUX_CTL_REG)
#define Receiver_SR_AUX_CONTROL_PTR       (  (reg8 *) Receiver_bSR_StsReg__STATUS_AUX_CTL_REG)

/* Obsolete names */
#define Receiver_SR_STATUS                Receiver_SR_STATUS_REG
#define Receiver_SR_STATUS_MASK           Receiver_SR_STATUS_MASK_REG
#define Receiver_SR_AUX_CONTROL           Receiver_SR_AUX_CONTROL_REG


#define Receiver_IN_FIFO_VAL_LSB_PTR      ((reg8 *) \
    Receiver_bSR_sC8_BShiftRegDp_u0__F0_REG )
#define Receiver_SHIFT_REG_LSB_PTR        ((reg8 *) \
    Receiver_bSR_sC8_BShiftRegDp_u0__A0_REG )
#define Receiver_SHIFT_REG_VALUE_LSB_PTR  ((reg8 *) \
    Receiver_bSR_sC8_BShiftRegDp_u0__A1_REG )
#define Receiver_OUT_FIFO_VAL_LSB_PTR     ((reg8 *) \
    Receiver_bSR_sC8_BShiftRegDp_u0__F1_REG )

/***************************************
*       Register Constants
***************************************/

#define Receiver_INTERRUPTS_ENABLE        (0x10u)
#define Receiver_LOAD_INT_EN              (0x01u)
#define Receiver_STORE_INT_EN             (0x02u)
#define Receiver_RESET_INT_EN             (0x04u)
#define Receiver_CLK_EN                   (0x01u)

#define Receiver_RESET_INT_EN_MASK        (0xFBu)
#define Receiver_LOAD_INT_EN_MASK         (0xFEu)
#define Receiver_STORE_INT_EN_MASK        (0xFDu)
#define Receiver_INTS_EN_MASK             (0x07u)

#define Receiver_OUT_FIFO_CLR_BIT         (0x02u)

#if (Receiver_USE_INPUT_FIFO == 1u)

    #define Receiver_IN_FIFO_MASK         (0x18u)

    #define Receiver_IN_FIFO_FULL         (0x00u)
    #define Receiver_IN_FIFO_EMPTY        (0x01u)
    #define Receiver_IN_FIFO_NOT_EMPTY    (0x02u)
    
#endif/*(Receiver_USE_INPUT_FIFO == 1u)*/

#define Receiver_OUT_FIFO_MASK            (0x60u)

#define Receiver_OUT_FIFO_EMPTY           (0x00u)
#define Receiver_OUT_FIFO_FULL            (0x01u)
#define Receiver_OUT_FIFO_NOT_EMPTY       (0x02u)
#define Receiver_IN_FIFO_SHFT_MASK        (0x03u)
#define Receiver_OUT_FIFO_SHFT_MASK       (0x05u)

#endif /* CY_SHIFTREG_Receiver_H */

/* [] END OF FILE */
