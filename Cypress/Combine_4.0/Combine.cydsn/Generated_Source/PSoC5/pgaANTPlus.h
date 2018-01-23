/*******************************************************************************
* File Name: pgaANTPlus.h  
* Version 2.0
*
* Description:
*  This file contains the function prototypes and constants used in
*  the PGA User Module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PGA_pgaANTPlus_H) 
#define CY_PGA_pgaANTPlus_H 

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PGA_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


#if(!CY_PSOC5A)
    #if(CYDEV_VARIABLE_VDDA == 1)
        #if (!defined(CY_LIB_SC_BST_CLK_EN))
            #error Component PGA_v2_0 requires cy_boot v3.30 or later
        #endif /* (!defined(CY_LIB_SC_BST_CLK_EN)) */
    #endif /* CYDEV_VARIABLE_VDDA == 1 */
#endif /* (!CY_PSOC5A) */

/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
    uint8   enableState;
    uint8   scCR1Reg;
    uint8   scCR2Reg;
    uint8   scCR3Reg;
}   pgaANTPlus_BACKUP_STRUCT;


/* variable describes init state of the component */
extern uint8 pgaANTPlus_initVar;


/***************************************
*        Function Prototypes 
***************************************/

void pgaANTPlus_Start(void)                 ; 
void pgaANTPlus_Stop(void)                  ; 
void pgaANTPlus_SetPower(uint8 power)       ;
void pgaANTPlus_SetGain(uint8 gain)         ;
void pgaANTPlus_Sleep(void)                 ; 
void pgaANTPlus_Wakeup(void)                ;
void pgaANTPlus_SaveConfig(void)            ; 
void pgaANTPlus_RestoreConfig(void)         ;
void pgaANTPlus_Init(void)                  ;
void pgaANTPlus_Enable(void)                ;


/***************************************
*            API Constants
***************************************/

/* Power constants for SetPower function */
#define pgaANTPlus_MINPOWER                 (0x00u)
#define pgaANTPlus_LOWPOWER                 (0x01u)
#define pgaANTPlus_MEDPOWER                 (0x02u)
#define pgaANTPlus_HIGHPOWER                (0x03u)

/* Constants for SetGain function */
#define pgaANTPlus_GAIN_01                  (0x00u)
#define pgaANTPlus_GAIN_02                  (0x01u)
#define pgaANTPlus_GAIN_04                  (0x02u)
#define pgaANTPlus_GAIN_08                  (0x03u)
#define pgaANTPlus_GAIN_16                  (0x04u)
#define pgaANTPlus_GAIN_24                  (0x05u)
#define pgaANTPlus_GAIN_32                  (0x06u)
#define pgaANTPlus_GAIN_48                  (0x07u)
#define pgaANTPlus_GAIN_50                  (0x08u)
#define pgaANTPlus_GAIN_MAX                 (0x08u)


/***************************************
*       Initialization Values
***************************************/

#define pgaANTPlus_DEFAULT_GAIN             (8u)
#define pgaANTPlus_VREF_MODE                ((0u != 0x00u) ? (0x00u) : pgaANTPlus_GNDVREF_E)
#define pgaANTPlus_DEFAULT_POWER            (3u)


/***************************************
*              Registers
***************************************/

#define pgaANTPlus_CR0_REG                  (* (reg8 *) pgaANTPlus_SC__CR0 )
#define pgaANTPlus_CR0_PTR                  (  (reg8 *) pgaANTPlus_SC__CR0 )
#define pgaANTPlus_CR1_REG                  (* (reg8 *) pgaANTPlus_SC__CR1 )
#define pgaANTPlus_CR1_PTR                  (  (reg8 *) pgaANTPlus_SC__CR1 )
#define pgaANTPlus_CR2_REG                  (* (reg8 *) pgaANTPlus_SC__CR2 )
#define pgaANTPlus_CR2_PTR                  (  (reg8 *) pgaANTPlus_SC__CR2 )
  /* Power manager */
#define pgaANTPlus_PM_ACT_CFG_REG           (* (reg8 *) pgaANTPlus_SC__PM_ACT_CFG )
#define pgaANTPlus_PM_ACT_CFG_PTR           (  (reg8 *) pgaANTPlus_SC__PM_ACT_CFG )  
#define pgaANTPlus_PM_STBY_CFG_REG          (* (reg8 *) pgaANTPlus_SC__PM_STBY_CFG )
  /* Power manager */
#define pgaANTPlus_PM_STBY_CFG_PTR          (  (reg8 *) pgaANTPlus_SC__PM_STBY_CFG )  
#define pgaANTPlus_BSTCLK_REG               (* (reg8 *) pgaANTPlus_SC__BST )
#define pgaANTPlus_BSTCLK_PTR               (  (reg8 *) pgaANTPlus_SC__BST )
/* Pump clock selectin register */
#define pgaANTPlus_PUMP_CR1_REG             (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)
#define pgaANTPlus_PUMP_CR1_PTR             (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

/* Pump Register for SC block */
#define pgaANTPlus_SC_MISC_REG              (* (reg8 *) CYDEV_ANAIF_RT_SC_MISC)
#define pgaANTPlus_SC_MISC_PTR              (  (reg8 *) CYDEV_ANAIF_RT_SC_MISC)

/* PM_ACT_CFG (Active Power Mode CFG Register)mask */ 
#define pgaANTPlus_ACT_PWR_EN               pgaANTPlus_SC__PM_ACT_MSK 

/* PM_STBY_CFG (Alternate Active Power Mode CFG Register)mask */ 
#define pgaANTPlus_STBY_PWR_EN              pgaANTPlus_SC__PM_STBY_MSK 


/***************************************
*            Register Constants
***************************************/

/* SC_MISC constants */
#define pgaANTPlus_PUMP_FORCE               (0x20u)
#define pgaANTPlus_PUMP_AUTO                (0x10u)
#define pgaANTPlus_DIFF_PGA_1_3             (0x02u)
#define pgaANTPlus_DIFF_PGA_0_2             (0x01u)

/* ANIF.PUMP.CR1 Constants */
#define pgaANTPlus_PUMP_CR1_SC_CLKSEL       (0x80u)

/* CR0 SC/CT Control Register 0 definitions */
#define pgaANTPlus_MODE_PGA                 (0x0Cu)

/* CR1 SC/CT Control Register 1 definitions */

/* Bit Field  SC_COMP_ENUM */
#define pgaANTPlus_COMP_MASK                (0x0Cu)
#define pgaANTPlus_COMP_3P0PF               (0x00u)
#define pgaANTPlus_COMP_3P6PF               (0x04u)
#define pgaANTPlus_COMP_4P35PF              (0x08u)
#define pgaANTPlus_COMP_5P1PF               (0x0Cu)

/* Bit Field  SC_DIV2_ENUM */
#define pgaANTPlus_DIV2_MASK                (0x10u)
#define pgaANTPlus_DIV2_DISABLE             (0x00u)
#define pgaANTPlus_DIV2_ENABLE              (0x10u)

/* Bit Field  SC_DRIVE_ENUM */
#define pgaANTPlus_DRIVE_MASK               (0x03u)
#define pgaANTPlus_DRIVE_280UA              (0x00u)
#define pgaANTPlus_DRIVE_420UA              (0x01u)
#define pgaANTPlus_DRIVE_530UA              (0x02u)
#define pgaANTPlus_DRIVE_650UA              (0x03u)

/* Bit Field  SC_PGA_MODE_ENUM */
#define pgaANTPlus_PGA_MODE_MASK            (0x20u)
#define pgaANTPlus_PGA_INV                  (0x00u)
#define pgaANTPlus_PGA_NINV                 (0x20u)

/* CR2 SC/CT Control Register 2 definitions */

/* Bit Field  SC_BIAS_CONTROL_ENUM */
#define pgaANTPlus_BIAS_MASK                (0x01u)
#define pgaANTPlus_BIAS_NORMAL              (0x00u)
#define pgaANTPlus_BIAS_LOW                 (0x01u)

/* Bit Field  SC_PGA_GNDVREF_ENUM  */
#define pgaANTPlus_GNDVREF_MASK             (0x80u)
#define pgaANTPlus_GNDVREF_DI               (0x00u)
#define pgaANTPlus_GNDVREF_E                (0x80u)

/* Bit Field  SC_R20_40B_ENUM */
#define pgaANTPlus_R20_40B_MASK             (0x02u)
#define pgaANTPlus_R20_40B_40K              (0x00u)
#define pgaANTPlus_R20_40B_20K              (0x02u)

/* Bit Field  SC_REDC_ENUM */
#define pgaANTPlus_REDC_MASK                (0x0Cu)
#define pgaANTPlus_REDC_00                  (0x00u)
#define pgaANTPlus_REDC_01                  (0x04u)
#define pgaANTPlus_REDC_10                  (0x08u)
#define pgaANTPlus_REDC_11                  (0x0Cu)

/* Bit Field  SC_RVAL_ENUM */
#define pgaANTPlus_RVAL_MASK                (0x70u)
#define pgaANTPlus_RVAL_0K                  (0x00u)
#define pgaANTPlus_RVAL_40K                 (0x10u)
#define pgaANTPlus_RVAL_120K                (0x20u)
#define pgaANTPlus_RVAL_280K                (0x30u)
#define pgaANTPlus_RVAL_600K                (0x40u)
#define pgaANTPlus_RVAL_460K                (0x60u)
#define pgaANTPlus_RVAL_620K                (0x50u)
#define pgaANTPlus_RVAL_470K                (0x60u)
#define pgaANTPlus_RVAL_490K                (0x70u)

/* Bit Field  PGA_GAIN_ENUM */
#define pgaANTPlus_PGA_GAIN_MASK            (0x72u)
#define pgaANTPlus_PGA_GAIN_01              (0x00u)
#define pgaANTPlus_PGA_GAIN_02              (0x10u)
#define pgaANTPlus_PGA_GAIN_04              (0x20u)
#define pgaANTPlus_PGA_GAIN_08              (0x30u)
#define pgaANTPlus_PGA_GAIN_16              (0x40u)
#define pgaANTPlus_PGA_GAIN_24              (0x50u)
#define pgaANTPlus_PGA_GAIN_25              (0x70u)
#define pgaANTPlus_PGA_GAIN_32              (0x52u)
#define pgaANTPlus_PGA_GAIN_48              (0x62u)
#define pgaANTPlus_PGA_GAIN_50              (0x72u)

#define pgaANTPlus_BST_CLK_EN               (0x08u)
#define pgaANTPlus_BST_CLK_INDEX_MASK       (0x07u)
#define pgaANTPlus_PM_ACT_CFG_MASK          (0x0Fu)

/* Constant for VDDA Threshold */
#define pgaANTPlus_CYDEV_VDDA_MV       (CYDEV_VDDA_MV)
#define pgaANTPlus_MINIMUM_VDDA_THRESHOLD_MV   (2700u)

/*******************************************************************************
* Following code are OBSOLETE and must not be used starting from PGA 2.0
*******************************************************************************/
#define pgaANTPlus_BST_REG            (pgaANTPlus_BSTCLK_REG)
#define pgaANTPlus_BST_PTR            (pgaANTPlus_BSTCLK_PTR)
#define pgaANTPlus_SC_REG_CLR         (0x00u)
#define pgaANTPlus_BST_REG_EN         (0x08u)


#endif /* CY_PGA_pgaANTPlus_H */


/* [] END OF FILE */
