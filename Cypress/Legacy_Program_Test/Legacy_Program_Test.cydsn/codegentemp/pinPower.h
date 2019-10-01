/*******************************************************************************
* File Name: pinPower.h  
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

#if !defined(CY_PINS_pinPower_H) /* Pins pinPower_H */
#define CY_PINS_pinPower_H

#include "cytypes.h"
#include "cyfitter.h"
#include "pinPower_aliases.h"


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
} pinPower_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   pinPower_Read(void);
void    pinPower_Write(uint8 value);
uint8   pinPower_ReadDataReg(void);
#if defined(pinPower__PC) || (CY_PSOC4_4200L) 
    void    pinPower_SetDriveMode(uint8 mode);
#endif
void    pinPower_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinPower_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void pinPower_Sleep(void); 
void pinPower_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(pinPower__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define pinPower_DRIVE_MODE_BITS        (3)
    #define pinPower_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - pinPower_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the pinPower_SetDriveMode() function.
         *  @{
         */
        #define pinPower_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define pinPower_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define pinPower_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define pinPower_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define pinPower_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define pinPower_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define pinPower_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define pinPower_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define pinPower_MASK               pinPower__MASK
#define pinPower_SHIFT              pinPower__SHIFT
#define pinPower_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinPower_SetInterruptMode() function.
     *  @{
     */
        #define pinPower_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define pinPower_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define pinPower_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define pinPower_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(pinPower__SIO)
    #define pinPower_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(pinPower__PC) && (CY_PSOC4_4200L)
    #define pinPower_USBIO_ENABLE               ((uint32)0x80000000u)
    #define pinPower_USBIO_DISABLE              ((uint32)(~pinPower_USBIO_ENABLE))
    #define pinPower_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define pinPower_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define pinPower_USBIO_ENTER_SLEEP          ((uint32)((1u << pinPower_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << pinPower_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinPower_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << pinPower_USBIO_SUSPEND_SHIFT)))
    #define pinPower_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << pinPower_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinPower_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(pinPower__PC)
    /* Port Configuration */
    #define pinPower_PC                 (* (reg32 *) pinPower__PC)
#endif
/* Pin State */
#define pinPower_PS                     (* (reg32 *) pinPower__PS)
/* Data Register */
#define pinPower_DR                     (* (reg32 *) pinPower__DR)
/* Input Buffer Disable Override */
#define pinPower_INP_DIS                (* (reg32 *) pinPower__PC2)

/* Interrupt configuration Registers */
#define pinPower_INTCFG                 (* (reg32 *) pinPower__INTCFG)
#define pinPower_INTSTAT                (* (reg32 *) pinPower__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define pinPower_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(pinPower__SIO)
    #define pinPower_SIO_REG            (* (reg32 *) pinPower__SIO)
#endif /* (pinPower__SIO_CFG) */

/* USBIO registers */
#if !defined(pinPower__PC) && (CY_PSOC4_4200L)
    #define pinPower_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define pinPower_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define pinPower_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define pinPower_DRIVE_MODE_SHIFT       (0x00u)
#define pinPower_DRIVE_MODE_MASK        (0x07u << pinPower_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins pinPower_H */


/* [] END OF FILE */
