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
  Middleware AES Source File

  Company:
    Microchip Technology Inc.

  File Name:
    mw_aes.c

  Summary:
    This file contains the Middleware AES functions for application user.

  Description:
    This file contains the Middleware AES functions for application user.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stddef.h>
#include "mba_error_defs.h"
#include "mw_aes.h"

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



// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

uint16_t MW_AES_CbcDecryptInit(MW_AES_Ctx_T * p_ctx, uint8_t *p_aesKey, uint8_t *p_iv)
{
    if (0 == CRYPT_AES_KeySet(&p_ctx->aesCtx, p_aesKey, 16, p_iv, CRYPT_AES_DECRYPTION))
    {
        return MBA_RES_SUCCESS;
    }
    else
    {
        return MBA_RES_FAIL;
    }
}

uint16_t MW_AES_AesCbcDecrypt(MW_AES_Ctx_T * p_ctx, uint16_t length, uint8_t *p_plainText, uint8_t *p_chiperText)
{
    if (0 == CRYPT_AES_CBC_Decrypt(&p_ctx->aesCtx, p_plainText, p_chiperText, length))
    {
        return MBA_RES_SUCCESS;
    }
    else
    {
        return MBA_RES_FAIL;
    }
}

uint16_t MW_AES_EcbEncryptInit(MW_AES_Ctx_T * p_ctx, uint8_t *p_aesKey)
{
    if (0 == CRYPT_AES_KeySet(&p_ctx->aesCtx, p_aesKey, 16, NULL, CRYPT_AES_ENCRYPTION))
    {
        return MBA_RES_SUCCESS;
    }
    else
    {
        return MBA_RES_FAIL;
    }
}

uint16_t MW_AES_AesEcbEncrypt(MW_AES_Ctx_T * p_ctx, uint16_t length, uint8_t *p_chiperText, uint8_t *p_plainText)
{
    if (0 == CRYPT_AES_DIRECT_Encrypt(&p_ctx->aesCtx, p_chiperText, p_plainText))
    {
        return MBA_RES_SUCCESS;
    }
    else
    {
        return MBA_RES_FAIL;
    }

}

