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

#define FALL_SPEED 2//???????  
#define TIMER_PERIOD 50 //


void fall_timer_cb(lv_timer_t * timer);
void press_envent(lv_event_t * e) ;
static void draw_line_example(void);
void create_timer_cb(lv_timer_t * timer);
//
// ???????
typedef struct {
    lv_obj_t *btn1;
    lv_timer_t *fall_timer;
    int speed;
    int pos;
} btn_timer_t;


void destroy_btn_timer(btn_timer_t *btn_timer);
static lv_style_t style;
static lv_style_t style_pr;
static lv_style_t style1;
static lv_style_t style_pr1;

int w =3;
int currnet_time =0;
int get (int * x,int i,int j){
    return  x[i*w+j];
}

void styles(){
    //static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_radius(&style, 3);

    lv_style_set_bg_opa(&style, LV_OPA_100);
    lv_style_set_bg_color(&style, lv_color_hex(0x33FFDD));
    lv_style_set_bg_grad_color(&style, lv_color_hex(0x33FFDD));
    lv_style_set_bg_grad_dir(&style, LV_GRAD_DIR_VER);

    lv_style_set_border_opa(&style, LV_OPA_40);
    lv_style_set_border_width(&style, 2);
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_GREY));

    lv_style_set_shadow_width(&style, 8);
    lv_style_set_shadow_color(&style, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_shadow_offset_y(&style, 8);

    lv_style_set_outline_opa(&style, LV_OPA_COVER);
    lv_style_set_outline_color(&style, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_set_text_color(&style, lv_color_white());
    lv_style_set_pad_all(&style, 10);

    /*Init the pressed style*/
    // static lv_style_t style_pr;
    lv_style_init(&style_pr);

    /*Add a large outline when pressed*/
    lv_style_set_outline_width(&style_pr, 15);
    lv_style_set_outline_opa(&style_pr, LV_OPA_TRANSP);

    lv_style_set_translate_y(&style_pr, 0);
    lv_style_set_shadow_offset_y(&style_pr, 3);
    lv_style_set_bg_color(&style_pr, lv_color_hex(0xFF3333));
    lv_style_set_bg_grad_color(&style_pr, lv_color_hex(0xFF3333));

    /*Add a transition to the outline*/
    static lv_style_transition_dsc_t trans;
    static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, 0};
    lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);

    lv_style_set_transition(&style_pr, &trans);
}


void stylesx(){
    //static lv_style_t style;
    lv_style_init(&style1);

    lv_style_set_radius(&style1, 3);

    lv_style_set_bg_opa(&style1, LV_OPA_100);
    lv_style_set_bg_color(&style1, lv_color_hex(0xFFBB66));
    lv_style_set_bg_grad_color(&style1, lv_color_hex(0xFFBB66));
    lv_style_set_bg_grad_dir(&style1, LV_GRAD_DIR_VER);

    lv_style_set_border_opa(&style1, LV_OPA_40);
    lv_style_set_border_width(&style1, 2);
    lv_style_set_border_color(&style1, lv_palette_main(LV_PALETTE_GREY));

    lv_style_set_shadow_width(&style1, 8);
    lv_style_set_shadow_color(&style1, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_shadow_offset_y(&style1, 8);

    lv_style_set_outline_opa(&style1, LV_OPA_COVER);
    lv_style_set_outline_color(&style1, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_set_text_color(&style1, lv_color_white());
    lv_style_set_pad_all(&style1, 10);

    /*Init the pressed style*/
    // static lv_style_t style_pr;
    lv_style_init(&style_pr1);

    /*Add a large outline when pressed*/
    lv_style_set_outline_width(&style_pr1, 15);
    lv_style_set_outline_opa(&style_pr1, LV_OPA_TRANSP);

    lv_style_set_translate_y(&style_pr1, 0);
    lv_style_set_shadow_offset_y(&style_pr1, 3);
    lv_style_set_bg_color(&style_pr1, lv_color_hex(0xFFFF33));
    lv_style_set_bg_grad_color(&style_pr1, lv_color_hex(0xFFFF33));

    /*Add a transition to the outline*/
    // static lv_style_transition_dsc_t trans;
    // static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, 0};
    // lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);

    // lv_style_set_transition(&style_pr1, &trans);
}
// ????????
static int inf[10*3]={1,0,FALL_SPEED,
                2,80,FALL_SPEED,
                2,160,FALL_SPEED,
                2,240,FALL_SPEED,
                4,0,FALL_SPEED,
                4,240,FALL_SPEED,
                5,160,FALL_SPEED,
                6,120,FALL_SPEED,
                7,240,FALL_SPEED,
                8,0,FALL_SPEED
};

void game_UI(void) {
    styles();
    stylesx();
    
    lv_timer_t *crete_timer = lv_timer_create(create_timer_cb, 1000, inf);
  
   
    draw_line_example();
}

void fall_timer_cb(lv_timer_t * timer) {
    btn_timer_t *btn_timer = (btn_timer_t *)timer->user_data;
    lv_obj_t * btn1 = btn_timer->btn1;
    lv_coord_t y = lv_obj_get_y(btn1);
    y += btn_timer->speed;
    lv_obj_set_y(btn1, y);

    if(y>160){
        //lv_obj_remove_style(btn1, &style_pr, 0);
        // lv_obj_set_style_bg_color(btn1, lv_color_hex(0xFFBB66), 0);
        // lv_obj_set_style_bg_grad_color(btn1, lv_color_hex(0xFFBB66), 0);
        lv_obj_remove_style(btn1, &style, 0);
        lv_obj_remove_style(btn1, &style_pr, LV_STATE_PRESSED);
        lv_obj_add_style(btn1, &style1, 0);
         lv_obj_add_style(btn1, &style_pr1, LV_STATE_PRESSED);

    }
    // ??ö™???????????
    if (y > lv_obj_get_height(lv_scr_act())) {
        LV_LOG_USER("???%d",y);
        destroy_btn_timer(btn_timer);
    }
    //
    
}

void press_envent(lv_event_t * e) {
    btn_timer_t *btn_timer = (btn_timer_t *)e->user_data;
    lv_obj_t * btn1 = lv_event_get_target(e);
    lv_coord_t y = lv_obj_get_y(btn1);
    if(y>160){
        //160??§Ø???
    LV_LOG_USER("???");
    destroy_btn_timer(btn_timer);
    }else{
    LV_LOG_USER("???");
    }
}

int max=0;

void destroy_btn_timer(btn_timer_t *btn_timer) {
    if (btn_timer) {
        if (btn_timer->fall_timer) {
            lv_timer_del(btn_timer->fall_timer);
        }
        if (btn_timer->btn1) {
            lv_obj_del(btn_timer->btn1);
        }
        
        free(btn_timer);
        max++;
    }
}

//
//????????????????????§Ó??????
int min=0;
//
void create_timer_cb(lv_timer_t * timer){

    int *x = timer->user_data;
    btn_timer_t* btn_timer[10];
    currnet_time++;
    for(int i=min;i<10;i++){
        if(get(x,i,0)==currnet_time){
            btn_timer[i] = malloc(sizeof(btn_timer_t));
            btn_timer[i]->speed = get(x, i, 2);
            btn_timer[i]->pos = get(x,i,1);
            btn_timer[i]->btn1 = lv_button_create(lv_scr_act());
            lv_obj_remove_style_all(btn_timer[i]->btn1);                          /*Remove the style coming from the theme*/
            lv_obj_add_style(btn_timer[i]->btn1, &style, 0);
            lv_obj_add_style(btn_timer[i]->btn1, &style_pr, LV_STATE_PRESSED);
            lv_obj_set_size(btn_timer[i]->btn1, 80, 20);
            lv_obj_align(btn_timer[i]->btn1,  LV_ALIGN_TOP_LEFT, 0+btn_timer[i]->pos, 0);
            lv_obj_add_event_cb(btn_timer[i]->btn1, press_envent, LV_EVENT_CLICKED, btn_timer[i]);
        
            // ?????????
            btn_timer[i]->fall_timer = lv_timer_create(fall_timer_cb, TIMER_PERIOD, btn_timer[i]);
            min=i+1;
            }
        else if(get(x,i,0)>currnet_time){
            break;}
        
    } 
    if(max==10){
        LV_LOG_USER("???????");
    }
   
}

static void draw_line_example(void) {
    // ??????????????
    static lv_point_t line_points[] = { {0, 160}, {320, 160} };


    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 5);
    lv_style_set_line_color(&style_line, lv_color_hex(0x000000));
    lv_style_set_line_rounded(&style_line, true);                                  // ??????????

    lv_obj_t * line1;
    line1 = lv_line_create(lv_screen_active());
    lv_line_set_points(line1, (lv_point_precise_t*)line_points, sizeof(line_points) / sizeof(lv_point_t));     /*Set the points*/
    lv_obj_add_style(line1, &style_line, 0);
    lv_obj_center(line1);
}

