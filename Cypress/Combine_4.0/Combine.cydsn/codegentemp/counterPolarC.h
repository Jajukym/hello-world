/*******************************************************************************
* File Name: counterPolarC.h  
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
    
#if !defined(CY_COUNTER_counterPolarC_H)
#define CY_COUNTER_counterPolarC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 counterPolarC_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Error message for removed counterPolarC_CounterUDB_sCTRLReg_ctrlreg through optimization */
#ifdef counterPolarC_CounterUDB_sCTRLReg_ctrlreg__REMOVED
    #error Counter_v3_0 detected with a constant 0 for the enable, a \
                                constant 0 for the count or constant 1 for \
                                the reset. This will prevent the component from\
                                operating.
#endif /* counterPolarC_CounterUDB_sCTRLReg_ctrlreg__REMOVED */


/**************************************
*           Parameter Defaults        
**************************************/

#define counterPolarC_Resolution            8u
#define counterPolarC_UsingFixedFunction    0u
#define counterPolarC_ControlRegRemoved     0u
#define counterPolarC_COMPARE_MODE_SOFTWARE 0u
#define counterPolarC_CAPTURE_MODE_SOFTWARE 0u
#define counterPolarC_RunModeUsed           0u


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

    #if (!counterPolarC_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!counterPolarC_ControlRegRemoved) */

}counterPolarC_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    counterPolarC_Start(void) ;
void    counterPolarC_Stop(void) ;
void    counterPolarC_SetInterruptMode(uint8 interruptsMask) ;
uint8   counterPolarC_ReadStatusRegister(void) ;
#define counterPolarC_GetInterruptSource() counterPolarC_ReadStatusRegister()
#if(!counterPolarC_ControlRegRemoved)
    uint8   counterPolarC_ReadControlRegister(void) ;
    void    counterPolarC_WriteControlRegister(uint8 control) \
        ;
#endif /* (!counterPolarC_ControlRegRemoved) */
#if (!(counterPolarC_UsingFixedFunction && (CY_PSOC5A)))
    void    counterPolarC_WriteCounter(uint8 counter) \
            ; 
#endif /* (!(counterPolarC_UsingFixedFunction && (CY_PSOC5A))) */
uint8  counterPolarC_ReadCounter(void) ;
uint8  counterPolarC_ReadCapture(void) ;
void    counterPolarC_WritePeriod(uint8 period) \
    ;
uint8  counterPolarC_ReadPeriod( void ) ;
#if (!counterPolarC_UsingFixedFunction)
    void    counterPolarC_WriteCompare(uint8 compare) \
        ;
    uint8  counterPolarC_ReadCompare( void ) \
        ;
#endif /* (!counterPolarC_UsingFixedFunction) */

#if (counterPolarC_COMPARE_MODE_SOFTWARE)
    void    counterPolarC_SetCompareMode(uint8 compareMode) ;
#endif /* (counterPolarC_COMPARE_MODE_SOFTWARE) */
#if (counterPolarC_CAPTURE_MODE_SOFTWARE)
    void    counterPolarC_SetCaptureMode(uint8 captureMode) ;
#endif /* (counterPolarC_CAPTURE_MODE_SOFTWARE) */
void counterPolarC_ClearFIFO(void)     ;
void counterPolarC_Init(void)          ;
void counterPolarC_Enable(void)        ;
void counterPolarC_SaveConfig(void)    ;
void counterPolarC_RestoreConfig(void) ;
void counterPolarC_Sleep(void)         ;
void counterPolarC_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define counterPolarC__B_COUNTER__LESS_THAN 1
#define counterPolarC__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define counterPolarC__B_COUNTER__EQUAL 0
#define counterPolarC__B_COUNTER__GREATER_THAN 3
#define counterPolarC__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define counterPolarC__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define counterPolarC_CMP_MODE_LT 1u
#define counterPolarC_CMP_MODE_LTE 2u
#define counterPolarC_CMP_MODE_EQ 0u
#define counterPolarC_CMP_MODE_GT 3u
#define counterPolarC_CMP_MODE_GTE 4u
#define counterPolarC_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define counterPolarC__B_COUNTER__NONE 0
#define counterPolarC__B_COUNTER__RISING_EDGE 1
#define counterPolarC__B_COUNTER__FALLING_EDGE 2
#define counterPolarC__B_COUNTER__EITHER_EDGE 3
#define counterPolarC__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define counterPolarC_CAP_MODE_NONE 0u
#define counterPolarC_CAP_MODE_RISE 1u
#define counterPolarC_CAP_MODE_FALL 2u
#define counterPolarC_CAP_MODE_BOTH 3u
#define counterPolarC_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define counterPolarC_CAPTURE_MODE_CONF       1u
#define counterPolarC_INIT_PERIOD_VALUE       255u
#define counterPolarC_INIT_COUNTER_VALUE      0u
#if (counterPolarC_UsingFixedFunction)
#define counterPolarC_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << counterPolarC_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define counterPolarC_INIT_COMPARE_VALUE      255u
#define counterPolarC_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << counterPolarC_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << counterPolarC_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << counterPolarC_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << counterPolarC_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << counterPolarC_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define counterPolarC_DEFAULT_COMPARE_MODE    0u

#if( 0 != counterPolarC_CAPTURE_MODE_CONF)
    #define counterPolarC_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)1u << counterPolarC_CTRL_CAPMODE0_SHIFT))
#else    
    #define counterPolarC_DEFAULT_CAPTURE_MODE    (1u )
#endif /* ( 0 != counterPolarC_CAPTURE_MODE_CONF) */

#endif /* (counterPolarC_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (counterPolarC_UsingFixedFunction)
    #define counterPolarC_STATICCOUNT_LSB     (*(reg16 *) counterPolarC_CounterHW__CAP0 )
    #define counterPolarC_STATICCOUNT_LSB_PTR ( (reg16 *) counterPolarC_CounterHW__CAP0 )
    #define counterPolarC_PERIOD_LSB          (*(reg16 *) counterPolarC_CounterHW__PER0 )
    #define counterPolarC_PERIOD_LSB_PTR      ( (reg16 *) counterPolarC_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define counterPolarC_COMPARE_LSB         (*(reg16 *) counterPolarC_CounterHW__CNT_CMP0 )
    #define counterPolarC_COMPARE_LSB_PTR     ( (reg16 *) counterPolarC_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define counterPolarC_COUNTER_LSB         (*(reg16 *) counterPolarC_CounterHW__CNT_CMP0 )
    #define counterPolarC_COUNTER_LSB_PTR     ( (reg16 *) counterPolarC_CounterHW__CNT_CMP0 )
    #define counterPolarC_RT1                 (*(reg8 *) counterPolarC_CounterHW__RT1)
    #define counterPolarC_RT1_PTR             ( (reg8 *) counterPolarC_CounterHW__RT1)
#else
    
    #if (counterPolarC_Resolution <= 8u) /* 8-bit Counter */
    
        #define counterPolarC_STATICCOUNT_LSB     (*(reg8 *) \
            counterPolarC_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define counterPolarC_STATICCOUNT_LSB_PTR ( (reg8 *) \
            counterPolarC_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define counterPolarC_PERIOD_LSB          (*(reg8 *) \
            counterPolarC_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define counterPolarC_PERIOD_LSB_PTR      ( (reg8 *) \
            counterPolarC_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define counterPolarC_COMPARE_LSB         (*(reg8 *) \
            counterPolarC_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define counterPolarC_COMPARE_LSB_PTR     ( (reg8 *) \
            counterPolarC_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define counterPolarC_COUNTER_LSB         (*(reg8 *) \
            counterPolarC_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define counterPolarC_COUNTER_LSB_PTR     ( (reg8 *)\
            counterPolarC_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #elif(counterPolarC_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define counterPolarC_STATICCOUNT_LSB     (*(reg16 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define counterPolarC_STATICCOUNT_LSB_PTR ( (reg16 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define counterPolarC_PERIOD_LSB          (*(reg16 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define counterPolarC_PERIOD_LSB_PTR      ( (reg16 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define counterPolarC_COMPARE_LSB         (*(reg16 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define counterPolarC_COMPARE_LSB_PTR     ( (reg16 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define counterPolarC_COUNTER_LSB         (*(reg16 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define counterPolarC_COUNTER_LSB_PTR     ( (reg16 *)\
                counterPolarC_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define counterPolarC_STATICCOUNT_LSB     (*(reg16 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define counterPolarC_STATICCOUNT_LSB_PTR ( (reg16 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define counterPolarC_PERIOD_LSB          (*(reg16 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define counterPolarC_PERIOD_LSB_PTR      ( (reg16 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define counterPolarC_COMPARE_LSB         (*(reg16 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define counterPolarC_COMPARE_LSB_PTR     ( (reg16 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define counterPolarC_COUNTER_LSB         (*(reg16 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )  
            #define counterPolarC_COUNTER_LSB_PTR     ( (reg16 *)\
                counterPolarC_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(counterPolarC_Resolution <= 24u) /* 24-bit Counter */
        
        #define counterPolarC_STATICCOUNT_LSB     (*(reg32 *) \
            counterPolarC_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define counterPolarC_STATICCOUNT_LSB_PTR ( (reg32 *) \
            counterPolarC_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define counterPolarC_PERIOD_LSB          (*(reg32 *) \
            counterPolarC_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define counterPolarC_PERIOD_LSB_PTR      ( (reg32 *) \
            counterPolarC_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define counterPolarC_COMPARE_LSB         (*(reg32 *) \
            counterPolarC_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define counterPolarC_COMPARE_LSB_PTR     ( (reg32 *) \
            counterPolarC_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define counterPolarC_COUNTER_LSB         (*(reg32 *) \
            counterPolarC_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define counterPolarC_COUNTER_LSB_PTR     ( (reg32 *)\
            counterPolarC_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define counterPolarC_STATICCOUNT_LSB     (*(reg32 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define counterPolarC_STATICCOUNT_LSB_PTR ( (reg32 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define counterPolarC_PERIOD_LSB          (*(reg32 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define counterPolarC_PERIOD_LSB_PTR      ( (reg32 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define counterPolarC_COMPARE_LSB         (*(reg32 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define counterPolarC_COMPARE_LSB_PTR     ( (reg32 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define counterPolarC_COUNTER_LSB         (*(reg32 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define counterPolarC_COUNTER_LSB_PTR     ( (reg32 *)\
                counterPolarC_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define counterPolarC_STATICCOUNT_LSB     (*(reg32 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define counterPolarC_STATICCOUNT_LSB_PTR ( (reg32 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define counterPolarC_PERIOD_LSB          (*(reg32 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define counterPolarC_PERIOD_LSB_PTR      ( (reg32 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define counterPolarC_COMPARE_LSB         (*(reg32 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define counterPolarC_COMPARE_LSB_PTR     ( (reg32 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define counterPolarC_COUNTER_LSB         (*(reg32 *) \
                counterPolarC_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )  
            #define counterPolarC_COUNTER_LSB_PTR     ( (reg32 *)\
                counterPolarC_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define counterPolarC_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                counterPolarC_CounterUDB_sC8_counterdp_u0__A0_REG )
				
    #define counterPolarC_AUX_CONTROLDP0 \
        (*(reg8 *) counterPolarC_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #define counterPolarC_AUX_CONTROLDP0_PTR \
        ( (reg8 *) counterPolarC_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (counterPolarC_Resolution == 16 || counterPolarC_Resolution == 24 || counterPolarC_Resolution == 32)
       #define counterPolarC_AUX_CONTROLDP1 \
           (*(reg8 *) counterPolarC_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
       #define counterPolarC_AUX_CONTROLDP1_PTR \
           ( (reg8 *) counterPolarC_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (counterPolarC_Resolution == 16 || counterPolarC_Resolution == 24 || counterPolarC_Resolution == 32) */
    
    #if (counterPolarC_Resolution == 24 || counterPolarC_Resolution == 32)
       #define counterPolarC_AUX_CONTROLDP2 \
           (*(reg8 *) counterPolarC_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
       #define counterPolarC_AUX_CONTROLDP2_PTR \
           ( (reg8 *) counterPolarC_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (counterPolarC_Resolution == 24 || counterPolarC_Resolution == 32) */
    
    #if (counterPolarC_Resolution == 32)
       #define counterPolarC_AUX_CONTROLDP3 \
           (*(reg8 *) counterPolarC_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
       #define counterPolarC_AUX_CONTROLDP3_PTR \
           ( (reg8 *) counterPolarC_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (counterPolarC_Resolution == 32) */

#endif  /* (counterPolarC_UsingFixedFunction) */

#if (counterPolarC_UsingFixedFunction)
    #define counterPolarC_STATUS         (*(reg8 *) counterPolarC_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define counterPolarC_STATUS_MASK             (*(reg8 *) counterPolarC_CounterHW__SR0 )
    #define counterPolarC_STATUS_MASK_PTR         ( (reg8 *) counterPolarC_CounterHW__SR0 )
    #define counterPolarC_CONTROL                 (*(reg8 *) counterPolarC_CounterHW__CFG0)
    #define counterPolarC_CONTROL_PTR             ( (reg8 *) counterPolarC_CounterHW__CFG0)
    #define counterPolarC_CONTROL2                (*(reg8 *) counterPolarC_CounterHW__CFG1)
    #define counterPolarC_CONTROL2_PTR            ( (reg8 *) counterPolarC_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define counterPolarC_CONTROL3       (*(reg8 *) counterPolarC_CounterHW__CFG2)
        #define counterPolarC_CONTROL3_PTR   ( (reg8 *) counterPolarC_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define counterPolarC_GLOBAL_ENABLE           (*(reg8 *) counterPolarC_CounterHW__PM_ACT_CFG)
    #define counterPolarC_GLOBAL_ENABLE_PTR       ( (reg8 *) counterPolarC_CounterHW__PM_ACT_CFG)
    #define counterPolarC_GLOBAL_STBY_ENABLE      (*(reg8 *) counterPolarC_CounterHW__PM_STBY_CFG)
    #define counterPolarC_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) counterPolarC_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define counterPolarC_BLOCK_EN_MASK          counterPolarC_CounterHW__PM_ACT_MSK
    #define counterPolarC_BLOCK_STBY_EN_MASK     counterPolarC_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define counterPolarC_CTRL_ENABLE_SHIFT      0x00u
    #define counterPolarC_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define counterPolarC_CTRL_ENABLE            ((uint8)((uint8)0x01u << counterPolarC_CTRL_ENABLE_SHIFT))         
    #define counterPolarC_ONESHOT                ((uint8)((uint8)0x01u << counterPolarC_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define counterPolarC_CTRL_MODE_SHIFT        0x01u    
        #define counterPolarC_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << counterPolarC_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define counterPolarC_CTRL_MODE_SHIFT        0x00u    
        #define counterPolarC_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << counterPolarC_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define counterPolarC_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define counterPolarC_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << counterPolarC_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define counterPolarC_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define counterPolarC_STATUS_ZERO_INT_EN_MASK_SHIFT      (counterPolarC_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define counterPolarC_STATUS_ZERO            ((uint8)((uint8)0x01u << counterPolarC_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define counterPolarC_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)counterPolarC_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define counterPolarC_RT1_SHIFT            0x04u
    #define counterPolarC_RT1_MASK             ((uint8)((uint8)0x03u << counterPolarC_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define counterPolarC_SYNC                 ((uint8)((uint8)0x03u << counterPolarC_RT1_SHIFT))
    #define counterPolarC_SYNCDSI_SHIFT        0x00u
    #define counterPolarC_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << counterPolarC_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define counterPolarC_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << counterPolarC_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !counterPolarC_UsingFixedFunction */
    #define counterPolarC_STATUS               (* (reg8 *) counterPolarC_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define counterPolarC_STATUS_PTR           (  (reg8 *) counterPolarC_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define counterPolarC_STATUS_MASK          (* (reg8 *) counterPolarC_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define counterPolarC_STATUS_MASK_PTR      (  (reg8 *) counterPolarC_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define counterPolarC_STATUS_AUX_CTRL      (*(reg8 *) counterPolarC_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define counterPolarC_STATUS_AUX_CTRL_PTR  ( (reg8 *) counterPolarC_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define counterPolarC_CONTROL              (* (reg8 *) counterPolarC_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )
    #define counterPolarC_CONTROL_PTR          (  (reg8 *) counterPolarC_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define counterPolarC_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define counterPolarC_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define counterPolarC_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define counterPolarC_CTRL_CMPMODE_MASK      0x07u 
    #define counterPolarC_CTRL_CAPMODE_MASK      0x03u  
    #define counterPolarC_CTRL_RESET             ((uint8)((uint8)0x01u << counterPolarC_CTRL_RESET_SHIFT))  
    #define counterPolarC_CTRL_ENABLE            ((uint8)((uint8)0x01u << counterPolarC_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define counterPolarC_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define counterPolarC_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define counterPolarC_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define counterPolarC_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define counterPolarC_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define counterPolarC_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define counterPolarC_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define counterPolarC_STATUS_CMP_INT_EN_MASK_SHIFT       counterPolarC_STATUS_CMP_SHIFT       
    #define counterPolarC_STATUS_ZERO_INT_EN_MASK_SHIFT      counterPolarC_STATUS_ZERO_SHIFT      
    #define counterPolarC_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  counterPolarC_STATUS_OVERFLOW_SHIFT  
    #define counterPolarC_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT counterPolarC_STATUS_UNDERFLOW_SHIFT 
    #define counterPolarC_STATUS_CAPTURE_INT_EN_MASK_SHIFT   counterPolarC_STATUS_CAPTURE_SHIFT   
    #define counterPolarC_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  counterPolarC_STATUS_FIFOFULL_SHIFT  
    #define counterPolarC_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  counterPolarC_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define counterPolarC_STATUS_CMP             ((uint8)((uint8)0x01u << counterPolarC_STATUS_CMP_SHIFT))  
    #define counterPolarC_STATUS_ZERO            ((uint8)((uint8)0x01u << counterPolarC_STATUS_ZERO_SHIFT)) 
    #define counterPolarC_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << counterPolarC_STATUS_OVERFLOW_SHIFT)) 
    #define counterPolarC_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << counterPolarC_STATUS_UNDERFLOW_SHIFT)) 
    #define counterPolarC_STATUS_CAPTURE         ((uint8)((uint8)0x01u << counterPolarC_STATUS_CAPTURE_SHIFT)) 
    #define counterPolarC_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << counterPolarC_STATUS_FIFOFULL_SHIFT))
    #define counterPolarC_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << counterPolarC_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define counterPolarC_STATUS_CMP_INT_EN_MASK            counterPolarC_STATUS_CMP                    
    #define counterPolarC_STATUS_ZERO_INT_EN_MASK           counterPolarC_STATUS_ZERO            
    #define counterPolarC_STATUS_OVERFLOW_INT_EN_MASK       counterPolarC_STATUS_OVERFLOW        
    #define counterPolarC_STATUS_UNDERFLOW_INT_EN_MASK      counterPolarC_STATUS_UNDERFLOW       
    #define counterPolarC_STATUS_CAPTURE_INT_EN_MASK        counterPolarC_STATUS_CAPTURE         
    #define counterPolarC_STATUS_FIFOFULL_INT_EN_MASK       counterPolarC_STATUS_FIFOFULL        
    #define counterPolarC_STATUS_FIFONEMP_INT_EN_MASK       counterPolarC_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define counterPolarC_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define counterPolarC_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define counterPolarC_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define counterPolarC_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define counterPolarC_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define counterPolarC_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* counterPolarC_UsingFixedFunction */

#endif  /* CY_COUNTER_counterPolarC_H */


/* [] END OF FILE */

