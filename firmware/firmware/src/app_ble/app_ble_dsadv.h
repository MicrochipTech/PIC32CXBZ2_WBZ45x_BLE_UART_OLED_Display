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
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_ble_dsadv.h

  Summary:
    This header file provides prototypes and definitions for the application BLE Deep Sleep Advertising (DSADV).

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef APP_BLE_DSADV_H
#define APP_BLE_DSADV_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************




// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    bool APP_BleDsadvIsEnable(void)

  Summary:
     Check if DSADV has been performed or not.

  Description:
     Return true means DSADV has been performed and the device wakes up from deep sleep.
     Return false means DSADV has not been performed yet and the device boots up from power on reset.

  Precondition:

  Parameters:
    None.

  Returns:
    True means DSADV has been performed; false means not.

*/
bool APP_BleDsadvIsEnable(void);

/*******************************************************************************
  Function:
    void APP_BleDsadvStart (bool flag)

  Summary:
     Start DSADV.

  Description:
     This function is used to start DSADV in the initialization.

  Precondition:

  Parameters:
    flag            True means the device wakes up from deep sleep; false means the device boots from power on reset.

  Returns:
    None.

*/
void APP_BleDsadvStart(bool flag);

/*******************************************************************************
  Function:
    void APP_BleDsadvRestart ( void )

  Summary:
     Restart DSADV when the BLE link is terminated.

  Description:
     This function is used to restart DSADV when the BLE link is terminated.

  Precondition:
     Only can be called once applocation receivces the callback event BLE_GAP_EVT_DISCONNECTED.
  Parameters:
    None.

  Returns:
    None.

*/
void APP_BleDsadvRestart(void);

/*******************************************************************************
  Function:
    uint16_t APP_BleDsadvCompl(void);

  Summary:
     Handle DSADV complete event.

  Description:

  Precondition:

  Parameters:
    None.

  Returns:
    None.

*/
void APP_BleDsadvCompl(void);

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* APP_BLE_DSADV_H */


/*******************************************************************************
 End of File
 */

