/*******************************************************************************
* File Name: ShiftCounter.c  
* Version 2.20
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "ShiftCounter.h"

uint8 ShiftCounter_initVar = 0u;


/*******************************************************************************
* Function Name: ShiftCounter_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void ShiftCounter_Init(void) 
{
        #if (!ShiftCounter_UsingFixedFunction && !ShiftCounter_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!ShiftCounter_UsingFixedFunction && !ShiftCounter_ControlRegRemoved) */
        
        #if(!ShiftCounter_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 ShiftCounter_interruptState;
        #endif /* (!ShiftCounter_UsingFixedFunction) */
        
        #if (ShiftCounter_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            ShiftCounter_CONTROL &= ShiftCounter_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                ShiftCounter_CONTROL2 &= ~ShiftCounter_CTRL_MODE_MASK;
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                ShiftCounter_CONTROL3 &= ~ShiftCounter_CTRL_MODE_MASK;                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (ShiftCounter_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                ShiftCounter_CONTROL |= ShiftCounter_ONESHOT;
            #endif /* (ShiftCounter_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            ShiftCounter_CONTROL2 |= ShiftCounter_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            ShiftCounter_RT1 &= ~ShiftCounter_RT1_MASK;
            ShiftCounter_RT1 |= ShiftCounter_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            ShiftCounter_RT1 &= ~(ShiftCounter_SYNCDSI_MASK);
            ShiftCounter_RT1 |= ShiftCounter_SYNCDSI_EN;

        #else
            #if(!ShiftCounter_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = ShiftCounter_CONTROL & ~ShiftCounter_CTRL_CMPMODE_MASK;
            ShiftCounter_CONTROL = ctrl | ShiftCounter_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = ShiftCounter_CONTROL & ~ShiftCounter_CTRL_CAPMODE_MASK;
            ShiftCounter_CONTROL = ctrl | ShiftCounter_DEFAULT_CAPTURE_MODE;
            #endif /* (!ShiftCounter_ControlRegRemoved) */
        #endif /* (ShiftCounter_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!ShiftCounter_UsingFixedFunction)
            ShiftCounter_ClearFIFO();
        #endif /* (!ShiftCounter_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        ShiftCounter_WritePeriod(ShiftCounter_INIT_PERIOD_VALUE);
        #if (!(ShiftCounter_UsingFixedFunction && (CY_PSOC5A)))
            ShiftCounter_WriteCounter(ShiftCounter_INIT_COUNTER_VALUE);
        #endif /* (!(ShiftCounter_UsingFixedFunction && (CY_PSOC5A))) */
        ShiftCounter_SetInterruptMode(ShiftCounter_INIT_INTERRUPTS_MASK);
        
        #if (!ShiftCounter_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            ShiftCounter_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            ShiftCounter_WriteCompare(ShiftCounter_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            ShiftCounter_interruptState = CyEnterCriticalSection();
            
            ShiftCounter_STATUS_AUX_CTRL |= ShiftCounter_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(ShiftCounter_interruptState);
            
        #endif /* (!ShiftCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ShiftCounter_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void ShiftCounter_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (ShiftCounter_UsingFixedFunction)
        ShiftCounter_GLOBAL_ENABLE |= ShiftCounter_BLOCK_EN_MASK;
        ShiftCounter_GLOBAL_STBY_ENABLE |= ShiftCounter_BLOCK_STBY_EN_MASK;
    #endif /* (ShiftCounter_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!ShiftCounter_ControlRegRemoved || ShiftCounter_UsingFixedFunction)
        ShiftCounter_CONTROL |= ShiftCounter_CTRL_ENABLE;                
    #endif /* (!ShiftCounter_ControlRegRemoved || ShiftCounter_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: ShiftCounter_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  ShiftCounter_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ShiftCounter_Start(void) 
{
    if(ShiftCounter_initVar == 0u)
    {
        ShiftCounter_Init();
        
        ShiftCounter_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    ShiftCounter_Enable();        
}


/*******************************************************************************
* Function Name: ShiftCounter_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void ShiftCounter_Stop(void) 
{
    /* Disable Counter */
    #if(!ShiftCounter_ControlRegRemoved || ShiftCounter_UsingFixedFunction)
        ShiftCounter_CONTROL &= ~ShiftCounter_CTRL_ENABLE;        
    #endif /* (!ShiftCounter_ControlRegRemoved || ShiftCounter_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (ShiftCounter_UsingFixedFunction)
        ShiftCounter_GLOBAL_ENABLE &= ~ShiftCounter_BLOCK_EN_MASK;
        ShiftCounter_GLOBAL_STBY_ENABLE &= ~ShiftCounter_BLOCK_STBY_EN_MASK;
    #endif /* (ShiftCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ShiftCounter_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void ShiftCounter_SetInterruptMode(uint8 interruptsMask) 
{
    ShiftCounter_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: ShiftCounter_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   ShiftCounter_ReadStatusRegister(void) 
{
    return ShiftCounter_STATUS;
}


#if(!ShiftCounter_ControlRegRemoved)
/*******************************************************************************
* Function Name: ShiftCounter_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   ShiftCounter_ReadControlRegister(void) 
{
    return ShiftCounter_CONTROL;
}


/*******************************************************************************
* Function Name: ShiftCounter_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    ShiftCounter_WriteControlRegister(uint8 control) 
{
    ShiftCounter_CONTROL = control;
}

#endif  /* (!ShiftCounter_ControlRegRemoved) */


#if (!(ShiftCounter_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: ShiftCounter_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void ShiftCounter_WriteCounter(uint8 counter) \
                                   
{
    #if(ShiftCounter_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (!(ShiftCounter_GLOBAL_ENABLE & ShiftCounter_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        ShiftCounter_GLOBAL_ENABLE |= ShiftCounter_BLOCK_EN_MASK;
        CY_SET_REG16(ShiftCounter_COUNTER_LSB_PTR, (uint16)counter);
        ShiftCounter_GLOBAL_ENABLE &= ~ShiftCounter_BLOCK_EN_MASK;
    #else
        CY_SET_REG8(ShiftCounter_COUNTER_LSB_PTR, counter);
    #endif /* (ShiftCounter_UsingFixedFunction) */
}
#endif /* (!(ShiftCounter_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: ShiftCounter_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) The present value of the counter.
*
*******************************************************************************/
uint8 ShiftCounter_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    CY_GET_REG8(ShiftCounter_COUNTER_LSB_PTR);
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    return (CY_GET_REG8(ShiftCounter_STATICCOUNT_LSB_PTR));
}


/*******************************************************************************
* Function Name: ShiftCounter_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) Present Capture value.
*
*******************************************************************************/
uint8 ShiftCounter_ReadCapture(void) 
{
   return ( CY_GET_REG8(ShiftCounter_STATICCOUNT_LSB_PTR) );  
}


/*******************************************************************************
* Function Name: ShiftCounter_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint8) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void ShiftCounter_WritePeriod(uint8 period) 
{
    #if(ShiftCounter_UsingFixedFunction)
        CY_SET_REG16(ShiftCounter_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(ShiftCounter_PERIOD_LSB_PTR,period);
    #endif /* (ShiftCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ShiftCounter_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) Present period value.
*
*******************************************************************************/
uint8 ShiftCounter_ReadPeriod(void) 
{
   return ( CY_GET_REG8(ShiftCounter_PERIOD_LSB_PTR));
}


#if (!ShiftCounter_UsingFixedFunction)
/*******************************************************************************
* Function Name: ShiftCounter_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void ShiftCounter_WriteCompare(uint8 compare) \
                                   
{
    #if(ShiftCounter_UsingFixedFunction)
        CY_SET_REG16(ShiftCounter_COMPARE_LSB_PTR,(uint16)compare);
    #else
        CY_SET_REG8(ShiftCounter_COMPARE_LSB_PTR,compare);
    #endif /* (ShiftCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ShiftCounter_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint8) Present compare value.
*
*******************************************************************************/
uint8 ShiftCounter_ReadCompare(void) 
{
   return ( CY_GET_REG8(ShiftCounter_COMPARE_LSB_PTR));
}


#if (ShiftCounter_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ShiftCounter_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void ShiftCounter_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    ShiftCounter_CONTROL &= ~ShiftCounter_CTRL_CMPMODE_MASK;
    
    /* Write the new setting */
    ShiftCounter_CONTROL |= (compareMode << ShiftCounter_CTRL_CMPMODE0_SHIFT);
}
#endif  /* (ShiftCounter_COMPARE_MODE_SOFTWARE) */


#if (ShiftCounter_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ShiftCounter_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void ShiftCounter_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    ShiftCounter_CONTROL &= ~ShiftCounter_CTRL_CAPMODE_MASK;
    
    /* Write the new setting */
    ShiftCounter_CONTROL |= (captureMode << ShiftCounter_CTRL_CAPMODE0_SHIFT);
}
#endif  /* (ShiftCounter_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: ShiftCounter_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void ShiftCounter_ClearFIFO(void) 
{

    while(ShiftCounter_ReadStatusRegister() & ShiftCounter_STATUS_FIFONEMP)
    {
        ShiftCounter_ReadCapture();
    }

}
#endif  /* (!ShiftCounter_UsingFixedFunction) */


/* [] END OF FILE */

