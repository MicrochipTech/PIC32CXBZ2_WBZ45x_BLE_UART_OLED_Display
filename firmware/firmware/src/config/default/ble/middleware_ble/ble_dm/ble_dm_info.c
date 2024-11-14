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
  Device Information Middleware Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_dm_info.c

  Summary:
    This file contains the Device Information functions for 
    BLE Device Manager module internal use.

  Description:
    This file contains the Device Information functions for 
    BLE Device Manager module internal use.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "osal/osal_freertos_extend.h"
#include "mba_error_defs.h"
#include "ble_gap.h"
#include "ble_dm_internal.h"
#include "ble_dm_info.h"
#include "ble_dm_dds.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
typedef struct BLE_DM_InfoCtrl_T
{
    BLE_DM_InfoConn_T *  conn[BLE_GAP_MAX_LINK_NBR];
    uint8_t              filterAcceptListCnt;
    uint8_t              filterAcceptList[BLE_DM_MAX_FILTER_ACCEPT_LIST_NUM];
} BLE_DM_InfoCtrl_T;


/**************************************************************************************************
  Variables
**************************************************************************************************/
static BLE_DM_InfoCtrl_T      *sp_dmInfoCtrl;


/**************************************************************************************************
  Function
**************************************************************************************************/

static BLE_DM_InfoConn_T *ble_dm_InfoGetFreeConn(void)
{
    uint8_t i;

    for (i = 0; i < BLE_GAP_MAX_LINK_NBR; i++)
    {
        if (sp_dmInfoCtrl->conn[i] == NULL)
        {
            sp_dmInfoCtrl->conn[i] = OSAL_Malloc(sizeof(BLE_DM_InfoConn_T));

            if (sp_dmInfoCtrl->conn[i] != NULL)
            {
                (void)memset((uint8_t *)sp_dmInfoCtrl->conn[i], 0, sizeof(BLE_DM_InfoConn_T));
            }
            return sp_dmInfoCtrl->conn[i];
        }
    }
    return NULL;
}

BLE_DM_InfoConn_T *BLE_DM_InfoGetConnByHandle(uint16_t connHandle)
{
    uint8_t i;

    for (i = 0; i < BLE_GAP_MAX_LINK_NBR; i++)
    {
        if ((sp_dmInfoCtrl->conn[i] != NULL) 
            && (sp_dmInfoCtrl->conn[i]->state == BLE_DM_INFO_STATE_CONNECTED) && (sp_dmInfoCtrl->conn[i]->connHandle == connHandle))
        {
            return sp_dmInfoCtrl->conn[i];
        }
    }
    return NULL;
}


static void ble_dm_FreeConn(BLE_DM_InfoConn_T * p_conn)
{
    uint8_t i;

    if (p_conn == NULL)
    {
        return;
    }
    
    for (i = 0U; i < BLE_GAP_MAX_LINK_NBR; i++)
    {
        if (sp_dmInfoCtrl->conn[i] == p_conn)
        {
            OSAL_Free(p_conn);
            sp_dmInfoCtrl->conn[i] = NULL;
        
            return;
        }
    }
}


bool BLE_DM_InfoInit(void)
{
    uint8_t i;

    if (sp_dmInfoCtrl == NULL)
    {
        sp_dmInfoCtrl = OSAL_Malloc(sizeof(BLE_DM_InfoCtrl_T));

        if (sp_dmInfoCtrl == NULL)
        {
            return false;
        }
    }
    else
    {
        for (i = 0U; i < BLE_GAP_MAX_LINK_NBR; i++)
        {
            ble_dm_FreeConn(sp_dmInfoCtrl->conn[i]);
        }
    }

    (void)memset(sp_dmInfoCtrl, 0x00, sizeof(BLE_DM_InfoCtrl_T));

    return true;
}

void BLE_DM_Info(STACK_Event_T *p_stackEvent)
{
    switch (p_stackEvent->groupId)
    {
        case STACK_GRP_BLE_GAP:
        {
            BLE_GAP_Event_T     *p_gapEvt = (BLE_GAP_Event_T *)p_stackEvent->p_event;
            BLE_DM_InfoConn_T   *p_conn;

            if (p_gapEvt->eventId == BLE_GAP_EVT_CONNECTED)
            {
                if ((p_gapEvt->eventField.evtConnect.status == GAP_STATUS_SUCCESS))
                {
                    BLE_DM_Event_T          dmEvt;

                    p_conn = ble_dm_InfoGetFreeConn();
                    if (p_conn!= NULL)
                    {
                        p_conn->connHandle = p_gapEvt->eventField.evtConnect.connHandle;
                        p_conn->role = p_gapEvt->eventField.evtConnect.role;
                        p_conn->remoteAddr = p_gapEvt->eventField.evtConnect.remoteAddr;
                        p_conn->state = BLE_DM_INFO_STATE_CONNECTED;
                        p_conn->devId = BLE_DM_DdsGetDeviceId(&p_conn->remoteAddr);

                        if (p_conn->devId != BLE_DM_PEER_DEV_ID_INVALID)
                        {
                            BLE_DM_PairedDevInfo_T  devInfo;

                            (void)memset(&devInfo, 0, sizeof(BLE_DM_PairedDevInfo_T));
                            if(BLE_DM_DdsGetPairedDevice(p_conn->devId, &devInfo)==MBA_RES_SUCCESS)
                            {
                                BLE_SMP_PairInfo_T      pairInfo;

                                pairInfo.lesc=devInfo.lesc;
                                pairInfo.auth=devInfo.auth;
                                (void)BLE_SMP_UpdateBondingInfo(p_conn->connHandle, devInfo.encryptKeySize, &pairInfo);
                            }
                        }

                        dmEvt.connHandle=p_gapEvt->eventField.evtConnect.connHandle;
                        dmEvt.eventId=BLE_DM_EVT_CONNECTED;                    
                        BLE_DM_ConveyEvent(&dmEvt);
                   }
                }
            }
            else if (p_gapEvt->eventId == BLE_GAP_EVT_DISCONNECTED)
            {
                BLE_DM_Event_T          dmEvt;
                uint8_t i;

                dmEvt.eventId=BLE_DM_EVT_DISCONNECTED;
                dmEvt.connHandle=p_gapEvt->eventField.evtDisconnect.connHandle;
                
                
                p_conn = BLE_DM_InfoGetConnByHandle(p_gapEvt->eventField.evtDisconnect.connHandle);
                if (p_conn != NULL)
                {
                    dmEvt.peerDevId = p_conn->devId;
                    ble_dm_FreeConn(p_conn);
                }
                else
                {
                    dmEvt.peerDevId = BLE_DM_PEER_DEV_ID_INVALID;
                }

                for(i=0;i<g_dmCbNum; i++)
                {
                    if(g_dmEventCb[i] != NULL)
                    {
                        g_dmEventCb[i](&dmEvt);
                    }
                }
            }
            else
            {
				//Shall not enter here
            }
        }
        break;

        default:
        {
            //Do nothing
        }
        break;
    }
}

uint16_t BLE_DM_InfoSetFilterAcceptList(uint8_t devCnt, uint8_t const * p_devId)
{
    uint16_t result;
    uint8_t i;

    if (p_devId == NULL || devCnt == 0U)
    {
        result = BLE_GAP_SetFilterAcceptList(0, NULL);
        if (result == MBA_RES_SUCCESS)
        {
            sp_dmInfoCtrl->filterAcceptListCnt = 0;
        }

        return result;
    }

    if (devCnt > BLE_DM_MAX_FILTER_ACCEPT_LIST_NUM)
    {
        return MBA_RES_INVALID_PARA;
    }

    BLE_GAP_Addr_T addr[BLE_DM_MAX_FILTER_ACCEPT_LIST_NUM];


    /* Get address by peer id */
    for (i = 0; i < devCnt; i++)
    {
        BLE_DM_PairedDevInfo_T pairedInfo;

        if ((result = BLE_DM_DdsGetPairedDevice(p_devId[i], &pairedInfo)) != MBA_RES_SUCCESS)
        {
            return result;
        }

        if (pairedInfo.remoteAddr.addrType != BLE_GAP_ADDR_TYPE_PUBLIC 
            && pairedInfo.remoteAddr.addrType != BLE_GAP_ADDR_TYPE_RANDOM_STATIC)
        {
            return MBA_RES_INVALID_PARA;
        }

        addr[i] = pairedInfo.remoteAddr;
    }

    result = BLE_GAP_SetFilterAcceptList(devCnt,addr);

    /* copy the devices added successfully to s_imFilterAcceptList */
    (void)memcpy(sp_dmInfoCtrl->filterAcceptList, p_devId, sizeof(uint8_t) * i);
    sp_dmInfoCtrl->filterAcceptListCnt = i;


    return result;
}


uint16_t BLE_DM_InfoGetFilterAcceptList(uint8_t *p_devCnt, BLE_GAP_Addr_T *p_addr)
{
    BLE_DM_PairedDevInfo_T pairedInfo;

    for (uint8_t i = 0; i < sp_dmInfoCtrl->filterAcceptListCnt; i++)
    {
        if (MBA_RES_SUCCESS != BLE_DM_DdsGetPairedDevice(sp_dmInfoCtrl->filterAcceptList[i], &pairedInfo))
        {
            return MBA_RES_FAIL;
        }

        p_addr[i] = pairedInfo.remoteAddr;
    }

    *p_devCnt = sp_dmInfoCtrl->filterAcceptListCnt;

    return MBA_RES_SUCCESS;
}

uint16_t BLE_DM_InfoSetResolvingList(uint8_t devCnt, uint8_t const *p_devId, uint8_t const *p_privacyMode)
{
    uint16_t                        result;
    uint8_t                         i;
    BLE_GAP_ResolvingListParams_T   *p_resolvingList;
    bool enable;
    BLE_GAP_LocalPrivacyParams_T privacy;


    result = MBA_RES_SUCCESS;

    if (p_devId == NULL || devCnt == 0U || p_privacyMode == NULL)
    {
        result = BLE_GAP_SetResolvingList(0, NULL);
        return result;
    }

    if (devCnt > BLE_DM_MAX_RESOLVING_LIST_NUM)
    {
        return MBA_RES_INVALID_PARA;
    }

    p_resolvingList = OSAL_Malloc(sizeof(BLE_GAP_ResolvingListParams_T) * devCnt);
    if (p_resolvingList == NULL)
    {
        return MBA_RES_OOM;
    }

    (void)BLE_GAP_GetLocalPrivacy(&enable, &privacy);

    /* Get address by peer id */
    for (i = 0; i < devCnt; i++)
    {
        BLE_DM_PairedDevInfo_T pairedInfo;

        (void)memset(&pairedInfo, 0, sizeof(BLE_DM_PairedDevInfo_T));
        result = BLE_DM_DdsGetPairedDevice(p_devId[i], &pairedInfo);
        if (result != MBA_RES_SUCCESS)
        {
            break;
        }

        if ((pairedInfo.remoteAddr.addrType != BLE_GAP_ADDR_TYPE_PUBLIC 
            && pairedInfo.remoteAddr.addrType != BLE_GAP_ADDR_TYPE_RANDOM_STATIC)
            || (p_privacyMode[i] > BLE_GAP_PRIVACY_MODE_DEVICE))
        {
            result = MBA_RES_INVALID_PARA;
            break;
        }

        if ((pairedInfo.localIrk[0]==0x00U) && (memcmp(pairedInfo.localIrk, pairedInfo.localIrk+1, 15) == 0))
        {
            (void)memcpy(p_resolvingList[i].localIrk, privacy.localIrk, 16);
        }
        else
        {
            (void)memcpy(p_resolvingList[i].localIrk, pairedInfo.localIrk, 16);
        }
        (void)memcpy(p_resolvingList[i].peerIrk, pairedInfo.remoteIrk, 16);
        p_resolvingList[i].peerIdAddr = pairedInfo.remoteAddr;
        p_resolvingList[i].privacyMode = p_privacyMode[i];
    }

    if (result == MBA_RES_SUCCESS)
    {
        result = BLE_GAP_SetResolvingList(devCnt,p_resolvingList);
    }

    OSAL_Free(p_resolvingList);

    return result;
}

uint16_t BLE_DM_InfoGetConnHandleByDevId(uint8_t devId, uint16_t *p_connHandle)
{
    uint8_t  i;
    uint16_t result;

    result=MBA_RES_FAIL;
    for (i = 0; i < BLE_GAP_MAX_LINK_NBR; i++)
    {
        if (sp_dmInfoCtrl->conn[i] != NULL && sp_dmInfoCtrl->conn[i]->devId == devId)
        {
            *p_connHandle = sp_dmInfoCtrl->conn[i]->connHandle;
            result=MBA_RES_SUCCESS;
            break;
        }
    }
    return result;
}
