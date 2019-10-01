/*******************************************************************************
* File Name: pinSwitchIndicator.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "pinSwitchIndicator.h"

static pinSwitchIndicator_BACKUP_STRUCT  pinSwitchIndicator_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: pinSwitchIndicator_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet pinSwitchIndicator_SUT.c usage_pinSwitchIndicator_Sleep_Wakeup
*******************************************************************************/
void pinSwitchIndicator_Sleep(void)
{
    #if defined(pinSwitchIndicator__PC)
        pinSwitchIndicator_backup.pcState = pinSwitchIndicator_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            pinSwitchIndicator_backup.usbState = pinSwitchIndicator_CR1_REG;
            pinSwitchIndicator_USB_POWER_REG |= pinSwitchIndicator_USBIO_ENTER_SLEEP;
            pinSwitchIndicator_CR1_REG &= pinSwitchIndicator_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(pinSwitchIndicator__SIO)
        pinSwitchIndicator_backup.sioState = pinSwitchIndicator_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        pinSwitchIndicator_SIO_REG &= (uint32)(~pinSwitchIndicator_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: pinSwitchIndicator_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to pinSwitchIndicator_Sleep() for an example usage.
*******************************************************************************/
void pinSwitchIndicator_Wakeup(void)
{
    #if defined(pinSwitchIndicator__PC)
        pinSwitchIndicator_PC = pinSwitchIndicator_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            pinSwitchIndicator_USB_POWER_REG &= pinSwitchIndicator_USBIO_EXIT_SLEEP_PH1;
            pinSwitchIndicator_CR1_REG = pinSwitchIndicator_backup.usbState;
            pinSwitchIndicator_USB_POWER_REG &= pinSwitchIndicator_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(pinSwitchIndicator__SIO)
        pinSwitchIndicator_SIO_REG = pinSwitchIndicator_backup.sioState;
    #endif
}


/* [] END OF FILE */
