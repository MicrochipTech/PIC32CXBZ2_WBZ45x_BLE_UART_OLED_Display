 /*******************************************************************************
  oled c example source file

  Company:
    Microchip Technology Inc.

  File Name:
  oled_c_example.c

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

#include "oled_c.h"

leFixedString textStr1;
leFixedString textStr2;
static leChar textStrLine1[TXT_STR1_MAX_LEN];
static leChar textStrLine2[TXT_STR2_MAX_LEN];

void oled_c_initialize(void)
{
    APP_Msg_T   appMsg;
    appMsg.msgId=APP_MSG_OLEDC_EVT;
    appMsg.msgData[0] = APP_OLEDC_INIT;
    OSAL_QUEUE_Send(&appData.appQueue, &appMsg, 0);    
}


void oled_c_print(uint8_t display, uint8_t line, uint8_t *data)
{
    APP_Msg_T   appMsg;
    uint8_t dataLen, dataEndPos;

    if((line == 2) || (line == 1))
    {
        dataLen = strlen((char *)data);        
        
        if(dataLen > TXT_STR2_MAX_LEN)
        {
            dataLen = TXT_STR2_MAX_LEN;
            appMsg.msgData[TXT_STR2_MAX_LEN+DISP_DATA_OFFSET] = '\0';
        }
        
        dataEndPos = dataLen + DISP_DATA_OFFSET;
        appMsg.msgId=APP_MSG_OLEDC_EVT;
        appMsg.msgData[0] = APP_OLEDC_PRINT;
        appMsg.msgData[1] = display;
        appMsg.msgData[2] = line;
        strcpy((char *)&appMsg.msgData[DISP_DATA_OFFSET+1], (char *)data);
        
        if(line == 2)
        {
            SERCOM0_USART_Write((uint8_t *)"DATA RECEIVED: ",15);
            SERCOM0_USART_Write((uint8_t *)data, dataLen);
            SERCOM0_USART_Write((uint8_t *)"\r\n",2);    
        }
        
        if(dataLen > (TXT_STR2_MAX_LEN/2))
        {
            for(uint8_t i = dataEndPos; i>3; i--)
            {
                if(appMsg.msgData[i] == 32) //check for space character
                {
                    appMsg.msgData[i] = 10; //insert new line
                    break;
                }
            }   
        }
        OSAL_QUEUE_Send(&appData.appQueue, &appMsg, 0);
    }
}

void oled_c_Text_Field_textStr1(uint8_t *dText)
{
    char lcl_textStrLine[TXT_STR1_MAX_LEN];
    memset(lcl_textStrLine, 0,TXT_STR1_MAX_LEN);
    sprintf( (char*)lcl_textStrLine, "%s", dText);
    textStr1.fn->setFromCStr(&textStr1, (char*)lcl_textStrLine);
    Screen0_txtStr1->fn->setString(Screen0_txtStr1, (leString*)&textStr1);
}

void oled_c_Text_Field_textStr2(uint8_t *dText)
{
    char lcl_textStrLine[TXT_STR2_MAX_LEN];
    memset(lcl_textStrLine, 0,TXT_STR2_MAX_LEN);
    sprintf( (char*)lcl_textStrLine, "%s", dText);
    textStr2.fn->setFromCStr(&textStr2, (char*)lcl_textStrLine);
    Screen0_txtStr2->fn->setString(Screen0_txtStr2, (leString*)&textStr2);
}

void oled_c_Image_mchplogo_visible(void)
{
    Screen0_mchplogo->fn->setVisible(Screen0_mchplogo, LE_TRUE);
}

void oled_c_Image_mchplogo_invisible(void)
{
    Screen0_mchplogo->fn->setVisible(Screen0_mchplogo, LE_FALSE);
}

void oled_c_dispaly_referesh(void)
{
    GFX_DISP_INTF_PIN_EN_Clear();
    GFX_DISP_INTF_PIN_EN_Set();
}


void APP_OLEDC_Handler(uint8_t *msgData)
{
    APP_OLEDC_T oledc_event = msgData[0];
    
    switch ( oledc_event )
    {
        case APP_OLEDC_INIT:
        {
            leFixedString_Constructor(&textStr1, textStrLine1, sizeof(textStrLine1));
            textStr1.fn->setFont(&textStr1, 
                leStringTable_GetStringFont(leGetState()->stringTable,
                    string_txtString1.index, 0));
            
            
            leFixedString_Constructor(&textStr2, textStrLine2, sizeof(textStrLine2));
            textStr2.fn->setFont(&textStr2, 
                leStringTable_GetStringFont(leGetState()->stringTable,
                    string_txtString2.index, 0));

            oled_c_dispaly_referesh();
        }
        break;
        case APP_OLEDC_PRINT:
        {
            if( msgData[1] == 0)
            {
                if(msgData[2] == 1)
                {
                    oled_c_Text_Field_textStr1(&msgData[3]);
                }
                else if(msgData[2] == 2)
                {
                    oled_c_Text_Field_textStr2(&msgData[3]);                    
                }
            }
        }
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

