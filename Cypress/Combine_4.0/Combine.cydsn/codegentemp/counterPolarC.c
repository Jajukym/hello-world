/*******************************************************************************
* File Name: counterPolarC.c  
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

#include "counterPolarC.h"

uint8 counterPolarC_initVar = 0u;


/*******************************************************************************
* Function Name: counterPolarC_Init
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
void counterPolarC_Init(void) 
{
        #if (!counterPolarC_UsingFixedFunction && !counterPolarC_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!counterPolarC_UsingFixedFunction && !counterPolarC_ControlRegRemoved) */
        
        #if(!counterPolarC_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 counterPolarC_interruptState;
        #endif /* (!counterPolarC_UsingFixedFunction) */
        
        #if (counterPolarC_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            counterPolarC_CONTROL &= counterPolarC_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                counterPolarC_CONTROL2 &= ((uint8)(~counterPolarC_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                counterPolarC_CONTROL3 &= ((uint8)(~counterPolarC_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (counterPolarC_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                counterPolarC_CONTROL |= counterPolarC_ONESHOT;
            #endif /* (counterPolarC_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            counterPolarC_CONTROL2 |= counterPolarC_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            counterPolarC_RT1 &= ((uint8)(~counterPolarC_RT1_MASK));
            counterPolarC_RT1 |= counterPolarC_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            counterPolarC_RT1 &= ((uint8)(~counterPolarC_SYNCDSI_MASK));
            counterPolarC_RT1 |= counterPolarC_SYNCDSI_EN;

        #else
            #if(!counterPolarC_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = counterPolarC_CONTROL & ((uint8)(~counterPolarC_CTRL_CMPMODE_MASK));
            counterPolarC_CONTROL = ctrl | counterPolarC_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = counterPolarC_CONTROL & ((uint8)(~counterPolarC_CTRL_CAPMODE_MASK));
            
            #if( 0 != counterPolarC_CAPTURE_MODE_CONF)
                counterPolarC_CONTROL = ctrl | counterPolarC_DEFAULT_CAPTURE_MODE;
            #else
                counterPolarC_CONTROL = ctrl;
            #endif /* 0 != counterPolarC_CAPTURE_MODE */ 
            
            #endif /* (!counterPolarC_ControlRegRemoved) */
        #endif /* (counterPolarC_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!counterPolarC_UsingFixedFunction)
            counterPolarC_ClearFIFO();
        #endif /* (!counterPolarC_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        counterPolarC_WritePeriod(counterPolarC_INIT_PERIOD_VALUE);
        #if (!(counterPolarC_UsingFixedFunction && (CY_PSOC5A)))
            counterPolarC_WriteCounter(counterPolarC_INIT_COUNTER_VALUE);
        #endif /* (!(counterPolarC_UsingFixedFunction && (CY_PSOC5A))) */
        counterPolarC_SetInterruptMode(counterPolarC_INIT_INTERRUPTS_MASK);
        
        #if (!counterPolarC_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)counterPolarC_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            counterPolarC_WriteCompare(counterPolarC_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            counterPolarC_interruptState = CyEnterCriticalSection();
            
            counterPolarC_STATUS_AUX_CTRL |= counterPolarC_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(counterPolarC_interruptState);
            
        #endif /* (!counterPolarC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarC_Enable
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
void counterPolarC_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (counterPolarC_UsingFixedFunction)
        counterPolarC_GLOBAL_ENABLE |= counterPolarC_BLOCK_EN_MASK;
        counterPolarC_GLOBAL_STBY_ENABLE |= counterPolarC_BLOCK_STBY_EN_MASK;
    #endif /* (counterPolarC_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!counterPolarC_ControlRegRemoved || counterPolarC_UsingFixedFunction)
        counterPolarC_CONTROL |= counterPolarC_CTRL_ENABLE;                
    #endif /* (!counterPolarC_ControlRegRemoved || counterPolarC_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: counterPolarC_Start
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
*  counterPolarC_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void counterPolarC_Start(void) 
{
    if(counterPolarC_initVar == 0u)
    {
        counterPolarC_Init();
        
        counterPolarC_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    counterPolarC_Enable();        
}


/*******************************************************************************
* Function Name: counterPolarC_Stop
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
void counterPolarC_Stop(void) 
{
    /* Disable Counter */
    #if(!counterPolarC_ControlRegRemoved || counterPolarC_UsingFixedFunction)
        counterPolarC_CONTROL &= ((uint8)(~counterPolarC_CTRL_ENABLE));        
    #endif /* (!counterPolarC_ControlRegRemoved || counterPolarC_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (counterPolarC_UsingFixedFunction)
        counterPolarC_GLOBAL_ENABLE &= ((uint8)(~counterPolarC_BLOCK_EN_MASK));
        counterPolarC_GLOBAL_STBY_ENABLE &= ((uint8)(~counterPolarC_BLOCK_STBY_EN_MASK));
    #endif /* (counterPolarC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarC_SetInterruptMode
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
void counterPolarC_SetInterruptMode(uint8 interruptsMask) 
{
    counterPolarC_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: counterPolarC_ReadStatusRegister
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
uint8   counterPolarC_ReadStatusRegister(void) 
{
    return counterPolarC_STATUS;
}


#if(!counterPolarC_ControlRegRemoved)
/*******************************************************************************
* Function Name: counterPolarC_ReadControlRegister
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
uint8   counterPolarC_ReadControlRegister(void) 
{
    return counterPolarC_CONTROL;
}


/*******************************************************************************
* Function Name: counterPolarC_WriteControlRegister
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
void    counterPolarC_WriteControlRegister(uint8 control) 
{
    counterPolarC_CONTROL = control;
}

#endif  /* (!counterPolarC_ControlRegRemoved) */


#if (!(counterPolarC_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: counterPolarC_WriteCounter
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
void counterPolarC_WriteCounter(uint8 counter) \
                                   
{
    #if(counterPolarC_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (counterPolarC_GLOBAL_ENABLE & counterPolarC_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        counterPolarC_GLOBAL_ENABLE |= counterPolarC_BLOCK_EN_MASK;
        CY_SET_REG16(counterPolarC_COUNTER_LSB_PTR, (uint16)counter);
        counterPolarC_GLOBAL_ENABLE &= ((uint8)(~counterPolarC_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(counterPolarC_COUNTER_LSB_PTR, counter);
    #endif /* (counterPolarC_UsingFixedFunction) */
}
#endif /* (!(counterPolarC_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: counterPolarC_ReadCounter
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
uint8 counterPolarC_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(counterPolarC_UsingFixedFunction)
		(void)CY_GET_REG16(counterPolarC_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(counterPolarC_COUNTER_LSB_PTR_8BIT);
	#endif/* (counterPolarC_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(counterPolarC_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(counterPolarC_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(counterPolarC_STATICCOUNT_LSB_PTR));
    #endif /* (counterPolarC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarC_ReadCapture
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
uint8 counterPolarC_ReadCapture(void) 
{
    #if(counterPolarC_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(counterPolarC_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(counterPolarC_STATICCOUNT_LSB_PTR));
    #endif /* (counterPolarC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarC_WritePeriod
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
void counterPolarC_WritePeriod(uint8 period) 
{
    #if(counterPolarC_UsingFixedFunction)
        CY_SET_REG16(counterPolarC_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(counterPolarC_PERIOD_LSB_PTR, period);
    #endif /* (counterPolarC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarC_ReadPeriod
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
uint8 counterPolarC_ReadPeriod(void) 
{
    #if(counterPolarC_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(counterPolarC_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(counterPolarC_PERIOD_LSB_PTR));
    #endif /* (counterPolarC_UsingFixedFunction) */
}


#if (!counterPolarC_UsingFixedFunction)
/*******************************************************************************
* Function Name: counterPolarC_WriteCompare
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
void counterPolarC_WriteCompare(uint8 compare) \
                                   
{
    #if(counterPolarC_UsingFixedFunction)
        CY_SET_REG16(counterPolarC_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(counterPolarC_COMPARE_LSB_PTR, compare);
    #endif /* (counterPolarC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarC_ReadCompare
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
uint8 counterPolarC_ReadCompare(void) 
{
    return (CY_GET_REG8(counterPolarC_COMPARE_LSB_PTR));
}


#if (counterPolarC_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: counterPolarC_SetCompareMode
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
void counterPolarC_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    counterPolarC_CONTROL &= ((uint8)(~counterPolarC_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    counterPolarC_CONTROL |= compareMode;
}
#endif  /* (counterPolarC_COMPARE_MODE_SOFTWARE) */


#if (counterPolarC_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: counterPolarC_SetCaptureMode
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
void counterPolarC_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    counterPolarC_CONTROL &= ((uint8)(~counterPolarC_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    counterPolarC_CONTROL |= ((uint8)((uint8)captureMode << counterPolarC_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (counterPolarC_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: counterPolarC_ClearFIFO
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
void counterPolarC_ClearFIFO(void) 
{

    while(0u != (counterPolarC_ReadStatusRegister() & counterPolarC_STATUS_FIFONEMP))
    {
        (void)counterPolarC_ReadCapture();
    }

}
#endif  /* (!counterPolarC_UsingFixedFunction) */


/* [] END OF FILE */

