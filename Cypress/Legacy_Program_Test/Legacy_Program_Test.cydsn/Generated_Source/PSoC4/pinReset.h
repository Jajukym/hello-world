/*******************************************************************************
* File Name: pinReset.h  
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

#if !defined(CY_PINS_pinReset_H) /* Pins pinReset_H */
#define CY_PINS_pinReset_H

#include "cytypes.h"
#include "cyfitter.h"
#include "pinReset_aliases.h"


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
} pinReset_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   pinReset_Read(void);
void    pinReset_Write(uint8 value);
uint8   pinReset_ReadDataReg(void);
#if defined(pinReset__PC) || (CY_PSOC4_4200L) 
    void    pinReset_SetDriveMode(uint8 mode);
#endif
void    pinReset_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinReset_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void pinReset_Sleep(void); 
void pinReset_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(pinReset__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define pinReset_DRIVE_MODE_BITS        (3)
    #define pinReset_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - pinReset_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the pinReset_SetDriveMode() function.
         *  @{
         */
        #define pinReset_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define pinReset_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define pinReset_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define pinReset_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define pinReset_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define pinReset_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define pinReset_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define pinReset_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define pinReset_MASK               pinReset__MASK
#define pinReset_SHIFT              pinReset__SHIFT
#define pinReset_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinReset_SetInterruptMode() function.
     *  @{
     */
        #define pinReset_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define pinReset_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define pinReset_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define pinReset_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(pinReset__SIO)
    #define pinReset_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(pinReset__PC) && (CY_PSOC4_4200L)
    #define pinReset_USBIO_ENABLE               ((uint32)0x80000000u)
    #define pinReset_USBIO_DISABLE              ((uint32)(~pinReset_USBIO_ENABLE))
    #define pinReset_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define pinReset_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define pinReset_USBIO_ENTER_SLEEP          ((uint32)((1u << pinReset_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << pinReset_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinReset_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << pinReset_USBIO_SUSPEND_SHIFT)))
    #define pinReset_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << pinReset_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinReset_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(pinReset__PC)
    /* Port Configuration */
    #define pinReset_PC                 (* (reg32 *) pinReset__PC)
#endif
/* Pin State */
#define pinReset_PS                     (* (reg32 *) pinReset__PS)
/* Data Register */
#define pinReset_DR                     (* (reg32 *) pinReset__DR)
/* Input Buffer Disable Override */
#define pinReset_INP_DIS                (* (reg32 *) pinReset__PC2)

/* Interrupt configuration Registers */
#define pinReset_INTCFG                 (* (reg32 *) pinReset__INTCFG)
#define pinReset_INTSTAT                (* (reg32 *) pinReset__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define pinReset_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(pinReset__SIO)
    #define pinReset_SIO_REG            (* (reg32 *) pinReset__SIO)
#endif /* (pinReset__SIO_CFG) */

/* USBIO registers */
#if !defined(pinReset__PC) && (CY_PSOC4_4200L)
    #define pinReset_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define pinReset_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define pinReset_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define pinReset_DRIVE_MODE_SHIFT       (0x00u)
#define pinReset_DRIVE_MODE_MASK        (0x07u << pinReset_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins pinReset_H */


/* [] END OF FILE */
