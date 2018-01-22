/*******************************************************************************
* File Name: counterShift.h  
* Version 3.0
*
*  Description:
*   Contains the function prototypes and constants available to the counter
*   user module.
*
*   Note:
*    None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
    
#if !defined(CY_COUNTER_counterShift_H)
#define CY_COUNTER_counterShift_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 counterShift_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Error message for removed counterShift_CounterUDB_sCTRLReg_ctrlreg through optimization */
#ifdef counterShift_CounterUDB_sCTRLReg_ctrlreg__REMOVED
    #error Counter_v3_0 detected with a constant 0 for the enable, a \
                                constant 0 for the count or constant 1 for \
                                the reset. This will prevent the component from\
                                operating.
#endif /* counterShift_CounterUDB_sCTRLReg_ctrlreg__REMOVED */


/**************************************
*           Parameter Defaults        
**************************************/

#define counterShift_Resolution            8u
#define counterShift_UsingFixedFunction    1u
#define counterShift_ControlRegRemoved     0u
#define counterShift_COMPARE_MODE_SOFTWARE 0u
#define counterShift_CAPTURE_MODE_SOFTWARE 0u
#define counterShift_RunModeUsed           0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Mode API Support
 * Backup structure for Sleep Wake up operations
 *************************************************************************/
typedef struct
{
    uint8 CounterEnableState; 
    uint8 CounterUdb;         /* Current Counter Value */

    #if (!counterShift_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!counterShift_ControlRegRemoved) */

}counterShift_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    counterShift_Start(void) ;
void    counterShift_Stop(void) ;
void    counterShift_SetInterruptMode(uint8 interruptsMask) ;
uint8   counterShift_ReadStatusRegister(void) ;
#define counterShift_GetInterruptSource() counterShift_ReadStatusRegister()
#if(!counterShift_ControlRegRemoved)
    uint8   counterShift_ReadControlRegister(void) ;
    void    counterShift_WriteControlRegister(uint8 control) \
        ;
#endif /* (!counterShift_ControlRegRemoved) */
#if (!(counterShift_UsingFixedFunction && (CY_PSOC5A)))
    void    counterShift_WriteCounter(uint8 counter) \
            ; 
#endif /* (!(counterShift_UsingFixedFunction && (CY_PSOC5A))) */
uint8  counterShift_ReadCounter(void) ;
uint8  counterShift_ReadCapture(void) ;
void    counterShift_WritePeriod(uint8 period) \
    ;
uint8  counterShift_ReadPeriod( void ) ;
#if (!counterShift_UsingFixedFunction)
    void    counterShift_WriteCompare(uint8 compare) \
        ;
    uint8  counterShift_ReadCompare( void ) \
        ;
#endif /* (!counterShift_UsingFixedFunction) */

#if (counterShift_COMPARE_MODE_SOFTWARE)
    void    counterShift_SetCompareMode(uint8 compareMode) ;
#endif /* (counterShift_COMPARE_MODE_SOFTWARE) */
#if (counterShift_CAPTURE_MODE_SOFTWARE)
    void    counterShift_SetCaptureMode(uint8 captureMode) ;
#endif /* (counterShift_CAPTURE_MODE_SOFTWARE) */
void counterShift_ClearFIFO(void)     ;
void counterShift_Init(void)          ;
void counterShift_Enable(void)        ;
void counterShift_SaveConfig(void)    ;
void counterShift_RestoreConfig(void) ;
void counterShift_Sleep(void)         ;
void counterShift_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define counterShift__B_COUNTER__LESS_THAN 1
#define counterShift__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define counterShift__B_COUNTER__EQUAL 0
#define counterShift__B_COUNTER__GREATER_THAN 3
#define counterShift__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define counterShift__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define counterShift_CMP_MODE_LT 1u
#define counterShift_CMP_MODE_LTE 2u
#define counterShift_CMP_MODE_EQ 0u
#define counterShift_CMP_MODE_GT 3u
#define counterShift_CMP_MODE_GTE 4u
#define counterShift_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define counterShift__B_COUNTER__NONE 0
#define counterShift__B_COUNTER__RISING_EDGE 1
#define counterShift__B_COUNTER__FALLING_EDGE 2
#define counterShift__B_COUNTER__EITHER_EDGE 3
#define counterShift__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define counterShift_CAP_MODE_NONE 0u
#define counterShift_CAP_MODE_RISE 1u
#define counterShift_CAP_MODE_FALL 2u
#define counterShift_CAP_MODE_BOTH 3u
#define counterShift_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define counterShift_CAPTURE_MODE_CONF       0u
#define counterShift_INIT_PERIOD_VALUE       8u
#define counterShift_INIT_COUNTER_VALUE      8u
#if (counterShift_UsingFixedFunction)
#define counterShift_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << counterShift_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define counterShift_INIT_COMPARE_VALUE      2u
#define counterShift_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << counterShift_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << counterShift_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << counterShift_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << counterShift_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << counterShift_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define counterShift_DEFAULT_COMPARE_MODE    1u

#if( 0 != counterShift_CAPTURE_MODE_CONF)
    #define counterShift_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)0u << counterShift_CTRL_CAPMODE0_SHIFT))
#else    
    #define counterShift_DEFAULT_CAPTURE_MODE    (0u )
#endif /* ( 0 != counterShift_CAPTURE_MODE_CONF) */

#endif /* (counterShift_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (counterShift_UsingFixedFunction)
    #define counterShift_STATICCOUNT_LSB     (*(reg16 *) counterShift_CounterHW__CAP0 )
    #define counterShift_STATICCOUNT_LSB_PTR ( (reg16 *) counterShift_CounterHW__CAP0 )
    #define counterShift_PERIOD_LSB          (*(reg16 *) counterShift_CounterHW__PER0 )
    #define counterShift_PERIOD_LSB_PTR      ( (reg16 *) counterShift_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define counterShift_COMPARE_LSB         (*(reg16 *) counterShift_CounterHW__CNT_CMP0 )
    #define counterShift_COMPARE_LSB_PTR     ( (reg16 *) counterShift_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define counterShift_COUNTER_LSB         (*(reg16 *) counterShift_CounterHW__CNT_CMP0 )
    #define counterShift_COUNTER_LSB_PTR     ( (reg16 *) counterShift_CounterHW__CNT_CMP0 )
    #define counterShift_RT1                 (*(reg8 *) counterShift_CounterHW__RT1)
    #define counterShift_RT1_PTR             ( (reg8 *) counterShift_CounterHW__RT1)
#else
    
    #if (counterShift_Resolution <= 8u) /* 8-bit Counter */
    
        #define counterShift_STATICCOUNT_LSB     (*(reg8 *) \
            counterShift_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define counterShift_STATICCOUNT_LSB_PTR ( (reg8 *) \
            counterShift_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define counterShift_PERIOD_LSB          (*(reg8 *) \
            counterShift_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define counterShift_PERIOD_LSB_PTR      ( (reg8 *) \
            counterShift_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define counterShift_COMPARE_LSB         (*(reg8 *) \
            counterShift_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define counterShift_COMPARE_LSB_PTR     ( (reg8 *) \
            counterShift_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define counterShift_COUNTER_LSB         (*(reg8 *) \
            counterShift_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define counterShift_COUNTER_LSB_PTR     ( (reg8 *)\
            counterShift_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #elif(counterShift_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define counterShift_STATICCOUNT_LSB     (*(reg16 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define counterShift_STATICCOUNT_LSB_PTR ( (reg16 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define counterShift_PERIOD_LSB          (*(reg16 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define counterShift_PERIOD_LSB_PTR      ( (reg16 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define counterShift_COMPARE_LSB         (*(reg16 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define counterShift_COMPARE_LSB_PTR     ( (reg16 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define counterShift_COUNTER_LSB         (*(reg16 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define counterShift_COUNTER_LSB_PTR     ( (reg16 *)\
                counterShift_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define counterShift_STATICCOUNT_LSB     (*(reg16 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define counterShift_STATICCOUNT_LSB_PTR ( (reg16 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define counterShift_PERIOD_LSB          (*(reg16 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define counterShift_PERIOD_LSB_PTR      ( (reg16 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define counterShift_COMPARE_LSB         (*(reg16 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define counterShift_COMPARE_LSB_PTR     ( (reg16 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define counterShift_COUNTER_LSB         (*(reg16 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )  
            #define counterShift_COUNTER_LSB_PTR     ( (reg16 *)\
                counterShift_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(counterShift_Resolution <= 24u) /* 24-bit Counter */
        
        #define counterShift_STATICCOUNT_LSB     (*(reg32 *) \
            counterShift_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define counterShift_STATICCOUNT_LSB_PTR ( (reg32 *) \
            counterShift_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define counterShift_PERIOD_LSB          (*(reg32 *) \
            counterShift_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define counterShift_PERIOD_LSB_PTR      ( (reg32 *) \
            counterShift_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define counterShift_COMPARE_LSB         (*(reg32 *) \
            counterShift_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define counterShift_COMPARE_LSB_PTR     ( (reg32 *) \
            counterShift_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define counterShift_COUNTER_LSB         (*(reg32 *) \
            counterShift_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define counterShift_COUNTER_LSB_PTR     ( (reg32 *)\
            counterShift_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define counterShift_STATICCOUNT_LSB     (*(reg32 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define counterShift_STATICCOUNT_LSB_PTR ( (reg32 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define counterShift_PERIOD_LSB          (*(reg32 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define counterShift_PERIOD_LSB_PTR      ( (reg32 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define counterShift_COMPARE_LSB         (*(reg32 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define counterShift_COMPARE_LSB_PTR     ( (reg32 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define counterShift_COUNTER_LSB         (*(reg32 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define counterShift_COUNTER_LSB_PTR     ( (reg32 *)\
                counterShift_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define counterShift_STATICCOUNT_LSB     (*(reg32 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define counterShift_STATICCOUNT_LSB_PTR ( (reg32 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define counterShift_PERIOD_LSB          (*(reg32 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define counterShift_PERIOD_LSB_PTR      ( (reg32 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define counterShift_COMPARE_LSB         (*(reg32 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define counterShift_COMPARE_LSB_PTR     ( (reg32 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define counterShift_COUNTER_LSB         (*(reg32 *) \
                counterShift_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )  
            #define counterShift_COUNTER_LSB_PTR     ( (reg32 *)\
                counterShift_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define counterShift_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                counterShift_CounterUDB_sC8_counterdp_u0__A0_REG )
				
    #define counterShift_AUX_CONTROLDP0 \
        (*(reg8 *) counterShift_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #define counterShift_AUX_CONTROLDP0_PTR \
        ( (reg8 *) counterShift_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (counterShift_Resolution == 16 || counterShift_Resolution == 24 || counterShift_Resolution == 32)
       #define counterShift_AUX_CONTROLDP1 \
           (*(reg8 *) counterShift_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
       #define counterShift_AUX_CONTROLDP1_PTR \
           ( (reg8 *) counterShift_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (counterShift_Resolution == 16 || counterShift_Resolution == 24 || counterShift_Resolution == 32) */
    
    #if (counterShift_Resolution == 24 || counterShift_Resolution == 32)
       #define counterShift_AUX_CONTROLDP2 \
           (*(reg8 *) counterShift_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
       #define counterShift_AUX_CONTROLDP2_PTR \
           ( (reg8 *) counterShift_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (counterShift_Resolution == 24 || counterShift_Resolution == 32) */
    
    #if (counterShift_Resolution == 32)
       #define counterShift_AUX_CONTROLDP3 \
           (*(reg8 *) counterShift_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
       #define counterShift_AUX_CONTROLDP3_PTR \
           ( (reg8 *) counterShift_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (counterShift_Resolution == 32) */

#endif  /* (counterShift_UsingFixedFunction) */

#if (counterShift_UsingFixedFunction)
    #define counterShift_STATUS         (*(reg8 *) counterShift_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define counterShift_STATUS_MASK             (*(reg8 *) counterShift_CounterHW__SR0 )
    #define counterShift_STATUS_MASK_PTR         ( (reg8 *) counterShift_CounterHW__SR0 )
    #define counterShift_CONTROL                 (*(reg8 *) counterShift_CounterHW__CFG0)
    #define counterShift_CONTROL_PTR             ( (reg8 *) counterShift_CounterHW__CFG0)
    #define counterShift_CONTROL2                (*(reg8 *) counterShift_CounterHW__CFG1)
    #define counterShift_CONTROL2_PTR            ( (reg8 *) counterShift_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define counterShift_CONTROL3       (*(reg8 *) counterShift_CounterHW__CFG2)
        #define counterShift_CONTROL3_PTR   ( (reg8 *) counterShift_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define counterShift_GLOBAL_ENABLE           (*(reg8 *) counterShift_CounterHW__PM_ACT_CFG)
    #define counterShift_GLOBAL_ENABLE_PTR       ( (reg8 *) counterShift_CounterHW__PM_ACT_CFG)
    #define counterShift_GLOBAL_STBY_ENABLE      (*(reg8 *) counterShift_CounterHW__PM_STBY_CFG)
    #define counterShift_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) counterShift_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define counterShift_BLOCK_EN_MASK          counterShift_CounterHW__PM_ACT_MSK
    #define counterShift_BLOCK_STBY_EN_MASK     counterShift_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define counterShift_CTRL_ENABLE_SHIFT      0x00u
    #define counterShift_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define counterShift_CTRL_ENABLE            ((uint8)((uint8)0x01u << counterShift_CTRL_ENABLE_SHIFT))         
    #define counterShift_ONESHOT                ((uint8)((uint8)0x01u << counterShift_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define counterShift_CTRL_MODE_SHIFT        0x01u    
        #define counterShift_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << counterShift_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define counterShift_CTRL_MODE_SHIFT        0x00u    
        #define counterShift_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << counterShift_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define counterShift_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define counterShift_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << counterShift_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define counterShift_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define counterShift_STATUS_ZERO_INT_EN_MASK_SHIFT      (counterShift_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define counterShift_STATUS_ZERO            ((uint8)((uint8)0x01u << counterShift_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define counterShift_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)counterShift_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define counterShift_RT1_SHIFT            0x04u
    #define counterShift_RT1_MASK             ((uint8)((uint8)0x03u << counterShift_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define counterShift_SYNC                 ((uint8)((uint8)0x03u << counterShift_RT1_SHIFT))
    #define counterShift_SYNCDSI_SHIFT        0x00u
    #define counterShift_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << counterShift_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define counterShift_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << counterShift_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !counterShift_UsingFixedFunction */
    #define counterShift_STATUS               (* (reg8 *) counterShift_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define counterShift_STATUS_PTR           (  (reg8 *) counterShift_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define counterShift_STATUS_MASK          (* (reg8 *) counterShift_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define counterShift_STATUS_MASK_PTR      (  (reg8 *) counterShift_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define counterShift_STATUS_AUX_CTRL      (*(reg8 *) counterShift_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define counterShift_STATUS_AUX_CTRL_PTR  ( (reg8 *) counterShift_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define counterShift_CONTROL              (* (reg8 *) counterShift_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )
    #define counterShift_CONTROL_PTR          (  (reg8 *) counterShift_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define counterShift_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define counterShift_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define counterShift_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define counterShift_CTRL_CMPMODE_MASK      0x07u 
    #define counterShift_CTRL_CAPMODE_MASK      0x03u  
    #define counterShift_CTRL_RESET             ((uint8)((uint8)0x01u << counterShift_CTRL_RESET_SHIFT))  
    #define counterShift_CTRL_ENABLE            ((uint8)((uint8)0x01u << counterShift_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define counterShift_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define counterShift_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define counterShift_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define counterShift_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define counterShift_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define counterShift_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define counterShift_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define counterShift_STATUS_CMP_INT_EN_MASK_SHIFT       counterShift_STATUS_CMP_SHIFT       
    #define counterShift_STATUS_ZERO_INT_EN_MASK_SHIFT      counterShift_STATUS_ZERO_SHIFT      
    #define counterShift_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  counterShift_STATUS_OVERFLOW_SHIFT  
    #define counterShift_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT counterShift_STATUS_UNDERFLOW_SHIFT 
    #define counterShift_STATUS_CAPTURE_INT_EN_MASK_SHIFT   counterShift_STATUS_CAPTURE_SHIFT   
    #define counterShift_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  counterShift_STATUS_FIFOFULL_SHIFT  
    #define counterShift_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  counterShift_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define counterShift_STATUS_CMP             ((uint8)((uint8)0x01u << counterShift_STATUS_CMP_SHIFT))  
    #define counterShift_STATUS_ZERO            ((uint8)((uint8)0x01u << counterShift_STATUS_ZERO_SHIFT)) 
    #define counterShift_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << counterShift_STATUS_OVERFLOW_SHIFT)) 
    #define counterShift_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << counterShift_STATUS_UNDERFLOW_SHIFT)) 
    #define counterShift_STATUS_CAPTURE         ((uint8)((uint8)0x01u << counterShift_STATUS_CAPTURE_SHIFT)) 
    #define counterShift_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << counterShift_STATUS_FIFOFULL_SHIFT))
    #define counterShift_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << counterShift_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define counterShift_STATUS_CMP_INT_EN_MASK            counterShift_STATUS_CMP                    
    #define counterShift_STATUS_ZERO_INT_EN_MASK           counterShift_STATUS_ZERO            
    #define counterShift_STATUS_OVERFLOW_INT_EN_MASK       counterShift_STATUS_OVERFLOW        
    #define counterShift_STATUS_UNDERFLOW_INT_EN_MASK      counterShift_STATUS_UNDERFLOW       
    #define counterShift_STATUS_CAPTURE_INT_EN_MASK        counterShift_STATUS_CAPTURE         
    #define counterShift_STATUS_FIFOFULL_INT_EN_MASK       counterShift_STATUS_FIFOFULL        
    #define counterShift_STATUS_FIFONEMP_INT_EN_MASK       counterShift_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define counterShift_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define counterShift_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define counterShift_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define counterShift_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define counterShift_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define counterShift_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* counterShift_UsingFixedFunction */

#endif  /* CY_COUNTER_counterShift_H */


/* [] END OF FILE */

