/*******************************************************************************
* File Name: pgaPolarS.h  
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

#if !defined(CY_PGA_pgaPolarS_H) 
#define CY_PGA_pgaPolarS_H 

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
}   pgaPolarS_BACKUP_STRUCT;


/* variable describes init state of the component */
extern uint8 pgaPolarS_initVar;


/***************************************
*        Function Prototypes 
***************************************/

void pgaPolarS_Start(void)                 ; 
void pgaPolarS_Stop(void)                  ; 
void pgaPolarS_SetPower(uint8 power)       ;
void pgaPolarS_SetGain(uint8 gain)         ;
void pgaPolarS_Sleep(void)                 ; 
void pgaPolarS_Wakeup(void)                ;
void pgaPolarS_SaveConfig(void)            ; 
void pgaPolarS_RestoreConfig(void)         ;
void pgaPolarS_Init(void)                  ;
void pgaPolarS_Enable(void)                ;


/***************************************
*            API Constants
***************************************/

/* Power constants for SetPower function */
#define pgaPolarS_MINPOWER                 (0x00u)
#define pgaPolarS_LOWPOWER                 (0x01u)
#define pgaPolarS_MEDPOWER                 (0x02u)
#define pgaPolarS_HIGHPOWER                (0x03u)

/* Constants for SetGain function */
#define pgaPolarS_GAIN_01                  (0x00u)
#define pgaPolarS_GAIN_02                  (0x01u)
#define pgaPolarS_GAIN_04                  (0x02u)
#define pgaPolarS_GAIN_08                  (0x03u)
#define pgaPolarS_GAIN_16                  (0x04u)
#define pgaPolarS_GAIN_24                  (0x05u)
#define pgaPolarS_GAIN_32                  (0x06u)
#define pgaPolarS_GAIN_48                  (0x07u)
#define pgaPolarS_GAIN_50                  (0x08u)
#define pgaPolarS_GAIN_MAX                 (0x08u)


/***************************************
*       Initialization Values
***************************************/

#define pgaPolarS_DEFAULT_GAIN             (8u)
#define pgaPolarS_VREF_MODE                ((0u != 0x00u) ? (0x00u) : pgaPolarS_GNDVREF_E)
#define pgaPolarS_DEFAULT_POWER            (3u)


/***************************************
*              Registers
***************************************/

#define pgaPolarS_CR0_REG                  (* (reg8 *) pgaPolarS_SC__CR0 )
#define pgaPolarS_CR0_PTR                  (  (reg8 *) pgaPolarS_SC__CR0 )
#define pgaPolarS_CR1_REG                  (* (reg8 *) pgaPolarS_SC__CR1 )
#define pgaPolarS_CR1_PTR                  (  (reg8 *) pgaPolarS_SC__CR1 )
#define pgaPolarS_CR2_REG                  (* (reg8 *) pgaPolarS_SC__CR2 )
#define pgaPolarS_CR2_PTR                  (  (reg8 *) pgaPolarS_SC__CR2 )
  /* Power manager */
#define pgaPolarS_PM_ACT_CFG_REG           (* (reg8 *) pgaPolarS_SC__PM_ACT_CFG )
#define pgaPolarS_PM_ACT_CFG_PTR           (  (reg8 *) pgaPolarS_SC__PM_ACT_CFG )  
#define pgaPolarS_PM_STBY_CFG_REG          (* (reg8 *) pgaPolarS_SC__PM_STBY_CFG )
  /* Power manager */
#define pgaPolarS_PM_STBY_CFG_PTR          (  (reg8 *) pgaPolarS_SC__PM_STBY_CFG )  
#define pgaPolarS_BSTCLK_REG               (* (reg8 *) pgaPolarS_SC__BST )
#define pgaPolarS_BSTCLK_PTR               (  (reg8 *) pgaPolarS_SC__BST )
/* Pump clock selectin register */
#define pgaPolarS_PUMP_CR1_REG             (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)
#define pgaPolarS_PUMP_CR1_PTR             (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

/* Pump Register for SC block */
#define pgaPolarS_SC_MISC_REG              (* (reg8 *) CYDEV_ANAIF_RT_SC_MISC)
#define pgaPolarS_SC_MISC_PTR              (  (reg8 *) CYDEV_ANAIF_RT_SC_MISC)

/* PM_ACT_CFG (Active Power Mode CFG Register)mask */ 
#define pgaPolarS_ACT_PWR_EN               pgaPolarS_SC__PM_ACT_MSK 

/* PM_STBY_CFG (Alternate Active Power Mode CFG Register)mask */ 
#define pgaPolarS_STBY_PWR_EN              pgaPolarS_SC__PM_STBY_MSK 


/***************************************
*            Register Constants
***************************************/

/* SC_MISC constants */
#define pgaPolarS_PUMP_FORCE               (0x20u)
#define pgaPolarS_PUMP_AUTO                (0x10u)
#define pgaPolarS_DIFF_PGA_1_3             (0x02u)
#define pgaPolarS_DIFF_PGA_0_2             (0x01u)

/* ANIF.PUMP.CR1 Constants */
#define pgaPolarS_PUMP_CR1_SC_CLKSEL       (0x80u)

/* CR0 SC/CT Control Register 0 definitions */
#define pgaPolarS_MODE_PGA                 (0x0Cu)

/* CR1 SC/CT Control Register 1 definitions */

/* Bit Field  SC_COMP_ENUM */
#define pgaPolarS_COMP_MASK                (0x0Cu)
#define pgaPolarS_COMP_3P0PF               (0x00u)
#define pgaPolarS_COMP_3P6PF               (0x04u)
#define pgaPolarS_COMP_4P35PF              (0x08u)
#define pgaPolarS_COMP_5P1PF               (0x0Cu)

/* Bit Field  SC_DIV2_ENUM */
#define pgaPolarS_DIV2_MASK                (0x10u)
#define pgaPolarS_DIV2_DISABLE             (0x00u)
#define pgaPolarS_DIV2_ENABLE              (0x10u)

/* Bit Field  SC_DRIVE_ENUM */
#define pgaPolarS_DRIVE_MASK               (0x03u)
#define pgaPolarS_DRIVE_280UA              (0x00u)
#define pgaPolarS_DRIVE_420UA              (0x01u)
#define pgaPolarS_DRIVE_530UA              (0x02u)
#define pgaPolarS_DRIVE_650UA              (0x03u)

/* Bit Field  SC_PGA_MODE_ENUM */
#define pgaPolarS_PGA_MODE_MASK            (0x20u)
#define pgaPolarS_PGA_INV                  (0x00u)
#define pgaPolarS_PGA_NINV                 (0x20u)

/* CR2 SC/CT Control Register 2 definitions */

/* Bit Field  SC_BIAS_CONTROL_ENUM */
#define pgaPolarS_BIAS_MASK                (0x01u)
#define pgaPolarS_BIAS_NORMAL              (0x00u)
#define pgaPolarS_BIAS_LOW                 (0x01u)

/* Bit Field  SC_PGA_GNDVREF_ENUM  */
#define pgaPolarS_GNDVREF_MASK             (0x80u)
#define pgaPolarS_GNDVREF_DI               (0x00u)
#define pgaPolarS_GNDVREF_E                (0x80u)

/* Bit Field  SC_R20_40B_ENUM */
#define pgaPolarS_R20_40B_MASK             (0x02u)
#define pgaPolarS_R20_40B_40K              (0x00u)
#define pgaPolarS_R20_40B_20K              (0x02u)

/* Bit Field  SC_REDC_ENUM */
#define pgaPolarS_REDC_MASK                (0x0Cu)
#define pgaPolarS_REDC_00                  (0x00u)
#define pgaPolarS_REDC_01                  (0x04u)
#define pgaPolarS_REDC_10                  (0x08u)
#define pgaPolarS_REDC_11                  (0x0Cu)

/* Bit Field  SC_RVAL_ENUM */
#define pgaPolarS_RVAL_MASK                (0x70u)
#define pgaPolarS_RVAL_0K                  (0x00u)
#define pgaPolarS_RVAL_40K                 (0x10u)
#define pgaPolarS_RVAL_120K                (0x20u)
#define pgaPolarS_RVAL_280K                (0x30u)
#define pgaPolarS_RVAL_600K                (0x40u)
#define pgaPolarS_RVAL_460K                (0x60u)
#define pgaPolarS_RVAL_620K                (0x50u)
#define pgaPolarS_RVAL_470K                (0x60u)
#define pgaPolarS_RVAL_490K                (0x70u)

/* Bit Field  PGA_GAIN_ENUM */
#define pgaPolarS_PGA_GAIN_MASK            (0x72u)
#define pgaPolarS_PGA_GAIN_01              (0x00u)
#define pgaPolarS_PGA_GAIN_02              (0x10u)
#define pgaPolarS_PGA_GAIN_04              (0x20u)
#define pgaPolarS_PGA_GAIN_08              (0x30u)
#define pgaPolarS_PGA_GAIN_16              (0x40u)
#define pgaPolarS_PGA_GAIN_24              (0x50u)
#define pgaPolarS_PGA_GAIN_25              (0x70u)
#define pgaPolarS_PGA_GAIN_32              (0x52u)
#define pgaPolarS_PGA_GAIN_48              (0x62u)
#define pgaPolarS_PGA_GAIN_50              (0x72u)

#define pgaPolarS_BST_CLK_EN               (0x08u)
#define pgaPolarS_BST_CLK_INDEX_MASK       (0x07u)
#define pgaPolarS_PM_ACT_CFG_MASK          (0x0Fu)

/* Constant for VDDA Threshold */
#define pgaPolarS_CYDEV_VDDA_MV       (CYDEV_VDDA_MV)
#define pgaPolarS_MINIMUM_VDDA_THRESHOLD_MV   (2700u)

/*******************************************************************************
* Following code are OBSOLETE and must not be used starting from PGA 2.0
*******************************************************************************/
#define pgaPolarS_BST_REG            (pgaPolarS_BSTCLK_REG)
#define pgaPolarS_BST_PTR            (pgaPolarS_BSTCLK_PTR)
#define pgaPolarS_SC_REG_CLR         (0x00u)
#define pgaPolarS_BST_REG_EN         (0x08u)


#endif /* CY_PGA_pgaPolarS_H */


/* [] END OF FILE */
