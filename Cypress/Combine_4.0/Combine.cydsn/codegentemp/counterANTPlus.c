/*******************************************************************************
* File Name: counterANTPlus.c  
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

#include "counterANTPlus.h"

uint8 counterANTPlus_initVar = 0u;


/*******************************************************************************
* Function Name: counterANTPlus_Init
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
void counterANTPlus_Init(void) 
{
        #if (!counterANTPlus_UsingFixedFunction && !counterANTPlus_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!counterANTPlus_UsingFixedFunction && !counterANTPlus_ControlRegRemoved) */
        
        #if(!counterANTPlus_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 counterANTPlus_interruptState;
        #endif /* (!counterANTPlus_UsingFixedFunction) */
        
        #if (counterANTPlus_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            counterANTPlus_CONTROL &= counterANTPlus_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                counterANTPlus_CONTROL2 &= ((uint8)(~counterANTPlus_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                counterANTPlus_CONTROL3 &= ((uint8)(~counterANTPlus_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (counterANTPlus_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                counterANTPlus_CONTROL |= counterANTPlus_ONESHOT;
            #endif /* (counterANTPlus_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            counterANTPlus_CONTROL2 |= counterANTPlus_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            counterANTPlus_RT1 &= ((uint8)(~counterANTPlus_RT1_MASK));
            counterANTPlus_RT1 |= counterANTPlus_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            counterANTPlus_RT1 &= ((uint8)(~counterANTPlus_SYNCDSI_MASK));
            counterANTPlus_RT1 |= counterANTPlus_SYNCDSI_EN;

        #else
            #if(!counterANTPlus_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = counterANTPlus_CONTROL & ((uint8)(~counterANTPlus_CTRL_CMPMODE_MASK));
            counterANTPlus_CONTROL = ctrl | counterANTPlus_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = counterANTPlus_CONTROL & ((uint8)(~counterANTPlus_CTRL_CAPMODE_MASK));
            
            #if( 0 != counterANTPlus_CAPTURE_MODE_CONF)
                counterANTPlus_CONTROL = ctrl | counterANTPlus_DEFAULT_CAPTURE_MODE;
            #else
                counterANTPlus_CONTROL = ctrl;
            #endif /* 0 != counterANTPlus_CAPTURE_MODE */ 
            
            #endif /* (!counterANTPlus_ControlRegRemoved) */
        #endif /* (counterANTPlus_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!counterANTPlus_UsingFixedFunction)
            counterANTPlus_ClearFIFO();
        #endif /* (!counterANTPlus_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        counterANTPlus_WritePeriod(counterANTPlus_INIT_PERIOD_VALUE);
        #if (!(counterANTPlus_UsingFixedFunction && (CY_PSOC5A)))
            counterANTPlus_WriteCounter(counterANTPlus_INIT_COUNTER_VALUE);
        #endif /* (!(counterANTPlus_UsingFixedFunction && (CY_PSOC5A))) */
        counterANTPlus_SetInterruptMode(counterANTPlus_INIT_INTERRUPTS_MASK);
        
        #if (!counterANTPlus_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)counterANTPlus_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            counterANTPlus_WriteCompare(counterANTPlus_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            counterANTPlus_interruptState = CyEnterCriticalSection();
            
            counterANTPlus_STATUS_AUX_CTRL |= counterANTPlus_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(counterANTPlus_interruptState);
            
        #endif /* (!counterANTPlus_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterANTPlus_Enable
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
void counterANTPlus_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (counterANTPlus_UsingFixedFunction)
        counterANTPlus_GLOBAL_ENABLE |= counterANTPlus_BLOCK_EN_MASK;
        counterANTPlus_GLOBAL_STBY_ENABLE |= counterANTPlus_BLOCK_STBY_EN_MASK;
    #endif /* (counterANTPlus_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!counterANTPlus_ControlRegRemoved || counterANTPlus_UsingFixedFunction)
        counterANTPlus_CONTROL |= counterANTPlus_CTRL_ENABLE;                
    #endif /* (!counterANTPlus_ControlRegRemoved || counterANTPlus_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: counterANTPlus_Start
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
*  counterANTPlus_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void counterANTPlus_Start(void) 
{
    if(counterANTPlus_initVar == 0u)
    {
        counterANTPlus_Init();
        
        counterANTPlus_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    counterANTPlus_Enable();        
}


/*******************************************************************************
* Function Name: counterANTPlus_Stop
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
void counterANTPlus_Stop(void) 
{
    /* Disable Counter */
    #if(!counterANTPlus_ControlRegRemoved || counterANTPlus_UsingFixedFunction)
        counterANTPlus_CONTROL &= ((uint8)(~counterANTPlus_CTRL_ENABLE));        
    #endif /* (!counterANTPlus_ControlRegRemoved || counterANTPlus_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (counterANTPlus_UsingFixedFunction)
        counterANTPlus_GLOBAL_ENABLE &= ((uint8)(~counterANTPlus_BLOCK_EN_MASK));
        counterANTPlus_GLOBAL_STBY_ENABLE &= ((uint8)(~counterANTPlus_BLOCK_STBY_EN_MASK));
    #endif /* (counterANTPlus_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterANTPlus_SetInterruptMode
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
void counterANTPlus_SetInterruptMode(uint8 interruptsMask) 
{
    counterANTPlus_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: counterANTPlus_ReadStatusRegister
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
uint8   counterANTPlus_ReadStatusRegister(void) 
{
    return counterANTPlus_STATUS;
}


#if(!counterANTPlus_ControlRegRemoved)
/*******************************************************************************
* Function Name: counterANTPlus_ReadControlRegister
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
uint8   counterANTPlus_ReadControlRegister(void) 
{
    return counterANTPlus_CONTROL;
}


/*******************************************************************************
* Function Name: counterANTPlus_WriteControlRegister
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
void    counterANTPlus_WriteControlRegister(uint8 control) 
{
    counterANTPlus_CONTROL = control;
}

#endif  /* (!counterANTPlus_ControlRegRemoved) */


#if (!(counterANTPlus_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: counterANTPlus_WriteCounter
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
void counterANTPlus_WriteCounter(uint8 counter) \
                                   
{
    #if(counterANTPlus_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (counterANTPlus_GLOBAL_ENABLE & counterANTPlus_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        counterANTPlus_GLOBAL_ENABLE |= counterANTPlus_BLOCK_EN_MASK;
        CY_SET_REG16(counterANTPlus_COUNTER_LSB_PTR, (uint16)counter);
        counterANTPlus_GLOBAL_ENABLE &= ((uint8)(~counterANTPlus_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(counterANTPlus_COUNTER_LSB_PTR, counter);
    #endif /* (counterANTPlus_UsingFixedFunction) */
}
#endif /* (!(counterANTPlus_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: counterANTPlus_ReadCounter
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
uint8 counterANTPlus_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(counterANTPlus_UsingFixedFunction)
		(void)CY_GET_REG16(counterANTPlus_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(counterANTPlus_COUNTER_LSB_PTR_8BIT);
	#endif/* (counterANTPlus_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(counterANTPlus_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(counterANTPlus_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(counterANTPlus_STATICCOUNT_LSB_PTR));
    #endif /* (counterANTPlus_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterANTPlus_ReadCapture
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
uint8 counterANTPlus_ReadCapture(void) 
{
    #if(counterANTPlus_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(counterANTPlus_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(counterANTPlus_STATICCOUNT_LSB_PTR));
    #endif /* (counterANTPlus_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterANTPlus_WritePeriod
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
void counterANTPlus_WritePeriod(uint8 period) 
{
    #if(counterANTPlus_UsingFixedFunction)
        CY_SET_REG16(counterANTPlus_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(counterANTPlus_PERIOD_LSB_PTR, period);
    #endif /* (counterANTPlus_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterANTPlus_ReadPeriod
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
uint8 counterANTPlus_ReadPeriod(void) 
{
    #if(counterANTPlus_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(counterANTPlus_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(counterANTPlus_PERIOD_LSB_PTR));
    #endif /* (counterANTPlus_UsingFixedFunction) */
}


#if (!counterANTPlus_UsingFixedFunction)
/*******************************************************************************
* Function Name: counterANTPlus_WriteCompare
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
void counterANTPlus_WriteCompare(uint8 compare) \
                                   
{
    #if(counterANTPlus_UsingFixedFunction)
        CY_SET_REG16(counterANTPlus_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(counterANTPlus_COMPARE_LSB_PTR, compare);
    #endif /* (counterANTPlus_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterANTPlus_ReadCompare
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
uint8 counterANTPlus_ReadCompare(void) 
{
    return (CY_GET_REG8(counterANTPlus_COMPARE_LSB_PTR));
}


#if (counterANTPlus_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: counterANTPlus_SetCompareMode
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
void counterANTPlus_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    counterANTPlus_CONTROL &= ((uint8)(~counterANTPlus_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    counterANTPlus_CONTROL |= compareMode;
}
#endif  /* (counterANTPlus_COMPARE_MODE_SOFTWARE) */


#if (counterANTPlus_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: counterANTPlus_SetCaptureMode
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
void counterANTPlus_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    counterANTPlus_CONTROL &= ((uint8)(~counterANTPlus_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    counterANTPlus_CONTROL |= ((uint8)((uint8)captureMode << counterANTPlus_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (counterANTPlus_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: counterANTPlus_ClearFIFO
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
void counterANTPlus_ClearFIFO(void) 
{

    while(0u != (counterANTPlus_ReadStatusRegister() & counterANTPlus_STATUS_FIFONEMP))
    {
        (void)counterANTPlus_ReadCapture();
    }

}
#endif  /* (!counterANTPlus_UsingFixedFunction) */


/* [] END OF FILE */

