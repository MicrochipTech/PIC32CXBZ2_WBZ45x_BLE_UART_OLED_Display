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
  ATT UUID Header File

  Company:
    Microchip Technology Inc.

  File Name:
    att_uuid.h

  Summary:
    This file contains the definition of ATT UUIDs.

  Description:
    This file contains the definition of ATT UUIDs.

 *******************************************************************************/


/**
 * @addtogroup GATT
 * @{
 * @brief Header file for the UUID definitions.
 */

#ifndef ATT_UUID_H
#define ATT_UUID_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

/**************************************************************************************************
  Macros
**************************************************************************************************/
/**@addtogroup GATT_DEFINES Defines
 * @{ */
 
/**@defgroup GATT_UUID_DEFS  UUID definitions
 * @brief The definition of GATT UUID.
 * @{ */
#define UUID_PRIMARY_SERVICE                                (0x2800U)              /**< Primary Service Declaration.*/
#define UUID_SECONDARY_SERVICE                              (0x2801U)              /**< Secondary Service Declaration.*/
#define UUID_INCLUDE                                        (0x2802U)              /**< Include Declaration.*/
#define UUID_CHARACTERISTIC                                 (0x2803U)              /**< Characteristic Declaration.*/
#define UUID_DESCRIPTOR_CHAR_EXT_PROP                       (0x2900U)              /**< Characteristic Extended Properties.*/
#define UUID_DESCRIPTOR_USER_DESC                           (0x2901U)              /**< Characteristic User Description Descriptor.*/
#define UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG                  (0x2902U)              /**< Client Characteristic Configuration Descriptor.*/
#define UUID_DESCRIPTOR_SERVER_CHAR_CONFIG                  (0x2903U)              /**< Server Characteristic Configuration Descriptor.*/
#define UUID_DESCRIPTOR_CHAR_PRE_FORMAT                     (0x2904U)              /**< Characteristic Presentation Format Descriptor.*/
#define UUID_DESCRIPTOR_CHAR_AGGRE_FROMAT                   (0x2905U)              /**< Characteristic Aggregate Format Descriptor.*/
#define UUID_DESCRIPTOR_VALID_RANGE                         (0x2906U)              /**< Valid Range.*/
#define UUID_DESCRIPTOR_EXTERNAL_REPORT_REF                 (0x2907U)              /**< External Report Reference.*/
#define UUID_DESCRIPTOR_REPORT_REF                          (0x2908U)              /**< Report Reference.*/
#define UUID_DESCRIPTOR_NUM_OF_DIGITALS                     (0x2909U)              /**< Number of Digitals.*/
#define UUID_DESCRIPTOR_VALUE_TRIGGER_SETTING               (0x290AU)              /**< Value Trigger Setting.*/
#define UUID_DESCRIPTOR_ENV_SENSING_CONFIG                  (0x290BU)              /**< Environmental Sensing Configuration.*/
#define UUID_DESCRIPTOR_ENV_SENSING_MEASURE                 (0x290CU)              /**< Environmental Sensing Measurement.*/
#define UUID_DESCRIPTOR_ENV_SENSING_TRIGGER_SETTING         (0x290DU)              /**< Environmental Sensing Trigger Setting.*/
#define UUID_DESCRIPTOR_TIME_TRIGGER_SETTING                (0x290EU)              /**< Time Trigger Setting.*/
#define UUID_DESCRIPTOR_COMPLETE_BREDR_BLOCK_DATA           (0x290FU)              /**< Complete BR-EDR Transport Block Data.*/
#define UUID_DESCRIPTOR_SIG_DEFINED_RESERVED                (0x29FFU)              /**< Reserve UUID 0x2900-0x29FF for SIG-defined descriptors. */
/** @} */


/**@defgroup ATT_UUID_LENGTH_TYPES UUID length
 * @brief The definition of UUID length.
 * @{ */
#define ATT_UUID_LENGTH_2                               (2U)                       /**< 16-bit Bluetooth UUID. */
#define ATT_UUID_LENGTH_4                               (4U)                       /**< 32-bit Bluetooth UUID. */
#define ATT_UUID_LENGTH_16                              (0x10U)                    /**< 128-bit Bluetooth UUID. */
/** @} */

/**@defgroup GATT_MAX_UUID_LENGTH Maximum UUID length
 * @brief The definition of max UUID length.
 * @{ */
#define ATT_MAX_UUID_SIZE                               ATT_UUID_LENGTH_16      /**< The Maximum UUID Length. 128-bit. */
/** @} */

/**@} */ //GATT_DEFINES

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**@addtogroup GATT_STRUCTS Structures
 * @{ */
 
/**@brief UUID parameters. */
typedef struct ATT_Uuid_T
{
    uint8_t uuid[ATT_MAX_UUID_SIZE];                                            /**< The UUID. */
    uint8_t uuidLength;                                                         /**< Length of the UUID. */
} ATT_Uuid_T;

/**@} */ //GATT_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************
/**@addtogroup GATT_DEFINES Defines
 * @{ */
 
/**@defgroup UUID_ARRAY UUID declaration
 * @brief The declaration of UUID for service table usage.
 * @{ */
extern const uint8_t g_gattUuidPrimSvc[ATT_UUID_LENGTH_2];                      /**< GATT Declaration UUID: Primary Service. */
extern const uint8_t g_gattUuidSecSvc[ATT_UUID_LENGTH_2];                       /**< GATT Declaration UUID: Secondary Service. */
extern const uint8_t g_gattUuidInc[ATT_UUID_LENGTH_2];                          /**< GATT Declaration UUID: Include. */
extern const uint8_t g_gattUuidChar[ATT_UUID_LENGTH_2];                         /**< GATT Declaration UUID: Characteristic Declaration. */

extern const uint8_t g_descUuidCharExtProp[ATT_UUID_LENGTH_2];                  /**< GATT Characteristic Descriptor UUID: Characteristic Extended Properties. */
extern const uint8_t g_descUuidUserDesc[ATT_UUID_LENGTH_2];                     /**< GATT Characteristic Descriptor UUID: Characteristic User Description. */
extern const uint8_t g_descUuidCcc[ATT_UUID_LENGTH_2];                          /**< GATT Characteristic Descriptor UUID: Client Characteristic Configuration. */
extern const uint8_t g_descUuidScc[ATT_UUID_LENGTH_2];                          /**< GATT Characteristic Descriptor UUID: Server Characteristic Configuration. */
extern const uint8_t g_descUuidPreFormat[ATT_UUID_LENGTH_2];                    /**< GATT Characteristic Descriptor UUID: Characteristic Presentation Format. */
extern const uint8_t g_descUuidAggFormat[ATT_UUID_LENGTH_2];                    /**< GATT Characteristic Descriptor UUID: Characteristic Aggregate Format. */
extern const uint8_t g_descUuidValidRange [ATT_UUID_LENGTH_2];                  /**< GATT Characteristic Descriptor UUID: Valid Range. */
extern const uint8_t g_descUuidExtReportRef[ATT_UUID_LENGTH_2];                 /**< GATT Characteristic Descriptor UUID: External Report Reference. */
extern const uint8_t g_descUuidReportRef[ATT_UUID_LENGTH_2];                    /**< GATT Characteristic Descriptor UUID: Report Reference. */
extern const uint8_t g_descUuidNumOfDigitals[ATT_UUID_LENGTH_2];                /**< GATT Characteristic Descriptor UUID: Number of Digitals. */
extern const uint8_t g_descUuidValueTriggetSet[ATT_UUID_LENGTH_2];              /**< GATT Characteristic Descriptor UUID: Value Trigger Setting. */
extern const uint8_t g_descUuidEnvSensingConfig[ATT_UUID_LENGTH_2];             /**< GATT Characteristic Descriptor UUID: Environmental Sensing Configuration. */
extern const uint8_t g_descUuidEnvSensingMeasure[ATT_UUID_LENGTH_2];            /**< GATT Characteristic Descriptor UUID: Environmental Sensing Measurement. */
extern const uint8_t g_descUuidEnvSensingTriggerSet[ATT_UUID_LENGTH_2];         /**< GATT Characteristic Descriptor UUID: Environmental Sensing Trigger Setting. */
extern const uint8_t g_descUuidTimeTriggerSet[ATT_UUID_LENGTH_2];               /**< GATT Characteristic Descriptor UUID: Time Trigger Setting. */
extern const uint8_t g_descUuidCompleteBredrBlockData[ATT_UUID_LENGTH_2];       /**< GATT Characteristic Descriptor UUID: Complete BR-EDR Transport Block Data. */
/** @} */

/**@} */ //GATT_DEFINES

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif

/**
  @}
 */

