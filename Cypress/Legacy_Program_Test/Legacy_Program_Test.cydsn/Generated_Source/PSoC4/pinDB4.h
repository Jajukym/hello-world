/*******************************************************************************
* File Name: pinDB4.h  
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

#if !defined(CY_PINS_pinDB4_H) /* Pins pinDB4_H */
#define CY_PINS_pinDB4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "pinDB4_aliases.h"


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
} pinDB4_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   pinDB4_Read(void);
void    pinDB4_Write(uint8 value);
uint8   pinDB4_ReadDataReg(void);
#if defined(pinDB4__PC) || (CY_PSOC4_4200L) 
    void    pinDB4_SetDriveMode(uint8 mode);
#endif
void    pinDB4_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinDB4_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void pinDB4_Sleep(void); 
void pinDB4_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(pinDB4__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define pinDB4_DRIVE_MODE_BITS        (3)
    #define pinDB4_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - pinDB4_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the pinDB4_SetDriveMode() function.
         *  @{
         */
        #define pinDB4_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define pinDB4_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define pinDB4_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define pinDB4_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define pinDB4_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define pinDB4_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define pinDB4_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define pinDB4_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define pinDB4_MASK               pinDB4__MASK
#define pinDB4_SHIFT              pinDB4__SHIFT
#define pinDB4_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinDB4_SetInterruptMode() function.
     *  @{
     */
        #define pinDB4_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define pinDB4_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define pinDB4_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define pinDB4_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(pinDB4__SIO)
    #define pinDB4_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(pinDB4__PC) && (CY_PSOC4_4200L)
    #define pinDB4_USBIO_ENABLE               ((uint32)0x80000000u)
    #define pinDB4_USBIO_DISABLE              ((uint32)(~pinDB4_USBIO_ENABLE))
    #define pinDB4_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define pinDB4_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define pinDB4_USBIO_ENTER_SLEEP          ((uint32)((1u << pinDB4_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << pinDB4_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinDB4_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << pinDB4_USBIO_SUSPEND_SHIFT)))
    #define pinDB4_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << pinDB4_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinDB4_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(pinDB4__PC)
    /* Port Configuration */
    #define pinDB4_PC                 (* (reg32 *) pinDB4__PC)
#endif
/* Pin State */
#define pinDB4_PS                     (* (reg32 *) pinDB4__PS)
/* Data Register */
#define pinDB4_DR                     (* (reg32 *) pinDB4__DR)
/* Input Buffer Disable Override */
#define pinDB4_INP_DIS                (* (reg32 *) pinDB4__PC2)

/* Interrupt configuration Registers */
#define pinDB4_INTCFG                 (* (reg32 *) pinDB4__INTCFG)
#define pinDB4_INTSTAT                (* (reg32 *) pinDB4__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define pinDB4_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(pinDB4__SIO)
    #define pinDB4_SIO_REG            (* (reg32 *) pinDB4__SIO)
#endif /* (pinDB4__SIO_CFG) */

/* USBIO registers */
#if !defined(pinDB4__PC) && (CY_PSOC4_4200L)
    #define pinDB4_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define pinDB4_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define pinDB4_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define pinDB4_DRIVE_MODE_SHIFT       (0x00u)
#define pinDB4_DRIVE_MODE_MASK        (0x07u << pinDB4_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins pinDB4_H */


/* [] END OF FILE */
