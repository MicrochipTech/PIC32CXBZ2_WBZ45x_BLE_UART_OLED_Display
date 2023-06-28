/*******************************************************************************
* Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/


/*******************************************************************************
  Application BLE Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_ble.c

  Summary:
    This file contains the Application BLE implementation for this project.

  Description:
    This file contains the Application BLE implementation for this project.
 *******************************************************************************/


#include "app.h"
#include "osal/osal_freertos_extend.h"
#include "app_ble.h"
#include "app_ble_handler.h"


#include "app_trsps_handler.h"










// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

#define GAP_DEV_NAME_VALUE          "Microchip"

// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************
BLE_DD_Config_T         ddConfig;

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

void APP_BleStackCb(STACK_Event_T *p_stack)
{
    STACK_Event_T stackEvent;
    APP_Msg_T   appMsg;
    APP_Msg_T   *p_appMsg;

    memcpy((uint8_t *)&stackEvent, (uint8_t *)p_stack, sizeof(STACK_Event_T));
    stackEvent.p_event=OSAL_Malloc(p_stack->evtLen);
    if(stackEvent.p_event==NULL)
    {
        return;
    }
    memcpy(stackEvent.p_event, p_stack->p_event, p_stack->evtLen);
    stackEvent.p_event=stackEvent.p_event;

    if (p_stack->groupId==STACK_GRP_GATT)
    {
        GATT_Event_T *p_evtGatt = (GATT_Event_T *)stackEvent.p_event;

        if (p_evtGatt->eventId == GATTS_EVT_CLIENT_CCCDLIST_CHANGE)
        {
            uint8_t *p_payload;

            p_payload = (uint8_t *)OSAL_Malloc((p_evtGatt->eventField.onClientCccdListChange.numOfCccd*4));
            if (p_payload != NULL)
            {
                memcpy(p_payload, (uint8_t *)p_evtGatt->eventField.onClientCccdListChange.p_cccdList, (p_evtGatt->eventField.onClientCccdListChange.numOfCccd*4));
                p_evtGatt->eventField.onClientCccdListChange.p_cccdList = (GATTS_CccdList_T *)p_payload;
            }
        }
    }

    appMsg.msgId=APP_MSG_BLE_STACK_EVT;

    ((STACK_Event_T *)appMsg.msgData)->groupId=p_stack->groupId;
    ((STACK_Event_T *)appMsg.msgData)->evtLen=p_stack->evtLen;
    ((STACK_Event_T *)appMsg.msgData)->p_event=stackEvent.p_event;

    p_appMsg = &appMsg;
    OSAL_QUEUE_Send(&appData.appQueue, p_appMsg, 0);
}

void APP_BleStackEvtHandler(STACK_Event_T *p_stackEvt)
{
    switch(p_stackEvt->groupId)
    {
        case STACK_GRP_BLE_GAP:
        {
            APP_BleGapEvtHandler((BLE_GAP_Event_T *)p_stackEvt->p_event);
        }
        break;
        
        case STACK_GRP_BLE_L2CAP:
        {
            APP_BleL2capEvtHandler((BLE_L2CAP_Event_T *)p_stackEvt->p_event);
         }
        break;
        case STACK_GRP_BLE_SMP:
        {
            APP_BleSmpEvtHandler((BLE_SMP_Event_T *)p_stackEvt->p_event);
         }
        break;

        case STACK_GRP_GATT:
        {
            APP_GattEvtHandler((GATT_Event_T *)p_stackEvt->p_event);
        }
        break;
        
        default:
        break;

    }

    //Direct event to BLE middleware
    BLE_DM_BleEventHandler(p_stackEvt);

    BLE_DD_BleEventHandler(&ddConfig, p_stackEvt);

    //Direct event to BLE profiles
    /* Transparent Profile */
    BLE_TRSPS_BleEventHandler(p_stackEvt);

    









    OSAL_Free(p_stackEvt->p_event);
}


void APP_BleStackLogHandler(BT_SYS_LogEvent_T *p_logEvt)
{
}

void APP_DdEvtHandler(BLE_DD_Event_T *p_event)
{





}



void APP_BleConfigBasic()
{
    int8_t                          connTxPower;
    int8_t                          advTxPower;
    BLE_GAP_AdvParams_T             advParam;
	uint8_t advData[]={0x02, 0x01, 0x04, 0x05, 0x16, 0xDA, 0xFE, 0xFF, 0x01};
    BLE_GAP_AdvDataParams_T         appAdvData;
    uint8_t scanRspData[]={0x0F, 0x09, 0x57, 0x42, 0x5A, 0x34, 0x35, 0x31, 0x5F, 0x44, 0x49, 0x53, 0x50, 0x4C, 0x41, 0x59};
    BLE_GAP_AdvDataParams_T         appScanRspData;

    // Configure advertising parameters
    BLE_GAP_SetAdvTxPowerLevel(9,&advTxPower);      /* Advertising TX Power */
    
    BLE_GAP_Addr_T devAddr;
    devAddr.addrType = BLE_GAP_ADDR_TYPE_PUBLIC;
    devAddr.addr[0] = 0x51;
    devAddr.addr[1] = 0x04;
    devAddr.addr[2] = 0x78;
    devAddr.addr[3] = 0xA6;
    devAddr.addr[4] = 0xB7;
    devAddr.addr[5] = 0xC8;

   // Configure device address
    BLE_GAP_SetDeviceAddr(&devAddr);
    
    
    memset(&advParam, 0, sizeof(BLE_GAP_AdvParams_T));
    advParam.intervalMin = 1600;     /* Advertising Interval Min */
    advParam.intervalMax = 1600;     /* Advertising Interval Max */
    advParam.type = BLE_GAP_ADV_TYPE_ADV_IND;        /* Advertising Type */
    advParam.advChannelMap = BLE_GAP_ADV_CHANNEL_ALL;        /* Advertising Channel Map */
    advParam.filterPolicy = BLE_GAP_ADV_FILTER_DEFAULT;     /* Advertising Filter Policy */
    BLE_GAP_SetAdvParams(&advParam);
    
    // Configure advertising data
    appAdvData.advLen=sizeof(advData);
    memcpy(appAdvData.advData, advData, appAdvData.advLen);     /* Advertising Data */
    BLE_GAP_SetAdvData(&appAdvData);

    //Configure advertising scan response data
    appScanRspData.advLen=sizeof(scanRspData);
    memcpy(appScanRspData.advData, scanRspData, appScanRspData.advLen);     /* Scan Response Data */
    BLE_GAP_SetScanRspData(&appScanRspData);

    BLE_GAP_SetConnTxPowerLevel(15, &connTxPower);      /* Connection TX Power */
}
void APP_BleConfigAdvance()
{
    uint8_t devName[]={GAP_DEV_NAME_VALUE};

    BLE_SMP_Config_T                smpParam;

   
    BLE_DM_Config_T                 dmConfig;
    BLE_GAP_ServiceOption_T         gapServiceOptions;
    

    // Configure Device Name
    BLE_GAP_SetDeviceName(sizeof(devName), devName);    /* Device Name */

    
    // GAP Service option
    gapServiceOptions.charDeviceName.enableWriteProperty = false;             /* Enable Device Name Write Property */
    gapServiceOptions.charAppearance.appearance = 0x0;                          /* Appearance */
    gapServiceOptions.charPeriPreferConnParam.enable = false;                    /* Enable Peripheral Preffered Connection Parameters */
    
    BLE_GAP_ConfigureBuildInService(&gapServiceOptions);
    
    


    // Configure SMP parameters
    memset(&smpParam, 0, sizeof(BLE_SMP_Config_T));
    smpParam.ioCapability = BLE_SMP_IO_NOINPUTNOOUTPUT;                  /* IO Capability */
    smpParam.authReqFlag |= BLE_SMP_OPTION_BONDING;             /* Authentication Setting: Bonding */
    smpParam.authReqFlag |= BLE_SMP_OPTION_SECURE_CONNECTION;   /* Authentication Setting: Secure Connections */
    BLE_SMP_Config(&smpParam);

    // Configure BLE_DM middleware parameters
    dmConfig.secAutoAccept = true;                          /* Auto Accept Security Request */
    dmConfig.connConfig.autoReplyUpdateRequest = true;      /* Auto Accept Connection Parameter Update Request */
    dmConfig.connConfig.minAcceptConnInterval = 6;    /* Minimum Connection Interval */
    dmConfig.connConfig.maxAcceptConnInterval = 3200;    /* Maximum Connection Interval */
    dmConfig.connConfig.minAcceptPeripheralLatency = 0;    /* Minimum Connection Latency */
    dmConfig.connConfig.maxAcceptPeripheralLatency = 499;    /* Maximum Connection Latency */
    BLE_DM_Config(&dmConfig);


    // Configure BLE_DD middleware parameters
    ddConfig.waitForSecurity = false;
    ddConfig.initDiscInCentral = true;
    ddConfig.initDiscInPeripheral = false;
}

void APP_BleStackInitBasic()
{
    BLE_GAP_Init();

    BLE_GAP_AdvInit();  /* Advertising */

    BLE_GAP_ConnPeripheralInit();   /* Peripheral */
}

void APP_BleStackInitAdvance()
{
    uint16_t gattsInitParam=GATTS_CONFIG_NONE;
    
    uint16_t gattcInitParam=GATTC_CONFIG_NONE;

    STACK_EventRegister(APP_BleStackCb);
    


    

    BLE_L2CAP_Init();
    
    GATTS_Init(gattsInitParam);
    
    GATTC_Init(gattcInitParam);     /* Enable Client Role */

    BLE_SMP_Init();
    

    //Initialize BLE middleware
    BLE_DM_Init();
    BLE_DM_EventRegister(APP_DmEvtHandler);

    BLE_DD_Init();
    BLE_DD_EventRegister(APP_DdEvtHandler);
    


    //Initialize BLE services

    //Initialize BLE profiles
    /* Transparent Profile */
    BLE_TRSPS_Init();                                   /* Enable Server Role */
    BLE_TRSPS_EventRegister(APP_TrspsEvtHandler);   /* Enable Server Role */











    APP_BleConfigAdvance();
}

void APP_BleStackInit()
{
    APP_BleStackInitBasic();
    APP_BleConfigBasic();
    APP_BleStackInitAdvance();
}