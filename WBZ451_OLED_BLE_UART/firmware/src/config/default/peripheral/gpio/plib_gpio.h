/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
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

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************

/*** Macros for GFX_DISP_INTF_PIN_CS pin ***/
#define GFX_DISP_INTF_PIN_CS_Set()               (GPIOA_REGS->GPIO_LATSET = (1U<<9U))
#define GFX_DISP_INTF_PIN_CS_Clear()             (GPIOA_REGS->GPIO_LATCLR = (1U<<9U))
#define GFX_DISP_INTF_PIN_CS_Toggle()            (GPIOA_REGS->GPIO_LATINV= (1U<<9U))
#define GFX_DISP_INTF_PIN_CS_Get()               ((GPIOA_REGS->GPIO_PORT >> 9U) & 0x1U)
#define GFX_DISP_INTF_PIN_CS_OutputEnable()      (GPIOA_REGS->GPIO_TRISCLR = (1U<<9U))
#define GFX_DISP_INTF_PIN_CS_InputEnable()       (GPIOA_REGS->GPIO_TRISSET = (1U<<9U))
#define GFX_DISP_INTF_PIN_CS_PIN                  GPIO_PIN_RA9
/*** Macros for GFX_DISP_INTF_PIN_RSDC pin ***/
#define GFX_DISP_INTF_PIN_RSDC_Set()               (GPIOA_REGS->GPIO_LATSET = (1U<<2U))
#define GFX_DISP_INTF_PIN_RSDC_Clear()             (GPIOA_REGS->GPIO_LATCLR = (1U<<2U))
#define GFX_DISP_INTF_PIN_RSDC_Toggle()            (GPIOA_REGS->GPIO_LATINV= (1U<<2U))
#define GFX_DISP_INTF_PIN_RSDC_Get()               ((GPIOA_REGS->GPIO_PORT >> 2U) & 0x1U)
#define GFX_DISP_INTF_PIN_RSDC_OutputEnable()      (GPIOA_REGS->GPIO_TRISCLR = (1U<<2U))
#define GFX_DISP_INTF_PIN_RSDC_InputEnable()       (GPIOA_REGS->GPIO_TRISSET = (1U<<2U))
#define GFX_DISP_INTF_PIN_RSDC_PIN                  GPIO_PIN_RA2
/*** Macros for GFX_DISP_INTF_PIN_RESET pin ***/
#define GFX_DISP_INTF_PIN_RESET_Set()               (GPIOB_REGS->GPIO_LATSET = (1U<<2U))
#define GFX_DISP_INTF_PIN_RESET_Clear()             (GPIOB_REGS->GPIO_LATCLR = (1U<<2U))
#define GFX_DISP_INTF_PIN_RESET_Toggle()            (GPIOB_REGS->GPIO_LATINV= (1U<<2U))
#define GFX_DISP_INTF_PIN_RESET_Get()               ((GPIOB_REGS->GPIO_PORT >> 2U) & 0x1U)
#define GFX_DISP_INTF_PIN_RESET_OutputEnable()      (GPIOB_REGS->GPIO_TRISCLR = (1U<<2U))
#define GFX_DISP_INTF_PIN_RESET_InputEnable()       (GPIOB_REGS->GPIO_TRISSET = (1U<<2U))
#define GFX_DISP_INTF_PIN_RESET_PIN                  GPIO_PIN_RB2
/*** Macros for GFX_DISP_INTF_PIN_EN pin ***/
#define GFX_DISP_INTF_PIN_EN_Set()               (GPIOB_REGS->GPIO_LATSET = (1U<<1U))
#define GFX_DISP_INTF_PIN_EN_Clear()             (GPIOB_REGS->GPIO_LATCLR = (1U<<1U))
#define GFX_DISP_INTF_PIN_EN_Toggle()            (GPIOB_REGS->GPIO_LATINV= (1U<<1U))
#define GFX_DISP_INTF_PIN_EN_Get()               ((GPIOB_REGS->GPIO_PORT >> 1U) & 0x1U)
#define GFX_DISP_INTF_PIN_EN_OutputEnable()      (GPIOB_REGS->GPIO_TRISCLR = (1U<<1U))
#define GFX_DISP_INTF_PIN_EN_InputEnable()       (GPIOB_REGS->GPIO_TRISSET = (1U<<1U))
#define GFX_DISP_INTF_PIN_EN_PIN                  GPIO_PIN_RB1


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/

#define    GPIO_PORT_A   (GPIOA_BASE_ADDRESS)
#define    GPIO_PORT_B   (GPIOB_BASE_ADDRESS)
typedef uint32_t GPIO_PORT;

typedef enum
{
    GPIO_INTERRUPT_ON_MISMATCH,
    GPIO_INTERRUPT_ON_RISING_EDGE,
    GPIO_INTERRUPT_ON_FALLING_EDGE,
    GPIO_INTERRUPT_ON_BOTH_EDGES,
}GPIO_INTERRUPT_STYLE;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/


#define     GPIO_PIN_RA0  (0U)
#define     GPIO_PIN_RA1  (1U)
#define     GPIO_PIN_RA2  (2U)
#define     GPIO_PIN_RA3  (3U)
#define     GPIO_PIN_RA4  (4U)
#define     GPIO_PIN_RA5  (5U)
#define     GPIO_PIN_RA6  (6U)
#define     GPIO_PIN_RA7  (7U)
#define     GPIO_PIN_RA8  (8U)
#define     GPIO_PIN_RA9  (9U)
#define     GPIO_PIN_RA10  (10U)
#define     GPIO_PIN_RA11  (11U)
#define     GPIO_PIN_RA12  (12U)
#define     GPIO_PIN_RA13  (13U)
#define     GPIO_PIN_RA14  (14U)
#define     GPIO_PIN_RB0  (16U)
#define     GPIO_PIN_RB1  (17U)
#define     GPIO_PIN_RB2  (18U)
#define     GPIO_PIN_RB3  (19U)
#define     GPIO_PIN_RB4  (20U)
#define     GPIO_PIN_RB5  (21U)
#define     GPIO_PIN_RB6  (22U)
#define     GPIO_PIN_RB7  (23U)
#define     GPIO_PIN_RB8  (24U)
#define     GPIO_PIN_RB9  (25U)
#define     GPIO_PIN_RB10  (26U)
#define     GPIO_PIN_RB11  (27U)
#define     GPIO_PIN_RB12  (28U)
#define     GPIO_PIN_RB13  (29U)

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
#define    GPIO_PIN_NONE    (-1)

typedef uint32_t GPIO_PIN;


void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
	uint32_t xvalue = (uint32_t)value;
    GPIO_PortWrite((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))), (uint32_t)(0x1U) << (pin & 0xFU), (xvalue) << (pin & 0xFU));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return ((((GPIO_PortRead((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))))) >> (pin & 0xFU)) & 0x1U) != 0U);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (((GPIO_PortLatchRead((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4)))) >> (pin & 0xFU)) & 0x1U) != 0U);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))), (uint32_t)0x1U << (pin & 0xFU));
}


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H
