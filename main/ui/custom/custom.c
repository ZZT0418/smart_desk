/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include "esp_lvgl_port.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
extern int screen_home_digital_clock_now_hour_value;
extern int screen_home_digital_clock_now_min_value;
extern int screen_home_digital_clock_now_sec_value;

/**
 * Create a demo application
 */

 //=============================设置主屏幕部件时间=======================================
void set_home_time(lv_ui* ui, int hour, int min, int sec)
{
    if (!lvgl_port_lock(0)) {
        return;
    }
    
    screen_home_digital_clock_now_hour_value = hour;
    screen_home_digital_clock_now_min_value = min;
    screen_home_digital_clock_now_sec_value = sec;
    
    if (lv_obj_is_valid(ui->screen_home_digital_clock_now)) {
        lv_label_set_text_fmt(ui->screen_home_digital_clock_now, "%d:%02d:%02d", 
                              hour, min, sec);
    }
    
    lvgl_port_unlock();
}

/*=============================设置主屏幕部件日期=======================================
 * @param ui：屏幕UI对象、year:年、month:月、day:日
 * @return 无
 */
void set_home_date(lv_ui* ui, int year, int month, int day)
{
    if (!lvgl_port_lock(0)) {
        return;
    }
    
    char date_str[16];
    snprintf(date_str, sizeof(date_str), "%04d/%02d/%02d", year, month, day);
    
    if (lv_obj_is_valid(ui->screen_home_datetext_now)) {
        lv_label_set_text(ui->screen_home_datetext_now, date_str);
    }
    
    lvgl_port_unlock();
}

/*=============================设置主屏幕部件星期=======================================
    @param ui：屏幕UI对象、weekday:星期
    @return 无
*/
void set_home_weekday(lv_ui* ui, int weekday)
{
    if (!lvgl_port_lock(0)) {
        return;
    }
    
    const char* weekday_str[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };
    
    if (weekday < 0 || weekday > 6) {
        weekday = 0;
    }
    
    if (lv_obj_is_valid(ui->screen_home_label_week)) {
        lv_label_set_text(ui->screen_home_label_week, weekday_str[weekday]);
    }
    
    lvgl_port_unlock();
}

/*=============================加载主屏幕天气部件图片=======================================
 *@param ui：屏幕UI对象、img_path:图片路径、low:最低温度、high:最高温度
 *@return 无
*/
void set_today_img(lv_ui* ui,const char* img_path,int low,int high)
{
    char temp_text[32];                                         // 用于存储温度文本
    lvgl_port_lock(0);                                           // 锁定LVGL
    lv_img_set_src(ui->screen_home_img_weather1, img_path);     // 加载图片
    snprintf(temp_text,sizeof(temp_text),"%d-%d℃",low,high);    // 格式化温度文本
    lv_label_set_text(ui->screen_home_label_temp1, temp_text);   // 设置温度文本
    lvgl_port_unlock();                                           // 解锁LVGL

}

void set_tomorrow_img(lv_ui* ui,const char* img_path,int low,int high)
{
    char temp_text[32];                                         // 用于存储温度文本
    lvgl_port_lock(0);                                           // 锁定LVGL
    lv_img_set_src(ui->screen_home_img_weather2, img_path);     // 加载图片
    snprintf(temp_text,sizeof(temp_text),"%d-%d℃",low,high);    // 格式化温度文本
    lv_label_set_text(ui->screen_home_label_temp2, temp_text);   // 设置温度文本
    lvgl_port_unlock();                                           // 解锁LVGL
}

void set_after_img(lv_ui* ui,const char* img_path,int low,int high)
{
    char temp_text[32];                                         // 用于存储温度文本
    lvgl_port_lock(0);                                           // 锁定LVGL
    lv_img_set_src(ui->screen_home_img_weather3, img_path);     // 加载图片
    snprintf(temp_text,sizeof(temp_text),"%d-%d℃",low,high);    // 格式化温度文本
    lv_label_set_text(ui->screen_home_label_temp3, temp_text);   // 设置温度文本
    lvgl_port_unlock();                                           // 解锁LVGL
}

/*=============================设置主屏幕显示的城市=======================================
 * @param ui：屏幕UI对象、city:城市名称
 * @return 无
 */
void set_home_city(lv_ui* ui,const char* city)
{
    char city_text[32];
    lvgl_port_lock(0);
    snprintf(city_text,sizeof(city_text),"%s",city);
    lv_label_set_text(ui->screen_home_label_city, city_text);
    lvgl_port_unlock();
}



void custom_init(lv_ui *ui)
{
    /* Add your codes here */
}

