/*******************************************************************************
* File Name: shiftregSender.h
* Version 2.30
*
* Description:
*  This header file contains definitions associated with the Shift Register
*  component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#if !defined(CY_SHIFTREG_shiftregSender_H)
#define CY_SHIFTREG_shiftregSender_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component ShiftReg_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define shiftregSender_FIFO_SIZE          (4u)
#define shiftregSender_USE_INPUT_FIFO     (1u)
#define shiftregSender_USE_OUTPUT_FIFO    (0u)
#define shiftregSender_SR_SIZE            (8u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;

    uint8 saveSrA0Reg;
    uint8 saveSrA1Reg;

    #if(CY_UDB_V0)
        uint8 saveSrIntMask;
    #endif /* (CY_UDB_V0) */

} shiftregSender_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  shiftregSender_Start(void)                              ;
void  shiftregSender_Stop(void)                               ;
void  shiftregSender_Init(void)                               ;
void  shiftregSender_Enable(void)                             ;
void  shiftregSender_RestoreConfig(void)                      ;
void  shiftregSender_SaveConfig(void)                         ;
void  shiftregSender_Sleep(void)                              ;
void  shiftregSender_Wakeup(void)                             ;
void  shiftregSender_EnableInt(void)                          ;
void  shiftregSender_DisableInt(void)                         ;
void  shiftregSender_SetIntMode(uint8 interruptSource)        ;
uint8 shiftregSender_GetIntStatus(void)                       ;
void  shiftregSender_WriteRegValue(uint8 shiftData) \
                                                                ;
uint8 shiftregSender_ReadRegValue(void) ;
uint8    shiftregSender_GetFIFOStatus(uint8 fifoId)           ;

#if(0u != shiftregSender_USE_INPUT_FIFO)
    cystatus shiftregSender_WriteData(uint8 shiftData) \
                                                                ;
#endif /* (0u != shiftregSender_USE_INPUT_FIFO) */

#if(0u != shiftregSender_USE_OUTPUT_FIFO)
    uint8 shiftregSender_ReadData(void) ;
#endif /* (0u != shiftregSender_USE_OUTPUT_FIFO) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 shiftregSender_initVar;


/***************************************
*           API Constants
***************************************/

#define shiftregSender_LOAD                   (0x01u)
#define shiftregSender_STORE                  (0x02u)
#define shiftregSender_RESET                  (0x04u)

#define shiftregSender_IN_FIFO                (0x01u)
#define shiftregSender_OUT_FIFO               (0x02u)

#define shiftregSender_RET_FIFO_FULL          (0x00u)

/* This define is obsolete */
#define shiftregSender_RET_FIFO_NOT_EMPTY     (0x01u)

#define shiftregSender_RET_FIFO_PARTIAL       (0x01u)
#define shiftregSender_RET_FIFO_EMPTY         (0x02u)
#define shiftregSender_RET_FIFO_NOT_DEFINED   (0xFEu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define shiftregSender__LEFT 0
#define shiftregSender__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define shiftregSender_SR_MASK    (0xFFu) /* Unsigned is added to parameter */
#define shiftregSender_INT_SRC    (1u)
#define shiftregSender_DIRECTION  (1u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define shiftregSender_SR_CONTROL_REG (* (reg8 *) \
                                           shiftregSender_bSR_SyncCtl_CtrlReg__CONTROL_REG)
#define shiftregSender_SR_CONTROL_PTR (  (reg8 *) \
                                           shiftregSender_bSR_SyncCtl_CtrlReg__CONTROL_REG)

/* Status register */
#define shiftregSender_SR_STATUS_REG      (* (reg8 *) shiftregSender_bSR_StsReg__STATUS_REG)
#define shiftregSender_SR_STATUS_PTR      (  (reg8 *) shiftregSender_bSR_StsReg__STATUS_REG)

/* Interrupt status register */
#define shiftregSender_SR_STATUS_MASK_REG (* (reg8 *) shiftregSender_bSR_StsReg__MASK_REG)
#define shiftregSender_SR_STATUS_MASK_PTR (  (reg8 *) shiftregSender_bSR_StsReg__MASK_REG)

/* Aux control register */
#define shiftregSender_SR_AUX_CONTROL_REG (* (reg8 *) shiftregSender_bSR_StsReg__STATUS_AUX_CTL_REG)
#define shiftregSender_SR_AUX_CONTROL_PTR (  (reg8 *) shiftregSender_bSR_StsReg__STATUS_AUX_CTL_REG)

/* A1 register: only used to implement capture function */
#define shiftregSender_SHIFT_REG_CAPTURE_PTR    ( (reg8 *) \
                                        shiftregSender_bSR_sC8_BShiftRegDp_u0__A1_REG )

#if(CY_PSOC3 || CY_PSOC5)
    #define shiftregSender_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        shiftregSender_bSR_sC8_BShiftRegDp_u0__F0_REG )

    #define shiftregSender_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        shiftregSender_bSR_sC8_BShiftRegDp_u0__A0_REG )

    #define shiftregSender_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        shiftregSender_bSR_sC8_BShiftRegDp_u0__A1_REG )

    #define shiftregSender_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        shiftregSender_bSR_sC8_BShiftRegDp_u0__F1_REG )

#else
    #if(shiftregSender_SR_SIZE <= 8u) /* 8bit - ShiftReg */
        #define shiftregSender_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        shiftregSender_bSR_sC8_BShiftRegDp_u0__F0_REG )

        #define shiftregSender_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        shiftregSender_bSR_sC8_BShiftRegDp_u0__A0_REG )

        #define shiftregSender_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        shiftregSender_bSR_sC8_BShiftRegDp_u0__A1_REG )

        #define shiftregSender_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        shiftregSender_bSR_sC8_BShiftRegDp_u0__F1_REG )

    #elif(shiftregSender_SR_SIZE <= 16u) /* 16bit - ShiftReg */
        #define shiftregSender_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                  shiftregSender_bSR_sC8_BShiftRegDp_u0__16BIT_F0_REG )

        #define shiftregSender_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                  shiftregSender_bSR_sC8_BShiftRegDp_u0__16BIT_A0_REG )

        #define shiftregSender_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                  shiftregSender_bSR_sC8_BShiftRegDp_u0__16BIT_A1_REG )

        #define shiftregSender_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                  shiftregSender_bSR_sC8_BShiftRegDp_u0__16BIT_F1_REG )


    #elif(shiftregSender_SR_SIZE <= 24u) /* 24bit - ShiftReg */
        #define shiftregSender_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        shiftregSender_bSR_sC8_BShiftRegDp_u0__F0_REG )

        #define shiftregSender_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        shiftregSender_bSR_sC8_BShiftRegDp_u0__A0_REG )

        #define shiftregSender_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        shiftregSender_bSR_sC8_BShiftRegDp_u0__A1_REG )

        #define shiftregSender_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        shiftregSender_bSR_sC8_BShiftRegDp_u0__F1_REG )

    #else /* 32bit - ShiftReg */
        #define shiftregSender_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                  shiftregSender_bSR_sC8_BShiftRegDp_u0__32BIT_F0_REG )

        #define shiftregSender_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                  shiftregSender_bSR_sC8_BShiftRegDp_u0__32BIT_A0_REG )

        #define shiftregSender_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                  shiftregSender_bSR_sC8_BShiftRegDp_u0__32BIT_A1_REG )

        #define shiftregSender_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                  shiftregSender_bSR_sC8_BShiftRegDp_u0__32BIT_F1_REG )

    #endif  /* (shiftregSender_SR_SIZE <= 8u) */
#endif      /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*       Register Constants
***************************************/

#define shiftregSender_INTERRUPTS_ENABLE      (0x10u)
#define shiftregSender_LOAD_INT_EN            (0x01u)
#define shiftregSender_STORE_INT_EN           (0x02u)
#define shiftregSender_RESET_INT_EN           (0x04u)
#define shiftregSender_CLK_EN                 (0x01u)

#define shiftregSender_RESET_INT_EN_MASK      (0xFBu)
#define shiftregSender_LOAD_INT_EN_MASK       (0xFEu)
#define shiftregSender_STORE_INT_EN_MASK      (0xFDu)
#define shiftregSender_INTS_EN_MASK           (0x07u)

#define shiftregSender_OUT_FIFO_CLR_BIT       (0x02u)

#if(0u != shiftregSender_USE_INPUT_FIFO)

    #define shiftregSender_IN_FIFO_MASK       (0x18u)

    #define shiftregSender_IN_FIFO_FULL       (0x00u)
    #define shiftregSender_IN_FIFO_EMPTY      (0x01u)
    #define shiftregSender_IN_FIFO_PARTIAL    (0x02u)
    
    /* This define is obsolete */
    #define shiftregSender_IN_FIFO_NOT_EMPTY  (0x02u)
    
#endif /* (0u != shiftregSender_USE_INPUT_FIFO) */

#define shiftregSender_OUT_FIFO_MASK          (0x60u)

#define shiftregSender_OUT_FIFO_EMPTY         (0x00u)
#define shiftregSender_OUT_FIFO_FULL          (0x01u)
#define shiftregSender_OUT_FIFO_PARTIAL       (0x02u)

/* This define is obsolete */
#define shiftregSender_OUT_FIFO_NOT_EMPTY     (0x02u)

#define shiftregSender_IN_FIFO_SHIFT_MASK     (0x03u)
#define shiftregSender_OUT_FIFO_SHIFT_MASK    (0x05u)

#define shiftregSender_DISABLED               (0u)
#define shiftregSender_DEFAULT_A0             (0u)
#define shiftregSender_DEFAULT_A1             (0u)


/***************************************
*       Macros
***************************************/

#define shiftregSender_IS_ENABLED         (0u != (shiftregSender_SR_CONTROL & shiftregSender_CLK_EN))

#define shiftregSender_GET_OUT_FIFO_STS   ((shiftregSender_SR_STATUS & shiftregSender_OUT_FIFO_MASK) >> \
                                              shiftregSender_OUT_FIFO_SHIFT_MASK)

#define shiftregSender_GET_IN_FIFO_STS    ((shiftregSender_SR_STATUS & shiftregSender_IN_FIFO_MASK)  >> \
                                              shiftregSender_IN_FIFO_SHIFT_MASK)


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from ShiftReg 2.20 
 */

#define shiftregSender_SR_CONTROL     (shiftregSender_SR_CONTROL_REG)
#define shiftregSender_SR_STATUS      (shiftregSender_SR_STATUS_REG)
#define shiftregSender_SR_STATUS_MASK (shiftregSender_SR_STATUS_MASK_REG)
#define shiftregSender_SR_AUX_CONTROL (shiftregSender_SR_AUX_CONTROL_REG)

#define shiftregSender_IN_FIFO_SHFT_MASK  (shiftregSender_IN_FIFO_SHIFT_MASK)
#define shiftregSender_OUT_FIFO_SHFT_MASK (shiftregSender_OUT_FIFO_SHFIT_MASK)

#define shiftregSender_RET_FIFO_BAD_PARAM (0xFFu)

#endif /* (CY_SHIFTREG_shiftregSender_H) */


/* [] END OF FILE */
