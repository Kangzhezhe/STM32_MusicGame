#include <src/core/lv_obj_event.h>
#include <src/core/lv_obj_pos.h>
#include <src/display/lv_display.h>
#include <src/misc/lv_area.h>
#include <src/misc/lv_style.h>
#include <src/misc/lv_timer.h>
#include <src/misc/lv_types.h>
#include <src/widgets/button/lv_button.h>
#include <src/widgets/label/lv_label.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "lvgl/lvgl.h"
#include <string.h>
#include "mp3Player.h"


static void play_pause_event_cb(lv_event_t * e);
static void slider_event_cb(lv_event_t * e);
static void prev_event_cb(lv_event_t * e);
static void next_event_cb(lv_event_t * e);
static void value_changed_event_cb(lv_event_t * e);
static void event_handler(lv_event_t * e);
static void event_list_handler(lv_event_t * e);
static void event_handler_top(lv_event_t * e);
static void event_handler_bottom(lv_event_t * e);
static void event_handler_up(lv_event_t * e);
static void event_handler_center(lv_event_t * e);
static void event_handler_dn(lv_event_t * e);
static void hidden_handler(lv_event_t * e);
void my_timer_callback(lv_timer_t * timer);
void lv_example_image_3(void);
void play_music(void);
void stop_music(void);
void resume_music(void);
void kill_music(void);
void change_sound(int);
double get_total_duration(const char* filename);
static bool is_playing = true;
int duration_time = 0;
int current_time = 0;
//lv_list
lv_obj_t * slider ;
lv_timer_t * timer;
static lv_obj_t * list1;
static lv_obj_t * list2;
static lv_obj_t * imgx;
static lv_obj_t * label3;
static lv_obj_t * label4;
static lv_obj_t * currentButton = NULL;
char xx[500] ="single";
//�ɱ��б�
 static const char * opts = "single\n"
                               "List\n"
                               "random"
                               ;

//
LV_IMG_DECLARE(test1);
LV_IMG_DECLARE(test2);
LV_IMG_DECLARE(test3);
LV_IMG_DECLARE(test4);
LV_IMG_DECLARE(zheba);
void lv_music_UI(void)
{   
    /*Create a transition animation on width transformation and recolor.*/
    static lv_style_prop_t tr_prop[] = {LV_STYLE_TRANSFORM_WIDTH, LV_STYLE_IMG_RECOLOR_OPA, 0};
    static lv_style_transition_dsc_t tr;
    lv_style_transition_dsc_init(&tr, tr_prop, lv_anim_path_linear, 200, 0, NULL);

    static lv_style_t style_def;
    lv_style_init(&style_def);
    lv_style_set_text_color(&style_def, lv_color_white());
    lv_style_set_transition(&style_def, &tr);

    /*Darken the button when pressed and make it wider*/
    static lv_style_t style_pr;
    lv_style_init(&style_pr);
    lv_style_set_img_recolor_opa(&style_pr, LV_OPA_30);
    lv_style_set_img_recolor(&style_pr, lv_color_black());
    lv_style_set_transform_width(&style_pr, 0);


    // lv_image_set_src(img_play, "A:/test1.png");
    // lv_image_set_src(img_pause, "A:/test2.png");
    // lv_obj_align(img_play, LV_ALIGN_CENTER, 0, 0);
    
    

    // ��������/��ͣ��ť
    
    lv_obj_t * play_pause_btn = lv_imagebutton_create(lv_screen_active());     /*Add a button the current screen*/
    // lv_imagebutton_set_src(play_pause_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/test1.png",
    //                       NULL);
    lv_imagebutton_set_src(play_pause_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &test1,NULL);

    lv_obj_set_width(play_pause_btn, 60);                      
    lv_obj_align(play_pause_btn, LV_ALIGN_CENTER, 0, 50);

    lv_obj_add_event_cb(play_pause_btn, play_pause_event_cb, LV_EVENT_CLICKED, NULL);
    
    // ������ǩ
    lv_obj_t * label1 = lv_label_create(lv_scr_act());
    lv_label_set_text(label1, "play mode"); // �������ı�ǩ�ı�
    lv_obj_align(label1, LV_ALIGN_CENTER, -120, 65); // ����λ�ã�ʹ���������б��Ϸ�

    // ѡ��ģʽ�������б�
    /*Create a normal drop down list*/
    lv_obj_t * dd = lv_dropdown_create(lv_screen_active());
    lv_dropdown_set_options_static(dd, opts);
    lv_dropdown_set_dir(dd, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(dd, LV_SYMBOL_UP);
    lv_obj_set_width(dd, 80); 
    lv_obj_align(dd, LV_ALIGN_CENTER, -120, 40);
    lv_obj_add_event_cb(dd, event_handler, LV_EVENT_ALL, NULL);

    // ��������һ�ס���ť
    lv_obj_t * prev_btn = lv_imagebutton_create(lv_scr_act()); 
    lv_imagebutton_set_src(prev_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &test4,
                          NULL);
    // ����ʱ����ʽ 
    lv_obj_add_style(prev_btn, &style_def, 0);
    lv_obj_add_style(prev_btn, &style_pr, LV_STATE_PRESSED);

    lv_obj_set_width(prev_btn, 40);                      
    lv_obj_align(prev_btn, LV_ALIGN_CENTER, -50, 50); // ���������λ������50����
    lv_obj_add_event_cb(prev_btn, prev_event_cb, LV_EVENT_CLICKED, NULL);
    
     // ��������һ�ס���ť
    lv_obj_t * next_btn = lv_imagebutton_create(lv_scr_act()); 
    lv_imagebutton_set_src(next_btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &test3,
                          NULL);
    // ����ʱ����ʽ                      
    lv_obj_add_style(next_btn, &style_def, 0);
    lv_obj_add_style(next_btn, &style_pr, LV_STATE_PRESSED);
    lv_obj_set_width(next_btn, 40);                      
    lv_obj_align(next_btn, LV_ALIGN_CENTER, 50, 50); // ���������λ������50����
    lv_obj_add_event_cb(next_btn, next_event_cb, LV_EVENT_CLICKED, NULL);
    
    //
    // ������ǩ
    lv_obj_t * label = lv_label_create(lv_screen_active());
    
    // �����������οؼ�
    lv_obj_t * arc = lv_arc_create(lv_screen_active());
    lv_obj_set_size(arc, 50, 50);
    lv_arc_set_rotation(arc, 135);
    lv_arc_set_bg_angles(arc, 0, 270);
    lv_arc_set_value(arc, 80);
   
    lv_obj_align(arc, LV_ALIGN_TOP_LEFT, 25, 50);
    lv_obj_add_event_cb(arc, value_changed_event_cb, LV_EVENT_VALUE_CHANGED, label);

    // ���ñ�ǩλ��
    //lv_obj_align(label,  LV_ALIGN_TOP_LEFT, 50, 45);// ����ǩ���ڡ���һ�ס���ť���·�

    // �ֶ����±�ǩ��һ��
    lv_obj_send_event(arc, LV_EVENT_VALUE_CHANGED, NULL);

    // �赥
    /*Create a list*/
    list1 = lv_list_create(lv_screen_active());
    lv_obj_set_size(list1, lv_pct(40), lv_pct(60));
    lv_obj_align(list1, LV_ALIGN_TOP_MID, lv_pct(0), 0);
    lv_obj_set_style_pad_row(list1, 5, 0);


    /* Create a style for the smaller font */
    static lv_style_t style_small;
    lv_style_init(&style_small);
    lv_style_set_text_font(&style_small, &lv_font_montserrat_10);
    lv_obj_t * small_label;
    /*Add buttons to the list*/

    lv_obj_t * btn;

    // for(int i = 0; i < 10; i++) {
    //     btn = lv_button_create(list1);
    //     lv_obj_set_width(btn, lv_pct(100));
    //     lv_obj_add_event_cb(btn, event_list_handler, LV_EVENT_CLICKED, NULL);
    //     lv_obj_t * label = lv_label_create(btn);
    //     lv_label_set_text_fmt(label, "It%d", i);
    //     lv_label_set_long_mode(label,LV_LABEL_LONG_SCROLL_CIRCULAR);
    //     lv_obj_set_width(label, lv_pct(100));
    // }


   lv_fs_dir_t dir;
   lv_fs_res_t res = lv_fs_dir_open(&dir, "A:/song_List");
   if (res != LV_FS_RES_OK) {
       printf("Failed to open directory\n");
       return;
   }
   char fn[50];
   while (true) {
       lv_fs_res_t res = lv_fs_dir_read(&dir, fn,256);
       if (res != LV_FS_RES_OK||fn[0] == 0) {
           break;
       }
       char *ext = strrchr(fn, '.');
       if (ext && strcmp(ext, ".mp3") == 0) {
           *ext = '\0'; // Null-terminate to remove the extension
       }
       printf("%s\r\n", fn);
       btn = lv_btn_create(list1);
       lv_obj_set_width(btn, lv_pct(100));
       lv_obj_add_event_cb(btn, event_list_handler, LV_EVENT_CLICKED, NULL);
       lv_obj_t * label = lv_label_create(btn);
       lv_label_set_text(label,fn);

       small_label = lv_obj_get_child(btn, 0); // Get the label object of the button
       lv_obj_add_style(small_label, &style_small, 0);
       lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
       lv_obj_set_width(label, lv_pct(100));
        }
        lv_fs_dir_close(&dir);

    /*Select the first button by default*/
    currentButton = lv_obj_get_child(list1, 0);
    lv_obj_add_state(currentButton, LV_STATE_CHECKED);


    //
     //duration time
    label3 = lv_label_create(lv_screen_active());
    lv_label_set_text(label3, "00:00"); // ���ñ�ǩ�ı�
    lv_obj_add_style(label3, &style_small, 0);
    lv_obj_align(label3, LV_ALIGN_CENTER, 140, 100); // ����λ�ã�ʹ���������б��Ϸ�
    //now time
    label4 = lv_label_create(lv_screen_active());
    lv_label_set_text(label4, "00:00"); // ���ñ�ǩ�ı�
    lv_obj_add_style(label4, &style_small, 0);
    lv_obj_align(label4, LV_ALIGN_LEFT_MID, 0, 100); // ����λ�ã�ʹ���������б��Ϸ�
    
     // ����һ����ʱ����ÿ�����һ�λص�����
    timer = lv_timer_create(my_timer_callback, 1000, NULL);
    //Ĭ�ϲ��ŵ�һ��
    // lv_obj_t *current_label = lv_obj_get_child(currentButton, 0);
    // const char *button_name = lv_label_get_text(current_label);
    // char output[326];
    // sprintf(output, "mplayer /song_List/%s.mp3 &", button_name);
    play_music();
    // system(output);
    //system("mplayer /song_List/after.mp3 &");
    //

    /*Create a second list with up and down buttons*/
    list2 = lv_list_create(lv_screen_active());
    lv_obj_set_size(list2, lv_pct(30), lv_pct(60));
    lv_obj_align(list2, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_flex_flow(list2, LV_FLEX_FLOW_COLUMN);

   
    //
    btn = lv_list_add_button(list2, NULL, "Top");
    lv_obj_add_event_cb(btn, event_handler_top, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn);
    small_label = lv_obj_get_child(btn, 0); // Get the label object of the button
    lv_obj_add_style(small_label, &style_small, 0);

    btn = lv_list_add_button(list2, NULL, "Up");
    lv_obj_add_event_cb(btn, event_handler_up, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn);
    small_label = lv_obj_get_child(btn, 0); // Get the label object of the button
    lv_obj_add_style(small_label, &style_small, 0);

    btn = lv_list_add_button(list2, NULL, "Center");
    lv_obj_add_event_cb(btn, event_handler_center, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn);
    small_label = lv_obj_get_child(btn, 0); // Get the label object of the button
    lv_obj_add_style(small_label, &style_small, 0);

    btn = lv_list_add_button(list2, NULL, "Down");
    lv_obj_add_event_cb(btn, event_handler_dn, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn);
    small_label = lv_obj_get_child(btn, 0); // Get the label object of the button
    lv_obj_add_style(small_label, &style_small, 0);

    btn = lv_list_add_button(list2, NULL, "Bottom");
    lv_obj_add_event_cb(btn, event_handler_bottom, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn);
    small_label = lv_obj_get_child(btn, 0); // Get the label object of the button
    lv_obj_add_style(small_label, &style_small, 0);
    

    //
    lv_obj_t * sw = lv_switch_create(lv_screen_active());
    lv_obj_align(sw,LV_ALIGN_CENTER, 100, 50);
    lv_obj_add_event_cb(sw, hidden_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(sw, LV_OBJ_FLAG_EVENT_BUBBLE);
    //
    // ������ǩ
    lv_obj_t * label2 = lv_label_create(lv_scr_act());
    lv_label_set_text(label2, "music_list"); // �������ı�ǩ�ı�
    lv_obj_align(label2, LV_ALIGN_CENTER, 110, 70); // ����λ�ã�ʹ���������б��Ϸ�
    //
    lv_example_image_3();
    //


     // ����������
    static lv_style_t style_bg;
    static lv_style_t style_indic;
    static lv_style_t style_knob;
    lv_style_init(&style_bg);
    lv_style_set_radius(&style_bg, LV_RADIUS_CIRCLE); // ���ñ���Բ��
    lv_style_set_bg_color(&style_bg, lv_color_hex(0xAAAAAA)); // ���ñ�����ɫ
    lv_style_set_bg_grad_color(&style_bg, lv_color_hex(0x888888)); // ���ý�����ɫ
    lv_style_set_bg_grad_dir(&style_bg, LV_GRAD_DIR_VER); // ���ý��䷽��
    lv_style_set_border_color(&style_bg, lv_color_hex(0x666666)); // ���ñ߿���ɫ
    lv_style_set_border_width(&style_bg, 2); // ���ñ߿���
    lv_style_set_pad_all(&style_bg, 2); // �����ڱ߾�
    lv_style_set_width(&style_bg, 10); // ���ñ������

    lv_style_init(&style_indic);
    lv_style_set_radius(&style_indic, LV_RADIUS_CIRCLE); // ����ָʾ��Բ��
    lv_style_set_border_width(&style_indic, 2); // ���ñ߿���
    
    lv_style_init(&style_knob);
    lv_style_set_radius(&style_knob, LV_RADIUS_CIRCLE); // ���û���Բ��
    lv_style_set_border_width(&style_knob, 0); // ���û���߿���
    lv_style_set_width(&style_knob, 3); // ���û�����
    lv_style_set_height(&style_knob, 3); // ���û���߶�
    // ����������
    slider = lv_slider_create(lv_screen_active());
    lv_obj_set_width(slider, 250);
    lv_obj_align(slider, LV_ALIGN_CENTER, 0, 100);
    lv_obj_add_style(slider, &style_bg, LV_PART_MAIN); // Ӧ�ñ�����ʽ
    lv_obj_add_style(slider, &style_indic, LV_PART_INDICATOR); // Ӧ��ָʾ����ʽ
    lv_obj_add_style(slider, &style_knob, LV_PART_KNOB); // Ӧ�û�����ʽ
    //lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_slider_set_value(slider, 0, LV_ANIM_OFF);
   
}

// ����/��ͣ��ť�ص�����
void play_pause_event_cb(lv_event_t * e)
{
    lv_obj_t * btn = lv_event_get_target(e);
    // ʵ�ֲ���/��ͣ�߼�
     is_playing = !is_playing; // �л�״̬
    if(is_playing==false) {
        if(currentButton == NULL) {
            return;}
          lv_imagebutton_set_src(btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &test2,
                          NULL);// ����Ϊ��ͣͼ��
        lv_obj_remove_state(currentButton, LV_STATE_CHECKED);
        stop_music();
          
    } else {
        if(currentButton == NULL) {
            return;}
        lv_imagebutton_set_src(btn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &test1,
                          NULL);// ����Ϊ����ͼ��
        lv_obj_add_state(currentButton, LV_STATE_CHECKED);
        resume_music();
    }
}

// �������¼��ص�����
void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    // ʵ�ֽ����������߼�
}

// ��һ�װ�ť�¼��ص�����
void prev_event_cb(lv_event_t * e)
{    lv_obj_t * btn = lv_event_get_target(e);
    printf("��һ��");
    if(currentButton == NULL) return;
    lv_obj_t * parent = lv_obj_get_parent(currentButton);
    uint32_t current_index = lv_obj_get_index(currentButton);
    uint32_t child_count = lv_obj_get_child_cnt(parent);
    uint32_t prev_index = (current_index + child_count - 1) % child_count;

    lv_obj_t * pre_Button = lv_obj_get_child(parent, prev_index);
    lv_obj_send_event(pre_Button , LV_EVENT_CLICKED, NULL);

    // kill_music();
    // play_music();
}


// ��һ�װ�ť�¼��ص�����
void next_event_cb(lv_event_t * e)
{
    lv_obj_t * btn = lv_event_get_target(e);
    printf("��һ��");
    if(currentButton == NULL) return;
    lv_obj_t * parent = lv_obj_get_parent(currentButton);
    uint32_t current_index = lv_obj_get_index(currentButton);
    uint32_t child_count = lv_obj_get_child_cnt(parent);
    uint32_t next_index = (current_index + 1) % child_count;

    lv_obj_t * pre_Button = lv_obj_get_child(parent, next_index);
    lv_obj_send_event(pre_Button , LV_EVENT_CLICKED, NULL);

    // kill_music();
    // play_music();
}

//
// ������ɫֵ�ĸ�������
static lv_color_t get_color_from_value(int value) {
    // ������ɫ����
    uint8_t r = (uint8_t)(255 * value / 100);
    uint8_t g = 0;
    uint8_t b = (uint8_t)(255 * (100 - value) / 100);

    return lv_color_make(r, g, b);
}
//
static void value_changed_event_cb(lv_event_t * e)
{
    lv_obj_t * arc = lv_event_get_target(e);
    lv_obj_t * label = lv_event_get_user_data(e);

    lv_label_set_text_fmt(label, "%d%%", lv_arc_get_value(arc));

    /*Update the sound value*/
    change_sound(lv_arc_get_value(arc));
    /*Rotate the label to the current position of the arc*/
    lv_arc_rotate_obj_to_angle(arc, label, 25);

    // ������ɫ������
    lv_color_t color = get_color_from_value(lv_arc_get_value(arc));
    lv_obj_set_style_arc_color(arc, color, LV_PART_INDICATOR);
}


static void event_handler(lv_event_t * e)
{
     lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Option: %s", buf);
        strcpy(xx, buf);
    }

}


//lv_list

static void event_list_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    //�������¼�,��ʾ�������ť���ı�����
    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked: %s", lv_list_get_button_text(list1, obj));
        // ���µ�ǰ��ť
        if(currentButton == obj) {
            currentButton = NULL;
            kill_music();
            lv_timer_pause(timer);
        }
        else {
            currentButton = obj;
            //�ŵ�ǰ����
            kill_music();
            play_music();
        }
        // ���°�ť��״̬
        //����Ӷ�����currentButton����������LV_STATE_CHECKED״̬����ʾѡ��״̬���������Ƴ���LV_STATE_CHECKED״̬��
        lv_obj_t * parent = lv_obj_get_parent(obj);
        uint32_t i;
        for(i = 0; i < lv_obj_get_child_count(parent); i++) {
            lv_obj_t * child = lv_obj_get_child(parent, i);
            if(child == currentButton) {
                lv_obj_add_state(child, LV_STATE_CHECKED);
            }
            else {
                lv_obj_remove_state(child, LV_STATE_CHECKED);
            }
        }
    }
    // ������ͼ��ȷ���ð�ť����Ұ��Χ�ڣ���ʹ�ö���Ч����
    if (currentButton!=NULL){
    lv_obj_scroll_to_view(currentButton, LV_ANIM_ON);}
    //�ŵ�ǰ����
    // kill_music();
    // play_music();
}

static void event_handler_top(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        // ����Ƿ��е�ǰѡ�еİ�ť��currentButton��
        if(currentButton == NULL) return;
        // �����ѡ�еİ�ť�������ƶ�������
        lv_obj_move_background(currentButton);
        // ������ͼ��ȷ���ð�ť����Ұ��Χ�ڣ���ʹ�ö���Ч����
        lv_obj_scroll_to_view(currentButton, LV_ANIM_ON);
    }
}

static void event_handler_bottom(lv_event_t * e)
{
    const lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        // ����Ƿ��е�ǰѡ�еİ�ť��currentButton��
        if(currentButton == NULL) return;
        // �����ѡ�еİ�ť�������ƶ���ǰ��
        lv_obj_move_foreground(currentButton);
        // ������ͼ��ȷ���ð�ť����Ұ��Χ�ڣ���ʹ�ö���Ч����
        lv_obj_scroll_to_view(currentButton, LV_ANIM_ON);
    }
}

static void event_handler_up(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
        if(currentButton == NULL) return;
        // ��ȡ currentButton ���丸�����Ӷ����б��е�����
        uint32_t index = lv_obj_get_index(currentButton);
        if(index <= 0) return;
        // currentButton �ƶ����䵱ǰ������ǰһ��λ�ã�����һ��λ��
        lv_obj_move_to_index(currentButton, index - 1);
        // ���д��������ͼ��ȷ�� currentButton ����Ұ��Χ�ڣ������ö���Ч��
        lv_obj_scroll_to_view(currentButton, LV_ANIM_ON);
    }
}

static void event_handler_center(lv_event_t * e)
{
    const lv_event_code_t code = lv_event_get_code(e);
    if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
        if(currentButton == NULL) return;

        lv_obj_t * parent = lv_obj_get_parent(currentButton);
        const uint32_t pos = lv_obj_get_child_count(parent) / 2;

        lv_obj_move_to_index(currentButton, pos);

        lv_obj_scroll_to_view(currentButton, LV_ANIM_ON);
    }
}

static void event_handler_dn(lv_event_t * e)
{
    const lv_event_code_t code = lv_event_get_code(e);
    if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
        if(currentButton == NULL) return;
        const uint32_t index = lv_obj_get_index(currentButton);

        lv_obj_move_to_index(currentButton, index + 1);
        lv_obj_scroll_to_view(currentButton, LV_ANIM_ON);
    }
}



static void set_angle(void * img, int32_t v)
{   
    if(is_playing) {
    lv_image_set_rotation(img, v);
    }
}


void lv_example_image_3(void){
    imgx = lv_image_create(lv_screen_active());
    lv_image_set_src(imgx, &zheba);
    lv_obj_align(imgx, LV_ALIGN_CENTER, 0, -40);
  
    /* ��ȡͼƬ�Ŀ�Ⱥ͸߶� */
    int32_t img_width = ((lv_image_t *)imgx)->w /2;
    int32_t img_height = ((lv_image_t *)imgx)->h /2;

    /* ������ת֧��ΪͼƬ������ */
    lv_image_set_pivot(imgx, img_width, img_height);

    
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, imgx);
    lv_anim_set_exec_cb(&a, set_angle);
    lv_anim_set_values(&a, 0, 3600);
    lv_anim_set_duration(&a, 5000);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);

    lv_obj_add_flag(imgx,LV_OBJ_FLAG_HIDDEN);
}


static void hidden_handler(lv_event_t * e){
     lv_obj_t * obj = lv_event_get_target(e);
     lv_event_code_t code = lv_event_get_code(e);
     if(code == LV_EVENT_VALUE_CHANGED){
     if(lv_obj_has_state(obj, LV_STATE_CHECKED)){
        LV_LOG_USER("yes");
        lv_obj_add_flag(list1,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(list2,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(imgx,LV_OBJ_FLAG_HIDDEN);
     }else{
        LV_LOG_USER("no");
        lv_obj_clear_flag(list1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(list2,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(imgx,LV_OBJ_FLAG_HIDDEN);
     }
     }
}

void play_music(){
    lv_obj_t *current_label = lv_obj_get_child(currentButton, 0);
    const char *button_name = lv_label_get_text(current_label);
    // char output[326];
    // sprintf(output, "mplayer A:/song_List/%s.mp3 &", button_name);
    // LV_LOG_USER("%s", output);
    // system(output);

    char files[300];
    sprintf(files, "0:/song_List/%s.mp3", button_name);
    LV_LOG_USER("%s", files);
    MP3_decode_file(files);
    duration_time = get_total_duration(files);
    lv_timer_resume(timer);
}
void stop_music(){
    // ʹ�� killall ������ͣ mplayer ����
    // system("killall -STOP mplayer");
    MP3_suspend();
    lv_timer_pause(timer);
}
void resume_music() {
    // ʹ�� killall ����ָ� mplayer ����
    // system("killall -CONT mplayer");
    MP3_resume();
    lv_timer_resume(timer);
}
void kill_music(){
    MP3_decoder_Free();
    // system("killall -9 mplayer") ; ;//�ر�ԭ�еĽ���
    current_time=0;
}
void change_sound(int nums){
    // int volume = 40+(nums*60/100);
    // char command[50];
    // ʹ�� amixer ������������

    // sprintf(command, "amixer set Master %d%%", (int)(volume));
    // system(command);
    MP3_Set_volume(nums);
}


double get_total_duration(const char* filename) {
    char command[1024];
    char buffer[1024];
    double duration = 0.0;

    // ���������ַ���
    // snprintf(command, sizeof(command), "mplayer -identify -frames 0 -ao null \"%s\" 2>&1", filename);

    // // �򿪹ܵ���ȡ�������
    // FILE* pipe = popen(command, "r");
    // if (!pipe) {
    //     perror("popen failed");
    //     return -1;
    // }

    // // ��ȡ���������������ʱ��
    // while (fgets(buffer, sizeof(buffer), pipe)) {
    //     if (strstr(buffer, "ID_LENGTH=") == buffer) {
    //         sscanf(buffer, "ID_LENGTH=%lf", &duration);
    //         break;
    //     }
    // }

    // // �رչܵ�
    // pclose(pipe);

    //LV_LOG_USER("Total duration��: %f\n", (int)duration);
    //duration = (int)duration;
    //LV_LOG_USER("Total duration��: %d\n", (int)duration/60);
    //��ʱ�����뵽��ǩ��

    duration = MP3_Get_duration();
    
    char buf[1024];
    int m = (int)duration / 60;
    int s = (int)duration % 60;
    if (s < 10) {
        sprintf(buf,"0%d:0%d",m,s);
    }
    else {
        sprintf(buf,"0%d:%d",m,s);
    }

   
    lv_label_set_text(label3, buf); // ���ñ�ǩ�ı�
    //s
    LV_LOG_USER("ʱ��: %s\n", buf);
    return duration;
}

void my_timer_callback(lv_timer_t * timer){
    current_time ++;
    char buf[1024];
     int m = (int)current_time / 60;
    int s = (int)current_time % 60;
    if (s < 10) {
        sprintf(buf,"0%d:0%d",m,s);
    }
    else {
        sprintf(buf,"0%d:%d",m,s);
    }
    lv_label_set_text(label4, buf); // ���ñ�ǩ�ı�
    
    //
    if(current_time <= duration_time){
    int value = (current_time * 100) / duration_time;
    lv_slider_set_value(slider, value, LV_ANIM_OFF);
    }

    // LV_LOG_USER("Option: %s", xx);duration_time
    //
    if (current_time >= duration_time){
        //˳�򲥷�
        if(currentButton == NULL) return;
        if (strcmp(xx, "List") == 0){
        lv_obj_t * parent = lv_obj_get_parent(currentButton);
        uint32_t current_index = lv_obj_get_index(currentButton);
        uint32_t child_count = lv_obj_get_child_cnt(parent);
        uint32_t next_index = (current_index + 1) % child_count;

        lv_obj_t * pre_Button = lv_obj_get_child(parent, next_index);
        lv_obj_send_event(pre_Button , LV_EVENT_CLICKED, NULL);

        }
        //ѭ������
        if (strcmp(xx, "single") == 0){
        kill_music();
        play_music();

        }
        //�漴����
        if (strcmp(xx, "random") == 0){
        lv_obj_t * parent = lv_obj_get_parent(currentButton);
        uint32_t current_index = lv_obj_get_index(currentButton);
        uint32_t child_count = lv_obj_get_child_cnt(parent);
        uint32_t next_index = (current_index + 2) % child_count;

        lv_obj_t * pre_Button = lv_obj_get_child(parent, next_index);
        lv_obj_send_event(pre_Button , LV_EVENT_CLICKED, NULL);
        }
    }
}   