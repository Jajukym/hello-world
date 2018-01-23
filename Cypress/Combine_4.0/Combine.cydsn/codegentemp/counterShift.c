/*******************************************************************************
* File Name: counterShift.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "counterShift.h"

uint8 counterShift_initVar = 0u;


/*******************************************************************************
* Function Name: counterShift_Init
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
void counterShift_Init(void) 
{
        #if (!counterShift_UsingFixedFunction && !counterShift_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!counterShift_UsingFixedFunction && !counterShift_ControlRegRemoved) */
        
        #if(!counterShift_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 counterShift_interruptState;
        #endif /* (!counterShift_UsingFixedFunction) */
        
        #if (counterShift_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            counterShift_CONTROL &= counterShift_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                counterShift_CONTROL2 &= ((uint8)(~counterShift_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                counterShift_CONTROL3 &= ((uint8)(~counterShift_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (counterShift_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                counterShift_CONTROL |= counterShift_ONESHOT;
            #endif /* (counterShift_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            counterShift_CONTROL2 |= counterShift_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            counterShift_RT1 &= ((uint8)(~counterShift_RT1_MASK));
            counterShift_RT1 |= counterShift_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            counterShift_RT1 &= ((uint8)(~counterShift_SYNCDSI_MASK));
            counterShift_RT1 |= counterShift_SYNCDSI_EN;

        #else
            #if(!counterShift_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = counterShift_CONTROL & ((uint8)(~counterShift_CTRL_CMPMODE_MASK));
            counterShift_CONTROL = ctrl | counterShift_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = counterShift_CONTROL & ((uint8)(~counterShift_CTRL_CAPMODE_MASK));
            
            #if( 0 != counterShift_CAPTURE_MODE_CONF)
                counterShift_CONTROL = ctrl | counterShift_DEFAULT_CAPTURE_MODE;
            #else
                counterShift_CONTROL = ctrl;
            #endif /* 0 != counterShift_CAPTURE_MODE */ 
            
            #endif /* (!counterShift_ControlRegRemoved) */
        #endif /* (counterShift_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!counterShift_UsingFixedFunction)
            counterShift_ClearFIFO();
        #endif /* (!counterShift_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        counterShift_WritePeriod(counterShift_INIT_PERIOD_VALUE);
        #if (!(counterShift_UsingFixedFunction && (CY_PSOC5A)))
            counterShift_WriteCounter(counterShift_INIT_COUNTER_VALUE);
        #endif /* (!(counterShift_UsingFixedFunction && (CY_PSOC5A))) */
        counterShift_SetInterruptMode(counterShift_INIT_INTERRUPTS_MASK);
        
        #if (!counterShift_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)counterShift_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            counterShift_WriteCompare(counterShift_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            counterShift_interruptState = CyEnterCriticalSection();
            
            counterShift_STATUS_AUX_CTRL |= counterShift_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(counterShift_interruptState);
            
        #endif /* (!counterShift_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterShift_Enable
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
void counterShift_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (counterShift_UsingFixedFunction)
        counterShift_GLOBAL_ENABLE |= counterShift_BLOCK_EN_MASK;
        counterShift_GLOBAL_STBY_ENABLE |= counterShift_BLOCK_STBY_EN_MASK;
    #endif /* (counterShift_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!counterShift_ControlRegRemoved || counterShift_UsingFixedFunction)
        counterShift_CONTROL |= counterShift_CTRL_ENABLE;                
    #endif /* (!counterShift_ControlRegRemoved || counterShift_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: counterShift_Start
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
*  counterShift_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void counterShift_Start(void) 
{
    if(counterShift_initVar == 0u)
    {
        counterShift_Init();
        
        counterShift_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    counterShift_Enable();        
}


/*******************************************************************************
* Function Name: counterShift_Stop
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
void counterShift_Stop(void) 
{
    /* Disable Counter */
    #if(!counterShift_ControlRegRemoved || counterShift_UsingFixedFunction)
        counterShift_CONTROL &= ((uint8)(~counterShift_CTRL_ENABLE));        
    #endif /* (!counterShift_ControlRegRemoved || counterShift_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (counterShift_UsingFixedFunction)
        counterShift_GLOBAL_ENABLE &= ((uint8)(~counterShift_BLOCK_EN_MASK));
        counterShift_GLOBAL_STBY_ENABLE &= ((uint8)(~counterShift_BLOCK_STBY_EN_MASK));
    #endif /* (counterShift_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterShift_SetInterruptMode
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
void counterShift_SetInterruptMode(uint8 interruptsMask) 
{
    counterShift_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: counterShift_ReadStatusRegister
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
uint8   counterShift_ReadStatusRegister(void) 
{
    return counterShift_STATUS;
}


#if(!counterShift_ControlRegRemoved)
/*******************************************************************************
* Function Name: counterShift_ReadControlRegister
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
uint8   counterShift_ReadControlRegister(void) 
{
    return counterShift_CONTROL;
}


/*******************************************************************************
* Function Name: counterShift_WriteControlRegister
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
void    counterShift_WriteControlRegister(uint8 control) 
{
    counterShift_CONTROL = control;
}

#endif  /* (!counterShift_ControlRegRemoved) */


#if (!(counterShift_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: counterShift_WriteCounter
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
void counterShift_WriteCounter(uint8 counter) \
                                   
{
    #if(counterShift_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (counterShift_GLOBAL_ENABLE & counterShift_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        counterShift_GLOBAL_ENABLE |= counterShift_BLOCK_EN_MASK;
        CY_SET_REG16(counterShift_COUNTER_LSB_PTR, (uint16)counter);
        counterShift_GLOBAL_ENABLE &= ((uint8)(~counterShift_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(counterShift_COUNTER_LSB_PTR, counter);
    #endif /* (counterShift_UsingFixedFunction) */
}
#endif /* (!(counterShift_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: counterShift_ReadCounter
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
uint8 counterShift_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(counterShift_UsingFixedFunction)
		(void)CY_GET_REG16(counterShift_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(counterShift_COUNTER_LSB_PTR_8BIT);
	#endif/* (counterShift_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(counterShift_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(counterShift_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(counterShift_STATICCOUNT_LSB_PTR));
    #endif /* (counterShift_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterShift_ReadCapture
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
uint8 counterShift_ReadCapture(void) 
{
    #if(counterShift_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(counterShift_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(counterShift_STATICCOUNT_LSB_PTR));
    #endif /* (counterShift_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterShift_WritePeriod
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
void counterShift_WritePeriod(uint8 period) 
{
    #if(counterShift_UsingFixedFunction)
        CY_SET_REG16(counterShift_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(counterShift_PERIOD_LSB_PTR, period);
    #endif /* (counterShift_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterShift_ReadPeriod
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
uint8 counterShift_ReadPeriod(void) 
{
    #if(counterShift_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(counterShift_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(counterShift_PERIOD_LSB_PTR));
    #endif /* (counterShift_UsingFixedFunction) */
}


#if (!counterShift_UsingFixedFunction)
/*******************************************************************************
* Function Name: counterShift_WriteCompare
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
void counterShift_WriteCompare(uint8 compare) \
                                   
{
    #if(counterShift_UsingFixedFunction)
        CY_SET_REG16(counterShift_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(counterShift_COMPARE_LSB_PTR, compare);
    #endif /* (counterShift_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterShift_ReadCompare
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
uint8 counterShift_ReadCompare(void) 
{
    return (CY_GET_REG8(counterShift_COMPARE_LSB_PTR));
}


#if (counterShift_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: counterShift_SetCompareMode
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
void counterShift_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    counterShift_CONTROL &= ((uint8)(~counterShift_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    counterShift_CONTROL |= compareMode;
}
#endif  /* (counterShift_COMPARE_MODE_SOFTWARE) */


#if (counterShift_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: counterShift_SetCaptureMode
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
void counterShift_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    counterShift_CONTROL &= ((uint8)(~counterShift_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    counterShift_CONTROL |= ((uint8)((uint8)captureMode << counterShift_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (counterShift_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: counterShift_ClearFIFO
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
void counterShift_ClearFIFO(void) 
{

    while(0u != (counterShift_ReadStatusRegister() & counterShift_STATUS_FIFONEMP))
    {
        (void)counterShift_ReadCapture();
    }

}
#endif  /* (!counterShift_UsingFixedFunction) */


/* [] END OF FILE */

