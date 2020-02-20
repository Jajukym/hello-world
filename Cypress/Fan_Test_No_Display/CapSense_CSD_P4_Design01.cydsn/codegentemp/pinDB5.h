/*******************************************************************************
* File Name: pinDB5.h  
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

#if !defined(CY_PINS_pinDB5_H) /* Pins pinDB5_H */
#define CY_PINS_pinDB5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "pinDB5_aliases.h"


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
} pinDB5_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   pinDB5_Read(void);
void    pinDB5_Write(uint8 value);
uint8   pinDB5_ReadDataReg(void);
#if defined(pinDB5__PC) || (CY_PSOC4_4200L) 
    void    pinDB5_SetDriveMode(uint8 mode);
#endif
void    pinDB5_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinDB5_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void pinDB5_Sleep(void); 
void pinDB5_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(pinDB5__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define pinDB5_DRIVE_MODE_BITS        (3)
    #define pinDB5_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - pinDB5_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the pinDB5_SetDriveMode() function.
         *  @{
         */
        #define pinDB5_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define pinDB5_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define pinDB5_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define pinDB5_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define pinDB5_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define pinDB5_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define pinDB5_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define pinDB5_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define pinDB5_MASK               pinDB5__MASK
#define pinDB5_SHIFT              pinDB5__SHIFT
#define pinDB5_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinDB5_SetInterruptMode() function.
     *  @{
     */
        #define pinDB5_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define pinDB5_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define pinDB5_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define pinDB5_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(pinDB5__SIO)
    #define pinDB5_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(pinDB5__PC) && (CY_PSOC4_4200L)
    #define pinDB5_USBIO_ENABLE               ((uint32)0x80000000u)
    #define pinDB5_USBIO_DISABLE              ((uint32)(~pinDB5_USBIO_ENABLE))
    #define pinDB5_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define pinDB5_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define pinDB5_USBIO_ENTER_SLEEP          ((uint32)((1u << pinDB5_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << pinDB5_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinDB5_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << pinDB5_USBIO_SUSPEND_SHIFT)))
    #define pinDB5_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << pinDB5_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinDB5_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(pinDB5__PC)
    /* Port Configuration */
    #define pinDB5_PC                 (* (reg32 *) pinDB5__PC)
#endif
/* Pin State */
#define pinDB5_PS                     (* (reg32 *) pinDB5__PS)
/* Data Register */
#define pinDB5_DR                     (* (reg32 *) pinDB5__DR)
/* Input Buffer Disable Override */
#define pinDB5_INP_DIS                (* (reg32 *) pinDB5__PC2)

/* Interrupt configuration Registers */
#define pinDB5_INTCFG                 (* (reg32 *) pinDB5__INTCFG)
#define pinDB5_INTSTAT                (* (reg32 *) pinDB5__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define pinDB5_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(pinDB5__SIO)
    #define pinDB5_SIO_REG            (* (reg32 *) pinDB5__SIO)
#endif /* (pinDB5__SIO_CFG) */

/* USBIO registers */
#if !defined(pinDB5__PC) && (CY_PSOC4_4200L)
    #define pinDB5_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define pinDB5_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define pinDB5_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define pinDB5_DRIVE_MODE_SHIFT       (0x00u)
#define pinDB5_DRIVE_MODE_MASK        (0x07u << pinDB5_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins pinDB5_H */


/* [] END OF FILE */