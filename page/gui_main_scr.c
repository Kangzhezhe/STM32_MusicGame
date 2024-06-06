/************************************************************************
 * FilePath     : gui_main_scr.c
 * Author       : GX.Duan
 * Date         : 2022-08-19 00:25:00
 * LastEditTime : 2022-10-03 14:42:59
 * LastEditors  : ShallowGreen123 2608653986@qq.com
 * Copyright (c): 2022 by GX.Duan, All Rights Reserved.
 * Github       : https://github.com/ShallowGreen123/lvgl_mydemo
 ************************************************************************/
#define __MAIN_SCR_C_

/*********************************************************************************
 *                                  INCLUDES
 * *******************************************************************************/
#include "gui_main_scr.h"

/*********************************************************************************
 *                                   DEFINES
 * *******************************************************************************/

/*********************************************************************************
 *                                   MACROS
 * *******************************************************************************/

/*********************************************************************************
 *                                  TYPEDEFS
 * *******************************************************************************/
static lv_obj_t *MainScrRoot = NULL;
static lv_obj_t *label       = NULL;

static lv_obj_t *switch_btn  = NULL;
static lv_obj_t *label2      = NULL;

static lv_obj_t *switch_btn_piano  = NULL;
static lv_obj_t *label_piano      = NULL;

static lv_obj_t *switch_btn_game  = NULL;
static lv_obj_t *label_game      = NULL;

/*********************************************************************************
 *                              STATIC FUNCTION
 * *******************************************************************************/
void swithc_btn_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);

    if (obj == switch_btn) {
        printf("Screen 1 switch_btn is pressed! printf\r\n");
        ScrMgrSwitchScr(GUI_TEST1_SCR_ID, true);
    }else if (obj == switch_btn_piano) {
        printf("switch_btn_piano is pressed! printf\r\n");
        ScrMgrSwitchScr(GUI_PIANO_SCR_ID, true);
    }else if (obj == switch_btn_game) {
        printf("switch_btn_game is pressed! printf\r\n");
        ScrMgrSwitchScr(GUI_GAME_SCR_ID, true);
    }
}

/*********************************************************************************
 *                              GLOBAL FUNCTION
 * *******************************************************************************/
static lv_obj_t *Gui_MainScrCreate(lv_obj_t *parent)
{
    MainScrRoot = lv_obj_create(parent);
    lv_obj_set_size(MainScrRoot, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(MainScrRoot, lv_color_black(), LV_PART_MAIN);

    label = lv_label_create(MainScrRoot);
    lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text(label, "Main Screen");

    switch_btn = lv_btn_create(MainScrRoot);
    lv_obj_set_size(switch_btn, 80, 40);
    label2 = lv_label_create(switch_btn);
    lv_label_set_text(label2, "player");

    switch_btn_piano = lv_btn_create(MainScrRoot);
    lv_obj_set_size(switch_btn_piano, 80, 40);
    label_piano = lv_label_create(switch_btn_piano);
    lv_label_set_text(label_piano, "piano");

    switch_btn_game = lv_btn_create(MainScrRoot);
    lv_obj_set_size(switch_btn_game, 80, 40);
    label_game = lv_label_create(switch_btn_game);
    lv_label_set_text(label_game, "game");

    // TRACE_I("main screen is created");
    printf("main screen is created\r\n");

    return MainScrRoot;
}

static void Gui_MainScrLayout(void)
{
    lv_obj_align_to(label, MainScrRoot, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_center(label2);
    lv_obj_center(label_piano);
    lv_obj_center(label_game);
    lv_obj_align_to(switch_btn, MainScrRoot, LV_ALIGN_LEFT_MID, 10, 0);
    lv_obj_align_to(switch_btn_piano, MainScrRoot, LV_ALIGN_LEFT_MID, 120, 0);
    lv_obj_align_to(switch_btn_game, MainScrRoot, LV_ALIGN_LEFT_MID, 230, 0);
}

static void Gui_MainScrEnter(void)
{
    Gui_MainScrLayout();

    lv_obj_add_event_cb(switch_btn, swithc_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(switch_btn_piano, swithc_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(switch_btn_game, swithc_btn_event_cb, LV_EVENT_CLICKED, NULL);
    // TRACE_I("main screen enter");
    printf("main screen enter\r\n");
}

static void Gui_MainScrExit(void)
{
    lv_obj_remove_event_cb(switch_btn, swithc_btn_event_cb);
    lv_obj_remove_event_cb(switch_btn_piano, swithc_btn_event_cb);
    lv_obj_remove_event_cb(switch_btn_game, swithc_btn_event_cb);
    // TRACE_I("main screen exit");
    printf("main screen exit\r\n");
}

static void Gui_MainScrDestory(void)
{
    // TRACE_I("main screen destory");
    // lv_obj_clean(MainScrRoot);
    // lv_obj_del(MainScrRoot);
    printf("main screen destory\r\n");
}

const SCR_MGR_SCR_HANDLE_T Gui_MainScrHandle = {
    .ScrId      = GUI_MIAN_SCR_ID,
    .ScrCreate  = Gui_MainScrCreate,
    .ScrEnter   = Gui_MainScrEnter,
    .ScrExit    = Gui_MainScrExit,
    .ScrDestroy = Gui_MainScrDestory,
};

SCR_MGR_REG(Gui_MainScrHandle);