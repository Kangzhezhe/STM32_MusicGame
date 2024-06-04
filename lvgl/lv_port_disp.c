/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include <stdbool.h>
//#include "lcd_st7735.h"
#include "lcd.h"

/*********************
 *      DEFINES
 *********************/
#define MY_DISP_HOR_RES    320
#define MY_DISP_VER_RES    240

#ifndef MY_DISP_HOR_RES
    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen width, default value 320 is used for now.
    #define MY_DISP_HOR_RES    LCD_WIDTH
#endif

#ifndef MY_DISP_VER_RES
    #warning Please define or replace the macro MY_DISP_VER_RES with the actual screen height, default value 240 is used for now.
    #define MY_DISP_VER_RES    LCD_HIGH
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
static lv_display_t * disp ;
void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*------------------------------------
     * Create a display and set a flush_cb
     * -----------------------------------*/
    
    disp =  lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
		//lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90); 
    lv_display_set_flush_cb(disp, disp_flush);

    /* Example 1
     * One buffer for partial rendering*/
    __align(4) static lv_color_t buf_1_1[MY_DISP_HOR_RES*5];                          /*A buffer for 10 rows*/
    lv_display_set_buffers(disp, buf_1_1, NULL, sizeof(buf_1_1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    /* Example 2
    //  * Two buffers for partial rendering
    //  * In flush_cb DMA or similar hardware should be used to update the display in the background.*/
    // static lv_color_t buf_2_1[MY_DISP_HOR_RES * 10];
    // static lv_color_t buf_2_2[MY_DISP_HOR_RES * 10];
    // lv_display_set_buffers(disp, buf_2_1, buf_2_2, sizeof(buf_2_1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    // /* Example 3
    //  * Two buffers screen sized buffer for double buffering.
    //  * Both LV_DISPLAY_RENDER_MODE_DIRECT and LV_DISPLAY_RENDER_MODE_FULL works, see their comments*/
    // static lv_color_t buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES];
    // static lv_color_t buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES];
    // lv_display_set_buffers(disp, buf_3_1, buf_3_2, sizeof(buf_3_1), LV_DISPLAY_RENDER_MODE_DIRECT);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/
#include "dma.h"
/*Initialize your display and the required peripherals.*/
void LVGL_LCD_FSMC_DMA_pCallback(DMA_HandleTypeDef *_hdma)
{
   lv_display_flush_ready(disp);
 
   //为了减少栈帧的使用
//    disp->flushing = 0;
//    disp->flushing_last = 0;
}

static void disp_init(void)
{
    /*You code here*/
    //LCD_Init();
		 __HAL_DMA_ENABLE_IT(&hdma_memtomem_dma2_stream6, DMA_IT_TC | DMA_IT_TE);
        HAL_DMA_RegisterCallback(&hdma_memtomem_dma2_stream6,HAL_DMA_XFER_CPLT_CB_ID,LVGL_LCD_FSMC_DMA_pCallback);
}



volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}




/*Flush the content of the internal buffer the specific area on the display.
 *`px_map` contains the rendered image as raw pixel map and it should be copied to `area` on the display.
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_display_flush_ready()' has to be called when it's finished.*/
vu16 color[400];
vu16 test_lcd[400];
static void disp_flush(lv_display_t * disp_drv, const lv_area_t * area, uint8_t * px_map)
{

    if(disp_flush_enabled) {
        //LCD_Color_Fill(area->x1,area->y1,area->x2,area->y2,(uint16_t*)px_map);  
			
					LCD_Address_Set(area->x1,area->y1,area->x2,area->y2);
				 HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream6, (uint32_t) px_map, (uint32_t) &LCD->LCD_RAM,
												 ((area->x2 + 1) - area->x1) * ((area->y2 + 1) - area->y1));

            //test lcd 

//            u32 index=0; 
//            u32 totalpoint;
//            LCD_Set_Window(10,10,20,20);//ÉèÖÃÈ«ÆÁ´°¿Ú
//					totalpoint=20 * 20; 			//µÃµ½×ÜµãÊý
//					LCD_SetCursor(10,10);	//ÉèÖÃ¹â±êÎ»ÖÃ 
//            LCD_WriteRAM_Prepare();     //¿ªÊ¼Ð´ÈëGRAM	 	  
//            for(index=0;index<totalpoint;index++)
//            {
//                color[index]=BRED;	
//            }
//             HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream6, (uint32_t) color, (uint32_t) &LCD->LCD_RAM,
//			 								 20 * 20);
						
    }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    // lv_display_flush_ready(disp_drv);
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
