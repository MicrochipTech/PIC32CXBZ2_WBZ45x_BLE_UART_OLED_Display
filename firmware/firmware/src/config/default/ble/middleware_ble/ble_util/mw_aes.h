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
  Middleware AES Header File

  Company:
    Microchip Technology Inc.

  File Name:
    mw_aes.h

  Summary:
    This file contains the BLE AES functions for application user.

  Description:
    This file contains the BLE AES functions for application user.
 *******************************************************************************/


/**
 * @addtogroup MW_AES
 * @{
 * @brief Header file for the Middleware AES library.
 * @note Definitions and prototypes for the Middleware AES stack layer application programming interface.
 */

#ifndef MW_AES_H
#define MW_AES_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include "crypto/crypto.h"

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


// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/**@addtogroup MW_AES_STRUCTS Structures
 * @{ */

/**@brief Structure of AES context which is used to contain aes information. */
typedef struct MW_AES_Ctx_T
{
    CRYPT_AES_CTX aesCtx;                                      /**< Context which saves state. */
} MW_AES_Ctx_T;


/**@} */ //MW_AES_STRUCTS

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
/**@addtogroup MW_AES_FUNS Functions
 * @{ */

/**
 *@brief The API is used to initialize AES CBC block cipher decryption.
 *
 *@param[out] p_ctx               Pointer to the structure of AES context. Refer to @ref MW_AES_Ctx_T for detail structure info.
 *@param[in] p_aesKey             Pointer to the 16 bytes encryption key.
 *@param[in] p_iv                 Pointer to the 16 bytes IV value.
 *
 *@retval MBA_RES_SUCCESS         Initialize successfully.
 *@retval MBA_RES_FAIL            Failed to initialize.
 */
uint16_t MW_AES_CbcDecryptInit(MW_AES_Ctx_T * p_ctx, uint8_t *p_aesKey, uint8_t *p_iv);

/**
 *@brief The API is used to decrypt a block of data using the AES CBC mode.
 *
 *@param[in] p_ctx                Pointer to the structure of AES context. Refer to @ref MW_AES_Ctx_T for detail structure info.
 *@param[in] length               The length of data to be decrypted.
 *@param[out] p_plainText         Pointer to buffer to store the results of the decryption.
 *@param[in] p_chiperText         Pointer to buffer holding the data to be decrypted.
 *
 *@retval MBA_RES_SUCCESS         Descrypt successfully.
 *@retval MBA_RES_FAIL            Failed to Descrypt.
 */
uint16_t MW_AES_AesCbcDecrypt(MW_AES_Ctx_T * p_ctx, uint16_t length, uint8_t *p_plainText, uint8_t *p_chiperText);

/**
 *@brief The API is used to initialize AES ECB block cipher Encryption.
 *
 *@param[out] p_ctx               Pointer to the structure of AES context. Refer to @ref MW_AES_Ctx_T for detail structure info.
 *@param[in] p_aesKey             Pointer to the 16 bytes encryption key.
 *
 *@retval MBA_RES_SUCCESS         Initialize successfully.
 *@retval MBA_RES_FAIL            Failed to initialize.
 */
uint16_t MW_AES_EcbEncryptInit(MW_AES_Ctx_T * p_ctx, uint8_t *p_aesKey);


/**
 *@brief The API is used to encrypt a block of data using the AES ECB mode.
 *
 *@param[in] p_ctx                Pointer to the structure of AES context. Refer to @ref MW_AES_Ctx_T for detail structure info.
 *@param[in] length               The length of data to be decrypted.
 *@param[out] p_chiperText        Pointer to buffer to store the results of the encryption.
 *@param[in] p_plainText          Pointer to buffer holding the data to be encrypted.
 *
 *@retval MBA_RES_SUCCESS         Descrypt successfully.
 *@retval MBA_RES_FAIL            Failed to Encrypt.
 */
uint16_t MW_AES_AesEcbEncrypt(MW_AES_Ctx_T * p_ctx, uint16_t length, uint8_t *p_chiperText, uint8_t *p_plainText);

/**@} */ //MW_AES_FUNS

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif
/**
 @}
*/


