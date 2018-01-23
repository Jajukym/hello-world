/*******************************************************************************
* File Name: shiftregReceiver.h
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


#if !defined(CY_SHIFTREG_shiftregReceiver_H)
#define CY_SHIFTREG_shiftregReceiver_H

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

#define shiftregReceiver_FIFO_SIZE          (4u)
#define shiftregReceiver_USE_INPUT_FIFO     (0u)
#define shiftregReceiver_USE_OUTPUT_FIFO    (1u)
#define shiftregReceiver_SR_SIZE            (8u)


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

} shiftregReceiver_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  shiftregReceiver_Start(void)                              ;
void  shiftregReceiver_Stop(void)                               ;
void  shiftregReceiver_Init(void)                               ;
void  shiftregReceiver_Enable(void)                             ;
void  shiftregReceiver_RestoreConfig(void)                      ;
void  shiftregReceiver_SaveConfig(void)                         ;
void  shiftregReceiver_Sleep(void)                              ;
void  shiftregReceiver_Wakeup(void)                             ;
void  shiftregReceiver_EnableInt(void)                          ;
void  shiftregReceiver_DisableInt(void)                         ;
void  shiftregReceiver_SetIntMode(uint8 interruptSource)        ;
uint8 shiftregReceiver_GetIntStatus(void)                       ;
void  shiftregReceiver_WriteRegValue(uint8 shiftData) \
                                                                ;
uint8 shiftregReceiver_ReadRegValue(void) ;
uint8    shiftregReceiver_GetFIFOStatus(uint8 fifoId)           ;

#if(0u != shiftregReceiver_USE_INPUT_FIFO)
    cystatus shiftregReceiver_WriteData(uint8 shiftData) \
                                                                ;
#endif /* (0u != shiftregReceiver_USE_INPUT_FIFO) */

#if(0u != shiftregReceiver_USE_OUTPUT_FIFO)
    uint8 shiftregReceiver_ReadData(void) ;
#endif /* (0u != shiftregReceiver_USE_OUTPUT_FIFO) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 shiftregReceiver_initVar;


/***************************************
*           API Constants
***************************************/

#define shiftregReceiver_LOAD                   (0x01u)
#define shiftregReceiver_STORE                  (0x02u)
#define shiftregReceiver_RESET                  (0x04u)

#define shiftregReceiver_IN_FIFO                (0x01u)
#define shiftregReceiver_OUT_FIFO               (0x02u)

#define shiftregReceiver_RET_FIFO_FULL          (0x00u)

/* This define is obsolete */
#define shiftregReceiver_RET_FIFO_NOT_EMPTY     (0x01u)

#define shiftregReceiver_RET_FIFO_PARTIAL       (0x01u)
#define shiftregReceiver_RET_FIFO_EMPTY         (0x02u)
#define shiftregReceiver_RET_FIFO_NOT_DEFINED   (0xFEu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define shiftregReceiver__LEFT 0
#define shiftregReceiver__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define shiftregReceiver_SR_MASK    (0xFFu) /* Unsigned is added to parameter */
#define shiftregReceiver_INT_SRC    (2u)
#define shiftregReceiver_DIRECTION  (0u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define shiftregReceiver_SR_CONTROL_REG (* (reg8 *) \
                                           shiftregReceiver_bSR_SyncCtl_CtrlReg__CONTROL_REG)
#define shiftregReceiver_SR_CONTROL_PTR (  (reg8 *) \
                                           shiftregReceiver_bSR_SyncCtl_CtrlReg__CONTROL_REG)

/* Status register */
#define shiftregReceiver_SR_STATUS_REG      (* (reg8 *) shiftregReceiver_bSR_StsReg__STATUS_REG)
#define shiftregReceiver_SR_STATUS_PTR      (  (reg8 *) shiftregReceiver_bSR_StsReg__STATUS_REG)

/* Interrupt status register */
#define shiftregReceiver_SR_STATUS_MASK_REG (* (reg8 *) shiftregReceiver_bSR_StsReg__MASK_REG)
#define shiftregReceiver_SR_STATUS_MASK_PTR (  (reg8 *) shiftregReceiver_bSR_StsReg__MASK_REG)

/* Aux control register */
#define shiftregReceiver_SR_AUX_CONTROL_REG (* (reg8 *) shiftregReceiver_bSR_StsReg__STATUS_AUX_CTL_REG)
#define shiftregReceiver_SR_AUX_CONTROL_PTR (  (reg8 *) shiftregReceiver_bSR_StsReg__STATUS_AUX_CTL_REG)

/* A1 register: only used to implement capture function */
#define shiftregReceiver_SHIFT_REG_CAPTURE_PTR    ( (reg8 *) \
                                        shiftregReceiver_bSR_sC8_BShiftRegDp_u0__A1_REG )

#if(CY_PSOC3 || CY_PSOC5)
    #define shiftregReceiver_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        shiftregReceiver_bSR_sC8_BShiftRegDp_u0__F0_REG )

    #define shiftregReceiver_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        shiftregReceiver_bSR_sC8_BShiftRegDp_u0__A0_REG )

    #define shiftregReceiver_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        shiftregReceiver_bSR_sC8_BShiftRegDp_u0__A1_REG )

    #define shiftregReceiver_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        shiftregReceiver_bSR_sC8_BShiftRegDp_u0__F1_REG )

#else
    #if(shiftregReceiver_SR_SIZE <= 8u) /* 8bit - ShiftReg */
        #define shiftregReceiver_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        shiftregReceiver_bSR_sC8_BShiftRegDp_u0__F0_REG )

        #define shiftregReceiver_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        shiftregReceiver_bSR_sC8_BShiftRegDp_u0__A0_REG )

        #define shiftregReceiver_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        shiftregReceiver_bSR_sC8_BShiftRegDp_u0__A1_REG )

        #define shiftregReceiver_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        shiftregReceiver_bSR_sC8_BShiftRegDp_u0__F1_REG )

    #elif(shiftregReceiver_SR_SIZE <= 16u) /* 16bit - ShiftReg */
        #define shiftregReceiver_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                  shiftregReceiver_bSR_sC8_BShiftRegDp_u0__16BIT_F0_REG )

        #define shiftregReceiver_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                  shiftregReceiver_bSR_sC8_BShiftRegDp_u0__16BIT_A0_REG )

        #define shiftregReceiver_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                  shiftregReceiver_bSR_sC8_BShiftRegDp_u0__16BIT_A1_REG )

        #define shiftregReceiver_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                  shiftregReceiver_bSR_sC8_BShiftRegDp_u0__16BIT_F1_REG )


    #elif(shiftregReceiver_SR_SIZE <= 24u) /* 24bit - ShiftReg */
        #define shiftregReceiver_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        shiftregReceiver_bSR_sC8_BShiftRegDp_u0__F0_REG )

        #define shiftregReceiver_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        shiftregReceiver_bSR_sC8_BShiftRegDp_u0__A0_REG )

        #define shiftregReceiver_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        shiftregReceiver_bSR_sC8_BShiftRegDp_u0__A1_REG )

        #define shiftregReceiver_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        shiftregReceiver_bSR_sC8_BShiftRegDp_u0__F1_REG )

    #else /* 32bit - ShiftReg */
        #define shiftregReceiver_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                  shiftregReceiver_bSR_sC8_BShiftRegDp_u0__32BIT_F0_REG )

        #define shiftregReceiver_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                  shiftregReceiver_bSR_sC8_BShiftRegDp_u0__32BIT_A0_REG )

        #define shiftregReceiver_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                  shiftregReceiver_bSR_sC8_BShiftRegDp_u0__32BIT_A1_REG )

        #define shiftregReceiver_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                  shiftregReceiver_bSR_sC8_BShiftRegDp_u0__32BIT_F1_REG )

    #endif  /* (shiftregReceiver_SR_SIZE <= 8u) */
#endif      /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*       Register Constants
***************************************/

#define shiftregReceiver_INTERRUPTS_ENABLE      (0x10u)
#define shiftregReceiver_LOAD_INT_EN            (0x01u)
#define shiftregReceiver_STORE_INT_EN           (0x02u)
#define shiftregReceiver_RESET_INT_EN           (0x04u)
#define shiftregReceiver_CLK_EN                 (0x01u)

#define shiftregReceiver_RESET_INT_EN_MASK      (0xFBu)
#define shiftregReceiver_LOAD_INT_EN_MASK       (0xFEu)
#define shiftregReceiver_STORE_INT_EN_MASK      (0xFDu)
#define shiftregReceiver_INTS_EN_MASK           (0x07u)

#define shiftregReceiver_OUT_FIFO_CLR_BIT       (0x02u)

#if(0u != shiftregReceiver_USE_INPUT_FIFO)

    #define shiftregReceiver_IN_FIFO_MASK       (0x18u)

    #define shiftregReceiver_IN_FIFO_FULL       (0x00u)
    #define shiftregReceiver_IN_FIFO_EMPTY      (0x01u)
    #define shiftregReceiver_IN_FIFO_PARTIAL    (0x02u)
    
    /* This define is obsolete */
    #define shiftregReceiver_IN_FIFO_NOT_EMPTY  (0x02u)
    
#endif /* (0u != shiftregReceiver_USE_INPUT_FIFO) */

#define shiftregReceiver_OUT_FIFO_MASK          (0x60u)

#define shiftregReceiver_OUT_FIFO_EMPTY         (0x00u)
#define shiftregReceiver_OUT_FIFO_FULL          (0x01u)
#define shiftregReceiver_OUT_FIFO_PARTIAL       (0x02u)

/* This define is obsolete */
#define shiftregReceiver_OUT_FIFO_NOT_EMPTY     (0x02u)

#define shiftregReceiver_IN_FIFO_SHIFT_MASK     (0x03u)
#define shiftregReceiver_OUT_FIFO_SHIFT_MASK    (0x05u)

#define shiftregReceiver_DISABLED               (0u)
#define shiftregReceiver_DEFAULT_A0             (0u)
#define shiftregReceiver_DEFAULT_A1             (0u)


/***************************************
*       Macros
***************************************/

#define shiftregReceiver_IS_ENABLED         (0u != (shiftregReceiver_SR_CONTROL & shiftregReceiver_CLK_EN))

#define shiftregReceiver_GET_OUT_FIFO_STS   ((shiftregReceiver_SR_STATUS & shiftregReceiver_OUT_FIFO_MASK) >> \
                                              shiftregReceiver_OUT_FIFO_SHIFT_MASK)

#define shiftregReceiver_GET_IN_FIFO_STS    ((shiftregReceiver_SR_STATUS & shiftregReceiver_IN_FIFO_MASK)  >> \
                                              shiftregReceiver_IN_FIFO_SHIFT_MASK)


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from ShiftReg 2.20 
 */

#define shiftregReceiver_SR_CONTROL     (shiftregReceiver_SR_CONTROL_REG)
#define shiftregReceiver_SR_STATUS      (shiftregReceiver_SR_STATUS_REG)
#define shiftregReceiver_SR_STATUS_MASK (shiftregReceiver_SR_STATUS_MASK_REG)
#define shiftregReceiver_SR_AUX_CONTROL (shiftregReceiver_SR_AUX_CONTROL_REG)

#define shiftregReceiver_IN_FIFO_SHFT_MASK  (shiftregReceiver_IN_FIFO_SHIFT_MASK)
#define shiftregReceiver_OUT_FIFO_SHFT_MASK (shiftregReceiver_OUT_FIFO_SHFIT_MASK)

#define shiftregReceiver_RET_FIFO_BAD_PARAM (0xFFu)

#endif /* (CY_SHIFTREG_shiftregReceiver_H) */


/* [] END OF FILE */
