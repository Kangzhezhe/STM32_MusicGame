#include <src/core/lv_obj.h>
#include <src/core/lv_obj_event.h>
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_style.h>
#include <src/display/lv_display.h>
#include <src/misc/lv_area.h>
#include <src/misc/lv_event.h>
#include <src/misc/lv_log.h>
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

#define FALL_SPEED 2//下落速度  
#define TIMER_PERIOD 50 //
#define LENTH 100 // 长滑块默认长度

void fall_timer_cb(lv_timer_t * timer);
void Lfall_timer_cb(lv_timer_t * timer);
void press_envent(lv_event_t * e) ;
void Lpress_envent(lv_event_t * e);
static void draw_line_example(void);
void create_timer_cb(lv_timer_t * timer);

//
// 定义结构体
typedef struct {
    lv_obj_t *btn1;
    lv_timer_t *fall_timer;
    int speed;
    int pos;
} btn_timer_t;

// 定义结构体
typedef struct {
    lv_obj_t *btn2;
    lv_timer_t *fall_timerx;
    int speed;
    int pos;
    int lenth;
} Lbtn_timer_t;


void destroy_btn_timer(btn_timer_t *btn_timer);
void destroy_Lbtn_timer(Lbtn_timer_t *btn_timer);
static lv_style_t style;
static lv_style_t style_pr;
static lv_style_t style1;
static lv_style_t style_pr1;

static lv_style_t stylex;
static lv_style_t style_prx;
static lv_style_t stylex1;
static lv_style_t style_prx1;

int w =3;
int currnet_time =0;
int get (int * x,int i,int j){
    return  x[i*w+j];
}
int wl=4;
int getL (int * x,int i,int j){
    return  x[i*wl+j];
}


void styleL(){
    //static lv_style_t style;
    lv_style_init(&stylex);

    lv_style_set_radius(&stylex, 3);

    lv_style_set_bg_opa(&stylex, LV_OPA_100);
    lv_style_set_bg_color(&stylex, lv_color_hex(0x99FFFF));
    lv_style_set_bg_grad_color(&stylex, lv_color_hex(0x00BBFF));
    lv_style_set_bg_grad_dir(&stylex, LV_GRAD_DIR_VER);

    lv_style_set_border_opa(&stylex, LV_OPA_40);
    lv_style_set_border_width(&stylex, 2);
    lv_style_set_border_color(&stylex, lv_palette_main(LV_PALETTE_GREY));

    lv_style_set_shadow_width(&stylex, 8);
    lv_style_set_shadow_color(&stylex, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_shadow_offset_y(&stylex, 8);

    lv_style_set_outline_opa(&stylex, LV_OPA_COVER);
    lv_style_set_outline_color(&stylex, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_set_text_color(&stylex, lv_color_white());
    lv_style_set_pad_all(&stylex, 10);

    /*Init the pressed style*/
    // static lv_style_t style_pr;
    lv_style_init(&style_prx);

    /*Add a large outline when pressed*/
    lv_style_set_outline_width(&style_prx, 15);
    lv_style_set_outline_opa(&style_prx, LV_OPA_TRANSP);

    lv_style_set_translate_y(&style_prx, 0);
    lv_style_set_shadow_offset_y(&style_prx, 3);
    lv_style_set_bg_color(&style_prx, lv_color_hex(0xFFB7DD));
    lv_style_set_bg_grad_color(&style_prx, lv_color_hex(0xFF0088));
    lv_style_set_bg_grad_dir(&style_prx, LV_GRAD_DIR_VER);

    /*Add a transition to the outline*/
    static lv_style_transition_dsc_t trans;
    static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, 0};
    lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);

    lv_style_set_transition(&style_prx, &trans);
}

void stylesxL(){
    //static lv_style_t style;
    // lv_style_init(&stylex1);

    // lv_style_set_radius(&stylex1, 3);

    // lv_style_set_bg_opa(&stylex1, LV_OPA_100);
    // lv_style_set_bg_color(&stylex1, lv_color_hex(0xFFBB66));
    // lv_style_set_bg_grad_color(&stylex1, lv_color_hex(0xFFBB66));
    // lv_style_set_bg_grad_dir(&stylex1, LV_GRAD_DIR_VER);

    // lv_style_set_border_opa(&stylex1, LV_OPA_40);
    // lv_style_set_border_width(&stylex1, 2);
    // lv_style_set_border_color(&stylex1, lv_palette_main(LV_PALETTE_GREY));

    // lv_style_set_shadow_width(&stylex1, 8);
    // lv_style_set_shadow_color(&stylex1, lv_palette_main(LV_PALETTE_GREY));
    // lv_style_set_shadow_offset_y(&stylex1, 8);

    // lv_style_set_outline_opa(&stylex1, LV_OPA_COVER);
    // lv_style_set_outline_color(&stylex1, lv_palette_main(LV_PALETTE_BLUE));

    // lv_style_set_text_color(&stylex1, lv_color_white());
    // lv_style_set_pad_all(&stylex1, 10);

    /*Init the pressed style*/
    // static lv_style_t style_pr;
    lv_style_init(&style_prx1);

    /*Add a large outline when pressed*/
    lv_style_set_outline_width(&style_prx1, 15);
    lv_style_set_outline_opa(&style_prx1, LV_OPA_TRANSP);

    lv_style_set_translate_y(&style_prx1, 0);
    lv_style_set_shadow_offset_y(&style_prx1, 3);
    lv_style_set_bg_color(&style_prx1, lv_color_hex(0xFFFFBB));
    lv_style_set_bg_grad_color(&style_prx1, lv_color_hex(0xFFFF33));

   
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
//


//
void game_L(void){
    styleL();
    stylesxL();
    //
    // Lbtn_timer_t *btn_timer = malloc(sizeof(Lbtn_timer_t));
    // btn_timer->lenth=LENTH;
    // btn_timer->pos = 0;
    // btn_timer->btn2 = lv_obj_create(lv_scr_act());
    // btn_timer->speed = FALL_SPEED;
    // lv_obj_remove_style_all(btn_timer->btn2);
    // lv_obj_add_style(btn_timer->btn2, &stylex, 0);
    // lv_obj_add_style(btn_timer->btn2, &style_prx, LV_STATE_PRESSED);

    // lv_obj_set_size(btn_timer->btn2, 80, btn_timer->lenth);
    // lv_obj_align(btn_timer->btn2,LV_ALIGN_TOP_LEFT,0+btn_timer->pos,-btn_timer->lenth);
    // lv_obj_add_event_cb(btn_timer->btn2, Lpress_envent, LV_EVENT_PRESSING, btn_timer);
    // btn_timer->fall_timerx = lv_timer_create(Lfall_timer_cb, TIMER_PERIOD, btn_timer);
    // //
    static int Linf[5*4]={1,0,FALL_SPEED,LENTH,
                    5,80,FALL_SPEED,LENTH,
                    10,160,FALL_SPEED,LENTH+50,
                    15,240,FALL_SPEED,LENTH,
                    20,0,FALL_SPEED,LENTH+100
    };
    lv_timer_t *crete_timer = lv_timer_create(create_timer_cb, 1000, Linf);
    draw_line_example();
}

void game_UI(void) {
    styles();
    stylesx();
    
    // 按键数据
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
    lv_timer_t *crete_timer = lv_timer_create(create_timer_cb, 1000, inf);
  
   
    draw_line_example();
}

static int inf[15*3]={
    1,0,FALL_SPEED,
    2,80,FALL_SPEED,
    2,160,FALL_SPEED,
    2,240,FALL_SPEED,
    4,0,FALL_SPEED,
    4,240,FALL_SPEED,
    5,160,FALL_SPEED,
    6,120,FALL_SPEED,
    7,240,FALL_SPEED,
    8,0,FALL_SPEED,
    32,80,FALL_SPEED,
    34,160,FALL_SPEED,
    34,240,FALL_SPEED,
    36,0,FALL_SPEED,
    36,160,FALL_SPEED,
};

static int Linf[5*4]={
    10,0,FALL_SPEED+1,LENTH,
    15,80,FALL_SPEED+1,LENTH,
    20,160,FALL_SPEED+1,LENTH+50,
    25,240,FALL_SPEED+1,LENTH,
    28,0,FALL_SPEED+1,LENTH+100
};

void game(void){
    styles();
    stylesx();
    styleL();
    stylesxL();
    lv_timer_t *crete_timer = lv_timer_create(create_timer_cb, 1000, NULL);
  
   
    draw_line_example();
}

void Lpress_envent(lv_event_t * e){
    Lbtn_timer_t *btn_timer = (Lbtn_timer_t *)e->user_data;
    lv_obj_t * btn1 = lv_event_get_target(e);
    lv_coord_t y = lv_obj_get_y(btn1);
    if(y+btn_timer->lenth>200){
        LV_LOG_USER("加分");

    }

}


void Lfall_timer_cb(lv_timer_t * timer){

    Lbtn_timer_t *btn_timer = (Lbtn_timer_t *)timer->user_data;
    lv_obj_t * btn2 = btn_timer->btn2;
    lv_coord_t y = lv_obj_get_y(btn2);
    y += btn_timer->speed;
    lv_obj_set_y(btn2, y);

    if(y+btn_timer->lenth>200){
        lv_obj_remove_style(btn2, &style_prx, LV_STATE_PRESSED);  
        lv_obj_add_style(btn2, &style_prx1, LV_STATE_PRESSED);
    }
     // 检查按钮是否超出屏幕底部
    if(y > lv_obj_get_height(lv_scr_act())) {
        LV_LOG_USER("失败");
        destroy_Lbtn_timer(btn_timer);
        //lv_obj_set_y(btn2, -btn_timer->lenth);  // 重置
    }
}


void fall_timer_cb(lv_timer_t * timer) {
    btn_timer_t *btn_timer = (btn_timer_t *)timer->user_data;
    lv_obj_t * btn1 = btn_timer->btn1;
    lv_coord_t y = lv_obj_get_y(btn1);
    y += btn_timer->speed;
    lv_obj_set_y(btn1, y);

    if(y+20>200){
        //lv_obj_remove_style(btn1, &style_pr, 0);
        // lv_obj_set_style_bg_color(btn1, lv_color_hex(0xFFBB66), 0);
        // lv_obj_set_style_bg_grad_color(btn1, lv_color_hex(0xFFBB66), 0);
        lv_obj_remove_style(btn1, &style, 0);
        lv_obj_remove_style(btn1, &style_pr, LV_STATE_PRESSED);
        lv_obj_add_style(btn1, &style1, 0);
        lv_obj_add_style(btn1, &style_pr1, LV_STATE_PRESSED);

    }
    // 检查按钮是否超出屏幕底部
    if (y > lv_obj_get_height(lv_scr_act())) {
        LV_LOG_USER("失败");
        destroy_btn_timer(btn_timer);
    }
    //
    
}

void press_envent(lv_event_t * e) {
    btn_timer_t *btn_timer = (btn_timer_t *)e->user_data;
    lv_obj_t * btn1 = lv_event_get_target(e);
    lv_coord_t y = lv_obj_get_y(btn1);
    if(y+20>200){
        //200为判断边界
    LV_LOG_USER("加分");
    destroy_btn_timer(btn_timer);
    }else{
    LV_LOG_USER("扣分");
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

void destroy_Lbtn_timer(Lbtn_timer_t *btn_timer) {
    if (btn_timer) {
        if (btn_timer->fall_timerx) {
            lv_timer_del(btn_timer->fall_timerx);
        }
        if (btn_timer->btn2) {
            lv_obj_del(btn_timer->btn2);
        }
        
        free(btn_timer);
        max++;
    }
}
//
//按键时许顺序给，可以运行才能更快
// int min=0;
//
// void create_timer_cb(lv_timer_t * timer){

    // int *x = timer->user_data;
    // btn_timer_t* btn_timer[10];
    // currnet_time++;
    // for(int i=min;i<10;i++){
    //     if(get(x,i,0)==currnet_time){
    //         btn_timer[i] = malloc(sizeof(btn_timer_t));
    //         btn_timer[i]->speed = get(x, i, 2);
    //         btn_timer[i]->pos = get(x,i,1);
    //         btn_timer[i]->btn1 = lv_button_create(lv_scr_act());
    //         lv_obj_remove_style_all(btn_timer[i]->btn1);                          /*Remove the style coming from the theme*/
    //         lv_obj_add_style(btn_timer[i]->btn1, &style, 0);
    //         lv_obj_add_style(btn_timer[i]->btn1, &style_pr, LV_STATE_PRESSED);
    //         lv_obj_set_size(btn_timer[i]->btn1, 80, 20);
    //         lv_obj_align(btn_timer[i]->btn1,  LV_ALIGN_TOP_LEFT, 0+btn_timer[i]->pos, 0);
    //         lv_obj_add_event_cb(btn_timer[i]->btn1, press_envent, LV_EVENT_PRESSED, btn_timer[i]);
        
    //         // 创建定时器
    //         btn_timer[i]->fall_timer = lv_timer_create(fall_timer_cb, TIMER_PERIOD, btn_timer[i]);
    //         min=i+1;
    //         }
    //     else if(get(x,i,0)>currnet_time){
    //         break;}
        
    // } 
    // if(max==10){
    //     LV_LOG_USER("游戏结束");
    // }

//     int *x = timer->user_data;
//     Lbtn_timer_t* btn_timer[5];
//     currnet_time++;
//     for(int i=min;i<5;i++){
//         if(getL(x,i,0)==currnet_time){
//             btn_timer[i] = malloc(sizeof(Lbtn_timer_t));
//             btn_timer[i]->speed = getL(x, i, 2);
//             btn_timer[i]->pos = getL(x,i,1);
//             btn_timer[i]->lenth = getL(x,i,3);
//             btn_timer[i]->btn2 = lv_button_create(lv_scr_act());
//             lv_obj_remove_style_all(btn_timer[i]->btn2);                          /*Remove the style coming from the theme*/
//             lv_obj_add_style(btn_timer[i]->btn2, &stylex, 0);
//             lv_obj_add_style(btn_timer[i]->btn2, &style_prx, LV_STATE_PRESSED);
//             lv_obj_set_size(btn_timer[i]->btn2, 80, btn_timer[i]->lenth);
//             lv_obj_align(btn_timer[i]->btn2,  LV_ALIGN_TOP_LEFT, 0+btn_timer[i]->pos, -btn_timer[i]->lenth);
//             lv_obj_add_event_cb(btn_timer[i]->btn2, Lpress_envent, LV_EVENT_PRESSING, btn_timer[i]);
        
//             // 创建定时器
//             btn_timer[i]->fall_timerx = lv_timer_create(Lfall_timer_cb, TIMER_PERIOD, btn_timer[i]);
//             min=i+1;
//             }
//         else if(get(x,i,0)>currnet_time){
//             break;}
        
//     } 
//     if(max==5){
//         LV_LOG_USER("游戏结束");
//     }
// }

int min1=0;
int minL=0;
void create_timer_cb(lv_timer_t * timer){
    int *x = inf;
    btn_timer_t* btn_timer[15];
    currnet_time++;
    for(int i=min1;i<15;i++){
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
            lv_obj_add_event_cb(btn_timer[i]->btn1, press_envent, LV_EVENT_PRESSED, btn_timer[i]);
        
            // 创建定时器
            btn_timer[i]->fall_timer = lv_timer_create(fall_timer_cb, TIMER_PERIOD, btn_timer[i]);
            min1=i+1;
            }
        else if(get(x,i,0)>currnet_time){
            break;}
        
    } 

    //

    int *y = Linf;
    Lbtn_timer_t* btnL_timer[5];
    for(int i=minL;i<5;i++){
        if(getL(y,i,0)==currnet_time){
            btnL_timer[i] = malloc(sizeof(Lbtn_timer_t));
            btnL_timer[i]->speed = getL(y, i, 2);
            btnL_timer[i]->pos = getL(y,i,1);
            btnL_timer[i]->lenth = getL(y,i,3);
            btnL_timer[i]->btn2 = lv_button_create(lv_scr_act());
            lv_obj_remove_style_all(btnL_timer[i]->btn2);                          /*Remove the style coming from the theme*/
            lv_obj_add_style(btnL_timer[i]->btn2, &stylex, 0);
            lv_obj_add_style(btnL_timer[i]->btn2, &style_prx, LV_STATE_PRESSED);
            lv_obj_set_size(btnL_timer[i]->btn2, 80, btnL_timer[i]->lenth);
            lv_obj_align(btnL_timer[i]->btn2,  LV_ALIGN_TOP_LEFT, 0+btnL_timer[i]->pos, -btnL_timer[i]->lenth);
            lv_obj_add_event_cb(btnL_timer[i]->btn2, Lpress_envent, LV_EVENT_PRESSING, btnL_timer[i]);
        
            // 创建定时器
            btnL_timer[i]->fall_timerx = lv_timer_create(Lfall_timer_cb, TIMER_PERIOD, btnL_timer[i]);
            minL=i+1;
            }
        else if(get(y,i,0)>currnet_time){
            break;}
    
    }
    if(max==20){
        LV_LOG_USER("游戏结束");
    }
}



static void draw_line_example(void) {
    // 定义线的起点和终点
    static lv_point_t line_points[] = { {0, 200}, {320, 200} };


    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 2);
    lv_style_set_line_color(&style_line, lv_color_hex(0x000000));
    lv_style_set_line_rounded(&style_line, true);                                  // 将线对象居中

    lv_obj_t * line1;
    line1 = lv_line_create(lv_screen_active());
    lv_line_set_points(line1,(lv_point_precise_t*)line_points, sizeof(line_points) / sizeof(lv_point_t));     /*Set the points*/
    lv_obj_add_style(line1, &style_line, 0);
    // lv_obj_center(line1);
    lv_obj_align(line1, LV_ALIGN_TOP_LEFT, 0, 0);
}

