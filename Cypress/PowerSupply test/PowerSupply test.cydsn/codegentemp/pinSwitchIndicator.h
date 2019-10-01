/*******************************************************************************
* File Name: pinSwitchIndicator.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_pinSwitchIndicator_H) /* Pins pinSwitchIndicator_H */
#define CY_PINS_pinSwitchIndicator_H

#include "cytypes.h"
#include "cyfitter.h"
#include "pinSwitchIndicator_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} pinSwitchIndicator_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   pinSwitchIndicator_Read(void);
void    pinSwitchIndicator_Write(uint8 value);
uint8   pinSwitchIndicator_ReadDataReg(void);
#if defined(pinSwitchIndicator__PC) || (CY_PSOC4_4200L) 
    void    pinSwitchIndicator_SetDriveMode(uint8 mode);
#endif
void    pinSwitchIndicator_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinSwitchIndicator_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void pinSwitchIndicator_Sleep(void); 
void pinSwitchIndicator_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(pinSwitchIndicator__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define pinSwitchIndicator_DRIVE_MODE_BITS        (3)
    #define pinSwitchIndicator_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - pinSwitchIndicator_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the pinSwitchIndicator_SetDriveMode() function.
         *  @{
         */
        #define pinSwitchIndicator_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define pinSwitchIndicator_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define pinSwitchIndicator_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define pinSwitchIndicator_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define pinSwitchIndicator_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define pinSwitchIndicator_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define pinSwitchIndicator_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define pinSwitchIndicator_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define pinSwitchIndicator_MASK               pinSwitchIndicator__MASK
#define pinSwitchIndicator_SHIFT              pinSwitchIndicator__SHIFT
#define pinSwitchIndicator_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinSwitchIndicator_SetInterruptMode() function.
     *  @{
     */
        #define pinSwitchIndicator_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define pinSwitchIndicator_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define pinSwitchIndicator_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define pinSwitchIndicator_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(pinSwitchIndicator__SIO)
    #define pinSwitchIndicator_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(pinSwitchIndicator__PC) && (CY_PSOC4_4200L)
    #define pinSwitchIndicator_USBIO_ENABLE               ((uint32)0x80000000u)
    #define pinSwitchIndicator_USBIO_DISABLE              ((uint32)(~pinSwitchIndicator_USBIO_ENABLE))
    #define pinSwitchIndicator_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define pinSwitchIndicator_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define pinSwitchIndicator_USBIO_ENTER_SLEEP          ((uint32)((1u << pinSwitchIndicator_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << pinSwitchIndicator_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinSwitchIndicator_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << pinSwitchIndicator_USBIO_SUSPEND_SHIFT)))
    #define pinSwitchIndicator_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << pinSwitchIndicator_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinSwitchIndicator_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(pinSwitchIndicator__PC)
    /* Port Configuration */
    #define pinSwitchIndicator_PC                 (* (reg32 *) pinSwitchIndicator__PC)
#endif
/* Pin State */
#define pinSwitchIndicator_PS                     (* (reg32 *) pinSwitchIndicator__PS)
/* Data Register */
#define pinSwitchIndicator_DR                     (* (reg32 *) pinSwitchIndicator__DR)
/* Input Buffer Disable Override */
#define pinSwitchIndicator_INP_DIS                (* (reg32 *) pinSwitchIndicator__PC2)

/* Interrupt configuration Registers */
#define pinSwitchIndicator_INTCFG                 (* (reg32 *) pinSwitchIndicator__INTCFG)
#define pinSwitchIndicator_INTSTAT                (* (reg32 *) pinSwitchIndicator__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define pinSwitchIndicator_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(pinSwitchIndicator__SIO)
    #define pinSwitchIndicator_SIO_REG            (* (reg32 *) pinSwitchIndicator__SIO)
#endif /* (pinSwitchIndicator__SIO_CFG) */

/* USBIO registers */
#if !defined(pinSwitchIndicator__PC) && (CY_PSOC4_4200L)
    #define pinSwitchIndicator_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define pinSwitchIndicator_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define pinSwitchIndicator_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define pinSwitchIndicator_DRIVE_MODE_SHIFT       (0x00u)
#define pinSwitchIndicator_DRIVE_MODE_MASK        (0x07u << pinSwitchIndicator_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins pinSwitchIndicator_H */


/* [] END OF FILE */
