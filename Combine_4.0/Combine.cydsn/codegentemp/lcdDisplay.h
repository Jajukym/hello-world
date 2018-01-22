/*******************************************************************************
* File Name: lcdDisplay.h
* Version 2.20
*
* Description:
*  This header file contains registers and constants associated with the
*  Character LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CHARLCD_lcdDisplay_H)
#define CY_CHARLCD_lcdDisplay_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define lcdDisplay_CONVERSION_ROUTINES     (1u)
#define lcdDisplay_CUSTOM_CHAR_SET         (0u)

/* Custom character set types */
#define lcdDisplay_NONE                     (0u)    /* No Custom Fonts      */
#define lcdDisplay_HORIZONTAL_BG            (1u)    /* Horizontal Bar Graph */
#define lcdDisplay_VERTICAL_BG              (2u)    /* Vertical Bar Graph   */
#define lcdDisplay_USER_DEFINED             (3u)    /* User Defined Fonts   */


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} lcdDisplay_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void lcdDisplay_Init(void) ;
void lcdDisplay_Enable(void) ;
void lcdDisplay_Start(void) ;
void lcdDisplay_Stop(void) ;
void lcdDisplay_WriteControl(uint8 cByte) ;
void lcdDisplay_WriteData(uint8 dByte) ;
void lcdDisplay_PrintString(char8 const string[]) ;
void lcdDisplay_Position(uint8 row, uint8 column) ;
void lcdDisplay_PutChar(char8 character) ;
void lcdDisplay_IsReady(void) ;
void lcdDisplay_SaveConfig(void) ;
void lcdDisplay_RestoreConfig(void) ;
void lcdDisplay_Sleep(void) ;
void lcdDisplay_Wakeup(void) ;

#if((lcdDisplay_CUSTOM_CHAR_SET == lcdDisplay_VERTICAL_BG) || \
                (lcdDisplay_CUSTOM_CHAR_SET == lcdDisplay_HORIZONTAL_BG))

    void  lcdDisplay_LoadCustomFonts(uint8 const customData[])
                        ;

    void  lcdDisplay_DrawHorizontalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                         ;

    void lcdDisplay_DrawVerticalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                        ;

#endif /* ((lcdDisplay_CUSTOM_CHAR_SET == lcdDisplay_VERTICAL_BG) */

#if(lcdDisplay_CUSTOM_CHAR_SET == lcdDisplay_USER_DEFINED)

    void lcdDisplay_LoadCustomFonts(uint8 const customData[])
                            ;

#endif /* ((lcdDisplay_CUSTOM_CHAR_SET == lcdDisplay_USER_DEFINED) */

#if(lcdDisplay_CONVERSION_ROUTINES == 1u)

    /* ASCII Conversion Routines */
    void lcdDisplay_PrintInt8(uint8 value) ;
    void lcdDisplay_PrintInt16(uint16 value) ;
    void lcdDisplay_PrintInt32(uint32 value) ;
    void lcdDisplay_PrintNumber(uint16 value) ; 
    void lcdDisplay_PrintU32Number(uint32 value) ;
    
#endif /* lcdDisplay_CONVERSION_ROUTINES == 1u */

/* Clear Macro */
#define lcdDisplay_ClearDisplay() lcdDisplay_WriteControl(lcdDisplay_CLEAR_DISPLAY)

/* Off Macro */
#define lcdDisplay_DisplayOff() lcdDisplay_WriteControl(lcdDisplay_DISPLAY_CURSOR_OFF)

/* On Macro */
#define lcdDisplay_DisplayOn() lcdDisplay_WriteControl(lcdDisplay_DISPLAY_ON_CURSOR_OFF)

#define lcdDisplay_PrintNumber(value) lcdDisplay_PrintU32Number((uint16) (value))


/***************************************
*           Global Variables
***************************************/

extern uint8 lcdDisplay_initVar;
extern uint8 lcdDisplay_enableState;
extern uint8 const CYCODE lcdDisplay_customFonts[64u];


/***************************************
*           API Constants
***************************************/

/* Full Byte Commands Sent as Two Nibbles */
#define lcdDisplay_DISPLAY_8_BIT_INIT       (0x03u)
#define lcdDisplay_DISPLAY_4_BIT_INIT       (0x02u)
#define lcdDisplay_DISPLAY_CURSOR_OFF       (0x08u)
#define lcdDisplay_CLEAR_DISPLAY            (0x01u)
#define lcdDisplay_CURSOR_AUTO_INCR_ON      (0x06u)
#define lcdDisplay_DISPLAY_CURSOR_ON        (0x0Eu)
#define lcdDisplay_DISPLAY_2_LINES_5x10     (0x2Cu)
#define lcdDisplay_DISPLAY_ON_CURSOR_OFF    (0x0Cu)

#define lcdDisplay_RESET_CURSOR_POSITION    (0x03u)
#define lcdDisplay_CURSOR_WINK              (0x0Du)
#define lcdDisplay_CURSOR_BLINK             (0x0Fu)
#define lcdDisplay_CURSOR_SH_LEFT           (0x10u)
#define lcdDisplay_CURSOR_SH_RIGHT          (0x14u)
#define lcdDisplay_DISPLAY_SCRL_LEFT        (0x18u)
#define lcdDisplay_DISPLAY_SCRL_RIGHT       (0x1Eu)
#define lcdDisplay_CURSOR_HOME              (0x02u)
#define lcdDisplay_CURSOR_LEFT              (0x04u)
#define lcdDisplay_CURSOR_RIGHT             (0x06u)

/* Point to Character Generator Ram 0 */
#define lcdDisplay_CGRAM_0                  (0x40u)

/* Point to Display Data Ram 0 */
#define lcdDisplay_DDRAM_0                  (0x80u)

/* LCD Characteristics */
#define lcdDisplay_CHARACTER_WIDTH          (0x05u)
#define lcdDisplay_CHARACTER_HEIGHT         (0x08u)

#if(lcdDisplay_CONVERSION_ROUTINES == 1u)
    #define lcdDisplay_NUMBER_OF_REMAINDERS_U32 (0x0Au)
    #define lcdDisplay_TEN                      (0x0Au)
    #define lcdDisplay_8_BIT_SHIFT              (8u)
    #define lcdDisplay_32_BIT_SHIFT             (32u)
    #define lcdDisplay_ZERO_CHAR_ASCII          (48u)
#endif /* lcdDisplay_CONVERSION_ROUTINES == 1u */

/* Nibble Offset and Mask */
#define lcdDisplay_NIBBLE_SHIFT             (0x04u)
#define lcdDisplay_NIBBLE_MASK              (0x0Fu)

/* LCD Module Address Constants */
#define lcdDisplay_ROW_0_START              (0x80u)
#define lcdDisplay_ROW_1_START              (0xC0u)
#define lcdDisplay_ROW_2_START              (0x94u)
#define lcdDisplay_ROW_3_START              (0xD4u)

/* Custom Character References */
#define lcdDisplay_CUSTOM_0                 (0x00u)
#define lcdDisplay_CUSTOM_1                 (0x01u)
#define lcdDisplay_CUSTOM_2                 (0x02u)
#define lcdDisplay_CUSTOM_3                 (0x03u)
#define lcdDisplay_CUSTOM_4                 (0x04u)
#define lcdDisplay_CUSTOM_5                 (0x05u)
#define lcdDisplay_CUSTOM_6                 (0x06u)
#define lcdDisplay_CUSTOM_7                 (0x07u)

/* Other constants */
#define lcdDisplay_BYTE_UPPER_NIBBLE_SHIFT  (0x04u)
#define lcdDisplay_BYTE_LOWER_NIBBLE_MASK   (0x0Fu)
#define lcdDisplay_U16_UPPER_BYTE_SHIFT     (0x08u)
#define lcdDisplay_U16_LOWER_BYTE_MASK      (0xFFu)
#define lcdDisplay_CUSTOM_CHAR_SET_LEN      (0x40u)

#define lcdDisplay_LONGEST_CMD_US           (0x651u)
#define lcdDisplay_WAIT_CYCLE               (0x10u)
#define lcdDisplay_READY_DELAY              ((lcdDisplay_LONGEST_CMD_US * 4u)/(lcdDisplay_WAIT_CYCLE))


/***************************************
*             Registers
***************************************/

/* Device specific registers */
#if (CY_PSOC4)

    #define lcdDisplay_PORT_DR_REG           (*(reg32 *) lcdDisplay_LCDPort__DR)  /* Data Output Register */
    #define lcdDisplay_PORT_DR_PTR           ( (reg32 *) lcdDisplay_LCDPort__DR)
    #define lcdDisplay_PORT_PS_REG           (*(reg32 *) lcdDisplay_LCDPort__PS)  /* Pin State Register */
    #define lcdDisplay_PORT_PS_PTR           ( (reg32 *) lcdDisplay_LCDPort__PS)
    
    #define lcdDisplay_PORT_PC_REG           (*(reg32 *) lcdDisplay_LCDPort__PC)
    #define lcdDisplay_PORT_PC_PTR           (*(reg32 *) lcdDisplay_LCDPort__PC)
    
#else

    #define lcdDisplay_PORT_DR_REG           (*(reg8 *) lcdDisplay_LCDPort__DR)  /* Data Output Register */
    #define lcdDisplay_PORT_DR_PTR           ( (reg8 *) lcdDisplay_LCDPort__DR)
    #define lcdDisplay_PORT_PS_REG           (*(reg8 *) lcdDisplay_LCDPort__PS)  /* Pin State Register */
    #define lcdDisplay_PORT_PS_PTR           ( (reg8 *) lcdDisplay_LCDPort__PS)

    #define lcdDisplay_PORT_DM0_REG          (*(reg8 *) lcdDisplay_LCDPort__DM0) /* Port Drive Mode 0 */
    #define lcdDisplay_PORT_DM0_PTR          ( (reg8 *) lcdDisplay_LCDPort__DM0)
    #define lcdDisplay_PORT_DM1_REG          (*(reg8 *) lcdDisplay_LCDPort__DM1) /* Port Drive Mode 1 */
    #define lcdDisplay_PORT_DM1_PTR          ( (reg8 *) lcdDisplay_LCDPort__DM1)
    #define lcdDisplay_PORT_DM2_REG          (*(reg8 *) lcdDisplay_LCDPort__DM2) /* Port Drive Mode 2 */
    #define lcdDisplay_PORT_DM2_PTR          ( (reg8 *) lcdDisplay_LCDPort__DM2)

#endif /* CY_PSOC4 */


/***************************************
*       Register Constants
***************************************/

/* SHIFT must be 1 or 0 */
#if (0 == lcdDisplay_LCDPort__SHIFT)
    #define lcdDisplay_PORT_SHIFT               (0x00u)
#else
    #define lcdDisplay_PORT_SHIFT               (0x01u)
#endif /* (0 == lcdDisplay_LCDPort__SHIFT) */

#define lcdDisplay_PORT_MASK                ((uint8) (lcdDisplay_LCDPort__MASK))

#if (CY_PSOC4)

    #define lcdDisplay_DM_PIN_STEP              (3u)
    /* Hi-Z Digital is defined by the value of "001b" and this should be set for
    * four data pins, in this way we get - 0x00000249. A similar Strong drive
    * is defined with "110b" so we get 0x00000DB6.
    */
    #define lcdDisplay_HIGH_Z_DATA_DM           ((0x00000249ul) << (lcdDisplay_PORT_SHIFT *\
                                                                          lcdDisplay_DM_PIN_STEP))
    #define lcdDisplay_STRONG_DATA_DM           ((0x00000DB6ul) << (lcdDisplay_PORT_SHIFT *\
                                                                          lcdDisplay_DM_PIN_STEP))
    #define lcdDisplay_DATA_PINS_MASK           (0x00000FFFul)
    #define lcdDisplay_DM_DATA_MASK             ((uint32) (lcdDisplay_DATA_PINS_MASK << \
                                                      (lcdDisplay_PORT_SHIFT * lcdDisplay_DM_PIN_STEP)))

#else

    /* Drive Mode register values for High Z */
    #define lcdDisplay_HIGH_Z_DM0               (0xFFu)
    #define lcdDisplay_HIGH_Z_DM1               (0x00u)
    #define lcdDisplay_HIGH_Z_DM2               (0x00u)

    /* Drive Mode register values for High Z Analog */
    #define lcdDisplay_HIGH_Z_A_DM0             (0x00u)
    #define lcdDisplay_HIGH_Z_A_DM1             (0x00u)
    #define lcdDisplay_HIGH_Z_A_DM2             (0x00u)

    /* Drive Mode register values for Strong */
    #define lcdDisplay_STRONG_DM0               (0x00u)
    #define lcdDisplay_STRONG_DM1               (0xFFu)
    #define lcdDisplay_STRONG_DM2               (0xFFu)

#endif /* CY_PSOC4 */

/* Pin Masks */
#define lcdDisplay_RS                     ((uint8) \
                                                (((uint8) 0x20u) << lcdDisplay_LCDPort__SHIFT))
#define lcdDisplay_RW                     ((uint8) \
                                                (((uint8) 0x40u) << lcdDisplay_LCDPort__SHIFT))
#define lcdDisplay_E                      ((uint8) \
                                                (((uint8) 0x10u) << lcdDisplay_LCDPort__SHIFT))
#define lcdDisplay_READY_BIT              ((uint8) \
                                                (((uint8) 0x08u) << lcdDisplay_LCDPort__SHIFT))
#define lcdDisplay_DATA_MASK              ((uint8) \
                                                (((uint8) 0x0Fu) << lcdDisplay_LCDPort__SHIFT))

/* These names are obsolete and will be removed in future revisions */
#define lcdDisplay_PORT_DR                  lcdDisplay_PORT_DR_REG
#define lcdDisplay_PORT_PS                  lcdDisplay_PORT_PS_REG
#define lcdDisplay_PORT_DM0                 lcdDisplay_PORT_DM0_REG
#define lcdDisplay_PORT_DM1                 lcdDisplay_PORT_DM1_REG
#define lcdDisplay_PORT_DM2                 lcdDisplay_PORT_DM2_REG


/***************************************
*       Obsolete function names
***************************************/
#if(lcdDisplay_CONVERSION_ROUTINES == 1u)
    /* This function names are obsolete and will be removed in future 
    * revisions of the component.
    */
    #define lcdDisplay_PrintDecUint16(x)   lcdDisplay_PrintNumber(x)  
    #define lcdDisplay_PrintHexUint8(x)    lcdDisplay_PrintInt8(x)
    #define lcdDisplay_PrintHexUint16(x)   lcdDisplay_PrintInt16(x)        

#endif /* lcdDisplay_CONVERSION_ROUTINES == 1u */

#endif /* CY_CHARLCD_lcdDisplay_H */


/* [] END OF FILE */
