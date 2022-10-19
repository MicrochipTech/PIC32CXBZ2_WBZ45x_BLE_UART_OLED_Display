// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include "device.h"
#include "definitions.h"


// *****************************************************************************
// *****************************************************************************
// Section: macro
// *****************************************************************************
// *****************************************************************************
#define CLK_READY_RETRIES  8000
#define BTZB_XTAL_NOT_READY ((BTZBSYS_REGS->BTZBSYS_SUBSYS_STATUS_REG1 \
                            & BTZBSYS_SUBSYS_STATUS_REG1_xtal_ready_out_Msk) \
                            != BTZBSYS_SUBSYS_STATUS_REG1_xtal_ready_out_Msk)
#define BTZB_PLL_NOT_LOCKED ((BTZBSYS_REGS->BTZBSYS_SUBSYS_STATUS_REG1 \
                            & BTZBSYS_SUBSYS_CNTRL_REG1_subsys_dbg_bus_sel_top_Msk) \
                            != BTZBSYS_SUBSYS_CNTRL_REG1_subsys_dbg_bus_sel_top_Msk)


/* The action ID for enter/exit sleep. */
typedef enum DEVICE_SLEEP_ActionId_T
{
    DEVICE_SLEEP_ENTER_SLEEP,                           /**< Enter sleep. */
    DEVICE_SLEEP_EXIT_SLEEP                             /**< Exit sleep. */
} DEVICE_SLEEP_ActionId_T;

/* The definition of clock source  */
typedef enum DEVICE_ClkSrcId_T
{
    DEVICE_NO_CLK = 0x00,                                /**< No clock is selected. */
    DEVICE_CLK_REFO1,                                    /**< REFO1 is selected. */
    DEVICE_CLK_REFO2,                                    /**< REFO2 is selected. */
    DEVICE_CLK_REFO3,                                    /**< REFO3 is selected. */
    DEVICE_CLK_REFO4,                                    /**< REFO4 is selected. */
    DEVICE_CLK_REFO5,                                    /**< REFO5 is selected. */
    DEVICE_CLK_REFO6,                                    /**< REFO6 is selected. */
    DEVICE_CLK_LPCLK,                                    /**< Low power clock is selected. */
    DEVICE_CLK_END
} DEVICE_ClkSrcId_T;

/* Peripheral enable/disable settings of PMD3. */
typedef struct DEVICE_Pmd3Reg_T
{
    uint8_t sercom1: 1;                                  /**< SERCOM 1. */
    uint8_t sercom2: 1;                                  /**< SERCOM 2. */
    uint8_t sercom3: 1;                                  /**< SERCOM 3. */
    uint8_t sercom4: 1;                                  /**< SERCOM 4. */
    uint8_t tc0: 1;                                      /**< TC 0. */
    uint8_t tc1: 1;                                      /**< TC 1. */
    uint8_t tc2: 1;                                      /**< TC 2. */
    uint8_t tc3: 1;                                      /**< TC 3. */
    uint8_t tcc0: 1;                                     /**< TCC 0. */
    uint8_t tcc1: 1;                                     /**< TCC 1. */
    uint8_t tcc2: 1;                                     /**< TCC 2. */
    uint8_t reserved: 5;                                 /**< Reserved. */
} DEVICE_Pmd3Reg_T;


// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************
static uint32_t s_pmd1Backup;
static uint32_t s_pmd2Backup;
static uint32_t s_pmd3Backup;

static uint32_t s_refo1Backup;
static uint32_t s_refo2Backup;
static uint32_t s_refo3Backup;
static uint32_t s_refo4Backup;
static uint32_t s_refo5Backup;
static uint32_t s_refo6Backup;


// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************
static void device_Delay(uint32_t value)
{
    uint32_t i;

    for (i = 0; i < value; i++)
    {
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();

    }
} 

/* Unlock system for clock configuration */
static void devie_SysUnlock(void)
{
    CFG_REGS->CFG_SYSKEY = 0x00000000;
    CFG_REGS->CFG_SYSKEY = 0xAA996655;
    CFG_REGS->CFG_SYSKEY = 0x556699AA;
}

static void devie_SysLock(void)
{
    CFG_REGS->CFG_SYSKEY = 0x33333333;
}

/* Configure Reference Oscillator Control Register */
static void device_configRefOscReg(DEVICE_SLEEP_ActionId_T action)
{
    if (action == DEVICE_SLEEP_ENTER_SLEEP)
    {
        s_refo1Backup = 0;
        s_refo2Backup = 0;
        s_refo3Backup = 0;
        s_refo4Backup = 0;
        s_refo5Backup = 0;
        s_refo6Backup = 0;

        //REFO1CON
        if ((CRU_REGS->CRU_REFO1CON & CRU_REFO1CON_ON_Msk) && (!(CRU_REGS->CRU_REFO1CON & CRU_REFO1CON_RSLP_Msk)))
        {
            //Disable REFOxCON in sleep mode

            //Backup REFOxCON
            s_refo1Backup = CRU_REGS->CRU_REFO1CON;

            //Can't update REFOxCON register if REFOxCON.ACTIVE != REFOxCON.ON
            while (!(CRU_REGS->CRU_REFO1CON & CRU_REFO1CON_ACTIVE_Msk));
            CRU_REGS->CRU_REFO1CONCLR = CRU_REFO1CON_ON_Msk;    //Disable REFOxCON

            while (CRU_REGS->CRU_REFO1CON & CRU_REFO1CON_ACTIVE_Msk);
            CRU_REGS->CRU_REFO1CONCLR = 0xFFFFFEFF;   //Clear REFOxCON (Bit 8 is read only)
        }

        //REFO2CON
        if ((CRU_REGS->CRU_REFO2CON & CRU_REFO2CON_ON_Msk) && (!(CRU_REGS->CRU_REFO2CON & CRU_REFO2CON_RSLP_Msk)))
        {
            //Disable REFOxCON in sleep mode

            //Backup REFOxCON
            s_refo2Backup = CRU_REGS->CRU_REFO2CON;

            //Can't update REFOxCON register if REFOxCON.ACTIVE != REFOxCON.ON
            while (!(CRU_REGS->CRU_REFO2CON & CRU_REFO2CON_ACTIVE_Msk));
            CRU_REGS->CRU_REFO2CONCLR = CRU_REFO2CON_ON_Msk;    //Disable REFOxCON

            while (CRU_REGS->CRU_REFO2CON & CRU_REFO2CON_ACTIVE_Msk);
            CRU_REGS->CRU_REFO2CONCLR = 0xFFFFFEFF;   //Clear REFOxCON (Bit 8 is read only)
        }

        //REFO3CON
        if ((CRU_REGS->CRU_REFO3CON & CRU_REFO3CON_ON_Msk) && (!(CRU_REGS->CRU_REFO3CON & CRU_REFO3CON_RSLP_Msk)))
        {
            //Disable REFOxCON in sleep mode

            //Backup REFOxCON
            s_refo3Backup = CRU_REGS->CRU_REFO3CON;

            //Can't update REFOxCON register if REFOxCON.ACTIVE != REFOxCON.ON
            while (!(CRU_REGS->CRU_REFO3CON & CRU_REFO3CON_ACTIVE_Msk));
            CRU_REGS->CRU_REFO3CONCLR = CRU_REFO3CON_ON_Msk;    //Disable REFOxCON

            while (CRU_REGS->CRU_REFO3CON & CRU_REFO3CON_ACTIVE_Msk);
            CRU_REGS->CRU_REFO3CONCLR = 0xFFFFFEFF;   //Clear REFOxCON (Bit 8 is read only)
        }

        //REFO4CON
        if ((CRU_REGS->CRU_REFO4CON & CRU_REFO4CON_ON_Msk) && (!(CRU_REGS->CRU_REFO4CON & CRU_REFO4CON_RSLP_Msk)))
        {
            //Disable REFOxCON in sleep mode

            //Backup REFOxCON
            s_refo4Backup = CRU_REGS->CRU_REFO4CON;

            //Can't update REFOxCON register if REFOxCON.ACTIVE != REFOxCON.ON
            while (!(CRU_REGS->CRU_REFO4CON & CRU_REFO4CON_ACTIVE_Msk));
            CRU_REGS->CRU_REFO4CONCLR = CRU_REFO4CON_ON_Msk;    //Disable REFOxCON

            while (CRU_REGS->CRU_REFO4CON & CRU_REFO4CON_ACTIVE_Msk);
            CRU_REGS->CRU_REFO4CONCLR = 0xFFFFFEFF;   //Clear REFOxCON (Bit 8 is read only)
        }

        //REFO5CON
        if ((CRU_REGS->CRU_REFO5CON & CRU_REFO5CON_ON_Msk) && (!(CRU_REGS->CRU_REFO5CON & CRU_REFO5CON_RSLP_Msk)))
        {
            //Disable REFOxCON in sleep mode

            //Backup REFOxCON
            s_refo5Backup = CRU_REGS->CRU_REFO5CON;

            //Can't update REFOxCON register if REFOxCON.ACTIVE != REFOxCON.ON
            while (!(CRU_REGS->CRU_REFO5CON & CRU_REFO5CON_ACTIVE_Msk));
            CRU_REGS->CRU_REFO5CONCLR = CRU_REFO5CON_ON_Msk;    //Disable REFOxCON

            while (CRU_REGS->CRU_REFO5CON & CRU_REFO5CON_ACTIVE_Msk);
            CRU_REGS->CRU_REFO5CONCLR = 0xFFFFFEFF;   //Clear REFOxCON (Bit 8 is read only)
        }

        //REFO6CON
        if ((CRU_REGS->CRU_REFO6CON & CRU_REFO6CON_ON_Msk) && (!(CRU_REGS->CRU_REFO6CON & CRU_REFO6CON_RSLP_Msk)))
        {
            //Disable REFOxCON in sleep mode

            //Backup REFOxCON
            s_refo6Backup = CRU_REGS->CRU_REFO6CON;

            //Can't update REFOxCON register if REFOxCON.ACTIVE != REFOxCON.ON
            while (!(CRU_REGS->CRU_REFO6CON & CRU_REFO6CON_ACTIVE_Msk));
            CRU_REGS->CRU_REFO6CONCLR = CRU_REFO6CON_ON_Msk;    //Disable REFOxCON

            while (CRU_REGS->CRU_REFO6CON & CRU_REFO6CON_ACTIVE_Msk);
            CRU_REGS->CRU_REFO6CONCLR = 0xFFFFFEFF;   //Clear REFOxCON (Bit 8 is read only)
        }
    }
    else
    {
        //Check if it needs to restore REFOx
        //REFO1CON
        if ((s_refo1Backup & CRU_REFO1CON_ON_Msk) && (!(s_refo1Backup & CRU_REFO1CON_RSLP_Msk)))
        {
            //Exclude output enable and active(read only) bit 
            s_refo1Backup &= ~(CRU_REFO1CON_ON_Msk | CRU_REFO1CON_ACTIVE_Msk);

            //Restore REFOx setting
            CRU_REGS->CRU_REFO1CON = s_refo1Backup;

            // Enable oscillator (ON bit)
            CRU_REGS->CRU_REFO1CONSET = CRU_REFO1CON_ON_Msk;
        }

        //REFO2CON
        if ((s_refo2Backup & CRU_REFO2CON_ON_Msk) && (!(s_refo2Backup & CRU_REFO2CON_RSLP_Msk)))
        {
            //Exclude output enable and active(read only) bit 
            s_refo2Backup &= ~(CRU_REFO2CON_ON_Msk | CRU_REFO2CON_ACTIVE_Msk);

            //Restore REFOx setting
            CRU_REGS->CRU_REFO2CON = s_refo2Backup;

            // Enable oscillator (ON bit)
            CRU_REGS->CRU_REFO2CONSET = CRU_REFO2CON_ON_Msk;
        }

        //REFO3CON
        if ((s_refo3Backup & CRU_REFO3CON_ON_Msk) && (!(s_refo3Backup & CRU_REFO3CON_RSLP_Msk)))
        {
            //Exclude output enable and active(read only) bit 
            s_refo3Backup &= ~(CRU_REFO3CON_ON_Msk | CRU_REFO3CON_ACTIVE_Msk);

            //Restore REFOx setting
            CRU_REGS->CRU_REFO3CON = s_refo3Backup;

            // Enable oscillator (ON bit)
            CRU_REGS->CRU_REFO3CONSET = CRU_REFO3CON_ON_Msk;
        }

        //REFO4CON
        if ((s_refo4Backup & CRU_REFO4CON_ON_Msk) && (!(s_refo4Backup & CRU_REFO4CON_RSLP_Msk)))
        {
            //Exclude output enable and active(read only) bit 
            s_refo4Backup &= ~(CRU_REFO4CON_ON_Msk | CRU_REFO4CON_ACTIVE_Msk);

            //Restore REFOx setting
            CRU_REGS->CRU_REFO4CON = s_refo4Backup;

            // Enable oscillator (ON bit)
            CRU_REGS->CRU_REFO4CONSET = CRU_REFO4CON_ON_Msk;
        }

        //REFO5CON
        if ((s_refo5Backup & CRU_REFO5CON_ON_Msk) && (!(s_refo5Backup & CRU_REFO5CON_RSLP_Msk)))
        {
            //Exclude output enable and active(read only) bit 
            s_refo5Backup &= ~(CRU_REFO5CON_ON_Msk | CRU_REFO5CON_ACTIVE_Msk);

            //Restore REFOx setting
            CRU_REGS->CRU_REFO5CON = s_refo5Backup;

            // Enable oscillator (ON bit)
            CRU_REGS->CRU_REFO5CONSET = CRU_REFO5CON_ON_Msk;
        }

        //REFO6CON
        if ((s_refo6Backup & CRU_REFO6CON_ON_Msk) && (!(s_refo6Backup & CRU_REFO6CON_RSLP_Msk)))
        {
            //Exclude output enable and active(read only) bit 
            s_refo6Backup &= ~(CRU_REFO6CON_ON_Msk | CRU_REFO6CON_ACTIVE_Msk);

            //Restore REFOx setting
            CRU_REGS->CRU_REFO6CON = s_refo6Backup;

            // Enable oscillator (ON bit)
            CRU_REGS->CRU_REFO6CONSET = CRU_REFO6CON_ON_Msk;
        }
    }
}

/* Check the if peripheral can be keep running in sleep mode. Return true means it can be keep running. */
static bool device_chkPeripheral(DEVICE_ClkSrcId_T select)
{
    uint32_t pmd2Val;

    pmd2Val = CFG_REGS->CFG_PMD2;

    if ((select == DEVICE_CLK_REFO1) && (!(pmd2Val & CFG_PMD2_REFO1MD_Msk)))    //REFO1 is not disabled in sleep mode
        return true;

    else if ((select == DEVICE_CLK_REFO2) && (!(pmd2Val & CFG_PMD2_REFO2MD_Msk)))   //REFO2 is not disabled in sleep mode
        return true;

    else if ((select == DEVICE_CLK_REFO3) && (!(pmd2Val & CFG_PMD2_REFO3MD_Msk)))   //REFO3 is not disabled in sleep mode
        return true;

    else if ((select == DEVICE_CLK_REFO4) && (!(pmd2Val & CFG_PMD2_REFO4MD_Msk)))   //REFO4 is not disabled in sleep mode
        return true;

    else if ((select == DEVICE_CLK_REFO5) && (!(pmd2Val & CFG_PMD2_REFO5MD_Msk)))   //REFO5 is not disabled in sleep mode
        return true;

    else if ((select == DEVICE_CLK_REFO6) && (!(pmd2Val & CFG_PMD2_REFO6MD_Msk)))   //REFO6 is not disabled in sleep mode
        return true;

    else if (select == DEVICE_CLK_LPCLK)   //LPCLK is used
        return true;

    else
        return false;
}

/* Configure PMD Register */
static void device_configPmdReg(DEVICE_SLEEP_ActionId_T action)
{
    if (action == DEVICE_SLEEP_ENTER_SLEEP)
    {
        DEVICE_Pmd3Reg_T pmdReg;
        DEVICE_ClkSrcId_T select;
        uint32_t pmd2Val, pmd3Val;

        memset((uint8_t *)&pmdReg, 0, sizeof(DEVICE_Pmd3Reg_T));

        //For PMD1, disable all PMD except RTC
        CFG_REGS->CFG_PMD1 = 0xFFFEFFFF;   // bit 16: RTC

        //For PMD2
        //Check if RSLP bit is set, do not disable this REFOx
        pmd2Val = 0xFFFFFFFF;

        if ((CRU_REGS->CRU_REFO1CON & CRU_REFO1CON_ON_Msk) && (CRU_REGS->CRU_REFO1CON & CRU_REFO1CON_RSLP_Msk))
            pmd2Val &= ~CFG_PMD2_REFO1MD_Msk;

        if ((CRU_REGS->CRU_REFO2CON & CRU_REFO2CON_ON_Msk) && (CRU_REGS->CRU_REFO2CON & CRU_REFO2CON_RSLP_Msk))
            pmd2Val &= ~CFG_PMD2_REFO2MD_Msk;

        if ((CRU_REGS->CRU_REFO3CON & CRU_REFO3CON_ON_Msk) && (CRU_REGS->CRU_REFO3CON & CRU_REFO3CON_RSLP_Msk))
            pmd2Val &= ~CFG_PMD2_REFO3MD_Msk;

        if ((CRU_REGS->CRU_REFO4CON & CRU_REFO4CON_ON_Msk) && (CRU_REGS->CRU_REFO4CON & CRU_REFO4CON_RSLP_Msk))
            pmd2Val &= ~CFG_PMD2_REFO4MD_Msk;

        if ((CRU_REGS->CRU_REFO5CON & CRU_REFO5CON_ON_Msk) && (CRU_REGS->CRU_REFO5CON & CRU_REFO5CON_RSLP_Msk))
            pmd2Val &= ~CFG_PMD2_REFO5MD_Msk;

        if ((CRU_REGS->CRU_REFO6CON & CRU_REFO6CON_ON_Msk) && (CRU_REGS->CRU_REFO6CON & CRU_REFO6CON_RSLP_Msk))
            pmd2Val &= ~CFG_PMD2_REFO6MD_Msk;

        CFG_REGS->CFG_PMD2 = pmd2Val;


        //For PMD3, check if the peripheral is enabled
        //bit 0~3 of PMD3 for SERCOM 0~3
        //bit 8~11 of PMD3 for TC0~3
        //bit 12~14 of PMD3 for TCC0~TCC2

        pmd3Val = 0xFFFF;

        if (!(CFG_REGS->CFG_PMD3 & CFG_PMD3_SER1MD_Msk))
            pmdReg.sercom1 = 1;

        if (!(CFG_REGS->CFG_PMD3 & CFG_PMD3_SER2MD_Msk))
            pmdReg.sercom2 = 1;

        if (!(CFG_REGS->CFG_PMD3 & CFG_PMD3_SER3MD_Msk))
            pmdReg.sercom3 = 1;

        if (!(CFG_REGS->CFG_PMD3 & CFG_PMD3_SER4MD_Msk))
            pmdReg.sercom4 = 1;


        if (!(CFG_REGS->CFG_PMD3 & CFG_PMD3_TC0MD_Msk))
            pmdReg.tc0 = 1;

        if (!(CFG_REGS->CFG_PMD3 & CFG_PMD3_TC1MD_Msk))
            pmdReg.tc1 = 1;

        if (!(CFG_REGS->CFG_PMD3 & CFG_PMD3_TC2MD_Msk))
            pmdReg.tc2 = 1;

        if (!(CFG_REGS->CFG_PMD3 & CFG_PMD3_TC3MD_Msk))
            pmdReg.tc3 = 1;


        if (!(CFG_REGS->CFG_PMD3 & CFG_PMD3_TCC0MD_Msk))
            pmdReg.tcc0 = 1;

        if (!(CFG_REGS->CFG_PMD3 & CFG_PMD3_TCC1MD_Msk))
            pmdReg.tcc1 = 1;

        if (!(CFG_REGS->CFG_PMD3 & CFG_PMD3_TCC2MD_Msk))
            pmdReg.tcc2 = 1;


        //Check CFGPCLKGEN1~3 to check if the peripheral clock is enabled and check its clock source
        //Do not turn the peripheral off if RSLP is set (s_refoxBackup = 0) or CLK SRC is set as LP CLK
        if (pmdReg.sercom1 || pmdReg.sercom2)
        {
            //Check CFGCLKGEN1 bit 15, if enabled, check the clock source by bit 12~14
            if (CFG_REGS->CFG_CFGPCLKGEN1 & CFG_CFGPCLKGEN1_S01CD_Msk)
            {
                select = (CFG_REGS->CFG_CFGPCLKGEN1 & CFG_CFGPCLKGEN1_SERCOM01CSEL_Msk) >> CFG_CFGPCLKGEN1_SERCOM01CSEL_Pos;

                if (device_chkPeripheral(select))
                {
                    if (pmdReg.sercom1)
                        pmd3Val &= ~CFG_PMD3_SER1MD_Msk;

                    if (pmdReg.sercom2)
                        pmd3Val &= ~CFG_PMD3_SER2MD_Msk;
                }
            }
        }

        if (pmdReg.sercom3 || pmdReg.sercom4)
        {
            //Check CFGCLKGEN1 bit 19, if enabled, check the clock source by bit 16~18
            if (CFG_REGS->CFG_CFGPCLKGEN1 & CFG_CFGPCLKGEN1_S23CD_Msk)
            {
                select = (CFG_REGS->CFG_CFGPCLKGEN1 & CFG_CFGPCLKGEN1_SERCOM23CSEL_Msk) >> CFG_CFGPCLKGEN1_SERCOM23CSEL_Pos;

                if (device_chkPeripheral(select))
                {
                    if (pmdReg.sercom3)
                        pmd3Val &= ~CFG_PMD3_SER3MD_Msk;

                    if (pmdReg.sercom4)
                        pmd3Val &= ~CFG_PMD3_SER4MD_Msk;
                }
            }
        }

        if (pmdReg.tc0)
        {
            //Check CFGCLKGEN3 bit 27, if enabled, check the clock source by bit 24~26
            if (CFG_REGS->CFG_CFGPCLKGEN3 & CFG_CFGPCLKGEN3_TC0CD_Msk)
            {
                select = (CFG_REGS->CFG_CFGPCLKGEN3 & CFG_CFGPCLKGEN3_TC0CSEL_Msk) >> CFG_CFGPCLKGEN3_TC0CSEL_Pos;

                if (device_chkPeripheral(select))
                {
                    pmd3Val &= ~CFG_PMD3_TC0MD_Msk;
                }
            }
        }

        if (pmdReg.tc1)
        {
            //Check CFGCLKGEN3 bit 31, if enabled, check the clock source by bit 28~30
            if (CFG_REGS->CFG_CFGPCLKGEN3 & CFG_CFGPCLKGEN3_TC1CD_Msk)
            {
                select = (CFG_REGS->CFG_CFGPCLKGEN3 & CFG_CFGPCLKGEN3_TC1CSEL_Msk) >> CFG_CFGPCLKGEN3_TC1CSEL_Pos;

                if (device_chkPeripheral(select))
                {
                    pmd3Val &= ~CFG_PMD3_TC1MD_Msk;
                }
            }
        }

        if (pmdReg.tc2 || pmdReg.tc3)
        {
            //Check CFGCLKGEN1 bit 27, if enabled, check the clock source by bit 24~26
            if (CFG_REGS->CFG_CFGPCLKGEN1 & CFG_CFGPCLKGEN1_TC23CD_Msk)
            {
                select = (CFG_REGS->CFG_CFGPCLKGEN1 & CFG_CFGPCLKGEN1_TC23CSEL_Msk) >> CFG_CFGPCLKGEN1_TC23CSEL_Pos;

                if (device_chkPeripheral(select))
                {
                    if (pmdReg.tc2)
                        pmd3Val &= ~CFG_PMD3_TC2MD_Msk;

                    if (pmdReg.tc3)
                        pmd3Val &= ~CFG_PMD3_TC3MD_Msk;
                }
            }
        }

        if (pmdReg.tcc0)
        {
            //Check CFGCLKGEN3 bit 23, if enabled, check the clock source by bit 20~22
            if (CFG_REGS->CFG_CFGPCLKGEN3 & CFG_CFGPCLKGEN3_TCC0CD_Msk)
            {
                select = (CFG_REGS->CFG_CFGPCLKGEN3 & CFG_CFGPCLKGEN3_TCC0CSEL_Msk) >> CFG_CFGPCLKGEN3_TCC0CSEL_Pos;

                if (device_chkPeripheral(select))
                {
                    pmd3Val &= ~CFG_PMD3_TCC0MD_Msk;
                }
            }
        }

        if (pmdReg.tcc1 || pmdReg.tcc2)
        {
            //Check CFGCLKGEN1 bit 23, if enabled, check the clock source by bit 20~22
            if (CFG_REGS->CFG_CFGPCLKGEN1 & CFG_CFGPCLKGEN1_TCC12CD_Msk)
            {
                select = (CFG_REGS->CFG_CFGPCLKGEN1 & CFG_CFGPCLKGEN1_TCC12CSEL_Msk) >> CFG_CFGPCLKGEN1_TCC12CSEL_Pos;

                if (device_chkPeripheral(select))
                {
                    if (pmdReg.tcc1)
                        pmd3Val &= ~CFG_PMD3_TCC1MD_Msk;

                    if (pmdReg.tcc2)
                        pmd3Val &= ~CFG_PMD3_TCC2MD_Msk;
                }
            }
        }

        CFG_REGS->CFG_PMD3 = pmd3Val;
    }
    else
    {
        CFG_REGS->CFG_PMD1 = s_pmd1Backup;
        CFG_REGS->CFG_PMD2 = s_pmd2Backup;
        CFG_REGS->CFG_PMD3 = s_pmd3Backup;
    }
}

void DEVICE_EnterSleepMode(void)
{
    // unlock key sequence
    devie_SysUnlock();

    // Step 1 : For connected sleep case, if SOSC clock is available on the module, set 32K CLK source to SOSC CLK in CRU and set MLPCLK_MOD to 1 to divide 32.768kHz clock to 32kHz clock to save power. Otherwise, set 32K CLK source to POSC CLK in CRU to ensure accuracy of 32K CLK
    //          For unconnected sleep case, set 32K CLK source to LPRC CLK in CRU to save power since accuracy requirement does not need to be met
    // step 1 has moved to CLK_Initialize()
    // Some steps are executed within library

    // Step 6 : Disable bt_zb_dbg bus toggling
    DEVICE_SLEEP_DisableDebugBus();

    // Step 14 : Disable PCHE Cache, which is proposed by SOC team for low power optimization
    PCHE_REGS->PCHE_CHECON = 0xf;
    
    // Step 15 : Set PB1 CLK to SYS_CLK/5, which is proposed by SOC team for low power optimization
    CRU_REGS->CRU_PB1DIV = 0x8804;

    // Step 16 : set REFOx registers to 0, combining step 17 to de-assert external PLL request 
    // since we don't know how and when plib_clock will be changed. so we will backup all 6 sets REFOx registers.
    // Ensure the Reference Clock Out Module is enabled, REFO1 Clock is selected by CFG_CFGPCLKGEN1

    // Check PMD lock bit
    if (CFG_REGS->CFG_CFGCON0 & CFG_CFGCON0_PMDLOCK_Msk)
    {
        // PMD lock is enabled, check CFGCLOCK
        if ((CFG_REGS->CFG_CFGCON0 & CFG_CFGCON0_CFGCLOCK_Msk) == 0)
        {
            // Disable PMD lock
            CFG_REGS->CFG_CFGCON0 &= ~CFG_CFGCON0_PMDLOCK_Msk;
        }
    }

    if (CFG_REGS->CFG_PMD2 & CFG_PMD2_REFO1MD_Msk)
    {
        // Enable PMD2_REFO1
        CFG_REGS->CFG_PMD2 &= ~CFG_PMD2_REFO1MD_Msk;
    }

    // Store all PMD setting
    s_pmd1Backup = CFG_REGS->CFG_PMD1;
    s_pmd2Backup = CFG_REGS->CFG_PMD2;
    s_pmd3Backup = CFG_REGS->CFG_PMD3;

    // Backup and Configure REFOxCON register
    device_configRefOscReg(DEVICE_SLEEP_ENTER_SLEEP);

    // Configure PMD register
    device_configPmdReg(DEVICE_SLEEP_ENTER_SLEEP);


    // Step 17 : Change SYS CLK source in CRU from SPLL1 CLK to POSC CLK 
    CRU_REGS->CRU_OSCCON &= (~0xf01); 
    CRU_REGS->CRU_OSCCON |= 0x200;

    // Request oscillator switch to occur
    CRU_REGS->CRU_OSCCONSET = CRU_OSCCON_OSWEN_Msk;

    // Wait for indication of successful clock change before proceeding
    while(CRU_REGS->CRU_OSCCON & CRU_OSCCON_OSWEN_Msk);

    // Step 18 : Set subsys_clk_src_sel to 0 to change subsys clock source from PLL CLK to XTAL CLK
    BTZBSYS_REGS->BTZBSYS_SUBSYS_CNTRL_REG1 &= (~0x30);
    
    // Step 19 :Disable CLKGEN Clock enable in RF
    DEVICE_SLEEP_ConfigRfClk(false);

    //Step 19.1 : If XTAL clock is OFF, set subsys_bypass_pll_lock to 0 via subsys config register
    if ((CFG_REGS->CFG_CFGCON4 & 0x3000) == 0x2000) // SOSC : XTAL_OFF
    {
        DEVICE_SLEEP_ConfigSubSysPllLock(false);
    }

    // Step 20 : Set die_BENXOANA_ovrd_en to 1 to switch LDO_PLL to CLDO
    BTZBSYS_REGS->BTZBSYS_SUBSYS_CNTRL_REG0 |= 0x800;

    // Step 21 : Set EN_RFLDO_ovrd_en to 1
    BTZBSYS_REGS->BTZBSYS_SUBSYS_CNTRL_REG0 |= 0x8000;
    
    // Step 22 : Combining step 21, de-assert external PLL power request to disable CLKGEN LDO enable in RF
    CRU_REGS->CRU_SPLLCON |= 0x08; 
    
    // Step 23 : set KEEP_ACLB_CLOCKS_ON to 1 to enable ACLB clocks for SPI access
    DEVICE_SLEEP_ConfigAclbClk(true);

    // Step 24 : Turn off MBS in RF
    DEVICE_SLEEP_ConfigRfMbs(false);

    // Step 25 : set KEEP_ACLB_CLOCKS_ON to 0 to disable ACLB clocks for SPI access
    DEVICE_SLEEP_ConfigAclbClk(false);
    
    // Step 26 : set bt_en_main_clk to 0 to disable BT main clock
    BTZBSYS_REGS->BTZBSYS_SUBSYS_CNTRL_REG0 &= (~0x00100000);  

    // Step 27 : change CLK source in CRU from POSC CLK to FRC CLK
    CRU_REGS->CRU_OSCCON &= (~0xf01);

    // Request oscillator switch to occur
    CRU_REGS->CRU_OSCCONSET = CRU_OSCCON_OSWEN_Msk;

    // Wait for indication of successful clock change before proceeding
    while(CRU_REGS->CRU_OSCCON & CRU_OSCCON_OSWEN_Msk);

    // If XTAL clock is OFF
    if ((CFG_REGS->CFG_CFGCON4 & 0x3000) == 0x2000)  // SOSC : XTAL_OFF
    {
        // Step 27.1 : If XTAL clock is OFF when bt_zb_subsys enters into sleep mode, 
        // set subsys_clk_src_sel to 1 via subsys config register (SUBSYS_CNTRL_REG1_ADDR[4]) to select PLL CLK as SRC clock
        BTZBSYS_REGS->BTZBSYS_SUBSYS_CNTRL_REG1 |= 0x10;
    
        // Step 28 : If XTAL clock is OFF when bt_zb_subsys enters into sleep mode, set BXTLEN to 0 via BT config register to disable XTAL
        device_Delay(4); // add 2us delay
        DEVICE_SLEEP_ConfigRfXtal(false);

        // Step 28.1 : If XTAL clock is OFF when bt_zb_subsys enters into sleep mode, set subsys_bypass_xtal_ready to 0 via subsys config register
        DEVICE_SLEEP_ConfigSubSysXtalReady(false);

    }
    // Step 29 : set deep sleep enable to 0
    DSCON_REGS->DSCON_DSCON &= ~(0x8000);

    // Step 30 : set sleep enable to 1, make CPU into sleep
    CRU_REGS->CRU_OSCCON |= 0x10;

    // Lock system since done with clock configuration
    devie_SysLock();
}

void DEVICE_ExitSleepMode(void)
{
    // unlock key sequence
    devie_SysUnlock();

    // step 1: Clear sleep flag
    RCON_REGS->RCON_RCON &= (~RCON_RCON_SLEEP_Msk);

    // If XTAL clock is off
    if ((CFG_REGS->CFG_CFGCON4 & 0x3000) == 0x2000) //SOSC : XTAL_OFF
    {
        
        // Step 2 : If XTAL clock is off when bt_zb_subsys enters into low power mode, wait for xtal_ready_out_sync
        // Enable bit 7 to creates one clk_lp_cycle wide pulse on ZBT Subsystem.external_NMI0 pin
        CFG_REGS->CFG_CFGCON1 |= CFG_CFGCON1_ZBTWKSYS_Msk;
        
        // Wait for xtal_ready      
        uint32_t clk_ready_tries = 0;
        do
        {
           clk_ready_tries++;
        } while(BTZB_XTAL_NOT_READY && (clk_ready_tries < CLK_READY_RETRIES));

        if((clk_ready_tries >= CLK_READY_RETRIES) && BTZB_XTAL_NOT_READY)
        {
           DEVICE_SLEEP_ConfigSubSysXtalReady(true);

           while(BTZB_XTAL_NOT_READY);
        }
        // Step 2.1 :
        // If XTAL clock is OFF when bt_zb_subsys enters into sleep mode, 
        // set subsys_clk_src_sel to 0 via subsys config register (SUBSYS_CNTRL_REG1_ADDR[4]) to select XTAL CLK as SRC clock
        BTZBSYS_REGS->BTZBSYS_SUBSYS_CNTRL_REG1 &= (~0x10);
    }

    // Step 3 : Change CLK source in CRU from FRC CLK to POSC CLK
    CRU_REGS->CRU_OSCCON &= (~0xf01);
    CRU_REGS->CRU_OSCCON |= 0x200;

    // Request oscillator switch to occur
    CRU_REGS->CRU_OSCCONSET = CRU_OSCCON_OSWEN_Msk;

    // Wait for indication of successful clock change before proceeding
    while(CRU_REGS->CRU_OSCCON & CRU_OSCCON_OSWEN_Msk);

    // Step 4 : set bt_en_main_clk to 1 to enable BT main clock
    BTZBSYS_REGS->BTZBSYS_SUBSYS_CNTRL_REG0 |= 0x00100000;
    
    // Step 5 : set KEEP_ACLB_CLOCKS_ON to 1 via BT config register 
    DEVICE_SLEEP_ConfigAclbClk(true);
    
    // Step 6 : Turn on MBS in RF
    DEVICE_SLEEP_ConfigRfMbs(true);

    // Step 7 : Wait for MBS settling time. Settling time value is 35us
    device_Delay(4);
    
    // Step 8 : Set KEEP_ACLB_CLOCKS_ON to 0 via BT config register 
    DEVICE_SLEEP_ConfigAclbClk(false);

    // Step 9 : Assert external PLL power request
    CRU_REGS->CRU_SPLLCON &= ~(0x08);
       
    // Step 10 : Combining step 9, set EN_RFLDO_ovrd_en to 0 to enable CLKGEN LDO enable in RF 
    BTZBSYS_REGS->BTZBSYS_SUBSYS_CNTRL_REG0 &= (~0x8000);

    // Step 11 : Wait for LDO settling time. Settling time value is 10us
    device_Delay(1);
   
    // Step 12 : Set die_BENXOANA_ovrd_en to 0 to switch CLDO to LDO_PLL 
    BTZBSYS_REGS->BTZBSYS_SUBSYS_CNTRL_REG0 &= (~0x800);
    
    // Step 13 : Enable CLKGEN CLK enable in RF 
    DEVICE_SLEEP_ConfigRfClk(true);

    // Step 14 : Poll pll_lock_out_sync to wait until pll_lock_out_sync is set
    // wait for PLL Lock
    uint32_t clk_ready_tries = 0;
    do
    {
        clk_ready_tries++;
    } while(BTZB_PLL_NOT_LOCKED && (clk_ready_tries < CLK_READY_RETRIES));
    
    if ((clk_ready_tries >= CLK_READY_RETRIES) && BTZB_PLL_NOT_LOCKED)
    {
        DEVICE_SLEEP_ConfigSubSysPllLock(true);

        while(BTZB_PLL_NOT_LOCKED);
    }

    // Step 15 : Restore REFOx registers programming for run mode

    // Check PMD lock bit
    if (CFG_REGS->CFG_CFGCON0 & CFG_CFGCON0_PMDLOCK_Msk)
    {
        // PMD lock is enabled, check CFGCLOCK
        if ((CFG_REGS->CFG_CFGCON0 & CFG_CFGCON0_CFGCLOCK_Msk) == 0)
        {
            // Disable PMD lock
            CFG_REGS->CFG_CFGCON0 &= ~CFG_CFGCON0_PMDLOCK_Msk;    
        }
    }

    // Restore all PMD setting
    device_configPmdReg(DEVICE_SLEEP_EXIT_SLEEP);


    //TODO: Can be removed
#if 0
    if (CFG_REGS->CFG_PMD2 & CFG_PMD2_REFO1MD_Msk)
    {
        CFG_REGS->CFG_PMD2 &= ~CFG_PMD2_REFO1MD_Msk;   //Enable PMD2_REFO1
    }
#endif

    //Restore the setting of REFOxCON register
    device_configRefOscReg(DEVICE_SLEEP_EXIT_SLEEP);

    // Step 16 : Set PB1 CLK to SYS_CLK to restore its clock rate for run mode 
    CRU_REGS->CRU_PB1DIV = 0x8800; 

    // Step 17 : Restore PCHE Cache programming for run mode
    PCHE_REGS->PCHE_CHECON = 0x07000011;

    // Step 18 : Change CLK source in CRU from POSC CLK to SPLL1 CLK
    CRU_REGS->CRU_OSCCON &= (~0xf01);
    CRU_REGS->CRU_OSCCON |= 0x100;

    // Request oscillator switch to occur
    CRU_REGS->CRU_OSCCONSET = CRU_OSCCON_OSWEN_Msk;

    // Wait for indication of successful clock change before proceeding
    while(CRU_REGS->CRU_OSCCON & CRU_OSCCON_OSWEN_Msk);

    // Step 19 : Set subsys_clk_src_sel to 1 to change subsys clock source from XTAL CLK to PLL CLK
    BTZBSYS_REGS->BTZBSYS_SUBSYS_CNTRL_REG1 &= (~0x30);
    BTZBSYS_REGS->BTZBSYS_SUBSYS_CNTRL_REG1 |= 0x10;

    // Remove sleep enable
    // not match to word! word should have CRU_OSCCON
    CRU_REGS->CRU_OSCCON &= (~0x10); 

    // Lock system since done with clock configuration
    devie_SysLock();
}
