/*******************************************************************************
* File Name: pinE.h  
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

#if !defined(CY_PINS_pinE_H) /* Pins pinE_H */
#define CY_PINS_pinE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "pinE_aliases.h"


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
} pinE_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   pinE_Read(void);
void    pinE_Write(uint8 value);
uint8   pinE_ReadDataReg(void);
#if defined(pinE__PC) || (CY_PSOC4_4200L) 
    void    pinE_SetDriveMode(uint8 mode);
#endif
void    pinE_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinE_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void pinE_Sleep(void); 
void pinE_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(pinE__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define pinE_DRIVE_MODE_BITS        (3)
    #define pinE_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - pinE_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the pinE_SetDriveMode() function.
         *  @{
         */
        #define pinE_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define pinE_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define pinE_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define pinE_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define pinE_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define pinE_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define pinE_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define pinE_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define pinE_MASK               pinE__MASK
#define pinE_SHIFT              pinE__SHIFT
#define pinE_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinE_SetInterruptMode() function.
     *  @{
     */
        #define pinE_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define pinE_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define pinE_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define pinE_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(pinE__SIO)
    #define pinE_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(pinE__PC) && (CY_PSOC4_4200L)
    #define pinE_USBIO_ENABLE               ((uint32)0x80000000u)
    #define pinE_USBIO_DISABLE              ((uint32)(~pinE_USBIO_ENABLE))
    #define pinE_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define pinE_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define pinE_USBIO_ENTER_SLEEP          ((uint32)((1u << pinE_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << pinE_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinE_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << pinE_USBIO_SUSPEND_SHIFT)))
    #define pinE_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << pinE_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinE_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(pinE__PC)
    /* Port Configuration */
    #define pinE_PC                 (* (reg32 *) pinE__PC)
#endif
/* Pin State */
#define pinE_PS                     (* (reg32 *) pinE__PS)
/* Data Register */
#define pinE_DR                     (* (reg32 *) pinE__DR)
/* Input Buffer Disable Override */
#define pinE_INP_DIS                (* (reg32 *) pinE__PC2)

/* Interrupt configuration Registers */
#define pinE_INTCFG                 (* (reg32 *) pinE__INTCFG)
#define pinE_INTSTAT                (* (reg32 *) pinE__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define pinE_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(pinE__SIO)
    #define pinE_SIO_REG            (* (reg32 *) pinE__SIO)
#endif /* (pinE__SIO_CFG) */

/* USBIO registers */
#if !defined(pinE__PC) && (CY_PSOC4_4200L)
    #define pinE_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define pinE_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define pinE_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define pinE_DRIVE_MODE_SHIFT       (0x00u)
#define pinE_DRIVE_MODE_MASK        (0x07u << pinE_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins pinE_H */


/* [] END OF FILE */
