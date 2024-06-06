/************************************************************************
 * FilePath     : gui_piano_scr.c
 * Author       : GX.Duan
 * Date         : 2022-09-10 17:10:59
 * LastEditTime : 2022-09-21 22:46:10
 * LastEditors  : ShallowGreen123 2608653986@qq.com
 * Copyright (c): 2022 by GX.Duan, All Rights Reserved.
 * Github       : https://github.com/ShallowGreen123/lvgl_mydemo
 ************************************************************************/
#define __MAIN_SCR_C_

/*********************************************************************************
 *                                  INCLUDES
 * *******************************************************************************/
#include "lvgl_app.h"

static lv_obj_t *PianoScrRoot = NULL;
static lv_obj_t *PianoLabel   = NULL;

static lv_obj_t *piano_btn    = NULL;
static lv_obj_t *BtnLabel     = NULL;

/*********************************************************************************
 *                                   DEFINES
 * *******************************************************************************/
// #include "../lv_examples.h"
#include "lvgl.h"
#include <stdio.h>
// #include "mp3Player.h"

void playSound(const char* soundFilePath) {
    MP3_decode_file(soundFilePath);
    printf("playSound: %s\r\n", soundFilePath);
}


// ##########
// �?�?鍏崇殑浜嬩�?�澶�?悊鍑芥暟
// ##########
typedef enum {
    STATE_LOW,
    STATE_MID,
    STATE_HIGH
} switch0_state_t;

static switch0_state_t switch0_state = STATE_MID;

static void event_handler_switch1(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        switch0_state = STATE_LOW;
        lv_obj_set_style_bg_color(PianoScrRoot, lv_palette_main(LV_PALETTE_PURPLE), 0);
    }
}

static void event_handler_switch2(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        switch0_state = STATE_MID;
        lv_obj_set_style_bg_color(PianoScrRoot, lv_palette_main(LV_PALETTE_GREEN), 0);
    }
}

static void event_handler_switch3(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        switch0_state = STATE_HIGH;
        lv_obj_set_style_bg_color(PianoScrRoot, lv_palette_main(LV_PALETTE_YELLOW), 0);
    }
}



// #############
// 鎸�?�挳鐨勪簨浠�??�?悊鍑芥暟
// #############
static void event_handler_btn0(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    int btn_id = (intptr_t)lv_event_get_user_data(e);


    if(code == LV_EVENT_PRESSED) {

        switch(switch0_state) {
            case STATE_LOW:
                switch(btn_id) {
                    case 1:
                        LV_LOG_USER("btn1-LOW");
                        playSound("0:/processed/c3_processed.mp3");
                        break;
                    case 2:
                        LV_LOG_USER("btn2-LOW");
                        playSound("0:/processed/d3_processed.mp3");
                        break;
                    case 3:
                        LV_LOG_USER("btn3-LOW");
                        playSound("0:/processed/e3_processed.mp3");
                        break;
                    case 4:
                        LV_LOG_USER("btn4-LOW");
                        playSound("0:/processed/f3_processed.mp3");
                        break;
                    case 5:
                        LV_LOG_USER("btn5-LOW");
                        playSound("0:/processed/g3_processed.mp3");
                        break;
                    case 6:
                        LV_LOG_USER("btn6-LOW");
                        playSound("0:/processed/a3_processed.mp3");
                        break;
                    case 7:
                        LV_LOG_USER("btn7-LOW");
                        playSound("0:/processed/b3_processed.mp3");
                        break;
                }
                break;
        
            case STATE_MID:
                switch(btn_id) {
                    case 1:
                        LV_LOG_USER("btn1-MID");
                        playSound("0:/processed/c4_processed.mp3");
                        break;
                    case 2:
                        LV_LOG_USER("btn2-MID");
                        playSound("0:/processed/d4_processed.mp3");
                        break;
                    case 3:
                        LV_LOG_USER("btn3-MID");
                        playSound("0:/processed/e4_processed.mp3");
                        break;
                    case 4:
                        LV_LOG_USER("btn4-MID");
                        playSound("0:/processed/f4_processed.mp3");
                        break;
                    case 5:
                        LV_LOG_USER("btn5-MID");
                        playSound("0:/processed/g4_processed.mp3");
                        break;
                    case 6:
                        LV_LOG_USER("btn6-MID");
                        playSound("0:/processed/a4_processed.mp3");
                        break;
                    case 7:
                        LV_LOG_USER("btn7-MID");
                        playSound("0:/processed/b4_processed.mp3");
                        break;
                }
                break;

            case STATE_HIGH:
                switch(btn_id) {
                    case 1:
                        LV_LOG_USER("btn1-HIGH");
                        playSound("0:/processed/c5_processed.mp3");
                        break;
                    case 2:
                        LV_LOG_USER("btn2-HIGH");
                        playSound("0:/processed/d5_processed.mp3");
                        break;
                    case 3:
                        LV_LOG_USER("btn3-HIGH");
                        playSound("0:/processed/e5_processed.mp3");
                        break;
                    case 4:
                        LV_LOG_USER("btn4-HIGH");
                        playSound("0:/processed/f5_processed.mp3");
                        break;
                    case 5:
                        LV_LOG_USER("btn5-HIGH");
                        playSound("0:/processed/g5_processed.mp3");
                        break;
                    case 6:
                        LV_LOG_USER("btn6-HIGH");
                        playSound("0:/processed/a5_processed.mp3");
                        break;
                    case 7:
                        LV_LOG_USER("btn7-HIGH");
                        playSound("0:/processed/b5_processed.mp3");
                        break;
                }
                break;
        }

    }
        
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}

static lv_style_t style_def;
static lv_style_t style_label;
static lv_style_t style_pr;
void my_piano(void)
{
    /*鍒濆?�?寲�?��???ょ姸�?佺殑鏍峰�?*/
    lv_style_init(&style_def);

    // 璁剧疆鎸夐挳杈�???�??滆�?�鍜�??藉�??
    lv_style_set_border_color(&style_def, lv_color_black()); // 璁剧疆杈�??�??滆�?�涓�?粦鑹?
    lv_style_set_border_width(&style_def, 2); // 璁剧疆杈�??�??藉�?�涓?2鍍忕�?

    lv_style_set_shadow_width(&style_def, 5);  // 璁剧疆闃村�?�瀹藉害涓? 8 鍍忕�?
    lv_style_set_shadow_color(&style_def, lv_color_make(0, 0, 0));  // 璁剧疆闃村�?�棰滆�?�涓�?粦鑹?
    lv_style_set_shadow_offset_y(&style_def, 8);  // 璁剧疆闃村�?�鍦? Y 杞存柟鍚戠殑鍋忕Щ�?? 8 鍍忕�?

    lv_style_set_outline_opa(&style_def, LV_OPA_COVER);
    lv_style_set_outline_color(&style_def, lv_palette_main(LV_PALETTE_DEEP_ORANGE));

    lv_style_set_text_color(&style_def, lv_color_white());

    /*鍦ㄥ?藉�?�鍙樻崲鍜岄噸鏂�?潃鑹�?笂鍒涘缓杩囨�?鍔ㄧ敾銆?*/
    static lv_style_prop_t tr_prop[] = {LV_STYLE_BG_COLOR, LV_STYLE_BORDER_COLOR, LV_STYLE_BORDER_WIDTH, 0};
    static lv_style_transition_dsc_t tr;
    lv_style_transition_dsc_init(&tr, tr_prop, lv_anim_path_linear, 200, 0, NULL);
    lv_style_set_transition(&style_def, &tr);
    // lv_style_set_transition(&style_pr, &tr);




    /*鍒濆?�?寲鎸変笅鐨勬牱�???*/
    /*褰撴寜涓�?寜閽?鏃朵娇鎸夐挳鍙樻�?骞跺彉灏?*/
    
    lv_style_init(&style_pr);
    // lv_style_set_image_recolor_opa(&style_pr, LV_OPA_20);
    // lv_style_set_image_recolor(&style_pr, lv_color_black());
    lv_style_set_bg_opa(&style_pr, LV_OPA_90); // 璁剧疆鑳屾櫙涓嶉�?忔�?�搴︿负20%
    lv_style_set_bg_color(&style_pr, lv_color_make(160, 160, 160)); // 璁剧疆鑳屾櫙棰滆壊涓虹伆�??
    lv_style_set_transform_width(&style_pr, -2);
    lv_style_set_transform_height(&style_pr, -5);

    /*鎸�?�笅鏃舵坊鍔犲ぇ�??�??*/
    lv_style_set_outline_width(&style_pr, 30);
    lv_style_set_outline_opa(&style_pr, LV_OPA_TRANSP);

    /*鎸�?�挳鍙婇槾褰变笅�??*/
    lv_style_set_translate_y(&style_pr, 3);
    lv_style_set_shadow_offset_y(&style_pr, 3);


    /*鍚戣疆�?�撴坊鍔犺繃�??*/
    static lv_style_transition_dsc_t trans;
    static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, 0};
    lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);
    lv_style_set_transition(&style_pr, &trans);




    lv_obj_set_style_bg_color(PianoScrRoot, lv_palette_main(LV_PALETTE_GREEN), 0);  //璁剧疆鍒�??�?儗鏅?棰滆�?



    // lv_obj_t * btn1 = lv_imagebutton_create(PianoScrRoot);
    // lv_imagebutton_set_src(btn1, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/Users/zhe/Documents/HUST璇剧�?/�??浠惰?�???/lv_port_pc_vscode/main/src/white_key.png", NULL);
    lv_obj_t * btn1 = lv_btn_create(PianoScrRoot);
    lv_obj_set_style_bg_color(btn1, lv_color_white(), LV_PART_MAIN);

    lv_obj_add_style(btn1, &style_def, 0);
    lv_obj_add_style(btn1, &style_pr, LV_STATE_PRESSED);

    lv_obj_add_event_cb(btn1, event_handler_btn0, LV_EVENT_ALL, (void *)1);

    lv_obj_set_width(btn1, 45);
    lv_obj_set_height(btn1, 200);
    lv_obj_align(btn1, LV_ALIGN_TOP_LEFT, 2, 0);
    /*鍦ㄥ浘鍍忔寜�??涓婂垱�?�轰竴涓?鏍囩??*/
    lv_obj_t * label = lv_label_create(btn1);
    lv_label_set_text(label, "Do");
    // 鍒涘缓涓�?�??鏍峰紡瀵�?�薄
    lv_style_init(&style_label);
    // 璁剧疆鏂囨湰棰滆壊涓虹传�??
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 灏嗘牱�??忓簲�?ㄥ埌鏍囩?�??硅薄�??
    lv_obj_add_style(label, &style_label, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);



    // lv_obj_t * btn2 = lv_imagebutton_create(PianoScrRoot);
    // lv_imagebutton_set_src(btn2, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/Users/zhe/Documents/HUST璇剧�?/�??浠惰?�???/lv_port_pc_vscode/main/src/white_key.png", NULL);
    lv_obj_t * btn2 = lv_btn_create(PianoScrRoot);
    lv_obj_set_style_bg_color(btn2, lv_color_white(), LV_PART_MAIN);

    lv_obj_add_style(btn2, &style_def, 0);
    lv_obj_add_style(btn2, &style_pr, LV_STATE_PRESSED);

    lv_obj_add_event_cb(btn2, event_handler_btn0, LV_EVENT_ALL, (void *)2);

    lv_obj_set_width(btn2, 45);
    lv_obj_set_height(btn2, 200);
    lv_obj_align(btn2, LV_ALIGN_TOP_LEFT, 47, 0);
    /*鍦ㄥ浘鍍忔寜�??涓婂垱�?�轰竴涓?鏍囩??*/
    label = lv_label_create(btn2);
    lv_label_set_text(label, "Re");
    // 鍒涘缓涓�?�??鏍峰紡瀵�?�薄
    // static lv_style_t style_label;
    lv_style_init(&style_label);
    // 璁剧疆鏂囨湰棰滆壊涓虹传�??
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 灏嗘牱�??忓簲�?ㄥ埌鏍囩?�??硅薄�??
    lv_obj_add_style(label, &style_label, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);
    


    

    // lv_obj_t * btn3 = lv_imagebutton_create(PianoScrRoot);
    // lv_imagebutton_set_src(btn3, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/Users/zhe/Documents/HUST璇剧�?/�??浠惰?�???/lv_port_pc_vscode/main/src/white_key.png", NULL);
    lv_obj_t * btn3 = lv_btn_create(PianoScrRoot);
    lv_obj_set_style_bg_color(btn3, lv_color_white(), LV_PART_MAIN);

    lv_obj_add_style(btn3, &style_def, 0);
    lv_obj_add_style(btn3, &style_pr, LV_STATE_PRESSED);

    lv_obj_add_event_cb(btn3, event_handler_btn0, LV_EVENT_ALL, (void *)3);

    lv_obj_set_width(btn3, 45);
    lv_obj_set_height(btn3, 200);
    lv_obj_align(btn3, LV_ALIGN_TOP_LEFT, 92, 0);
    /*鍦ㄥ浘鍍忔寜�??涓婂垱�?�轰竴涓?鏍囩??*/
    label = lv_label_create(btn3);
    lv_label_set_text(label, "Mi");
    // 鍒涘缓涓�?�??鏍峰紡瀵�?�薄
    // static lv_style_t style_label;
    lv_style_init(&style_label);
    // 璁剧疆鏂囨湰棰滆壊涓虹传�??
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 灏嗘牱�??忓簲�?ㄥ埌鏍囩?�??硅薄�??
    lv_obj_add_style(label, &style_label, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);



    // lv_obj_t * btn4 = lv_imagebutton_create(PianoScrRoot);
    // lv_imagebutton_set_src(btn4, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/Users/zhe/Documents/HUST璇剧�?/�??浠惰?�???/lv_port_pc_vscode/main/src/white_key.png", NULL);
    lv_obj_t * btn4 = lv_btn_create(PianoScrRoot);
    lv_obj_set_style_bg_color(btn4, lv_color_white(), LV_PART_MAIN);

    lv_obj_add_style(btn4, &style_def, 0);
    lv_obj_add_style(btn4, &style_pr, LV_STATE_PRESSED);

    lv_obj_add_event_cb(btn4, event_handler_btn0, LV_EVENT_ALL, (void *)4);

    lv_obj_set_width(btn4, 45);
    lv_obj_set_height(btn4, 200);
    lv_obj_align(btn4, LV_ALIGN_TOP_LEFT, 137, 0);
    /*鍦ㄥ浘鍍忔寜�??涓婂垱�?�轰竴涓?鏍囩??*/
    label = lv_label_create(btn4);
    lv_label_set_text(label, "Fa");
    // 鍒涘缓涓�?�??鏍峰紡瀵�?�薄
    // static lv_style_t style_label;
    lv_style_init(&style_label);
    // 璁剧疆鏂囨湰棰滆壊涓虹传�??
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 灏嗘牱�??忓簲�?ㄥ埌鏍囩?�??硅薄�??
    lv_obj_add_style(label, &style_label, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);


    // lv_obj_t * btn5 = lv_imagebutton_create(PianoScrRoot);
    // lv_imagebutton_set_src(btn5, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/Users/zhe/Documents/HUST璇剧�?/�??浠惰?�???/lv_port_pc_vscode/main/src/white_key.png", NULL);
    lv_obj_t * btn5 = lv_btn_create(PianoScrRoot);
    lv_obj_set_style_bg_color(btn5, lv_color_white(), LV_PART_MAIN);

    lv_obj_add_style(btn5, &style_def, 0);
    lv_obj_add_style(btn5, &style_pr, LV_STATE_PRESSED);

    lv_obj_add_event_cb(btn5, event_handler_btn0, LV_EVENT_ALL, (void *)5);

    lv_obj_set_width(btn5, 45);
    lv_obj_set_height(btn5, 200);
    lv_obj_align(btn5, LV_ALIGN_TOP_LEFT, 182, 0);
    /*鍦ㄥ浘鍍忔寜�??涓婂垱�?�轰竴涓?鏍囩??*/
    label = lv_label_create(btn5);
    lv_label_set_text(label, "Sol");
    // 鍒涘缓涓�?�??鏍峰紡瀵�?�薄
    // static lv_style_t style_label;
    lv_style_init(&style_label);
    // 璁剧疆鏂囨湰棰滆壊涓虹传�??
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 灏嗘牱�??忓簲�?ㄥ埌鏍囩?�??硅薄�??
    lv_obj_add_style(label, &style_label, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);




    // lv_obj_t * btn6 = lv_imagebutton_create(PianoScrRoot);
    // lv_imagebutton_set_src(btn6, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/Users/zhe/Documents/HUST璇剧�?/�??浠惰?�???/lv_port_pc_vscode/main/src/white_key.png", NULL);
    lv_obj_t * btn6 = lv_btn_create(PianoScrRoot);
    lv_obj_set_style_bg_color(btn6, lv_color_white(), LV_PART_MAIN);

    lv_obj_add_style(btn6, &style_def, 0);
    lv_obj_add_style(btn6, &style_pr, LV_STATE_PRESSED);

    lv_obj_add_event_cb(btn6, event_handler_btn0, LV_EVENT_ALL, (void *)6);

    lv_obj_set_width(btn6, 45);
    lv_obj_set_height(btn6, 200);
    lv_obj_align(btn6, LV_ALIGN_TOP_LEFT, 227, 0);
    /*鍦ㄥ浘鍍忔寜�??涓婂垱�?�轰竴涓?鏍囩??*/
    label = lv_label_create(btn6);
    lv_label_set_text(label, "La");
    // 鍒涘缓涓�?�??鏍峰紡瀵�?�薄
    // static lv_style_t style_label;
    lv_style_init(&style_label);
    // 璁剧疆鏂囨湰棰滆壊涓虹传�??
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 灏嗘牱�??忓簲�?ㄥ埌鏍囩?�??硅薄�??
    lv_obj_add_style(label, &style_label, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);





    // lv_obj_t * btn7 = lv_imagebutton_create(PianoScrRoot);
    // lv_imagebutton_set_src(btn7, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/Users/zhe/Documents/HUST璇剧�?/�??浠惰?�???/lv_port_pc_vscode/main/src/white_key.png", NULL);
    lv_obj_t * btn7 = lv_btn_create(PianoScrRoot);
    lv_obj_set_style_bg_color(btn7, lv_color_white(), LV_PART_MAIN);

    lv_obj_add_style(btn7, &style_def, 0);
    lv_obj_add_style(btn7, &style_pr, LV_STATE_PRESSED);

    lv_obj_add_event_cb(btn7, event_handler_btn0, LV_EVENT_ALL, (void *)7);

    lv_obj_set_width(btn7, 45);
    lv_obj_set_height(btn7, 200);
    lv_obj_align(btn7, LV_ALIGN_TOP_LEFT, 272, 0);
    /*鍦ㄥ浘鍍忔寜�??涓婂垱�?�轰竴涓?鏍囩??*/
    label = lv_label_create(btn7);
    lv_label_set_text(label, "Si");
    // 鍒涘缓涓�?�??鏍峰紡瀵�?�薄
    // static lv_style_t style_label;
    lv_style_init(&style_label);
    // 璁剧疆鏂囨湰棰滆壊涓虹传�??
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 灏嗘牱�??忓簲�?ㄥ埌鏍囩?�??硅薄�??
    lv_obj_add_style(label, &style_label, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);





    lv_obj_t * switch1 = lv_button_create(PianoScrRoot);
    lv_obj_add_event_cb(switch1, event_handler_switch1, LV_EVENT_ALL, NULL);
    lv_obj_align(switch1, LV_ALIGN_BOTTOM_LEFT, 10, 0);
    lv_obj_remove_flag(switch1, LV_OBJ_FLAG_PRESS_LOCK);
    // lv_obj_add_flag(switch1, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_width(switch1, 84);
    lv_obj_set_height(switch1, 32);

    label = lv_label_create(switch1);
    lv_label_set_text(label, "LOW");
    lv_obj_center(label);


    lv_obj_t * switch2 = lv_button_create(PianoScrRoot);
    lv_obj_add_event_cb(switch2, event_handler_switch2, LV_EVENT_ALL, NULL);
    lv_obj_align(switch2, LV_ALIGN_BOTTOM_LEFT, 108, 0);
    lv_obj_remove_flag(switch1, LV_OBJ_FLAG_PRESS_LOCK);
    // lv_obj_add_flag(switch2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_width(switch2, 84);
    lv_obj_set_height(switch2, 32);

    label = lv_label_create(switch2);
    lv_label_set_text(label, "MID");
    lv_obj_center(label);



    lv_obj_t * switch3 = lv_button_create(PianoScrRoot);
    lv_obj_add_event_cb(switch3, event_handler_switch3, LV_EVENT_ALL, NULL);
    lv_obj_align(switch3, LV_ALIGN_BOTTOM_LEFT, 206, 0);
    lv_obj_remove_flag(switch1, LV_OBJ_FLAG_PRESS_LOCK);
    // lv_obj_add_flag(switch3, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_width(switch3, 84);
    lv_obj_set_height(switch3, 32);

    label = lv_label_create(switch3);
    lv_label_set_text(label, "HIGH");
    lv_obj_center(label);
}

/*********************************************************************************
 *                                   MACROS
 * *******************************************************************************/

/*********************************************************************************
 *                                  TYPEDEFS
 * *******************************************************************************/


/*********************************************************************************
 *                              STATIC FUNCTION
 * *******************************************************************************/
void piano_btn_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);

    if (obj == piano_btn) {
        printf("Screen 3 piano_btn is pressed! printf\r\n");
        // ScrMgrPopScr(true);
        ScrMgrSwitchScr(GUI_MIAN_SCR_ID, true);
    }
}

/*********************************************************************************
 *                              GLOBAL FUNCTION
 * *******************************************************************************/
static lv_obj_t *Gui_PianoScrCreate(lv_obj_t *parent)
{
    PianoScrRoot = lv_obj_create(parent);
    lv_obj_set_size(PianoScrRoot, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(PianoScrRoot, lv_color_black(), LV_PART_MAIN);

    // PianoLabel = lv_label_create(PianoScrRoot);
    // lv_obj_set_style_text_color(PianoLabel, lv_color_white(), LV_PART_MAIN);
    // lv_label_set_text(PianoLabel, "Screen 3");

    piano_btn = lv_btn_create(PianoScrRoot);
    lv_obj_set_size(piano_btn, 1, 1);
    BtnLabel = lv_label_create(piano_btn);
    lv_label_set_text(BtnLabel, "r");
    // lv_obj_add_flag(piano_btn, LV_OBJ_FLAG_HIDDEN);

    // lv_obj_align_to(PianoLabel, PianoScrRoot, LV_ALIGN_CENTER, 0, -30);
    lv_obj_center(BtnLabel);
    lv_obj_align_to(piano_btn, PianoScrRoot, LV_ALIGN_TOP_LEFT, 0, 0);

    my_piano();
    printf("piano created\r\n");
    return PianoScrRoot;
}

static void Gui_PianoScrLayout(void)
{
   
}

static void Gui_PianoScrEnter(void)
{
    Gui_PianoScrLayout();
    printf("piano enter\r\n");
    lv_obj_add_event_cb(piano_btn, piano_btn_event_cb, LV_EVENT_CLICKED, NULL);
}

static void Gui_PianoScrExit(void)
{
    printf("piano exit\r\n");
    lv_obj_remove_event_cb(piano_btn, piano_btn_event_cb);
}

static void Gui_PianoScrDestory(void)
{
    lv_obj_clean(PianoScrRoot);
    // lv_obj_del(PianoScrRoot);
    lv_style_reset(&style_def);
    lv_style_reset(&style_label);
    lv_style_reset(&style_pr);
    lv_obj_del_async(PianoScrRoot);
    printf("piano destory\r\n");
}

const SCR_MGR_SCR_HANDLE_T Gui_PianoScrHandle = {
    .ScrId      = GUI_PIANO_SCR_ID,
    .ScrCreate  = Gui_PianoScrCreate,
    .ScrEnter   = Gui_PianoScrEnter,
    .ScrExit    = Gui_PianoScrExit,
    .ScrDestroy = Gui_PianoScrDestory,
};

SCR_MGR_REG(Gui_PianoScrHandle);