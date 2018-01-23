/*******************************************************************************
* File Name: counterANTPlus.h  
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
    
#if !defined(CY_COUNTER_counterANTPlus_H)
#define CY_COUNTER_counterANTPlus_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 counterANTPlus_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Error message for removed counterANTPlus_CounterUDB_sCTRLReg_ctrlreg through optimization */
#ifdef counterANTPlus_CounterUDB_sCTRLReg_ctrlreg__REMOVED
    #error Counter_v3_0 detected with a constant 0 for the enable, a \
                                constant 0 for the count or constant 1 for \
                                the reset. This will prevent the component from\
                                operating.
#endif /* counterANTPlus_CounterUDB_sCTRLReg_ctrlreg__REMOVED */


/**************************************
*           Parameter Defaults        
**************************************/

#define counterANTPlus_Resolution            8u
#define counterANTPlus_UsingFixedFunction    0u
#define counterANTPlus_ControlRegRemoved     0u
#define counterANTPlus_COMPARE_MODE_SOFTWARE 0u
#define counterANTPlus_CAPTURE_MODE_SOFTWARE 0u
#define counterANTPlus_RunModeUsed           0u


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

    #if (!counterANTPlus_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!counterANTPlus_ControlRegRemoved) */

}counterANTPlus_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    counterANTPlus_Start(void) ;
void    counterANTPlus_Stop(void) ;
void    counterANTPlus_SetInterruptMode(uint8 interruptsMask) ;
uint8   counterANTPlus_ReadStatusRegister(void) ;
#define counterANTPlus_GetInterruptSource() counterANTPlus_ReadStatusRegister()
#if(!counterANTPlus_ControlRegRemoved)
    uint8   counterANTPlus_ReadControlRegister(void) ;
    void    counterANTPlus_WriteControlRegister(uint8 control) \
        ;
#endif /* (!counterANTPlus_ControlRegRemoved) */
#if (!(counterANTPlus_UsingFixedFunction && (CY_PSOC5A)))
    void    counterANTPlus_WriteCounter(uint8 counter) \
            ; 
#endif /* (!(counterANTPlus_UsingFixedFunction && (CY_PSOC5A))) */
uint8  counterANTPlus_ReadCounter(void) ;
uint8  counterANTPlus_ReadCapture(void) ;
void    counterANTPlus_WritePeriod(uint8 period) \
    ;
uint8  counterANTPlus_ReadPeriod( void ) ;
#if (!counterANTPlus_UsingFixedFunction)
    void    counterANTPlus_WriteCompare(uint8 compare) \
        ;
    uint8  counterANTPlus_ReadCompare( void ) \
        ;
#endif /* (!counterANTPlus_UsingFixedFunction) */

#if (counterANTPlus_COMPARE_MODE_SOFTWARE)
    void    counterANTPlus_SetCompareMode(uint8 compareMode) ;
#endif /* (counterANTPlus_COMPARE_MODE_SOFTWARE) */
#if (counterANTPlus_CAPTURE_MODE_SOFTWARE)
    void    counterANTPlus_SetCaptureMode(uint8 captureMode) ;
#endif /* (counterANTPlus_CAPTURE_MODE_SOFTWARE) */
void counterANTPlus_ClearFIFO(void)     ;
void counterANTPlus_Init(void)          ;
void counterANTPlus_Enable(void)        ;
void counterANTPlus_SaveConfig(void)    ;
void counterANTPlus_RestoreConfig(void) ;
void counterANTPlus_Sleep(void)         ;
void counterANTPlus_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define counterANTPlus__B_COUNTER__LESS_THAN 1
#define counterANTPlus__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define counterANTPlus__B_COUNTER__EQUAL 0
#define counterANTPlus__B_COUNTER__GREATER_THAN 3
#define counterANTPlus__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define counterANTPlus__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define counterANTPlus_CMP_MODE_LT 1u
#define counterANTPlus_CMP_MODE_LTE 2u
#define counterANTPlus_CMP_MODE_EQ 0u
#define counterANTPlus_CMP_MODE_GT 3u
#define counterANTPlus_CMP_MODE_GTE 4u
#define counterANTPlus_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define counterANTPlus__B_COUNTER__NONE 0
#define counterANTPlus__B_COUNTER__RISING_EDGE 1
#define counterANTPlus__B_COUNTER__FALLING_EDGE 2
#define counterANTPlus__B_COUNTER__EITHER_EDGE 3
#define counterANTPlus__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define counterANTPlus_CAP_MODE_NONE 0u
#define counterANTPlus_CAP_MODE_RISE 1u
#define counterANTPlus_CAP_MODE_FALL 2u
#define counterANTPlus_CAP_MODE_BOTH 3u
#define counterANTPlus_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define counterANTPlus_CAPTURE_MODE_CONF       1u
#define counterANTPlus_INIT_PERIOD_VALUE       255u
#define counterANTPlus_INIT_COUNTER_VALUE      0u
#if (counterANTPlus_UsingFixedFunction)
#define counterANTPlus_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << counterANTPlus_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define counterANTPlus_INIT_COMPARE_VALUE      255u
#define counterANTPlus_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << counterANTPlus_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << counterANTPlus_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << counterANTPlus_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << counterANTPlus_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << counterANTPlus_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define counterANTPlus_DEFAULT_COMPARE_MODE    0u

#if( 0 != counterANTPlus_CAPTURE_MODE_CONF)
    #define counterANTPlus_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)1u << counterANTPlus_CTRL_CAPMODE0_SHIFT))
#else    
    #define counterANTPlus_DEFAULT_CAPTURE_MODE    (1u )
#endif /* ( 0 != counterANTPlus_CAPTURE_MODE_CONF) */

#endif /* (counterANTPlus_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (counterANTPlus_UsingFixedFunction)
    #define counterANTPlus_STATICCOUNT_LSB     (*(reg16 *) counterANTPlus_CounterHW__CAP0 )
    #define counterANTPlus_STATICCOUNT_LSB_PTR ( (reg16 *) counterANTPlus_CounterHW__CAP0 )
    #define counterANTPlus_PERIOD_LSB          (*(reg16 *) counterANTPlus_CounterHW__PER0 )
    #define counterANTPlus_PERIOD_LSB_PTR      ( (reg16 *) counterANTPlus_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define counterANTPlus_COMPARE_LSB         (*(reg16 *) counterANTPlus_CounterHW__CNT_CMP0 )
    #define counterANTPlus_COMPARE_LSB_PTR     ( (reg16 *) counterANTPlus_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define counterANTPlus_COUNTER_LSB         (*(reg16 *) counterANTPlus_CounterHW__CNT_CMP0 )
    #define counterANTPlus_COUNTER_LSB_PTR     ( (reg16 *) counterANTPlus_CounterHW__CNT_CMP0 )
    #define counterANTPlus_RT1                 (*(reg8 *) counterANTPlus_CounterHW__RT1)
    #define counterANTPlus_RT1_PTR             ( (reg8 *) counterANTPlus_CounterHW__RT1)
#else
    
    #if (counterANTPlus_Resolution <= 8u) /* 8-bit Counter */
    
        #define counterANTPlus_STATICCOUNT_LSB     (*(reg8 *) \
            counterANTPlus_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define counterANTPlus_STATICCOUNT_LSB_PTR ( (reg8 *) \
            counterANTPlus_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define counterANTPlus_PERIOD_LSB          (*(reg8 *) \
            counterANTPlus_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define counterANTPlus_PERIOD_LSB_PTR      ( (reg8 *) \
            counterANTPlus_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define counterANTPlus_COMPARE_LSB         (*(reg8 *) \
            counterANTPlus_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define counterANTPlus_COMPARE_LSB_PTR     ( (reg8 *) \
            counterANTPlus_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define counterANTPlus_COUNTER_LSB         (*(reg8 *) \
            counterANTPlus_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define counterANTPlus_COUNTER_LSB_PTR     ( (reg8 *)\
            counterANTPlus_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #elif(counterANTPlus_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define counterANTPlus_STATICCOUNT_LSB     (*(reg16 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define counterANTPlus_STATICCOUNT_LSB_PTR ( (reg16 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define counterANTPlus_PERIOD_LSB          (*(reg16 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define counterANTPlus_PERIOD_LSB_PTR      ( (reg16 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define counterANTPlus_COMPARE_LSB         (*(reg16 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define counterANTPlus_COMPARE_LSB_PTR     ( (reg16 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define counterANTPlus_COUNTER_LSB         (*(reg16 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define counterANTPlus_COUNTER_LSB_PTR     ( (reg16 *)\
                counterANTPlus_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define counterANTPlus_STATICCOUNT_LSB     (*(reg16 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define counterANTPlus_STATICCOUNT_LSB_PTR ( (reg16 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define counterANTPlus_PERIOD_LSB          (*(reg16 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define counterANTPlus_PERIOD_LSB_PTR      ( (reg16 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define counterANTPlus_COMPARE_LSB         (*(reg16 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define counterANTPlus_COMPARE_LSB_PTR     ( (reg16 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define counterANTPlus_COUNTER_LSB         (*(reg16 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )  
            #define counterANTPlus_COUNTER_LSB_PTR     ( (reg16 *)\
                counterANTPlus_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(counterANTPlus_Resolution <= 24u) /* 24-bit Counter */
        
        #define counterANTPlus_STATICCOUNT_LSB     (*(reg32 *) \
            counterANTPlus_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define counterANTPlus_STATICCOUNT_LSB_PTR ( (reg32 *) \
            counterANTPlus_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define counterANTPlus_PERIOD_LSB          (*(reg32 *) \
            counterANTPlus_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define counterANTPlus_PERIOD_LSB_PTR      ( (reg32 *) \
            counterANTPlus_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define counterANTPlus_COMPARE_LSB         (*(reg32 *) \
            counterANTPlus_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define counterANTPlus_COMPARE_LSB_PTR     ( (reg32 *) \
            counterANTPlus_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define counterANTPlus_COUNTER_LSB         (*(reg32 *) \
            counterANTPlus_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define counterANTPlus_COUNTER_LSB_PTR     ( (reg32 *)\
            counterANTPlus_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define counterANTPlus_STATICCOUNT_LSB     (*(reg32 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define counterANTPlus_STATICCOUNT_LSB_PTR ( (reg32 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define counterANTPlus_PERIOD_LSB          (*(reg32 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define counterANTPlus_PERIOD_LSB_PTR      ( (reg32 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define counterANTPlus_COMPARE_LSB         (*(reg32 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define counterANTPlus_COMPARE_LSB_PTR     ( (reg32 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define counterANTPlus_COUNTER_LSB         (*(reg32 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define counterANTPlus_COUNTER_LSB_PTR     ( (reg32 *)\
                counterANTPlus_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define counterANTPlus_STATICCOUNT_LSB     (*(reg32 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define counterANTPlus_STATICCOUNT_LSB_PTR ( (reg32 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define counterANTPlus_PERIOD_LSB          (*(reg32 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define counterANTPlus_PERIOD_LSB_PTR      ( (reg32 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define counterANTPlus_COMPARE_LSB         (*(reg32 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define counterANTPlus_COMPARE_LSB_PTR     ( (reg32 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define counterANTPlus_COUNTER_LSB         (*(reg32 *) \
                counterANTPlus_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )  
            #define counterANTPlus_COUNTER_LSB_PTR     ( (reg32 *)\
                counterANTPlus_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define counterANTPlus_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                counterANTPlus_CounterUDB_sC8_counterdp_u0__A0_REG )
				
    #define counterANTPlus_AUX_CONTROLDP0 \
        (*(reg8 *) counterANTPlus_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #define counterANTPlus_AUX_CONTROLDP0_PTR \
        ( (reg8 *) counterANTPlus_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (counterANTPlus_Resolution == 16 || counterANTPlus_Resolution == 24 || counterANTPlus_Resolution == 32)
       #define counterANTPlus_AUX_CONTROLDP1 \
           (*(reg8 *) counterANTPlus_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
       #define counterANTPlus_AUX_CONTROLDP1_PTR \
           ( (reg8 *) counterANTPlus_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (counterANTPlus_Resolution == 16 || counterANTPlus_Resolution == 24 || counterANTPlus_Resolution == 32) */
    
    #if (counterANTPlus_Resolution == 24 || counterANTPlus_Resolution == 32)
       #define counterANTPlus_AUX_CONTROLDP2 \
           (*(reg8 *) counterANTPlus_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
       #define counterANTPlus_AUX_CONTROLDP2_PTR \
           ( (reg8 *) counterANTPlus_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (counterANTPlus_Resolution == 24 || counterANTPlus_Resolution == 32) */
    
    #if (counterANTPlus_Resolution == 32)
       #define counterANTPlus_AUX_CONTROLDP3 \
           (*(reg8 *) counterANTPlus_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
       #define counterANTPlus_AUX_CONTROLDP3_PTR \
           ( (reg8 *) counterANTPlus_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (counterANTPlus_Resolution == 32) */

#endif  /* (counterANTPlus_UsingFixedFunction) */

#if (counterANTPlus_UsingFixedFunction)
    #define counterANTPlus_STATUS         (*(reg8 *) counterANTPlus_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define counterANTPlus_STATUS_MASK             (*(reg8 *) counterANTPlus_CounterHW__SR0 )
    #define counterANTPlus_STATUS_MASK_PTR         ( (reg8 *) counterANTPlus_CounterHW__SR0 )
    #define counterANTPlus_CONTROL                 (*(reg8 *) counterANTPlus_CounterHW__CFG0)
    #define counterANTPlus_CONTROL_PTR             ( (reg8 *) counterANTPlus_CounterHW__CFG0)
    #define counterANTPlus_CONTROL2                (*(reg8 *) counterANTPlus_CounterHW__CFG1)
    #define counterANTPlus_CONTROL2_PTR            ( (reg8 *) counterANTPlus_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define counterANTPlus_CONTROL3       (*(reg8 *) counterANTPlus_CounterHW__CFG2)
        #define counterANTPlus_CONTROL3_PTR   ( (reg8 *) counterANTPlus_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define counterANTPlus_GLOBAL_ENABLE           (*(reg8 *) counterANTPlus_CounterHW__PM_ACT_CFG)
    #define counterANTPlus_GLOBAL_ENABLE_PTR       ( (reg8 *) counterANTPlus_CounterHW__PM_ACT_CFG)
    #define counterANTPlus_GLOBAL_STBY_ENABLE      (*(reg8 *) counterANTPlus_CounterHW__PM_STBY_CFG)
    #define counterANTPlus_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) counterANTPlus_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define counterANTPlus_BLOCK_EN_MASK          counterANTPlus_CounterHW__PM_ACT_MSK
    #define counterANTPlus_BLOCK_STBY_EN_MASK     counterANTPlus_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define counterANTPlus_CTRL_ENABLE_SHIFT      0x00u
    #define counterANTPlus_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define counterANTPlus_CTRL_ENABLE            ((uint8)((uint8)0x01u << counterANTPlus_CTRL_ENABLE_SHIFT))         
    #define counterANTPlus_ONESHOT                ((uint8)((uint8)0x01u << counterANTPlus_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define counterANTPlus_CTRL_MODE_SHIFT        0x01u    
        #define counterANTPlus_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << counterANTPlus_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define counterANTPlus_CTRL_MODE_SHIFT        0x00u    
        #define counterANTPlus_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << counterANTPlus_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define counterANTPlus_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define counterANTPlus_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << counterANTPlus_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define counterANTPlus_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define counterANTPlus_STATUS_ZERO_INT_EN_MASK_SHIFT      (counterANTPlus_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define counterANTPlus_STATUS_ZERO            ((uint8)((uint8)0x01u << counterANTPlus_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define counterANTPlus_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)counterANTPlus_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define counterANTPlus_RT1_SHIFT            0x04u
    #define counterANTPlus_RT1_MASK             ((uint8)((uint8)0x03u << counterANTPlus_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define counterANTPlus_SYNC                 ((uint8)((uint8)0x03u << counterANTPlus_RT1_SHIFT))
    #define counterANTPlus_SYNCDSI_SHIFT        0x00u
    #define counterANTPlus_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << counterANTPlus_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define counterANTPlus_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << counterANTPlus_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !counterANTPlus_UsingFixedFunction */
    #define counterANTPlus_STATUS               (* (reg8 *) counterANTPlus_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define counterANTPlus_STATUS_PTR           (  (reg8 *) counterANTPlus_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define counterANTPlus_STATUS_MASK          (* (reg8 *) counterANTPlus_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define counterANTPlus_STATUS_MASK_PTR      (  (reg8 *) counterANTPlus_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define counterANTPlus_STATUS_AUX_CTRL      (*(reg8 *) counterANTPlus_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define counterANTPlus_STATUS_AUX_CTRL_PTR  ( (reg8 *) counterANTPlus_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define counterANTPlus_CONTROL              (* (reg8 *) counterANTPlus_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )
    #define counterANTPlus_CONTROL_PTR          (  (reg8 *) counterANTPlus_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define counterANTPlus_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define counterANTPlus_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define counterANTPlus_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define counterANTPlus_CTRL_CMPMODE_MASK      0x07u 
    #define counterANTPlus_CTRL_CAPMODE_MASK      0x03u  
    #define counterANTPlus_CTRL_RESET             ((uint8)((uint8)0x01u << counterANTPlus_CTRL_RESET_SHIFT))  
    #define counterANTPlus_CTRL_ENABLE            ((uint8)((uint8)0x01u << counterANTPlus_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define counterANTPlus_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define counterANTPlus_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define counterANTPlus_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define counterANTPlus_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define counterANTPlus_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define counterANTPlus_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define counterANTPlus_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define counterANTPlus_STATUS_CMP_INT_EN_MASK_SHIFT       counterANTPlus_STATUS_CMP_SHIFT       
    #define counterANTPlus_STATUS_ZERO_INT_EN_MASK_SHIFT      counterANTPlus_STATUS_ZERO_SHIFT      
    #define counterANTPlus_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  counterANTPlus_STATUS_OVERFLOW_SHIFT  
    #define counterANTPlus_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT counterANTPlus_STATUS_UNDERFLOW_SHIFT 
    #define counterANTPlus_STATUS_CAPTURE_INT_EN_MASK_SHIFT   counterANTPlus_STATUS_CAPTURE_SHIFT   
    #define counterANTPlus_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  counterANTPlus_STATUS_FIFOFULL_SHIFT  
    #define counterANTPlus_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  counterANTPlus_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define counterANTPlus_STATUS_CMP             ((uint8)((uint8)0x01u << counterANTPlus_STATUS_CMP_SHIFT))  
    #define counterANTPlus_STATUS_ZERO            ((uint8)((uint8)0x01u << counterANTPlus_STATUS_ZERO_SHIFT)) 
    #define counterANTPlus_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << counterANTPlus_STATUS_OVERFLOW_SHIFT)) 
    #define counterANTPlus_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << counterANTPlus_STATUS_UNDERFLOW_SHIFT)) 
    #define counterANTPlus_STATUS_CAPTURE         ((uint8)((uint8)0x01u << counterANTPlus_STATUS_CAPTURE_SHIFT)) 
    #define counterANTPlus_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << counterANTPlus_STATUS_FIFOFULL_SHIFT))
    #define counterANTPlus_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << counterANTPlus_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define counterANTPlus_STATUS_CMP_INT_EN_MASK            counterANTPlus_STATUS_CMP                    
    #define counterANTPlus_STATUS_ZERO_INT_EN_MASK           counterANTPlus_STATUS_ZERO            
    #define counterANTPlus_STATUS_OVERFLOW_INT_EN_MASK       counterANTPlus_STATUS_OVERFLOW        
    #define counterANTPlus_STATUS_UNDERFLOW_INT_EN_MASK      counterANTPlus_STATUS_UNDERFLOW       
    #define counterANTPlus_STATUS_CAPTURE_INT_EN_MASK        counterANTPlus_STATUS_CAPTURE         
    #define counterANTPlus_STATUS_FIFOFULL_INT_EN_MASK       counterANTPlus_STATUS_FIFOFULL        
    #define counterANTPlus_STATUS_FIFONEMP_INT_EN_MASK       counterANTPlus_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define counterANTPlus_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define counterANTPlus_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define counterANTPlus_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define counterANTPlus_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define counterANTPlus_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define counterANTPlus_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* counterANTPlus_UsingFixedFunction */

#endif  /* CY_COUNTER_counterANTPlus_H */


/* [] END OF FILE */

