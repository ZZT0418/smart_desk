/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



int screen_home_digital_clock_now_min_value = 40;
int screen_home_digital_clock_now_hour_value = 14;
int screen_home_digital_clock_now_sec_value = 0;
void setup_scr_screen_home(lv_ui *ui)
{
    //Write codes screen_home
    ui->screen_home = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_home, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_home, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_digital_clock_now
    static bool screen_home_digital_clock_now_timer_enabled = false;
    ui->screen_home_digital_clock_now = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_digital_clock_now, 41, 39);
    lv_obj_set_size(ui->screen_home_digital_clock_now, 130, 36);
    lv_label_set_text(ui->screen_home_digital_clock_now, "14:40:00");
    if (!screen_home_digital_clock_now_timer_enabled) {
        lv_timer_create(screen_home_digital_clock_now_timer, 1000, NULL);
        screen_home_digital_clock_now_timer_enabled = true;
    }

    //Write style for screen_home_digital_clock_now, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_home_digital_clock_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_digital_clock_now, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_digital_clock_now, &lv_font_ZiTiQuanWeiJunHeiW22_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_digital_clock_now, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_digital_clock_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_digital_clock_now, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_digital_clock_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_digital_clock_now, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_digital_clock_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_digital_clock_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_digital_clock_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_digital_clock_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_datetext_now
    ui->screen_home_datetext_now = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_datetext_now, 180, 39);
    lv_obj_set_size(ui->screen_home_datetext_now, 130, 36);
    lv_label_set_text(ui->screen_home_datetext_now, "2025/03/07");
    lv_obj_set_style_text_align(ui->screen_home_datetext_now, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui->screen_home_datetext_now, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->screen_home_datetext_now, screen_home_datetext_now_event_handler, LV_EVENT_ALL, NULL);

    //Write style for screen_home_datetext_now, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_home_datetext_now, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_datetext_now, &lv_font_ZiTiQuanWeiJunHeiW22_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_datetext_now, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_datetext_now, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_datetext_now, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_datetext_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_home_datetext_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_datetext_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_datetext_now, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_datetext_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_datetext_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_datetext_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_img_line
    ui->screen_home_img_line = lv_image_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_img_line, 38, 86);
    lv_obj_set_size(ui->screen_home_img_line, 263, 9);
    lv_obj_add_flag(ui->screen_home_img_line, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_home_img_line, &_line_RGB565A8_263x9);
    lv_image_set_pivot(ui->screen_home_img_line, 50,50);
    lv_image_set_rotation(ui->screen_home_img_line, 0);

    //Write style for screen_home_img_line, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_img_line, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_img_line, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_week
    ui->screen_home_label_week = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_label_week, 192, 68);
    lv_obj_set_size(ui->screen_home_label_week, 100, 32);
    lv_label_set_text(ui->screen_home_label_week, "week");
    lv_label_set_long_mode(ui->screen_home_label_week, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_week, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_week, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_week, &lv_font_ZiTiQuanWeiJunHeiW22_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_week, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_week, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_city
    ui->screen_home_label_city = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_label_city, 230, 4);
    lv_obj_set_size(ui->screen_home_label_city, 100, 30);
    lv_label_set_text(ui->screen_home_label_city, "衡阳");
    lv_label_set_long_mode(ui->screen_home_label_city, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_city, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_city, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_city, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_city, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_city, &lv_font_ZiTiQuanWeiJunHeiW22_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_city, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_city, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_city, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_city, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_city, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_city, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_city, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_city, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_city, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_city, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_img_wifi
    ui->screen_home_img_wifi = lv_image_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_img_wifi, 4, 4);
    lv_obj_set_size(ui->screen_home_img_wifi, 30, 30);
    lv_obj_add_flag(ui->screen_home_img_wifi, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_home_img_wifi, &_wifi_RGB565A8_30x30);
    lv_image_set_pivot(ui->screen_home_img_wifi, 50,50);
    lv_image_set_rotation(ui->screen_home_img_wifi, 0);

    //Write style for screen_home_img_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_img_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_img_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_today
    ui->screen_home_label_today = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_label_today, 27, 115);
    lv_obj_set_size(ui->screen_home_label_today, 100, 32);
    lv_label_set_text(ui->screen_home_label_today, "今天");
    lv_label_set_long_mode(ui->screen_home_label_today, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_today, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_today, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_today, &lv_font_ZiTiQuanWeiJunHeiW22_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_today, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_today, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_tomorrow
    ui->screen_home_label_tomorrow = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_label_tomorrow, 112, 115);
    lv_obj_set_size(ui->screen_home_label_tomorrow, 100, 32);
    lv_label_set_text(ui->screen_home_label_tomorrow, "明天");
    lv_label_set_long_mode(ui->screen_home_label_tomorrow, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_tomorrow, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_tomorrow, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_tomorrow, &lv_font_ZiTiQuanWeiJunHeiW22_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_tomorrow, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_tomorrow, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_after
    ui->screen_home_label_after = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_label_after, 197, 115);
    lv_obj_set_size(ui->screen_home_label_after, 100, 32);
    lv_label_set_text(ui->screen_home_label_after, "后天");
    lv_label_set_long_mode(ui->screen_home_label_after, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_after, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_after, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_after, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_after, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_after, &lv_font_ZiTiQuanWeiJunHeiW22_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_after, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_after, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_after, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_after, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_after, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_after, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_after, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_after, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_after, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_after, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_img_weather1
    ui->screen_home_img_weather1 = lv_image_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_img_weather1, 53, 150);
    lv_obj_set_size(ui->screen_home_img_weather1, 50, 50);
    lv_obj_add_flag(ui->screen_home_img_weather1, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_home_img_weather1, &_qing_RGB565A8_50x50);
    lv_image_set_pivot(ui->screen_home_img_weather1, 50,50);
    lv_image_set_rotation(ui->screen_home_img_weather1, 0);

    //Write style for screen_home_img_weather1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_img_weather1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_img_weather1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_img_weather2
    ui->screen_home_img_weather2 = lv_image_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_img_weather2, 140, 150);
    lv_obj_set_size(ui->screen_home_img_weather2, 50, 50);
    lv_obj_add_flag(ui->screen_home_img_weather2, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_home_img_weather2, &_yu_RGB565A8_50x50);
    lv_image_set_pivot(ui->screen_home_img_weather2, 50,50);
    lv_image_set_rotation(ui->screen_home_img_weather2, 0);

    //Write style for screen_home_img_weather2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_img_weather2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_img_weather2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_img_weather3
    ui->screen_home_img_weather3 = lv_image_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_img_weather3, 227, 150);
    lv_obj_set_size(ui->screen_home_img_weather3, 50, 50);
    lv_obj_add_flag(ui->screen_home_img_weather3, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_home_img_weather3, &_yun_RGB565A8_50x50);
    lv_image_set_pivot(ui->screen_home_img_weather3, 50,50);
    lv_image_set_rotation(ui->screen_home_img_weather3, 0);

    //Write style for screen_home_img_weather3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_img_weather3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_img_weather3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_temp1
    ui->screen_home_label_temp1 = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_label_temp1, 24, 215);
    lv_obj_set_size(ui->screen_home_label_temp1, 100, 32);
    lv_label_set_text(ui->screen_home_label_temp1, "28~32℃");
    lv_label_set_long_mode(ui->screen_home_label_temp1, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_temp1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_temp1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_temp1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_temp1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_temp1, &lv_font_ZiTiQuanWeiJunHeiW22_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_temp1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_temp1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_temp1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_temp1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_temp1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_temp1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_temp1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_temp1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_temp1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_temp1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_temp2
    ui->screen_home_label_temp2 = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_label_temp2, 114, 215);
    lv_obj_set_size(ui->screen_home_label_temp2, 100, 32);
    lv_label_set_text(ui->screen_home_label_temp2, "27~31℃");
    lv_label_set_long_mode(ui->screen_home_label_temp2, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_temp2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_temp2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_temp2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_temp2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_temp2, &lv_font_ZiTiQuanWeiJunHeiW22_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_temp2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_temp2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_temp2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_temp2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_temp2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_temp2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_temp2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_temp2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_temp2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_temp2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_temp3
    ui->screen_home_label_temp3 = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_label_temp3, 204, 215);
    lv_obj_set_size(ui->screen_home_label_temp3, 100, 32);
    lv_label_set_text(ui->screen_home_label_temp3, "25~29℃");
    lv_label_set_long_mode(ui->screen_home_label_temp3, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_temp3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_temp3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_temp3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_temp3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_temp3, &lv_font_ZiTiQuanWeiJunHeiW22_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_temp3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_temp3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_temp3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_temp3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_temp3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_temp3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_temp3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_temp3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_temp3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_temp3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_home.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_home);

    //Init events for screen.
    events_init_screen_home(ui);
}
