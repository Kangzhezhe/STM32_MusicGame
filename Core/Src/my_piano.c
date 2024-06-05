// #include "../lv_examples.h"
#include "lvgl.h"
#include <stdio.h>
#include "mp3Player.h"

void playSound(const char* soundFilePath) {
    // CFURLRef soundFileURL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, CFStringCreateWithCString(NULL, soundFilePath, kCFStringEncodingUTF8), kCFURLPOSIXPathStyle, false);
    // SystemSoundID soundID;
    // AudioServicesCreateSystemSoundID(soundFileURL, &soundID);
    // AudioServicesPlaySystemSound(soundID);
    // CFRelease(soundFileURL);
    MP3_decode_file(soundFilePath);
    printf("playSound: %s\r\n", soundFilePath);
}



// ##########
// 开关的事件处理函数
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
        lv_obj_set_style_bg_color(lv_scr_act(), lv_palette_main(LV_PALETTE_PURPLE), 0);
    }
}

static void event_handler_switch2(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        switch0_state = STATE_MID;
        lv_obj_set_style_bg_color(lv_scr_act(), lv_palette_main(LV_PALETTE_GREEN), 0);
    }
}

static void event_handler_switch3(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        switch0_state = STATE_HIGH;
        lv_obj_set_style_bg_color(lv_scr_act(), lv_palette_main(LV_PALETTE_YELLOW), 0);
    }
}



// #############
// 按钮的事件�?�理函数
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


void my_piano(void)
{
    /*初�?�化默�?�状态的样式*/
    static lv_style_t style_def;
    lv_style_init(&style_def);

    // 设置按钮边�?��?�色和�?�度
    lv_style_set_border_color(&style_def, lv_color_black()); // 设置边�?��?�色为黑�?
    lv_style_set_border_width(&style_def, 2); // 设置边�?��?�度�?2像素

    lv_style_set_shadow_width(&style_def, 5);  // 设置阴影宽度�? 8 像素
    lv_style_set_shadow_color(&style_def, lv_color_make(0, 0, 0));  // 设置阴影颜色为黑�?
    lv_style_set_shadow_offset_y(&style_def, 8);  // 设置阴影�? Y 轴方向的偏移�? 8 像素

    lv_style_set_outline_opa(&style_def, LV_OPA_COVER);
    lv_style_set_outline_color(&style_def, lv_palette_main(LV_PALETTE_DEEP_ORANGE));

    lv_style_set_text_color(&style_def, lv_color_white());

    /*在�?�度变换和重新着色上创建过渡动画�?*/
    static lv_style_prop_t tr_prop[] = {LV_STYLE_BG_COLOR, LV_STYLE_BORDER_COLOR, LV_STYLE_BORDER_WIDTH, 0};
    static lv_style_transition_dsc_t tr;
    lv_style_transition_dsc_init(&tr, tr_prop, lv_anim_path_linear, 200, 0, NULL);
    lv_style_set_transition(&style_def, &tr);
    // lv_style_set_transition(&style_pr, &tr);





    /*初�?�化按下的样�?*/
    /*当按下按�?时使按钮变暗并变�?*/
    static lv_style_t style_pr;
    lv_style_init(&style_pr);
    // lv_style_set_image_recolor_opa(&style_pr, LV_OPA_20);
    // lv_style_set_image_recolor(&style_pr, lv_color_black());
    lv_style_set_bg_opa(&style_pr, LV_OPA_90); // 设置背景不透明度为20%
    lv_style_set_bg_color(&style_pr, lv_color_make(160, 160, 160)); // 设置背景颜色为灰�?
    lv_style_set_transform_width(&style_pr, -2);
    lv_style_set_transform_height(&style_pr, -5);

    /*按下时添加大�?�?*/
    lv_style_set_outline_width(&style_pr, 30);
    lv_style_set_outline_opa(&style_pr, LV_OPA_TRANSP);

    /*按钮及阴影下�?*/
    lv_style_set_translate_y(&style_pr, 3);
    lv_style_set_shadow_offset_y(&style_pr, 3);


    /*向轮廓添加过�?*/
    static lv_style_transition_dsc_t trans;
    static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, 0};
    lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);
    lv_style_set_transition(&style_pr, &trans);



    lv_obj_set_style_bg_color(lv_scr_act(), lv_palette_main(LV_PALETTE_GREEN), 0);  //设置初�?�背�?颜色



    // lv_obj_t * btn1 = lv_imagebutton_create(lv_screen_active());
    // lv_imagebutton_set_src(btn1, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/Users/zhe/Documents/HUST课程/�?件�?��??/lv_port_pc_vscode/main/src/white_key.png", NULL);
    lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
    lv_obj_set_style_bg_color(btn1, lv_color_white(), LV_PART_MAIN);

    lv_obj_add_style(btn1, &style_def, 0);
    lv_obj_add_style(btn1, &style_pr, LV_STATE_PRESSED);

    lv_obj_add_event_cb(btn1, event_handler_btn0, LV_EVENT_ALL, (void *)1);

    lv_obj_set_width(btn1, 45);
    lv_obj_set_height(btn1, 200);
    lv_obj_align(btn1, LV_ALIGN_TOP_LEFT, 2, 0);
    /*在图像按�?上创建一�?标�??*/
    lv_obj_t * label = lv_label_create(btn1);
    lv_label_set_text(label, "Do");
    // 创建一�?样式对象
    static lv_style_t style_label;
    lv_style_init(&style_label);
    // 设置文本颜色为紫�?
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 将样式应用到标�?��?�象�?
    lv_obj_add_style(label, &style_label, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);




    // lv_obj_t * btn2 = lv_imagebutton_create(lv_screen_active());
    // lv_imagebutton_set_src(btn2, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/Users/zhe/Documents/HUST课程/�?件�?��??/lv_port_pc_vscode/main/src/white_key.png", NULL);
    lv_obj_t * btn2 = lv_btn_create(lv_scr_act());
    lv_obj_set_style_bg_color(btn2, lv_color_white(), LV_PART_MAIN);

    lv_obj_add_style(btn2, &style_def, 0);
    lv_obj_add_style(btn2, &style_pr, LV_STATE_PRESSED);

    lv_obj_add_event_cb(btn2, event_handler_btn0, LV_EVENT_ALL, (void *)2);

    lv_obj_set_width(btn2, 45);
    lv_obj_set_height(btn2, 200);
    lv_obj_align(btn2, LV_ALIGN_TOP_LEFT, 47, 0);
    /*在图像按�?上创建一�?标�??*/
    label = lv_label_create(btn2);
    lv_label_set_text(label, "Re");
    // 创建一�?样式对象
    // static lv_style_t style_label;
    lv_style_init(&style_label);
    // 设置文本颜色为紫�?
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 将样式应用到标�?��?�象�?
    lv_obj_add_style(label, &style_label, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);
    


    

    // lv_obj_t * btn3 = lv_imagebutton_create(lv_screen_active());
    // lv_imagebutton_set_src(btn3, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/Users/zhe/Documents/HUST课程/�?件�?��??/lv_port_pc_vscode/main/src/white_key.png", NULL);
    lv_obj_t * btn3 = lv_btn_create(lv_scr_act());
    lv_obj_set_style_bg_color(btn3, lv_color_white(), LV_PART_MAIN);

    lv_obj_add_style(btn3, &style_def, 0);
    lv_obj_add_style(btn3, &style_pr, LV_STATE_PRESSED);

    lv_obj_add_event_cb(btn3, event_handler_btn0, LV_EVENT_ALL, (void *)3);

    lv_obj_set_width(btn3, 45);
    lv_obj_set_height(btn3, 200);
    lv_obj_align(btn3, LV_ALIGN_TOP_LEFT, 92, 0);
    /*在图像按�?上创建一�?标�??*/
    label = lv_label_create(btn3);
    lv_label_set_text(label, "Mi");
    // 创建一�?样式对象
    // static lv_style_t style_label;
    lv_style_init(&style_label);
    // 设置文本颜色为紫�?
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 将样式应用到标�?��?�象�?
    lv_obj_add_style(label, &style_label, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);




    // lv_obj_t * btn4 = lv_imagebutton_create(lv_screen_active());
    // lv_imagebutton_set_src(btn4, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/Users/zhe/Documents/HUST课程/�?件�?��??/lv_port_pc_vscode/main/src/white_key.png", NULL);
    lv_obj_t * btn4 = lv_btn_create(lv_scr_act());
    lv_obj_set_style_bg_color(btn4, lv_color_white(), LV_PART_MAIN);

    lv_obj_add_style(btn4, &style_def, 0);
    lv_obj_add_style(btn4, &style_pr, LV_STATE_PRESSED);

    lv_obj_add_event_cb(btn4, event_handler_btn0, LV_EVENT_ALL, (void *)4);

    lv_obj_set_width(btn4, 45);
    lv_obj_set_height(btn4, 200);
    lv_obj_align(btn4, LV_ALIGN_TOP_LEFT, 137, 0);
    /*在图像按�?上创建一�?标�??*/
    label = lv_label_create(btn4);
    lv_label_set_text(label, "Fa");
    // 创建一�?样式对象
    // static lv_style_t style_label;
    lv_style_init(&style_label);
    // 设置文本颜色为紫�?
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 将样式应用到标�?��?�象�?
    lv_obj_add_style(label, &style_label, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);





    // lv_obj_t * btn5 = lv_imagebutton_create(lv_screen_active());
    // lv_imagebutton_set_src(btn5, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/Users/zhe/Documents/HUST课程/�?件�?��??/lv_port_pc_vscode/main/src/white_key.png", NULL);
    lv_obj_t * btn5 = lv_btn_create(lv_scr_act());
    lv_obj_set_style_bg_color(btn5, lv_color_white(), LV_PART_MAIN);

    lv_obj_add_style(btn5, &style_def, 0);
    lv_obj_add_style(btn5, &style_pr, LV_STATE_PRESSED);

    lv_obj_add_event_cb(btn5, event_handler_btn0, LV_EVENT_ALL, (void *)5);

    lv_obj_set_width(btn5, 45);
    lv_obj_set_height(btn5, 200);
    lv_obj_align(btn5, LV_ALIGN_TOP_LEFT, 182, 0);
    /*在图像按�?上创建一�?标�??*/
    label = lv_label_create(btn5);
    lv_label_set_text(label, "Sol");
    // 创建一�?样式对象
    // static lv_style_t style_label;
    lv_style_init(&style_label);
    // 设置文本颜色为紫�?
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 将样式应用到标�?��?�象�?
    lv_obj_add_style(label, &style_label, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);




    // lv_obj_t * btn6 = lv_imagebutton_create(lv_screen_active());
    // lv_imagebutton_set_src(btn6, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/Users/zhe/Documents/HUST课程/�?件�?��??/lv_port_pc_vscode/main/src/white_key.png", NULL);
    lv_obj_t * btn6 = lv_btn_create(lv_scr_act());
    lv_obj_set_style_bg_color(btn6, lv_color_white(), LV_PART_MAIN);

    lv_obj_add_style(btn6, &style_def, 0);
    lv_obj_add_style(btn6, &style_pr, LV_STATE_PRESSED);

    lv_obj_add_event_cb(btn6, event_handler_btn0, LV_EVENT_ALL, (void *)6);

    lv_obj_set_width(btn6, 45);
    lv_obj_set_height(btn6, 200);
    lv_obj_align(btn6, LV_ALIGN_TOP_LEFT, 227, 0);
    /*在图像按�?上创建一�?标�??*/
    label = lv_label_create(btn6);
    lv_label_set_text(label, "La");
    // 创建一�?样式对象
    // static lv_style_t style_label;
    lv_style_init(&style_label);
    // 设置文本颜色为紫�?
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 将样式应用到标�?��?�象�?
    lv_obj_add_style(label, &style_label, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);





    // lv_obj_t * btn7 = lv_imagebutton_create(lv_screen_active());
    // lv_imagebutton_set_src(btn7, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/Users/zhe/Documents/HUST课程/�?件�?��??/lv_port_pc_vscode/main/src/white_key.png", NULL);
    lv_obj_t * btn7 = lv_btn_create(lv_scr_act());
    lv_obj_set_style_bg_color(btn7, lv_color_white(), LV_PART_MAIN);

    lv_obj_add_style(btn7, &style_def, 0);
    lv_obj_add_style(btn7, &style_pr, LV_STATE_PRESSED);

    lv_obj_add_event_cb(btn7, event_handler_btn0, LV_EVENT_ALL, (void *)7);

    lv_obj_set_width(btn7, 45);
    lv_obj_set_height(btn7, 200);
    lv_obj_align(btn7, LV_ALIGN_TOP_LEFT, 272, 0);
    /*在图像按�?上创建一�?标�??*/
    label = lv_label_create(btn7);
    lv_label_set_text(label, "Si");
    // 创建一�?样式对象
    // static lv_style_t style_label;
    lv_style_init(&style_label);
    // 设置文本颜色为紫�?
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 将样式应用到标�?��?�象�?
    lv_obj_add_style(label, &style_label, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);





    lv_obj_t * switch1 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(switch1, event_handler_switch1, LV_EVENT_ALL, NULL);
    lv_obj_align(switch1, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_remove_flag(switch1, LV_OBJ_FLAG_PRESS_LOCK);
    // lv_obj_add_flag(switch1, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_width(switch1, 104);
    lv_obj_set_height(switch1, 32);

    label = lv_label_create(switch1);
    lv_label_set_text(label, "LOW");
    lv_obj_center(label);



    lv_obj_t * switch2 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(switch2, event_handler_switch2, LV_EVENT_ALL, NULL);
    lv_obj_align(switch2, LV_ALIGN_BOTTOM_LEFT, 108, 0);
    lv_obj_remove_flag(switch1, LV_OBJ_FLAG_PRESS_LOCK);
    // lv_obj_add_flag(switch2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_width(switch2, 104);
    lv_obj_set_height(switch2, 32);

    label = lv_label_create(switch2);
    lv_label_set_text(label, "MID");
    lv_obj_center(label);



    lv_obj_t * switch3 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(switch3, event_handler_switch3, LV_EVENT_ALL, NULL);
    lv_obj_align(switch3, LV_ALIGN_BOTTOM_LEFT, 216, 0);
    lv_obj_remove_flag(switch1, LV_OBJ_FLAG_PRESS_LOCK);
    // lv_obj_add_flag(switch3, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_width(switch3, 104);
    lv_obj_set_height(switch3, 32);

    label = lv_label_create(switch3);
    lv_label_set_text(label, "HIGH");
    lv_obj_center(label);
}
