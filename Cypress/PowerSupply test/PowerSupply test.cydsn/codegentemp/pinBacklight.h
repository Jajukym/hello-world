/*******************************************************************************
* File Name: pinBacklight.h  
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

#if !defined(CY_PINS_pinBacklight_H) /* Pins pinBacklight_H */
#define CY_PINS_pinBacklight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "pinBacklight_aliases.h"


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
} pinBacklight_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   pinBacklight_Read(void);
void    pinBacklight_Write(uint8 value);
uint8   pinBacklight_ReadDataReg(void);
#if defined(pinBacklight__PC) || (CY_PSOC4_4200L) 
    void    pinBacklight_SetDriveMode(uint8 mode);
#endif
void    pinBacklight_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinBacklight_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void pinBacklight_Sleep(void); 
void pinBacklight_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(pinBacklight__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define pinBacklight_DRIVE_MODE_BITS        (3)
    #define pinBacklight_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - pinBacklight_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the pinBacklight_SetDriveMode() function.
         *  @{
         */
        #define pinBacklight_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define pinBacklight_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define pinBacklight_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define pinBacklight_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define pinBacklight_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define pinBacklight_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define pinBacklight_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define pinBacklight_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define pinBacklight_MASK               pinBacklight__MASK
#define pinBacklight_SHIFT              pinBacklight__SHIFT
#define pinBacklight_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinBacklight_SetInterruptMode() function.
     *  @{
     */
        #define pinBacklight_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define pinBacklight_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define pinBacklight_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define pinBacklight_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(pinBacklight__SIO)
    #define pinBacklight_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(pinBacklight__PC) && (CY_PSOC4_4200L)
    #define pinBacklight_USBIO_ENABLE               ((uint32)0x80000000u)
    #define pinBacklight_USBIO_DISABLE              ((uint32)(~pinBacklight_USBIO_ENABLE))
    #define pinBacklight_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define pinBacklight_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define pinBacklight_USBIO_ENTER_SLEEP          ((uint32)((1u << pinBacklight_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << pinBacklight_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinBacklight_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << pinBacklight_USBIO_SUSPEND_SHIFT)))
    #define pinBacklight_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << pinBacklight_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinBacklight_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(pinBacklight__PC)
    /* Port Configuration */
    #define pinBacklight_PC                 (* (reg32 *) pinBacklight__PC)
#endif
/* Pin State */
#define pinBacklight_PS                     (* (reg32 *) pinBacklight__PS)
/* Data Register */
#define pinBacklight_DR                     (* (reg32 *) pinBacklight__DR)
/* Input Buffer Disable Override */
#define pinBacklight_INP_DIS                (* (reg32 *) pinBacklight__PC2)

/* Interrupt configuration Registers */
#define pinBacklight_INTCFG                 (* (reg32 *) pinBacklight__INTCFG)
#define pinBacklight_INTSTAT                (* (reg32 *) pinBacklight__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define pinBacklight_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(pinBacklight__SIO)
    #define pinBacklight_SIO_REG            (* (reg32 *) pinBacklight__SIO)
#endif /* (pinBacklight__SIO_CFG) */

/* USBIO registers */
#if !defined(pinBacklight__PC) && (CY_PSOC4_4200L)
    #define pinBacklight_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define pinBacklight_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define pinBacklight_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define pinBacklight_DRIVE_MODE_SHIFT       (0x00u)
#define pinBacklight_DRIVE_MODE_MASK        (0x07u << pinBacklight_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins pinBacklight_H */


/* [] END OF FILE */
