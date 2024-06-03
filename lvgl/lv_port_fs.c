/**
 * @file lv_port_fs_templ.c
 *
 */

/*Copy this file as "lv_port_fs.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_fs.h"
#include "../../lvgl.h"
#include <stdio.h>

#include "fatfs.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void fs_init(void);

static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode);
static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p);
static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br);
static lv_fs_res_t fs_write(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw);
static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence);
static lv_fs_res_t fs_size(lv_fs_drv_t * drv, void * file_p, uint32_t * size_p);
static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p);

static void * fs_dir_open(lv_fs_drv_t * drv, const char * path);
static lv_fs_res_t fs_dir_read(lv_fs_drv_t * drv, void * rddir_p, char * fn, uint32_t fn_len);
static lv_fs_res_t fs_dir_close(lv_fs_drv_t * drv, void * rddir_p);

/**********************
 *  STATIC VARIABLES
 **********************/
extern FIL file;
/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_fs_init(void)
{
    /*----------------------------------------------------
     * Initialize your storage device and File System
     * -------------------------------------------------*/
    fs_init();

    /*---------------------------------------------------
     * Register the file system interface in LVGL
     *--------------------------------------------------*/

    static lv_fs_drv_t fs_drv;
    lv_fs_drv_init(&fs_drv);

    /*Set up fields...*/
    fs_drv.letter = 'A';
    fs_drv.open_cb = fs_open;
    fs_drv.close_cb = fs_close;
    fs_drv.read_cb = fs_read;
    fs_drv.write_cb = fs_write;
    fs_drv.seek_cb = fs_seek;
    fs_drv.tell_cb = fs_tell;

    fs_drv.dir_close_cb = fs_dir_close;
    fs_drv.dir_open_cb = fs_dir_open;
    fs_drv.dir_read_cb = fs_dir_read;

    lv_fs_drv_register(&fs_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your Storage device and File system.*/
static void fs_init(void)
{
    /*E.g. for FatFS initialize the SD card and FatFS itself*/
    retSD = f_mount(&SDFatFS, "0:", 1);
    switch(retSD)
    {
        case FR_OK :
            printf("Mount successful\r\n");
            break;
        default :
            printf("Other error %d\r\n", retSD);
            break;
    }
    /*You code here*/
}

/**
 * Open a file
 * @param drv       pointer to a driver where this function belongs
 * @param path      path to the file beginning with the driver letter (e.g. S:/folder/file.txt)
 * @param mode      read: FS_MODE_RD, write: FS_MODE_WR, both: FS_MODE_RD | FS_MODE_WR
 * @return          a file descriptor or NULL on error
 */
static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode)
{
    FRESULT res;
    FIL *file_p = lv_malloc(sizeof(FIL));
    
    char * p = lv_malloc(30*sizeof(char));
    char * dist = "0:";
    strcpy(p, dist);
    strcat(p, path);
    printf("open path :%s\r\n",p);

    if(mode == LV_FS_MODE_WR) {
        res = f_open(file_p, p, FA_CREATE_ALWAYS | FA_WRITE);
    }
    else if(mode == LV_FS_MODE_RD) {
			
        res = f_open(file_p, p, FA_OPEN_EXISTING | FA_READ);
    }
    else if(mode == (LV_FS_MODE_WR | LV_FS_MODE_RD)) {
        res = f_open(file_p, p, FA_OPEN_EXISTING | FA_READ | FA_WRITE);
    }
    
    if(res != FR_OK) {
        lv_free(file_p);
        return NULL;
    }

    return file_p;
}

/**
 * Close an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p)
{
    FRESULT res = f_close((FIL *)file_p);
    lv_free(file_p);
    return res == FR_OK ? LV_FS_RES_OK : LV_FS_RES_UNKNOWN;
}

/**
 * Read data from an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param buf       pointer to a memory block where to store the read data
 * @param btr       number of Bytes To Read
 * @param br        the real number of read bytes (Byte Read)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    FRESULT res = f_read((FIL *)file_p, buf, btr, (UINT *)br);
    return res == FR_OK ? LV_FS_RES_OK : LV_FS_RES_UNKNOWN;
}

/**
 * Write into a file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable
 * @param buf       pointer to a buffer with the bytes to write
 * @param btw       Bytes To Write
 * @param bw        the number of real written bytes (Bytes Written). NULL if unused.
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_write(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw)
{
    FRESULT res = f_write((FIL *)file_p, buf, btw, (UINT *)bw);
    return res == FR_OK ? LV_FS_RES_OK : LV_FS_RES_UNKNOWN;
}

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open )
 * @param pos       the new position of read write pointer
 * @param whence    tells from where to interpret the `pos`. See @lv_fs_whence_t
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence)
{
    FRESULT res;
    switch(whence)
    {
        case LV_FS_SEEK_SET:
            res = f_lseek((FIL *)file_p, pos);
            break;
        case LV_FS_SEEK_CUR:
            res = f_lseek((FIL *)file_p, f_tell((FIL *)file_p) + pos);
            break;
        case LV_FS_SEEK_END:
            res = f_lseek((FIL *)file_p, f_size((FIL *)file_p) + pos);
            break;
        default:
            return LV_FS_RES_INV_PARAM;
    }
    return res == FR_OK ? LV_FS_RES_OK : LV_FS_RES_UNKNOWN;
}
/**
 * Give the position of the read write pointer
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable
 * @param pos_p     pointer to store the result
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p)
{
    *pos_p = f_tell((FIL *)file_p);
    return LV_FS_RES_OK;
}

/**
 * Initialize a 'lv_fs_dir_t' variable for directory reading
 * @param drv       pointer to a driver where this function belongs
 * @param path      path to a directory
 * @return          pointer to the directory read descriptor or NULL on error
 */
static void * fs_dir_open(lv_fs_drv_t * drv, const char * path)
{
    DIR *dir_p = lv_malloc(sizeof(DIR));
    if(f_opendir(dir_p, path) != FR_OK)
    {
        lv_free(dir_p);
        return NULL;
    }
    return dir_p;
}

/**
 * Read the next filename form a directory.
 * The name of the directories will begin with '/'
 * @param drv       pointer to a driver where this function belongs
 * @param rddir_p   pointer to an initialized 'lv_fs_dir_t' variable
 * @param fn        pointer to a buffer to store the filename
 * @param fn_len    length of the buffer to store the filename
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_read(lv_fs_drv_t * drv, void * rddir_p, char * fn, uint32_t fn_len)
{
   FRESULT res;
    FILINFO fno;
    DIR *dir_p = (DIR *)rddir_p;

    res = f_readdir(dir_p, &fno);
    if (res != FR_OK) {
        return LV_FS_RES_UNKNOWN;
    }

    if (fno.fname[0] == '\0') {
        fn[0] = '\0';
        return LV_FS_RES_OK;
    }

    if (fno.fattrib & AM_DIR) {
        lv_snprintf(fn, fn_len, "/%s", fno.fname);
    } else {
        lv_snprintf(fn, fn_len, "%s", fno.fname);
    }

    return LV_FS_RES_OK;
}

/**
 * Close the directory reading
 * @param drv       pointer to a driver where this function belongs
 * @param rddir_p   pointer to an initialized 'lv_fs_dir_t' variable
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_close(lv_fs_drv_t * drv, void * rddir_p)
{
    FRESULT res = f_closedir((DIR *)rddir_p);
    lv_free(rddir_p);
    return res == FR_OK ? LV_FS_RES_OK : LV_FS_RES_UNKNOWN;
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
