/************************************************************************
 * FilePath     : gui_game_scr.c
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

/*********************************************************************************
 *                                   DEFINES
 * *******************************************************************************/

/*********************************************************************************
 *                                   MACROS
 * *******************************************************************************/

/*********************************************************************************
 *                                  TYPEDEFS
 * *******************************************************************************/
static lv_obj_t *GameScrRoot = NULL;
static lv_obj_t *GameLabel   = NULL;

static lv_obj_t *game_btn    = NULL;
static lv_obj_t *BtnLabel     = NULL;




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
//#include <dirent.h>
#include <string.h>

#include "lvgl_app.h"


#define FALL_SPEED 2//下落速度  
#define TIMER_PERIOD 50 //
#define LENTH 100 // 长滑块默认长度

void fall_timer_cb(lv_timer_t * timer);
void Lfall_timer_cb(lv_timer_t * timer);
void press_envent(lv_event_t * e) ;
void Lpress_envent(lv_event_t * e);
static void draw_line_example(void);
void create_timer_cb(lv_timer_t * timer);


static void create_explosion_effect(lv_obj_t * parent, int x, int y);


//
// 定义结构体
typedef struct {
    u8 id;
    lv_obj_t *btn1;
    lv_timer_t *fall_timer;
    int speed;
    int pos;
} btn_timer_t;

// 定义结构体
typedef struct {
    u8 id;
    lv_obj_t *btn2;
    lv_timer_t *fall_timerx;
    int speed;
    int pos;
    int lenth;
} Lbtn_timer_t;
#define MAX_SHORT 15
#define MAX_LONG 5
static btn_timer_t* btn_timer[MAX_SHORT];
static u8 btn_timer_die[MAX_SHORT];
static Lbtn_timer_t* btnL_timer[MAX_LONG];
static u8 btnL_timer_die[MAX_LONG];

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

int goal = 0;
lv_obj_t * goal_label;


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



static int inf[MAX_SHORT*3]={
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

static int Linf[MAX_LONG*4]={
    10,0,FALL_SPEED+1,LENTH,
    15,80,FALL_SPEED+1,LENTH,
    20,160,FALL_SPEED+1,LENTH+50,
    25,240,FALL_SPEED+1,LENTH,
    28,0,FALL_SPEED+1,LENTH+100
};

static lv_timer_t *crete_timer;
void game(void){
    styles();
    stylesx();
    styleL();
    stylesxL();
     for (int i =0;i<MAX_SHORT;i++){
        btn_timer[i] = NULL;
        btn_timer_die[i] = 0;
    }
    for (int i = 0; i < MAX_LONG; i++)
    {
        btnL_timer[i] = NULL;
        btnL_timer_die[i] = 0;
    }

    
    goal_label = lv_label_create(GameScrRoot);

    // 创建一个样式对象
    static lv_style_t style_label;
    lv_style_init(&style_label);
    // 设置文本颜色为紫色
    lv_style_set_text_color(&style_label, lv_palette_main(LV_PALETTE_PURPLE));
    // 将样式应用到标签对象上
    lv_obj_add_style(goal_label, &style_label, 0);

    lv_obj_align(goal_label, LV_ALIGN_TOP_MID, 0, 0);
    lv_label_set_text_fmt(goal_label, "%d", goal);

    crete_timer = lv_timer_create(create_timer_cb, 1000, NULL);
  
   
    draw_line_example();
}


void Lpress_envent(lv_event_t * e){
    Lbtn_timer_t *btn_timer = (Lbtn_timer_t *)e->user_data;
    lv_obj_t * btn1 = lv_event_get_target(e);
    lv_coord_t y = lv_obj_get_y(btn1);
    if(y+btn_timer->lenth>200){
        LV_LOG_USER("加分");
        goal += 1;
    }
    lv_label_set_text_fmt(goal_label, "%d", goal);
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
    if(y > 240) {
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
    if (y > 240) {
        LV_LOG_USER("失败");
        destroy_btn_timer(btn_timer);
    }
    //
    
}

void press_envent(lv_event_t * e) {
    btn_timer_t *btn_timer = (btn_timer_t *)e->user_data;
    lv_obj_t * btn1 = lv_event_get_target(e);
    lv_coord_t y = lv_obj_get_y(btn1);
    lv_coord_t x = lv_obj_get_x(btn1);
    if(y+20>200){
        //200为判断边界
    LV_LOG_USER("加分");
    destroy_btn_timer(btn_timer);
    goal += 50;
    
    create_explosion_effect(GameScrRoot, x+40, y+10);


    }else{
    LV_LOG_USER("扣分");
    goal -= 10;
    }

    // lv_label_cut_text(goal_label, 0, 1);
    lv_label_set_text_fmt(goal_label, "%d", goal);
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
        btn_timer_die[btn_timer->id] = 1;
        lv_free(btn_timer);
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
        btnL_timer_die[btn_timer->id] = 1;
        
        lv_free(btn_timer);
        max++;
    }
}

void game_over(){
    static lv_style_t styleb;
    lv_style_init(&styleb);

    lv_style_set_bg_opa(&styleb, LV_OPA_COVER);                    
    lv_style_set_bg_color(&styleb, lv_palette_main(LV_PALETTE_BLUE));     // 璧峰?嬮?滆壊
    lv_style_set_bg_grad_color(&styleb, lv_palette_main(LV_PALETTE_RED)); // 缁撴潫棰滆壊
    lv_style_set_bg_grad_dir(&styleb, LV_GRAD_DIR_HOR);                    // 娓愬彉鏂瑰悜锛屾按骞?
    lv_obj_t *label = lv_label_create(GameScrRoot);
    lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN);
    lv_obj_add_style(label, &styleb, 0);
    lv_label_set_text(label, "Game Over");
    lv_obj_align_to(label, GameScrRoot, LV_ALIGN_CENTER, 0, 0);

}

int min1=0;
int minL=0;

void create_timer_cb(lv_timer_t * timer){
    int *x = inf;
   
    currnet_time++;
    printf("currnet_time %d\r\n",currnet_time);
    for(int i=min1;i<MAX_SHORT;i++){
        if(get(x,i,0)==currnet_time){
            btn_timer[i] = lv_malloc(sizeof(btn_timer_t));
            btn_timer[i]->speed = get(x, i, 2);
            btn_timer[i]->pos = get(x,i,1);
            btn_timer[i]->btn1 = lv_button_create(GameScrRoot);
            btn_timer[i]->id = i;
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

    
    int *y = Linf;

    for(int i=minL;i<5;i++){
        if(getL(y,i,0)==currnet_time){
            btnL_timer[i] = lv_malloc(sizeof(Lbtn_timer_t));
            btnL_timer[i]->speed = getL(y, i, 2);
            btnL_timer[i]->pos = getL(y,i,1);
            btnL_timer[i]->lenth = getL(y,i,3);
            btnL_timer[i]->btn2 = lv_button_create(GameScrRoot);
            btnL_timer[i]->id = i;
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
    if(max==MAX_LONG+MAX_SHORT){
        LV_LOG_USER("游戏结束");
        game_over();
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
    line1 = lv_line_create(GameScrRoot);
    lv_line_set_points(line1,(lv_point_precise_t*)line_points, sizeof(line_points) / sizeof(lv_point_t));     /*Set the points*/
    lv_obj_add_style(line1, &style_line, 0);
    // lv_obj_center(line1);
    lv_obj_align(line1, LV_ALIGN_TOP_LEFT, 0, 0);
}

static void explosion_anim_cb(void * var, int32_t v) {
    // 从宽度动画计算当前高度
    int width = (v - 80) * (25 - 20) / (100 - 60) + 20;
    lv_obj_set_size(var, v, width);
    lv_obj_set_style_opa(var, 255 - (v * 2.55), 0);  // 根据宽度调整透明度
}

static void anim_del(lv_anim_t * a) {
    lv_obj_del((lv_obj_t *)a->var);
}

static void create_explosion_effect(lv_obj_t * parent, int x, int y) {
    // 创建一个矩形对象
    lv_obj_t * obj = lv_obj_create(parent);
    lv_obj_set_size(obj, 80, 20);  // 初始尺寸
    lv_obj_align(obj, LV_ALIGN_CENTER, x - 160, y - 120);
    lv_obj_set_style_bg_color(obj, lv_color_make(255, 100, 0), 0);  // 设置背景颜色为红色

    // 创建动画
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_values(&a, 80, 100);  // 从 60 像素增长到 100 像素
    lv_anim_set_time(&a, 800);  // 动画时间 500 毫秒
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);  // 动画路径
    lv_anim_set_exec_cb(&a, explosion_anim_cb);  // 设置动画执行回调
    // lv_anim_set_ready_cb(&a, (lv_anim_ready_cb_t)lv_obj_del);  // 动画结束时删除对象
    // lv_anim_set_ready_cb(&a, del_anim);  // 动画结束时删除对象
    lv_anim_set_ready_cb(&a, anim_del);  // 动画结束时删除对象

    // 启动动画
    lv_anim_start(&a);
}



/*********************************************************************************
 *                              STATIC FUNCTION
 * *******************************************************************************/
void game_btn_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);

    if (obj == game_btn) {
        printf("Game game_btn is pressed! printf\r\n");
        // ScrMgrPopScr(true);
        ScrMgrSwitchScr(GUI_MIAN_SCR_ID, true);
    }
}

/*********************************************************************************
 *                              GLOBAL FUNCTION
 * *******************************************************************************/
static lv_obj_t *Gui_GameScrCreate(lv_obj_t *parent)
{
    GameScrRoot = lv_obj_create(parent);
    lv_obj_set_size(GameScrRoot, lv_pct(100), lv_pct(100));
    // lv_obj_set_style_bg_color(GameScrRoot, lv_color_black(), LV_PART_MAIN);

    // GameLabel = lv_label_create(GameScrRoot);
    // lv_obj_set_style_text_color(GameLabel, lv_color_white(), LV_PART_MAIN);
    // lv_label_set_text(GameLabel, "Game");

    game_btn = lv_btn_create(GameScrRoot);
    lv_obj_set_size(game_btn, 20, 20);
    BtnLabel = lv_label_create(game_btn);
    lv_label_set_text(BtnLabel, "ret");
    // lv_obj_add_flag(game_btn, LV_OBJ_FLAG_HIDDEN);

    // lv_obj_align_to(GameLabel, GameScrRoot, LV_ALIGN_CENTER, 0, -30);
    lv_obj_center(BtnLabel);
    lv_obj_align_to(game_btn, GameScrRoot, LV_ALIGN_TOP_LEFT, 0, 20);
    lv_obj_add_event_cb(game_btn, game_btn_event_cb, LV_EVENT_CLICKED, NULL);

    game();

    printf("game created\r\n");
    return GameScrRoot;
}

static void Gui_GameScrLayout(void)
{
   
}

static void Gui_GameScrEnter(void)
{
    Gui_GameScrLayout();
    printf("game enter\r\n");
    // lv_obj_add_event_cb(game_btn, game_btn_event_cb, LV_EVENT_CLICKED, NULL);
}

static void Gui_GameScrExit(void)
{
    printf("game exit\r\n");
    // lv_obj_remove_event_cb(game_btn, game_btn_event_cb);
}

static void Gui_GameScrDestory(void)
{
    for (int i =0;i<MAX_SHORT;i++){
        if (!btn_timer_die[i]&&btn_timer[i]) {
            lv_timer_del(btn_timer[i]->fall_timer);
            lv_obj_del(btn_timer[i]->btn1);
            lv_free(btn_timer[i]);
            printf("del timer %d\r\n",i);
        }
    }
    for (int i =0;i<MAX_LONG;i++){
        if (!btnL_timer_die[i]&&btnL_timer[i]) {
            lv_timer_del(btnL_timer[i]->fall_timerx);
            lv_obj_del(btnL_timer[i]->btn2);
            lv_free(btnL_timer[i]);
            printf("del timer L %d\r\n",i);
        }
    }
    lv_timer_del(crete_timer);
    min1 = 0;
    max = 0;
    currnet_time = 0;
    minL = 0;
    goal = 0;


    lv_obj_clean(GameScrRoot);
    lv_obj_del_async(GameScrRoot);
    printf("game destory\r\n");
}

const SCR_MGR_SCR_HANDLE_T Gui_GameScrHandle = {
    .ScrId      = GUI_GAME_SCR_ID,
    .ScrCreate  = Gui_GameScrCreate,
    .ScrEnter   = Gui_GameScrEnter,
    .ScrExit    = Gui_GameScrExit,
    .ScrDestroy = Gui_GameScrDestory,
};

SCR_MGR_REG(Gui_GameScrHandle);