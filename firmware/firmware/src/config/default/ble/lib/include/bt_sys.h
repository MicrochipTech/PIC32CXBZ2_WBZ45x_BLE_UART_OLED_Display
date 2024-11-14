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
  Bluetooth System Header File

  Company:
    Microchip Technology Inc.

  File Name:
    bt_sys.h

  Summary:
    This file contains the BLE System functions for the project.

  Description:
    This file contains the BLE System functions for the project. The "BT_SYS_Init"
    function shall be called in the "SYS_Initialize" function to initialize the
    this modules in the system. And the "BM_Task"  shall be called in the "SYS_Tasks".
 *******************************************************************************/


/**
 * @defgroup BT_SYS Bluetooth System
 * @brief Definitions of Bluetooth system
 * @{
 */

#ifndef BT_SYS_H
#define BT_SYS_H

/** @defgroup BT_SYS_INT Bluetooth System Interface
 *  @brief This module defines the interface of the Bluetooth system.
 *  @{ */

#include <stdbool.h>
#include <stdint.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************


/**@addtogroup BT_SYS_DEFINES Defines
 * @{ */

/**@defgroup BT_SYS_ADDR_LEN Length of Bluetooth address
 * @brief Length of Bluetooth address.
 * @{ */
#define BT_SYS_DEV_ADDR_LEN                 (7U)           /**< Length of the Bluetooth address. */
/**@} */ //BT_SYS_ADDR_LEN


/**@defgroup BT_SYS_TRACE_MASK Trace Mask
 * @brief The definition of trace mask.
 * @{ */
#define BT_SYS_TRACE_INFO_LL_H              (1U)          /**< LL trace high priority information. */
#define BT_SYS_TRACE_INFO_LL_L              (1U<<1U)      /**< LL trace low priority information. */
#define BT_SYS_TRACE_INFO_HOST              (1U<<2U)      /**< Host trace info. */
/**@} */ //BT_SYS_TRACE_MASK


/**@defgroup BT_SYS_TRACE_LEVEL Trace Level
 * @brief The definition of trace level.
 * @{ */
#define BT_SYS_TRACE_LEVEL_ERR				0			  /**< Error level. */
#define BT_SYS_TRACE_LEVEL_API				1		      /**< API level. */
#define BT_SYS_TRACE_LEVEL_OP				2			  /**< OP level. */
/**@} */ //BT_SYS_TRACE_LEVEL


/**@defgroup BT_SYS_RF_SUSPEND_STATUS Rf Suspned Status
 * @brief The definition of rf suspend status.
 * @{ */
#define BT_SYS_RF_NOT_SUSPEND               (0U)          /**< BLE RF is not allowed to suspend. */
#define BT_SYS_RF_SUSPENDED_NO_SLEEP        (1U)          /**< BLE RF is allowed to suspended without ble sleep mode. */
#define BT_SYS_RF_SUSPENDED_WITH_SLEEP      (2U)          /**< BLE RF is allowed to suspended with ble sleep mode. */
/**@} */ //BT_SYS_RF_SUSPEND

/**@defgroup BT_SYS_FEAT_MASK Feature Mask
 * @brief The definition of feature mask.
 * @{ */
#define BT_SYS_FEAT_PWR_CTRL                (1U)          /**< Power control. */
/**@} */ //BT_SYS_FEAT_MASK

/**@} */ //BT_SYS_DEFINES


/**@addtogroup BT_SYS_ENUM Enumerations
 * @{ */

/**@defgroup BT_SYS_TRACE_FMT Trace format
 * @{ */
/**@brief The definition of trace format. */
typedef enum BT_SYS_TraceFmt_T{
	BT_SYS_FMT_ASCII,	                                 /**< ASCII. */
}BT_SYS_TraceFmt_T;
/**@} */ //BT_SYS_TRACE_FMT


/**@defgroup BT_SYS_ERR BT system error code
 * @{ */
/**@brief The definition of BT system error code. */
typedef enum BT_SYS_ErrCode_T{
	BT_SYS_ERR_OOM,	                                 	/**< Out of memory. */
	BT_SYS_ERR_END										/**< End of error code definition. */
}BT_SYS_ErrCode_T;
/**@} */ //BT_SYS_ERR


/**@} */ //BT_SYS_ENUM

// *****************************************************************************
// *****************************************************************************
// SSection: Data Types
// *****************************************************************************

/**@addtogroup BT_SYS_STRUCTS Structures
 * @{ */

/**@brief Bluetooth system configuration. */
typedef struct BT_SYS_Cfg_T
{
    int8_t      	antennaGain;                        /**< Antenna gain. */
    unsigned int  	addrValid:1;                        /**< Set true if devAddr field is valid. */
    unsigned int   	rssiOffsetValid:1;                  /**< Set true if rssiOffset field is valid. */
    uint8_t     	devAddr[BT_SYS_DEV_ADDR_LEN];       /**< Device address. */
    int8_t      	rssiOffset;                         /**< RSSI offset. */
} BT_SYS_Cfg_T;

/**@brief Bluetooth system initialization. */
typedef struct BT_SYS_Option_T
{
    uint32_t        cmnMemSize;                     	/**< Common memory size. */
    uint8_t         *p_cmnMemAddr;                  	/**< Common memory address. */
    uint32_t        *p_sramVecorTable;              	/**< Vector table. */
    unsigned int	hciMode:1;							/**< HCI mode option. Set TRUE to enable HCI mode. */
    uint32_t        deFeatMask;                         /**< Features to be disabled. See @ref BT_SYS_FEAT_MASK. */
} BT_SYS_Option_T;

/**@brief Trace event additional information. */
typedef struct BT_SYS_TraceInfo_T
{
	uint8_t			level;								/**< Level. */
    uint8_t     	componentId;                        /**< Component id. */
    uint8_t     	eventId;                  			/**< Event id. */
} BT_SYS_TraceInfo_T;

/**@brief BT system trace callback type. This callback function sends trace events to the application. */
typedef void (*BT_SYS_TraceEventCb_T)(BT_SYS_TraceInfo_T *p_traceInfo, uint8_t length, uint8_t *p_tracePayload);


/**@brief BT system error callback type.*/
typedef void(*BT_SYS_ErrCb_T)(BT_SYS_ErrCode_T errCode);


/**@brief BT system HPA CPS callback type.*/
typedef void(*BT_SYS_HpaCpsCb_T)(bool bypass);

/**@brief BT system HPA CTX callback type.*/
typedef void(*BT_SYS_HpaCtxCb_T)(bool active);

/**@} */ //BT_SYS_STRUCTS


// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

/**@addtogroup BT_SYS_FUNS Functions
 * @{ */

/**@brief Initialize Bluetooth system.
 *
 * @param[in] p_reqQueueHandle                  OS handle for Bluetooth internal task.
 * @param[in] p_osalApiList                     OSAL api list.
 * @param[in] p_option                          Initialization option.
 * @param[in] p_cfg                             System configuration.
 *
 * @retval true                                 Success to initialize BT.
 * @retval false                                Fail to initialize BT.
 */
bool BT_SYS_Init(void *p_reqQueueHandle, void *p_osalApiList, BT_SYS_Option_T *p_option, BT_SYS_Cfg_T *p_cfg);


/**@brief Retrieve BT version.
 *
 * @param[out] p_version                        Point to version buffer.
 *
 */
void BT_SYS_ReadVersion(uint32_t *p_version);


/**@brief Query if BT is sleeping.
 *
 * @retval true                                     BT is sleeping.
 * @retval false                                    BT is not sleeping.
 */
bool BT_SYS_GetSleepMode(void);


/**@brief Request BT enter sleep mode.
 *
 * @param[in] ulRtcFrequency                        RTC frequency.
 * @param[in] ulRtcCurrentCnt                       RTC current count.
 *
 * @retval true                                     BT is ready for idle and enter sleep.
 * @retval false                                    BT is already sleeping or BT is not ready for idle.
 */
bool BT_SYS_EnterSleepMode(uint32_t ulRtcFrequency, uint32_t ulRtcCurrentCnt);


/**@brief Query if BT allow system enter sleep mode.
 *
 * @param[in] ulRtcFrequency                        RTC frequency.
 * @param[in] ulRtcCurrentCnt                       RTC current count.
 *
 * @retval true                                     BT is sleeping and BT is ready for System enter sleep.
 * @retval false                                    BT is not sleeping or BT is not ready for System enter sleep.
 */
bool BT_SYS_AllowSystemSleep(uint32_t ulRtcFrequency, uint32_t ulRtcCurrentCnt);


/**@brief Request BT enter deep sleep mode. */
void BT_SYS_EnterDeepSleepMode(void);


/**@brief Request BT suspend RF.
 *
 * @param[in] enable                                Set true to suspend RF. Otherwise set false.
 *
 * @retval BT_SYS_RF_SUSPEND_STATUS                 BT system RF Suspend status. See @ref BT_SYS_RF_SUSPEND_STATUS.
 */
uint8_t BT_SYS_RfSuspendReq(bool enable);


/**@brief Enable BT trace message indication.
 *
 * @param[in] fmt                                   BT system trace format. See @ref BT_SYS_TRACE_FMT.
 * @param[in] traceMask                             BT system trace mask. See @ref BT_SYS_TRACE_MASK.
 * @param[in] traceCb                               BT system trace callback.
 *
 */
void BT_SYS_TraceEnable(BT_SYS_TraceFmt_T fmt, uint32_t traceMask, BT_SYS_TraceEventCb_T traceCb);


/**@brief Register BT system error callback.
 *
 * @param[in] errHandler                             BT system error callback function.
 *
 */
void BT_SYS_ErrRegister(BT_SYS_ErrCb_T errHandler);


/**@brief Initialize BT system HPA with a callback function.
 *
 * @param[in] hpaCb                             BT system HPA callback function.
 * @param[in] hpaCtxCb                        BT system HPA CTX callback function.
 *
 */
void BT_SYS_HpaInit(BT_SYS_HpaCpsCb_T hpaCb,  BT_SYS_HpaCtxCb_T hpaCtxCb);


/**@brief Hook Bluetooth task.
 *
 * @param[in] p_param Pointer that will be used as the parameter for the task.
 *
 */
void BM_Task(void *p_param);

/**@} */ //BT_SYS_FUNS

/**
  @}
*/
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END


#endif//BT_SYS_H

/**
  @}
*/
