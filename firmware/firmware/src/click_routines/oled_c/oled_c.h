 /*******************************************************************************
  oled c example Header file

  Company:
    Microchip Technology Inc.

  File Name:
  oled_c_example.h 

  Summary:

  Description:
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*
    (c) 2021 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/
// DOM-IGNORE-END
#ifndef OLED_C_H
#define	OLED_C_H

#include <stdio.h>
#include "definitions.h"

#define TXT_STR1_MAX_LEN     30u
#define TXT_STR2_MAX_LEN     30u
#define DISP_DATA_OFFSET     02u

#define BLE_DATA_LINE                     02u
#define BLE_DATA                          03u
#define BLE_TEXT_LINE1                    01u
#define BLE_TEXT_LINE2                    02u
#define BLE_TEXT_LINE_LENGTH_OFFSET       02u
#define BLE_TEXT_STATUS_SIZE                 13u

typedef enum APP_OLEDC_T
{
    APP_OLEDC_INIT,
    APP_OLEDC_PRINT,
    APP_OLEDC_STACK_END
} APP_OLEDC_T;

void oled_c_initialize(void);
void oled_c_Text_Field_textStr1(uint8_t *dText);
void oled_c_Text_Field_textStr2(uint8_t *dText);
void oled_c_Image_mchplogo_visible(void);
void oled_c_Image_mchplogo_invisible(void);
void oled_c_dispaly_referesh(void);
void APP_OLEDC_Handler(uint8_t *msgData);
void oled_c_print(uint8_t disp, uint8_t line, uint8_t *data);

#define LCD_INIT()          oled_c_initialize()
#define LCD_PRINT(...)      oled_c_print(__VA_ARGS__)

#endif