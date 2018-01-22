/*******************************************************************************
* File Name: ShiftCounter.h  
* Version 2.20
*
*  Description:
*   Contains the function prototypes and constants available to the counter
*   user module.
*
*   Note:
*    None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
    
#if !defined(CY_COUNTER_ShiftCounter_H)
#define CY_COUNTER_ShiftCounter_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults        
**************************************/

#define ShiftCounter_Resolution            8u
#define ShiftCounter_UsingFixedFunction    1u
#define ShiftCounter_ControlRegRemoved     0u
#define ShiftCounter_COMPARE_MODE_SOFTWARE 0u
#define ShiftCounter_CAPTURE_MODE_SOFTWARE 0u
#define ShiftCounter_RunModeUsed           0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Mode API Support
 * Backup structure for Sleep Wake up operations
 *************************************************************************/
typedef struct ShiftCounter_backupStruct
{
    /* Sleep BackUp structure */
    uint8 CounterEnableState; 
    #if (CY_PSOC5A)
        uint8 CounterUdb;    /* Current Counter Value      */
        uint8 CounterPeriod; /* Counter Period Value       */
        uint8 CompareValue;  /* Counter Compare Value      */           
        uint8 InterruptMaskValue; /* Counter Compare Value */
    #endif /* (CY_PSOC5A) */

    #if (CY_PSOC3 || CY_PSOC5LP)
            uint8 CounterUdb;
            uint8 InterruptMaskValue;
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    #if (!ShiftCounter_ControlRegRemoved)
        uint8 CounterControlRegister;          /* Counter Control Register   */
    #endif /* (!ShiftCounter_ControlRegRemoved) */
}ShiftCounter_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    ShiftCounter_Start(void) ;
void    ShiftCounter_Stop(void) ;
void    ShiftCounter_SetInterruptMode(uint8 interruptsMask) ;
uint8   ShiftCounter_ReadStatusRegister(void) ;
#define ShiftCounter_GetInterruptSource() ShiftCounter_ReadStatusRegister()
#if(!ShiftCounter_ControlRegRemoved)
    uint8   ShiftCounter_ReadControlRegister(void) ;
    void    ShiftCounter_WriteControlRegister(uint8 control) \
        ;
#endif /* (!ShiftCounter_ControlRegRemoved) */
#if (!(ShiftCounter_UsingFixedFunction && (CY_PSOC5A)))
    void    ShiftCounter_WriteCounter(uint8 counter) \
            ; 
#endif /* (!(ShiftCounter_UsingFixedFunction && (CY_PSOC5A))) */
uint8  ShiftCounter_ReadCounter(void) ;
uint8  ShiftCounter_ReadCapture(void) ;
void    ShiftCounter_WritePeriod(uint8 period) \
    ;
uint8  ShiftCounter_ReadPeriod( void ) ;
#if (!ShiftCounter_UsingFixedFunction)
    void    ShiftCounter_WriteCompare(uint8 compare) \
        ;
    uint8  ShiftCounter_ReadCompare( void ) \
        ;
#endif /* (!ShiftCounter_UsingFixedFunction) */

#if (ShiftCounter_COMPARE_MODE_SOFTWARE)
    void    ShiftCounter_SetCompareMode(uint8 comparemode) ;
#endif /* (ShiftCounter_COMPARE_MODE_SOFTWARE) */
#if (ShiftCounter_CAPTURE_MODE_SOFTWARE)
    void    ShiftCounter_SetCaptureMode(uint8 capturemode) ;
#endif /* (ShiftCounter_CAPTURE_MODE_SOFTWARE) */
void ShiftCounter_ClearFIFO(void)     ;
void ShiftCounter_Init(void)          ;
void ShiftCounter_Enable(void)        ;
void ShiftCounter_SaveConfig(void)    ;
void ShiftCounter_RestoreConfig(void) ;
void ShiftCounter_Sleep(void)         ;
void ShiftCounter_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define ShiftCounter__B_COUNTER__LESS_THAN 1
#define ShiftCounter__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define ShiftCounter__B_COUNTER__EQUAL 0
#define ShiftCounter__B_COUNTER__GREATER_THAN 3
#define ShiftCounter__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define ShiftCounter__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define ShiftCounter_CMP_MODE_LT 1u
#define ShiftCounter_CMP_MODE_LTE 2u
#define ShiftCounter_CMP_MODE_EQ 0u
#define ShiftCounter_CMP_MODE_GT 3u
#define ShiftCounter_CMP_MODE_GTE 4u
#define ShiftCounter_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define ShiftCounter__B_COUNTER__NONE 0
#define ShiftCounter__B_COUNTER__RISING_EDGE 1
#define ShiftCounter__B_COUNTER__FALLING_EDGE 2
#define ShiftCounter__B_COUNTER__EITHER_EDGE 3
#define ShiftCounter__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define ShiftCounter_CAP_MODE_NONE 0u
#define ShiftCounter_CAP_MODE_RISE 1u
#define ShiftCounter_CAP_MODE_FALL 2u
#define ShiftCounter_CAP_MODE_BOTH 3u
#define ShiftCounter_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define ShiftCounter_INIT_PERIOD_VALUE       8u
#define ShiftCounter_INIT_COUNTER_VALUE      8u
#if (ShiftCounter_UsingFixedFunction)
#define ShiftCounter_INIT_INTERRUPTS_MASK    ((0u << ShiftCounter_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define ShiftCounter_INIT_COMPARE_VALUE      2u
#define ShiftCounter_INIT_INTERRUPTS_MASK ((0u << ShiftCounter_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        (0u << ShiftCounter_STATUS_CAPTURE_INT_EN_MASK_SHIFT) | \
        (0u << ShiftCounter_STATUS_CMP_INT_EN_MASK_SHIFT) | \
        (0u << ShiftCounter_STATUS_OVERFLOW_INT_EN_MASK_SHIFT) | \
        (0u << ShiftCounter_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT))
#define ShiftCounter_DEFAULT_COMPARE_MODE    (1u << ShiftCounter_CTRL_CMPMODE0_SHIFT)
#define ShiftCounter_DEFAULT_CAPTURE_MODE    (0u << ShiftCounter_CTRL_CAPMODE0_SHIFT)
#endif /* (ShiftCounter_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (ShiftCounter_UsingFixedFunction)
    #define ShiftCounter_STATICCOUNT_LSB     (*(reg16 *) ShiftCounter_CounterHW__CAP0 )
    #define ShiftCounter_STATICCOUNT_LSB_PTR ( (reg16 *) ShiftCounter_CounterHW__CAP0 )
    #define ShiftCounter_PERIOD_LSB          (*(reg16 *) ShiftCounter_CounterHW__PER0 )
    #define ShiftCounter_PERIOD_LSB_PTR      ( (reg16 *) ShiftCounter_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define ShiftCounter_COMPARE_LSB         (*(reg16 *) ShiftCounter_CounterHW__CNT_CMP0 )
    #define ShiftCounter_COMPARE_LSB_PTR     ( (reg16 *) ShiftCounter_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define ShiftCounter_COUNTER_LSB         (*(reg16 *) ShiftCounter_CounterHW__CNT_CMP0 )
    #define ShiftCounter_COUNTER_LSB_PTR     ( (reg16 *) ShiftCounter_CounterHW__CNT_CMP0 )
    #define ShiftCounter_RT1                 (*(reg8 *) ShiftCounter_CounterHW__RT1)
    #define ShiftCounter_RT1_PTR             ( (reg8 *) ShiftCounter_CounterHW__RT1)
#else
    #define ShiftCounter_STATICCOUNT_LSB     (*(reg8 *) \
        ShiftCounter_CounterUDB_sC8_counterdp_u0__F0_REG )
    #define ShiftCounter_STATICCOUNT_LSB_PTR ( (reg8 *) \
        ShiftCounter_CounterUDB_sC8_counterdp_u0__F0_REG )
    #define ShiftCounter_PERIOD_LSB          (*(reg8 *) \
        ShiftCounter_CounterUDB_sC8_counterdp_u0__D0_REG )
    #define ShiftCounter_PERIOD_LSB_PTR      ( (reg8 *) \
        ShiftCounter_CounterUDB_sC8_counterdp_u0__D0_REG )
    #define ShiftCounter_COMPARE_LSB         (*(reg8 *) \
        ShiftCounter_CounterUDB_sC8_counterdp_u0__D1_REG )
    #define ShiftCounter_COMPARE_LSB_PTR     ( (reg8 *) \
        ShiftCounter_CounterUDB_sC8_counterdp_u0__D1_REG )
    #define ShiftCounter_COUNTER_LSB         (*(reg8 *) \
        ShiftCounter_CounterUDB_sC8_counterdp_u0__A0_REG )
    #define ShiftCounter_COUNTER_LSB_PTR     ( (reg8 *)\
        ShiftCounter_CounterUDB_sC8_counterdp_u0__A0_REG )

    #define ShiftCounter_AUX_CONTROLDP0 \
        (*(reg8 *) ShiftCounter_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    #define ShiftCounter_AUX_CONTROLDP0_PTR \
        ( (reg8 *) ShiftCounter_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    #if (ShiftCounter_Resolution == 16 || ShiftCounter_Resolution == 24 || ShiftCounter_Resolution == 32)
       #define ShiftCounter_AUX_CONTROLDP1 \
           (*(reg8 *) ShiftCounter_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
       #define ShiftCounter_AUX_CONTROLDP1_PTR \
           ( (reg8 *) ShiftCounter_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (ShiftCounter_Resolution == 16 || ShiftCounter_Resolution == 24 || ShiftCounter_Resolution == 32) */
    #if (ShiftCounter_Resolution == 24 || ShiftCounter_Resolution == 32)
       #define ShiftCounter_AUX_CONTROLDP2 \
           (*(reg8 *) ShiftCounter_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
       #define ShiftCounter_AUX_CONTROLDP2_PTR \
           ( (reg8 *) ShiftCounter_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (ShiftCounter_Resolution == 24 || ShiftCounter_Resolution == 32) */
    #if (ShiftCounter_Resolution == 32)
       #define ShiftCounter_AUX_CONTROLDP3 \
           (*(reg8 *) ShiftCounter_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
       #define ShiftCounter_AUX_CONTROLDP3_PTR \
           ( (reg8 *) ShiftCounter_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (ShiftCounter_Resolution == 32) */
#endif  /* (ShiftCounter_UsingFixedFunction) */

#if (ShiftCounter_UsingFixedFunction)
    #define ShiftCounter_STATUS         (*(reg8 *) ShiftCounter_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define ShiftCounter_STATUS_MASK             (*(reg8 *) ShiftCounter_CounterHW__SR0 )
    #define ShiftCounter_STATUS_MASK_PTR         ( (reg8 *) ShiftCounter_CounterHW__SR0 )
    #define ShiftCounter_CONTROL                 (*(reg8 *) ShiftCounter_CounterHW__CFG0)
    #define ShiftCounter_CONTROL_PTR             ( (reg8 *) ShiftCounter_CounterHW__CFG0)
    #define ShiftCounter_CONTROL2                (*(reg8 *) ShiftCounter_CounterHW__CFG1)
    #define ShiftCounter_CONTROL2_PTR            ( (reg8 *) ShiftCounter_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define ShiftCounter_CONTROL3       (*(reg8 *) ShiftCounter_CounterHW__CFG2)
        #define ShiftCounter_CONTROL3_PTR   ( (reg8 *) ShiftCounter_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define ShiftCounter_GLOBAL_ENABLE           (*(reg8 *) ShiftCounter_CounterHW__PM_ACT_CFG)
    #define ShiftCounter_GLOBAL_ENABLE_PTR       ( (reg8 *) ShiftCounter_CounterHW__PM_ACT_CFG)
    #define ShiftCounter_GLOBAL_STBY_ENABLE      (*(reg8 *) ShiftCounter_CounterHW__PM_STBY_CFG)
    #define ShiftCounter_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) ShiftCounter_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define ShiftCounter_BLOCK_EN_MASK          ShiftCounter_CounterHW__PM_ACT_MSK
    #define ShiftCounter_BLOCK_STBY_EN_MASK     ShiftCounter_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define ShiftCounter_CTRL_ENABLE_SHIFT      0x00u
    #define ShiftCounter_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define ShiftCounter_CTRL_ENABLE            (0x01u << ShiftCounter_CTRL_ENABLE_SHIFT)         
    #define ShiftCounter_ONESHOT                (0x01u << ShiftCounter_ONESHOT_SHIFT)

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define ShiftCounter_CTRL_MODE_SHIFT        0x01u    
        #define ShiftCounter_CTRL_MODE_MASK         (0x07u << ShiftCounter_CTRL_MODE_SHIFT)
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define ShiftCounter_CTRL_MODE_SHIFT        0x00u    
        #define ShiftCounter_CTRL_MODE_MASK         (0x03u << ShiftCounter_CTRL_MODE_SHIFT)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define ShiftCounter_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define ShiftCounter_CTRL2_IRQ_SEL          (0x01u << ShiftCounter_CTRL2_IRQ_SEL_SHIFT)     
    
    /* Status Register Bit Locations */
    #define ShiftCounter_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define ShiftCounter_STATUS_ZERO_INT_EN_MASK_SHIFT      (ShiftCounter_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define ShiftCounter_STATUS_ZERO            (0x01u << ShiftCounter_STATUS_ZERO_SHIFT)

    /* Status Register Interrupt Bit Masks*/
    #define ShiftCounter_STATUS_ZERO_INT_EN_MASK       (ShiftCounter_STATUS_ZERO >> 0x04u)
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define ShiftCounter_RT1_SHIFT            0x04u
    #define ShiftCounter_RT1_MASK             (0x03u << ShiftCounter_RT1_SHIFT)  /* Sync TC and CMP bit masks */
    #define ShiftCounter_SYNC                 (0x03u << ShiftCounter_RT1_SHIFT)
    #define ShiftCounter_SYNCDSI_SHIFT        0x00u
    #define ShiftCounter_SYNCDSI_MASK         (0x0Fu << ShiftCounter_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define ShiftCounter_SYNCDSI_EN           (0x0Fu << ShiftCounter_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    
#else /* !ShiftCounter_UsingFixedFunction */
    #define ShiftCounter_STATUS               (* (reg8 *) ShiftCounter_CounterUDB_sSTSReg_nrstSts_stsreg__STATUS_REG )
    #define ShiftCounter_STATUS_PTR           (  (reg8 *) ShiftCounter_CounterUDB_sSTSReg_nrstSts_stsreg__STATUS_REG )
    #define ShiftCounter_STATUS_MASK          (* (reg8 *) ShiftCounter_CounterUDB_sSTSReg_nrstSts_stsreg__MASK_REG )
    #define ShiftCounter_STATUS_MASK_PTR      (  (reg8 *) ShiftCounter_CounterUDB_sSTSReg_nrstSts_stsreg__MASK_REG )
    #define ShiftCounter_STATUS_AUX_CTRL      (*(reg8 *) ShiftCounter_CounterUDB_sSTSReg_nrstSts_stsreg__STATUS_AUX_CTL_REG)
    #define ShiftCounter_STATUS_AUX_CTRL_PTR  ( (reg8 *) ShiftCounter_CounterUDB_sSTSReg_nrstSts_stsreg__STATUS_AUX_CTL_REG)
    #define ShiftCounter_CONTROL              (* (reg8 *) ShiftCounter_CounterUDB_sCTRLReg_AsyncCtl_ctrlreg__CONTROL_REG )
    #define ShiftCounter_CONTROL_PTR          (  (reg8 *) ShiftCounter_CounterUDB_sCTRLReg_AsyncCtl_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define ShiftCounter_CTRL_CMPMODE0_SHIFT    0x00u       /* As defined by Verilog Implementation */
    #define ShiftCounter_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define ShiftCounter_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define ShiftCounter_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define ShiftCounter_CTRL_CMPMODE_MASK      (0x07u << ShiftCounter_CTRL_CMPMODE0_SHIFT)  
    #define ShiftCounter_CTRL_CAPMODE_MASK      (0x03u << ShiftCounter_CTRL_CAPMODE0_SHIFT)  
    #define ShiftCounter_CTRL_RESET             (0x01u << ShiftCounter_CTRL_RESET_SHIFT)  
    #define ShiftCounter_CTRL_ENABLE            (0x01u << ShiftCounter_CTRL_ENABLE_SHIFT) 

    /* Status Register Bit Locations */
    #define ShiftCounter_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define ShiftCounter_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define ShiftCounter_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define ShiftCounter_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define ShiftCounter_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define ShiftCounter_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define ShiftCounter_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define ShiftCounter_STATUS_CMP_INT_EN_MASK_SHIFT       ShiftCounter_STATUS_CMP_SHIFT       
    #define ShiftCounter_STATUS_ZERO_INT_EN_MASK_SHIFT      ShiftCounter_STATUS_ZERO_SHIFT      
    #define ShiftCounter_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  ShiftCounter_STATUS_OVERFLOW_SHIFT  
    #define ShiftCounter_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT ShiftCounter_STATUS_UNDERFLOW_SHIFT 
    #define ShiftCounter_STATUS_CAPTURE_INT_EN_MASK_SHIFT   ShiftCounter_STATUS_CAPTURE_SHIFT   
    #define ShiftCounter_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  ShiftCounter_STATUS_FIFOFULL_SHIFT  
    #define ShiftCounter_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  ShiftCounter_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define ShiftCounter_STATUS_CMP             (0x01u << ShiftCounter_STATUS_CMP_SHIFT)  
    #define ShiftCounter_STATUS_ZERO            (0x01u << ShiftCounter_STATUS_ZERO_SHIFT) 
    #define ShiftCounter_STATUS_OVERFLOW        (0x01u << ShiftCounter_STATUS_OVERFLOW_SHIFT) 
    #define ShiftCounter_STATUS_UNDERFLOW       (0x01u << ShiftCounter_STATUS_UNDERFLOW_SHIFT) 
    #define ShiftCounter_STATUS_CAPTURE         (0x01u << ShiftCounter_STATUS_CAPTURE_SHIFT) 
    #define ShiftCounter_STATUS_FIFOFULL        (0x01u << ShiftCounter_STATUS_FIFOFULL_SHIFT)
    #define ShiftCounter_STATUS_FIFONEMP        (0x01u << ShiftCounter_STATUS_FIFONEMP_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define ShiftCounter_STATUS_CMP_INT_EN_MASK            ShiftCounter_STATUS_CMP                    
    #define ShiftCounter_STATUS_ZERO_INT_EN_MASK           ShiftCounter_STATUS_ZERO            
    #define ShiftCounter_STATUS_OVERFLOW_INT_EN_MASK       ShiftCounter_STATUS_OVERFLOW        
    #define ShiftCounter_STATUS_UNDERFLOW_INT_EN_MASK      ShiftCounter_STATUS_UNDERFLOW       
    #define ShiftCounter_STATUS_CAPTURE_INT_EN_MASK        ShiftCounter_STATUS_CAPTURE         
    #define ShiftCounter_STATUS_FIFOFULL_INT_EN_MASK       ShiftCounter_STATUS_FIFOFULL        
    #define ShiftCounter_STATUS_FIFONEMP_INT_EN_MASK       ShiftCounter_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define ShiftCounter_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define ShiftCounter_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define ShiftCounter_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define ShiftCounter_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define ShiftCounter_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define ShiftCounter_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* ShiftCounter_UsingFixedFunction */

#endif  /* CY_COUNTER_ShiftCounter_H */


/* [] END OF FILE */

