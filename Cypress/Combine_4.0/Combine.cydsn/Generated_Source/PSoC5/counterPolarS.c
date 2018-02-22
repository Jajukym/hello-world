/*******************************************************************************
* File Name: counterPolarS.c  
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

#include "counterPolarS.h"

uint8 counterPolarS_initVar = 0u;


/*******************************************************************************
* Function Name: counterPolarS_Init
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
void counterPolarS_Init(void) 
{
        #if (!counterPolarS_UsingFixedFunction && !counterPolarS_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!counterPolarS_UsingFixedFunction && !counterPolarS_ControlRegRemoved) */
        
        #if(!counterPolarS_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 counterPolarS_interruptState;
        #endif /* (!counterPolarS_UsingFixedFunction) */
        
        #if (counterPolarS_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            counterPolarS_CONTROL &= counterPolarS_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                counterPolarS_CONTROL2 &= ((uint8)(~counterPolarS_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                counterPolarS_CONTROL3 &= ((uint8)(~counterPolarS_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (counterPolarS_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                counterPolarS_CONTROL |= counterPolarS_ONESHOT;
            #endif /* (counterPolarS_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            counterPolarS_CONTROL2 |= counterPolarS_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            counterPolarS_RT1 &= ((uint8)(~counterPolarS_RT1_MASK));
            counterPolarS_RT1 |= counterPolarS_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            counterPolarS_RT1 &= ((uint8)(~counterPolarS_SYNCDSI_MASK));
            counterPolarS_RT1 |= counterPolarS_SYNCDSI_EN;

        #else
            #if(!counterPolarS_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = counterPolarS_CONTROL & ((uint8)(~counterPolarS_CTRL_CMPMODE_MASK));
            counterPolarS_CONTROL = ctrl | counterPolarS_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = counterPolarS_CONTROL & ((uint8)(~counterPolarS_CTRL_CAPMODE_MASK));
            
            #if( 0 != counterPolarS_CAPTURE_MODE_CONF)
                counterPolarS_CONTROL = ctrl | counterPolarS_DEFAULT_CAPTURE_MODE;
            #else
                counterPolarS_CONTROL = ctrl;
            #endif /* 0 != counterPolarS_CAPTURE_MODE */ 
            
            #endif /* (!counterPolarS_ControlRegRemoved) */
        #endif /* (counterPolarS_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!counterPolarS_UsingFixedFunction)
            counterPolarS_ClearFIFO();
        #endif /* (!counterPolarS_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        counterPolarS_WritePeriod(counterPolarS_INIT_PERIOD_VALUE);
        #if (!(counterPolarS_UsingFixedFunction && (CY_PSOC5A)))
            counterPolarS_WriteCounter(counterPolarS_INIT_COUNTER_VALUE);
        #endif /* (!(counterPolarS_UsingFixedFunction && (CY_PSOC5A))) */
        counterPolarS_SetInterruptMode(counterPolarS_INIT_INTERRUPTS_MASK);
        
        #if (!counterPolarS_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)counterPolarS_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            counterPolarS_WriteCompare(counterPolarS_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            counterPolarS_interruptState = CyEnterCriticalSection();
            
            counterPolarS_STATUS_AUX_CTRL |= counterPolarS_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(counterPolarS_interruptState);
            
        #endif /* (!counterPolarS_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarS_Enable
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
void counterPolarS_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (counterPolarS_UsingFixedFunction)
        counterPolarS_GLOBAL_ENABLE |= counterPolarS_BLOCK_EN_MASK;
        counterPolarS_GLOBAL_STBY_ENABLE |= counterPolarS_BLOCK_STBY_EN_MASK;
    #endif /* (counterPolarS_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!counterPolarS_ControlRegRemoved || counterPolarS_UsingFixedFunction)
        counterPolarS_CONTROL |= counterPolarS_CTRL_ENABLE;                
    #endif /* (!counterPolarS_ControlRegRemoved || counterPolarS_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: counterPolarS_Start
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
*  counterPolarS_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void counterPolarS_Start(void) 
{
    if(counterPolarS_initVar == 0u)
    {
        counterPolarS_Init();
        
        counterPolarS_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    counterPolarS_Enable();        
}


/*******************************************************************************
* Function Name: counterPolarS_Stop
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
void counterPolarS_Stop(void) 
{
    /* Disable Counter */
    #if(!counterPolarS_ControlRegRemoved || counterPolarS_UsingFixedFunction)
        counterPolarS_CONTROL &= ((uint8)(~counterPolarS_CTRL_ENABLE));        
    #endif /* (!counterPolarS_ControlRegRemoved || counterPolarS_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (counterPolarS_UsingFixedFunction)
        counterPolarS_GLOBAL_ENABLE &= ((uint8)(~counterPolarS_BLOCK_EN_MASK));
        counterPolarS_GLOBAL_STBY_ENABLE &= ((uint8)(~counterPolarS_BLOCK_STBY_EN_MASK));
    #endif /* (counterPolarS_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarS_SetInterruptMode
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
void counterPolarS_SetInterruptMode(uint8 interruptsMask) 
{
    counterPolarS_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: counterPolarS_ReadStatusRegister
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
uint8   counterPolarS_ReadStatusRegister(void) 
{
    return counterPolarS_STATUS;
}


#if(!counterPolarS_ControlRegRemoved)
/*******************************************************************************
* Function Name: counterPolarS_ReadControlRegister
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
uint8   counterPolarS_ReadControlRegister(void) 
{
    return counterPolarS_CONTROL;
}


/*******************************************************************************
* Function Name: counterPolarS_WriteControlRegister
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
void    counterPolarS_WriteControlRegister(uint8 control) 
{
    counterPolarS_CONTROL = control;
}

#endif  /* (!counterPolarS_ControlRegRemoved) */


#if (!(counterPolarS_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: counterPolarS_WriteCounter
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
void counterPolarS_WriteCounter(uint8 counter) \
                                   
{
    #if(counterPolarS_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (counterPolarS_GLOBAL_ENABLE & counterPolarS_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        counterPolarS_GLOBAL_ENABLE |= counterPolarS_BLOCK_EN_MASK;
        CY_SET_REG16(counterPolarS_COUNTER_LSB_PTR, (uint16)counter);
        counterPolarS_GLOBAL_ENABLE &= ((uint8)(~counterPolarS_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(counterPolarS_COUNTER_LSB_PTR, counter);
    #endif /* (counterPolarS_UsingFixedFunction) */
}
#endif /* (!(counterPolarS_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: counterPolarS_ReadCounter
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
uint8 counterPolarS_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(counterPolarS_UsingFixedFunction)
		(void)CY_GET_REG16(counterPolarS_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(counterPolarS_COUNTER_LSB_PTR_8BIT);
	#endif/* (counterPolarS_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(counterPolarS_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(counterPolarS_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(counterPolarS_STATICCOUNT_LSB_PTR));
    #endif /* (counterPolarS_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarS_ReadCapture
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
uint8 counterPolarS_ReadCapture(void) 
{
    #if(counterPolarS_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(counterPolarS_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(counterPolarS_STATICCOUNT_LSB_PTR));
    #endif /* (counterPolarS_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarS_WritePeriod
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
void counterPolarS_WritePeriod(uint8 period) 
{
    #if(counterPolarS_UsingFixedFunction)
        CY_SET_REG16(counterPolarS_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(counterPolarS_PERIOD_LSB_PTR, period);
    #endif /* (counterPolarS_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarS_ReadPeriod
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
uint8 counterPolarS_ReadPeriod(void) 
{
    #if(counterPolarS_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(counterPolarS_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(counterPolarS_PERIOD_LSB_PTR));
    #endif /* (counterPolarS_UsingFixedFunction) */
}


#if (!counterPolarS_UsingFixedFunction)
/*******************************************************************************
* Function Name: counterPolarS_WriteCompare
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
void counterPolarS_WriteCompare(uint8 compare) \
                                   
{
    #if(counterPolarS_UsingFixedFunction)
        CY_SET_REG16(counterPolarS_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(counterPolarS_COMPARE_LSB_PTR, compare);
    #endif /* (counterPolarS_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarS_ReadCompare
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
uint8 counterPolarS_ReadCompare(void) 
{
    return (CY_GET_REG8(counterPolarS_COMPARE_LSB_PTR));
}


#if (counterPolarS_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: counterPolarS_SetCompareMode
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
void counterPolarS_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    counterPolarS_CONTROL &= ((uint8)(~counterPolarS_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    counterPolarS_CONTROL |= compareMode;
}
#endif  /* (counterPolarS_COMPARE_MODE_SOFTWARE) */


#if (counterPolarS_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: counterPolarS_SetCaptureMode
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
void counterPolarS_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    counterPolarS_CONTROL &= ((uint8)(~counterPolarS_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    counterPolarS_CONTROL |= ((uint8)((uint8)captureMode << counterPolarS_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (counterPolarS_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: counterPolarS_ClearFIFO
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
void counterPolarS_ClearFIFO(void) 
{

    while(0u != (counterPolarS_ReadStatusRegister() & counterPolarS_STATUS_FIFONEMP))
    {
        (void)counterPolarS_ReadCapture();
    }

}
#endif  /* (!counterPolarS_UsingFixedFunction) */


/* [] END OF FILE */
