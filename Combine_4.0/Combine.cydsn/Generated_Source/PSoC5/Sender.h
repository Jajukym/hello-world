/*******************************************************************************
* File Name: Sender.h
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


#ifndef CY_SHIFTREG_Sender_H
#define CY_SHIFTREG_Sender_H

#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component ShiftReg_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Sender_FIFO_SIZE                (4u)
#define Sender_USE_INPUT_FIFO           (1u)
#define Sender_USE_OUTPUT_FIFO          (0u)
#define Sender_SR_SIZE                  (8u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */

typedef struct _Sender_backupStruct
{    
    uint8 enableState;
    
    uint8 saveSrA0Reg;
    uint8 saveSrA1Reg;

    #if(CY_UDB_V0) /* CY_UDB_V0 */
        uint8 saveSrIntMask;
    #endif /* CY_UDB_V0 */

} Sender_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  Sender_Start(void) ;
void  Sender_Stop(void) ; 
void  Sender_Init(void) ;
void  Sender_Enable(void) ; 
void  Sender_RestoreConfig(void) ;
void  Sender_SaveConfig(void) ;
void  Sender_Sleep(void) ;
void  Sender_Wakeup(void) ; 
void  Sender_EnableInt(void) ;
void  Sender_DisableInt(void) ;
void  Sender_SetIntMode(uint8 interruptSource) ;
uint8 Sender_GetIntStatus(void) ;
void  Sender_WriteRegValue(uint8 shiftData) \
                    ;
uint8 Sender_ReadRegValue(void) ;
uint8    Sender_GetFIFOStatus(uint8 fifoId) ;

#if (Sender_USE_INPUT_FIFO == 1u)
    uint8 Sender_WriteData(uint8 shiftData)\
                    ;
#endif/*(Sender_USE_INPUT_FIFO == 1u)*/
#if (Sender_USE_OUTPUT_FIFO == 1u)
    uint8 Sender_ReadData(void) ;
#endif/*(Sender_USE_OUTPUT_FIFO == 1u)*/


/***************************************
*           API Constants
***************************************/

#define Sender_LOAD                     (0x01u)
#define Sender_STORE                    (0x02u)
#define Sender_RESET                    (0x04u)

#define Sender_IN_FIFO                  (0x01u)
#define Sender_OUT_FIFO                 (0x02u)

#define Sender_RET_FIFO_FULL            (0x00u)
#define Sender_RET_FIFO_NOT_EMPTY       (0x01u)
#define Sender_RET_FIFO_EMPTY           (0x02u)

#define Sender_RET_FIFO_NOT_DEFINED     (0xFEu)
#define Sender_RET_FIFO_BAD_PARAM       (0xFFu)

/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Sender__LEFT 0
#define Sender__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define Sender_SR_MASK                  (0xFFu)
#define Sender_INT_SRC                  (1u)
#define Sender_DIRECTION                (1u)


/***************************************
*             Registers
***************************************/

/* Shift Register control register */

#define Sender_SR_CONTROL_REG       (* (reg8 *) \
    Sender_bSR_AsyncCtl_CtrlReg__CONTROL_REG)
#define Sender_SR_CONTROL_PTR       (  (reg8 *) \
    Sender_bSR_AsyncCtl_CtrlReg__CONTROL_REG)

/* Obsolete control reg name*/
#define Sender_SR_CONTROL               Sender_SR_CONTROL_REG

/* Shift Regisster interupt status register */

#define Sender_SR_STATUS_REG            (* (reg8 *) Sender_bSR_StsReg__STATUS_REG)
#define Sender_SR_STATUS_PTR            (  (reg8 *) Sender_bSR_StsReg__STATUS_REG)
#define Sender_SR_STATUS_MASK_REG       (* (reg8 *) Sender_bSR_StsReg__MASK_REG)
#define Sender_SR_STATUS_MASK_PTR       (  (reg8 *) Sender_bSR_StsReg__MASK_REG)
#define Sender_SR_AUX_CONTROL_REG       (* (reg8 *) Sender_bSR_StsReg__STATUS_AUX_CTL_REG)
#define Sender_SR_AUX_CONTROL_PTR       (  (reg8 *) Sender_bSR_StsReg__STATUS_AUX_CTL_REG)

/* Obsolete names */
#define Sender_SR_STATUS                Sender_SR_STATUS_REG
#define Sender_SR_STATUS_MASK           Sender_SR_STATUS_MASK_REG
#define Sender_SR_AUX_CONTROL           Sender_SR_AUX_CONTROL_REG


#define Sender_IN_FIFO_VAL_LSB_PTR      ((reg8 *) \
    Sender_bSR_sC8_BShiftRegDp_u0__F0_REG )
#define Sender_SHIFT_REG_LSB_PTR        ((reg8 *) \
    Sender_bSR_sC8_BShiftRegDp_u0__A0_REG )
#define Sender_SHIFT_REG_VALUE_LSB_PTR  ((reg8 *) \
    Sender_bSR_sC8_BShiftRegDp_u0__A1_REG )
#define Sender_OUT_FIFO_VAL_LSB_PTR     ((reg8 *) \
    Sender_bSR_sC8_BShiftRegDp_u0__F1_REG )

/***************************************
*       Register Constants
***************************************/

#define Sender_INTERRUPTS_ENABLE        (0x10u)
#define Sender_LOAD_INT_EN              (0x01u)
#define Sender_STORE_INT_EN             (0x02u)
#define Sender_RESET_INT_EN             (0x04u)
#define Sender_CLK_EN                   (0x01u)

#define Sender_RESET_INT_EN_MASK        (0xFBu)
#define Sender_LOAD_INT_EN_MASK         (0xFEu)
#define Sender_STORE_INT_EN_MASK        (0xFDu)
#define Sender_INTS_EN_MASK             (0x07u)

#define Sender_OUT_FIFO_CLR_BIT         (0x02u)

#if (Sender_USE_INPUT_FIFO == 1u)

    #define Sender_IN_FIFO_MASK         (0x18u)

    #define Sender_IN_FIFO_FULL         (0x00u)
    #define Sender_IN_FIFO_EMPTY        (0x01u)
    #define Sender_IN_FIFO_NOT_EMPTY    (0x02u)
    
#endif/*(Sender_USE_INPUT_FIFO == 1u)*/

#define Sender_OUT_FIFO_MASK            (0x60u)

#define Sender_OUT_FIFO_EMPTY           (0x00u)
#define Sender_OUT_FIFO_FULL            (0x01u)
#define Sender_OUT_FIFO_NOT_EMPTY       (0x02u)
#define Sender_IN_FIFO_SHFT_MASK        (0x03u)
#define Sender_OUT_FIFO_SHFT_MASK       (0x05u)

#endif /* CY_SHIFTREG_Sender_H */

/* [] END OF FILE */
