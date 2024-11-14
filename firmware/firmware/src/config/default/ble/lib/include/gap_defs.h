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
  GAP Definition Header File

  Company:
    Microchip Technology Inc.

  File Name:
    gap_defs.h

  Summary:
    This file contains the GAP definitions.

  Description:
    This file contains the GAP definitions.
 *******************************************************************************/


/**
 *@addtogroup BLE_GAP
 *@{
 *@brief Header file for the BT/BLE Generic Access Profile library.
 * @note Definitions and prototypes for the BT/BLE GAP stack layer application programming interface.
 */
#ifndef GAP_DEFS_H
#define GAP_DEFS_H


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
/**@addtogroup BLE_GAP_DEFINES Defines
 * @{ */
 
 
/**@defgroup GAP_STATUS Status definitions
 * @brief The definitions list the various possible status.
 * @{ */
#define GAP_STATUS_SUCCESS                                   (0x00U)        /**< Successful status. */
#define GAP_STATUS_UNKNOWN_HCI_COMMAND                       (0x01U)        /**< Unknown HCI Command. */
#define GAP_STATUS_UNKNOWN_CONNECTION_IDENTIFIER             (0x02U)        /**< Unknown Connection Identifier. */
#define GAP_STATUS_HARDWARE_FAILURE                          (0x03U)        /**< Hardware Failure. */
#define GAP_STATUS_PAGE_TIMEOUT                              (0x04U)        /**< Page Timeout. */
#define GAP_STATUS_AUTHENTICATION_FAILURE                    (0x05U)        /**< Authentication Failure. */
#define GAP_STATUS_PIN_KEY_MISSING                           (0x06U)        /**< PIN or Key Missing. */
#define GAP_STATUS_MEMORY_CAPACITY_EXCEEDED                  (0x07U)        /**< Memory Capacity Exceeded. */
#define GAP_STATUS_CONNECTION_TIMEOUT                        (0x08U)        /**< Connection Timeout. */
#define GAP_STATUS_CONNECTION_LIMIT_EXCEEDED                 (0x09U)        /**< Connection Limit Exceeded. */
#define GAP_STATUS_SYNCHRONOUS_CONNECTION_LIMIT_EXCEEDED     (0x0AU)        /**< Synchronous Connection Limit To A Device Exceeded. */
#define GAP_STATUS_CONNECTION_ALREADY_EXISTS                 (0x0BU)        /**< Connection Already Exists. */
#define GAP_STATUS_COMMAND_DISALLOWED                        (0x0CU)        /**< Command Disallowed. */
#define GAP_STATUS_REJECTED_DUE_TO_LIMITED_RESOURCES         (0x0DU)        /**< Connection Rejected due to Limited Resources. */
#define GAP_STATUS_REJECTED_DUE_TO_SECURITY_REASONS          (0x0EU)        /**< Connection Rejected due To Security Reasons. */
#define GAP_STATUS_REJECTED_DUE_TO_UNACCEPTABLE_BDADDR       (0x0FU)        /**< Connection Rejected due to Unacceptable BD_ADDR. */
#define GAP_STATUS_CONNECTION_ACCEPT_TIMEOUT                 (0x10U)        /**< Connection Accept Timeout Exceeded. */
#define GAP_STATUS_UNSUPPORTED_FEATURE                       (0x11U)        /**< Unsupported Feature or Parameter Value. */
#define GAP_STATUS_INVALID_HCI_COMMAND_PARAMETERS            (0x12U)        /**< Invalid HCI Command Parameters. */
#define GAP_STATUS_REMOTE_TML_CONN               			 (0x13U)        /**< Remote User Terminated Connection. */
#define GAP_STATUS_REMOTE_TML_CONN_LOW_RESOURCE  			 (0x14U)        /**< Remote Device Terminated Connection due to Low Resources. */
#define GAP_STATUS_REMOTE_TML_CONN_POWEROFF      			 (0x15U)        /**< Remote Device Terminated Connection due to Power Off. */
#define GAP_STATUS_LOCAL_HOST_TERMINATE_CONNECTION           (0x16U)        /**< Connection Terminated By Local Host. */
#define GAP_STATUS_REPEATED_ATTEMPTS                         (0x17U)        /**< Repeated Attempts. */
#define GAP_STATUS_PAIRING_NOT_ALLOWED                       (0x18U)        /**< Pairing Not Allowed. */
#define GAP_STATUS_UNKNOWN_LMP_PDU                           (0x19U)        /**< Unknown LMP PDU. */
#define GAP_STATUS_UNSUPPORTED_REMOTE_FEATURE                (0x1AU)        /**< Unsupported Remote Feature / Unsupported LMP Feature. */
#define GAP_STATUS_SCO_OFFSET_REJECT                         (0x1BU)        /**< SCO Offset Rejected. */
#define GAP_STATUS_SCO_INTEVAL_REJECT                        (0x1CU)        /**< SCO Interval Rejected. */
#define GAP_STATUS_SCO_AIR_MODE_REJECT                       (0x1DU)        /**< SCO Air Mode Rejected. */
#define GAP_STATUS_INVALID_LMP_PARAMETERS                    (0x1EU)        /**< Invalid LMP Parameters / Invalid LL Parameters. */
#define GAP_STATUS_UNSPECIFIED_ERROR                         (0x1FU)        /**< Unspecified Error. */
#define GAP_STATUS_UNSUPPORTED_LMP_PARAMETERS                (0x20U)        /**< Unsupported LMP Parameter Value / Unsupported LL Parameter Value. */
#define GAP_STATUS_ROLE_CHANGE_NOT_ALLOW                     (0x21U)        /**< Role Change Not Allowed. */
#define GAP_STATUS_LMP_RESPONSE_TIMEOUT                      (0x22U)        /**< LMP Response Timeout / LL Response Timeout. */
#define GAP_STATUS_LMP_ERROR_TRANSACTION_COLLISION           (0x23U)        /**< LMP Error Transaction Collision / LL Procedure Collision. */
#define GAP_STATUS_LMP_PDU_NOT_ALLOW                         (0x24U)        /**< LMP PDU Not Allowed. */
#define GAP_STATUS_ENCRYPTION_MODE_NOT_ACCEPTABLE            (0x25U)        /**< Encryption Mode Not Acceptable. */
#define GAP_STATUS_LINK_KEY_CANNOT_BE_CHANGED                (0x26U)        /**< Link Key cannot be Changed. */
#define GAP_STATUS_REQUESTED_QOS_NOT_SUPPORT                 (0x27U)        /**< Requested QoS Not Supported. */
#define GAP_STATUS_INSTANT_PASSED                            (0x28U)        /**< Instant Passed. */
#define GAP_STATUS_PAIRING_WITH_UNIT_KEY_NOT_SUPPORT         (0x29U)        /**< Pairing With Unit Key Not Supported. */
#define GAP_STATUS_DIFFERENT_TRANSACTION_COLLISION           (0x2AU)        /**< Different Transaction Collision. */
#define GAP_STATUS_QOS_UNACCEPTABLE_PARAMETER                (0x2CU)        /**< QoS Unacceptable Parameter. */
#define GAP_STATUS_QOS_REJECTED                              (0x2DU)        /**< QoS Rejected. */
#define GAP_STATUS_CHANNEL_CLASSIFICATION_NOT_SUPPORT        (0x2EU)        /**< Channel Classification Not Supported. */
#define GAP_STATUS_INSUFFICIENT_SECURITY                     (0x2FU)        /**< Insufficient Security. */
#define GAP_STATUS_PARAMETER_OUT_OF_MANDATORY_RANGE          (0x30U)        /**< Parameter Out Of Mandatory Range. */
#define GAP_STATUS_ROLE_SWITCH_PENDING                       (0x32U)        /**< Role Switch Pending. */
#define GAP_STATUS_RESERVED_SLOT_VIOLATION                   (0x34U)        /**< Reserved Slot Violation. */
#define GAP_STATUS_ROLE_SWITCH_FAILED                        (0x35U)        /**< Role Switch Failed. */
#define GAP_STATUS_EXTENDED_INQUIRY_RESPONSE_TOO_LARGE       (0x36U)        /**< Extended Inquiry Response Too Large. */
#define GAP_STATUS_SECURE_SIMPLE_PAIRING_NOT_SUPPORT         (0x37U)        /**< Secure Simple Pairing Not Supported By Host. */
#define GAP_STATUS_HOST_BUSY_PAIRING                         (0x38U)        /**< Host Busy - Pairing. */
#define GAP_STATUS_CONNECTION_REJECT_NON_SUITABLE_CHANNEL    (0x39U)        /**< Connection Rejected due to No Suitable Channel Found. */
#define GAP_STATUS_CONTROLLER_BUSY                           (0x3AU)        /**< Controller Busy. */
#define GAP_STATUS_UNACCEPTABLE_CONNECTION_PARAMETERS        (0x3BU)        /**< Unacceptable Connection Parameters. */
#define GAP_STATUS_ADVERTISING_TIMEOUT                       (0x3CU)        /**< Advertising Timeout. */
#define GAP_STATUS_CONNECTION_TERMINATE_MIC_FAILURE          (0x3DU)        /**< Connection Terminated due to MIC Failure. */
#define GAP_STATUS_CONNECTION_FAILED_TO_BE_ESTABLISHED       (0x3EU)        /**< Connection Failed to be Established. */
#define GAP_STATUS_MAC_CONNECTION_FAILED                     (0x3FU)        /**< MAC Connection Failed. */
#define GAP_STATUS_COARSE_CLOCK_ADJUSTMENT_REJECTED          (0x40U)        /**< Coarse Clock Adjustment Rejected but Will Try to Adjust Using Clock Dragging. */
#define GAP_STATUS_TYPE0_SUBMAP_NOT_DEFINED                  (0x41U)        /**< Type0 Submap Not Defined. */
#define GAP_STATUS_UNKNOWN_ADVERTISING_IDENTIFIER            (0x42U)        /**< Unknown Advertising Identifier. */
#define GAP_STATUS_LIMIT_REACHED                             (0x43U)        /**< Limit Reached. */
#define GAP_STATUS_OPERATION_CANCELLED_BY_HOST               (0x44U)        /**< Operation Cancelled by Host. */
/** @} */

/**@defgroup GAP_MAX_ADDRESS_LEN Address length
 * @brief The definition of maximum Bluetooth address length.
 * @{ */
#define GAP_MAX_BD_ADDRESS_LEN                               (0x06U)        /**< Maximum length of BD address . */
/** @} */


/**@defgroup GAP_MAX_DEVICE_NAME_LEN Maximum device name length
 * @brief The definition of maximum length of device name.
 * @{ */
#define GAP_MAX_DEVICE_NAME_LEN                              (0x20U)        /**< Maximum length of device name. */
/** @} */


/**@defgroup GAP_DISC_REASON Disconnect reason
 * @brief The definition of disconnection reason.
 * @{ */
#define GAP_DISC_REASON_AUTH_FAIL                            (0x05U)        /**< Authentication failure */
#define GAP_DISC_REASON_REMOTE_TERMINATE                     (0x13U)        /**< Remote User Terminated Connection */
#define GAP_DISC_REASON_LOW_RESOURCES                        (0x14U)        /**< Remote Device Terminated Connection due to Low Resources */
#define GAP_DISC_REASON_POWER_OFF                            (0x15U)        /**< Remote Device Terminated Connection due to Power Off */
#define GAP_DISC_REASON_UNSUPPORTED                          (0x1AU)        /**< Unsupported Remote Feature / Unsupported LMP Feature */
#define GAP_DISC_REASON_KEY_LEN_UNSUPPORTED                  (0x29U)        /**< Pairing with Unit Key Not Supported */
#define GAP_DISC_REASON_UNACCEPTABLE_CP                      (0x3BU)        /**< Unacceptable Connection Parameters */
/** @} */


/**@defgroup GAP_APPEARANCE_DEF Appearance definition
 * @brief The definition of appearance.
 * @{ */
#define GAP_APPEARANCE_UNKNOWN                                  (0U)        /**< Unknown. */
#define GAP_APPEARANCE_GENERIC_PHONE                           (64U)        /**< Generic Phone. */
#define GAP_APPEARANCE_GENERIC_COMPUTER                       (128U)        /**< Generic Computer. */
#define GAP_APPEARANCE_GENERIC_WATCH                          (192U)        /**< Generic Watch. */
#define GAP_APPEARANCE_GENERIC_HID                            (960U)        /**< Human Interface Device (HID). */
#define GAP_APPEARANCE_GENERIC_GLUCOSE_METER                 (1024U)        /**< Generic Glucose Meter. */
#define GAP_APPEARANCE_GENERIC_CYCLING                       (1152U)        /**< Generic Cycling. */
#define GAP_APPEARANCE_GENERIC_WEIGHT_SCALE                  (3200U)        /**< Generic Weight Scale. */
/** @} */


/**@} */ //BLE_GAP_DEFINES

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif


/**
  @}
*/
