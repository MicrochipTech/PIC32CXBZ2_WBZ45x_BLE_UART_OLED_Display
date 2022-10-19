#include "gfx/legato/generated/screen/le_gen_screen_Screen0.h"

// screen member widget declarations
static leWidget* root0;

leWidget* Screen0_BackgroundPanel;
leImageWidget* Screen0_mchplogo;
leTextFieldWidget* Screen0_txtStr1;
leTextFieldWidget* Screen0_txtStr2;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Screen0(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Screen0(void)
{
    if(showing == LE_TRUE)
        return LE_FAILURE;

    // layer 0
    root0 = leWidget_New();
    root0->fn->setSize(root0, 96, 96);
    root0->fn->setBackgroundType(root0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->setMargins(root0, 0, 0, 0, 0);
    root0->flags |= LE_WIDGET_IGNOREEVENTS;
    root0->flags |= LE_WIDGET_IGNOREPICK;

    Screen0_BackgroundPanel = leWidget_New();
    Screen0_BackgroundPanel->fn->setPosition(Screen0_BackgroundPanel, 0, 0);
    Screen0_BackgroundPanel->fn->setSize(Screen0_BackgroundPanel, 96, 96);
    Screen0_BackgroundPanel->fn->setScheme(Screen0_BackgroundPanel, &WhiteScheme);
    root0->fn->addChild(root0, (leWidget*)Screen0_BackgroundPanel);

    Screen0_mchplogo = leImageWidget_New();
    Screen0_mchplogo->fn->setPosition(Screen0_mchplogo, 0, 0);
    Screen0_mchplogo->fn->setSize(Screen0_mchplogo, 96, 28);
    Screen0_mchplogo->fn->setBackgroundType(Screen0_mchplogo, LE_WIDGET_BACKGROUND_NONE);
    Screen0_mchplogo->fn->setBorderType(Screen0_mchplogo, LE_WIDGET_BORDER_NONE);
    Screen0_mchplogo->fn->setImage(Screen0_mchplogo, (leImage*)&oled_c);
    root0->fn->addChild(root0, (leWidget*)Screen0_mchplogo);

    Screen0_txtStr1 = leTextFieldWidget_New();
    Screen0_txtStr1->fn->setPosition(Screen0_txtStr1, 0, 28);
    Screen0_txtStr1->fn->setSize(Screen0_txtStr1, 96, 33);
    Screen0_txtStr1->fn->setBorderType(Screen0_txtStr1, LE_WIDGET_BORDER_NONE);
    Screen0_txtStr1->fn->setString(Screen0_txtStr1, (leString*)&string_txtString1);
    Screen0_txtStr1->fn->setHintString(Screen0_txtStr1, (leString*)&string_txtString1);
    Screen0_txtStr1->fn->setFont(Screen0_txtStr1, (leFont*)&NotoMono_Regular);
    root0->fn->addChild(root0, (leWidget*)Screen0_txtStr1);

    Screen0_txtStr2 = leTextFieldWidget_New();
    Screen0_txtStr2->fn->setPosition(Screen0_txtStr2, 0, 61);
    Screen0_txtStr2->fn->setSize(Screen0_txtStr2, 96, 35);
    Screen0_txtStr2->fn->setBorderType(Screen0_txtStr2, LE_WIDGET_BORDER_NONE);
    Screen0_txtStr2->fn->setString(Screen0_txtStr2, (leString*)&string_txtString2);
    Screen0_txtStr2->fn->setHintString(Screen0_txtStr2, (leString*)&string_txtString2);
    Screen0_txtStr2->fn->setFont(Screen0_txtStr2, (leFont*)&NotoMono_Regular);
    root0->fn->addChild(root0, (leWidget*)Screen0_txtStr2);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Screen0(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_Screen0(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Screen0_BackgroundPanel = NULL;
    Screen0_mchplogo = NULL;
    Screen0_txtStr1 = NULL;
    Screen0_txtStr2 = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Screen0(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Screen0(uint32_t lyrIdx)
{
    if(lyrIdx >= LE_LAYER_COUNT)
        return NULL;

    switch(lyrIdx)
    {
        case 0:
        {
            return root0;
        }
        default:
        {
            return NULL;
        }
    }
}

