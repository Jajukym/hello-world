/*******************************************************************************
* File Name: LCD_Char.h
* Version 1.0
*
* Description:
*  This header file contains registers and constants associated with the
*  Character LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CHARLCD_LCD_Char_H)
#define CY_CHARLCD_LCD_Char_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define LCD_Char_CONVERSION_ROUTINES     (1u)
#define LCD_Char_CUSTOM_CHAR_SET         (0u)

/* Custom character set types */
#define LCD_Char_NONE                     (0u)    /* No Custom Fonts      */
#define LCD_Char_HORIZONTAL_BG            (1u)    /* Horizontal Bar Graph */
#define LCD_Char_VERTICAL_BG              (2u)    /* Vertical Bar Graph   */
#define LCD_Char_USER_DEFINED             (3u)    /* User Defined Fonts   */


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} LCD_Char_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void LCD_Char_Init(void) ;
void LCD_Char_Enable(void) ;
void LCD_Char_Start(void) ;
void LCD_Char_Stop(void) ;
void LCD_Char_WriteControl(uint8 cByte) ;
void LCD_Char_WriteData(uint8 dByte) ;
void LCD_Char_PrintString(char8 const string[]) ;
void LCD_Char_Position(uint8 row, uint8 column) ;
void LCD_Char_PutChar(char8 character) ;
void LCD_Char_IsReady(void) ;
void LCD_Char_SaveConfig(void) ;
void LCD_Char_RestoreConfig(void) ;
void LCD_Char_Sleep(void) ;
void LCD_Char_Wakeup(void) ;

#if((LCD_Char_CUSTOM_CHAR_SET == LCD_Char_VERTICAL_BG) || \
                (LCD_Char_CUSTOM_CHAR_SET == LCD_Char_HORIZONTAL_BG))

    void  LCD_Char_LoadCustomFonts(uint8 const customData[])
                        ;

    void  LCD_Char_DrawHorizontalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                         ;

    void LCD_Char_DrawVerticalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                        ;

#endif /* ((LCD_Char_CUSTOM_CHAR_SET == LCD_Char_VERTICAL_BG) */

#if(LCD_Char_CUSTOM_CHAR_SET == LCD_Char_USER_DEFINED)

    void LCD_Char_LoadCustomFonts(uint8 const customData[])
                            ;

#endif /* ((LCD_Char_CUSTOM_CHAR_SET == LCD_Char_USER_DEFINED) */

#if(LCD_Char_CONVERSION_ROUTINES == 1u)

    /* ASCII Conversion Routines */
    void LCD_Char_PrintInt8(uint8 value) ;
    void LCD_Char_PrintInt16(uint16 value) ;
    void LCD_Char_PrintNumber(uint16 value) ; 

#endif /* LCD_Char_CONVERSION_ROUTINES == 1u */

/* Clear Macro */
#define LCD_Char_ClearDisplay() LCD_Char_WriteControl(LCD_Char_CLEAR_DISPLAY)

/* Off Macro */
#define LCD_Char_DisplayOff() LCD_Char_WriteControl(LCD_Char_DISPLAY_CURSOR_OFF)

/* On Macro */
#define LCD_Char_DisplayOn() LCD_Char_WriteControl(LCD_Char_DISPLAY_ON_CURSOR_OFF)


/***************************************
*           Global Variables
***************************************/

extern uint8 LCD_Char_initVar;
extern uint8 LCD_Char_enableState;
extern uint8 const CYCODE LCD_Char_customFonts[64u];


/***************************************
*           API Constants
***************************************/

/* Full Byte Commands Sent as Two Nibbles */
#define LCD_Char_DISPLAY_8_BIT_INIT       (0x03u)
#define LCD_Char_DISPLAY_4_BIT_INIT       (0x02u)
#define LCD_Char_DISPLAY_CURSOR_OFF       (0x08u)
#define LCD_Char_CLEAR_DISPLAY            (0x01u)
#define LCD_Char_CURSOR_AUTO_INCR_ON      (0x06u)
#define LCD_Char_DISPLAY_CURSOR_ON        (0x0Eu)
#define LCD_Char_DISPLAY_2_LINES_5x10     (0x2Cu)
#define LCD_Char_DISPLAY_ON_CURSOR_OFF    (0x0Cu)

#define LCD_Char_RESET_CURSOR_POSITION    (0x03u)
#define LCD_Char_CURSOR_WINK              (0x0Du)
#define LCD_Char_CURSOR_BLINK             (0x0Fu)
#define LCD_Char_CURSOR_SH_LEFT           (0x10u)
#define LCD_Char_CURSOR_SH_RIGHT          (0x14u)
#define LCD_Char_CURSOR_HOME              (0x02u)
#define LCD_Char_CURSOR_LEFT              (0x04u)
#define LCD_Char_CURSOR_RIGHT             (0x06u)

/* Point to Character Generator Ram 0 */
#define LCD_Char_CGRAM_0                  (0x40u)

/* Point to Display Data Ram 0 */
#define LCD_Char_DDRAM_0                  (0x80u)

/* LCD Characteristics */
#define LCD_Char_CHARACTER_WIDTH          (0x05u)
#define LCD_Char_CHARACTER_HEIGHT         (0x08u)

#if(LCD_Char_CONVERSION_ROUTINES == 1u)
    #define LCD_Char_NUMBER_OF_REMAINDERS (0x05u)
    #define LCD_Char_TEN                  (0x0Au)
#endif /* LCD_Char_CONVERSION_ROUTINES == 1u */

/* Nibble Offset and Mask */
#define LCD_Char_NIBBLE_SHIFT             (0x04u)
#define LCD_Char_NIBBLE_MASK              (0x0Fu)

/* LCD Module Address Constants */
#define LCD_Char_ROW_0_START              (0x80u)
#define LCD_Char_ROW_1_START              (0xC0u)
#define LCD_Char_ROW_2_START              (0x94u)
#define LCD_Char_ROW_3_START              (0xD4u)

/* Custom Character References */
#define LCD_Char_CUSTOM_0                 (0x00u)
#define LCD_Char_CUSTOM_1                 (0x01u)
#define LCD_Char_CUSTOM_2                 (0x02u)
#define LCD_Char_CUSTOM_3                 (0x03u)
#define LCD_Char_CUSTOM_4                 (0x04u)
#define LCD_Char_CUSTOM_5                 (0x05u)
#define LCD_Char_CUSTOM_6                 (0x06u)
#define LCD_Char_CUSTOM_7                 (0x07u)

/* Other constants */
#define LCD_Char_BYTE_UPPER_NIBBLE_SHIFT   (0x04u)
#define LCD_Char_BYTE_LOWER_NIBBLE_MASK    (0x0Fu)
#define LCD_Char_U16_UPPER_BYTE_SHIFT      (0x08u)
#define LCD_Char_U16_LOWER_BYTE_MASK       (0xFFu)
#define LCD_Char_CUSTOM_CHAR_SET_LEN       (0x40u)

#define LCD_Char_CMD_DELAY_US              (1500u)
#define LCD_Char_DATA_DELAY_US              (150u)
#define LCD_Char_NIB_DELAY_US               (100u)


/***************************************
*             Registers
***************************************/

/* Control Register */
#define LCD_Char_CNTL_REG        (* (reg8 *) LCD_Char_Cntl_Port_Sync_ctrl_reg__CONTROL_REG )
#define LCD_Char_CNTL_PTR        (  (reg8 *) LCD_Char_Cntl_Port_Sync_ctrl_reg__CONTROL_REG )

/***************************************
 *       Register Constants
 ***************************************/
                                                  
/* Pin Masks */
#define LCD_Char_E                        ((uint8) 0x10u)
#define LCD_Char_RS                       ((uint8) 0x20u)
#define LCD_Char_RW                       ((uint8) 0x40u)
#define LCD_Char_READY_BIT                ((uint8) 0x08u)
#define LCD_Char_DATA_MASK                ((uint8) 0x0Fu)


/***************************************
*       Obsolete function names
***************************************/
#if(LCD_Char_CONVERSION_ROUTINES == 1u)
    /* This function names are obsolete an they will be removed in future 
    * revisions of component.
    */
    #define LCD_Char_PrintDecUint16(x)   LCD_Char_PrintNumber(x)  
    #define LCD_Char_PrintHexUint8(x)    LCD_Char_PrintInt8(x)
    #define LCD_Char_PrintHexUint16(x)   LCD_Char_PrintInt16(x)        

#endif /* LCD_Char_CONVERSION_ROUTINES == 1u */

#endif /* CY_CHARLCD_LCD_Char_H */


/* [] END OF FILE */
