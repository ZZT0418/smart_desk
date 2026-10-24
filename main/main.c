#include <stdio.h>
#include <time.h>
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "lvgl_port.h"
#include "xl9555.h"
#include "ft6336u_driver.h"
#include "gui_guider.h"         // GUI界面
#include "custom.h"             //自定义控件
#include "button.h"
#include "ap_wifi.h"
#include "esp_sntp.h"
#include "nvs_flash.h"
#include "esp_spiffs.h"
#include "weather.h"


#define TAG "main"

#define XL9555_SDA              GPIO_NUM_10         //xl9555的SDA引脚
#define XL9555_SCL              GPIO_NUM_11         //xl9555的SCL引脚
#define INT_IO                  GPIO_NUM_17         //xl9555的中断引脚
#define LCD_RST_IO              IO1_3               //LCD复位引脚
#define LCD_BL_IO               IO1_2               //LCD背光引脚
#define TP_RST_IO               IO1_0               //触摸屏复位引脚
#define TP_INT_IO               IO1_1               //触摸屏中断引脚

lv_ui guider_ui;

//按位表示
static volatile uint16_t xl9555_io_level = 0xFFFF;
/**=================xl9555中断回调函数===================
 * @brief xl9555中断回调函数
 * @param io_num 中断引脚编号
 * @param level 中断引脚电平
 *======================================================*/
void xl9555_input_cb(uint16_t io_num,int level)
{
    if(level)
        xl9555_io_level |= io_num;
    else
        xl9555_io_level &= ~io_num;
    if(io_num == TP_INT_IO)         //如果检测到TP_INT引脚有电平变化
    {
        ft6336u_interrupt_info(!level);    //调用ft6336u_int_info通知ft6336u
    }
}

/*=================sntp时间同步回调函数===================
  @brief sntp时间同步回调函数
  @param tv_sec 时间戳
  @return 无
  ======================================================*/
static void time_sync_notification_cb(struct timeval *tv)
{
    struct tm t;
    localtime_r(&tv->tv_sec,&t);

    int year = t.tm_year + 1900;
    int month = t.tm_mon + 1;
    int day = t.tm_mday;
    int weekday = t.tm_wday;
    
    ESP_LOGI(TAG, "时间同步成功：%04d-%02d-%02d 星期%d %02d:%02d:%02d",
             year, month, day, weekday,
             t.tm_hour, t.tm_min, t.tm_sec);
    
    set_home_time(&guider_ui, t.tm_hour, t.tm_min, t.tm_sec);
    set_home_date(&guider_ui, year, month, day);
    set_home_weekday(&guider_ui, weekday);
}

/**=================sntp初始化===========================
 * @brief sntp初始化
 * @param 无
 * @return 无
 *======================================================*/
void my_sntp_init(void)
{
    ESP_LOGI(TAG,"sntp初始化开始");
    if (!esp_sntp_enabled())
    {
    //设置单拨模式
    esp_sntp_setoperatingmode(ESP_SNTP_OPMODE_POLL);
    //设置3个sntp校时服务器
    esp_sntp_setservername(0, "ntp.aliyun.com");
    esp_sntp_setservername(1, "time.asia.apple.com");
    esp_sntp_setservername(2, "pool.ntp.org");
    //校时完成的回调通知函数
    esp_sntp_set_time_sync_notification_cb(time_sync_notification_cb);
    //开启SNTP
    esp_sntp_init();
    }
    ESP_LOGI(TAG,"sntp初始化完成");
}
    


//wifi状态回调函数
void  wifi_state_callback(WIFI_STATE state)
{
    //网络连接成功才发起sntp校时
    if(state == WIFI_STATE_CONNECTED)
    {
        if(!esp_sntp_enabled())    //判断sntp是否已经启动
            my_sntp_init();           //启动sntp
    }
}
/**=================按键获取电平回调函数=======================
 * @brief 按键获取电平回调函数
 * @param gpio 按键引脚编号
 * @return 无
 *======================================================*/
int get_button_level(int gpio)
{
    return (xl9555_io_level&gpio)?1:0;
}

/**=================按键长按回调函数=======================
 * @brief 按键长按回调函数,长按启动wifi配网
 * @param 无
 * @return 无
 *======================================================*/
void long_press(int gpio)
{
    ap_wifi_apcfg(true);
}
/**=================按键初始化===========================
 * @brief 按键初始化
 * @param 无
 * @return 无
 *======================================================*/
void button_init(void)
{
    button_config_t button_cfg =
    {
        .active_level = 0,                          //引脚电平为低时为按下
        .getlevel_cb = get_button_level,            //引脚电平获取函数
        .gpio_num = IO0_1,                           //引脚编号
        .long_cb = long_press,                       //长按回调函数
        .long_press_time = 3000,                    //长按时间
        .short_cb = NULL,                           //短按回调函数
    };
    button_event_set(&button_cfg);          //应用按键配置
}       

/**=================图像的文件系统初始化==================
 * @brief image spiffs初始化
 * @param 无
 * @return 无
 *======================================================*/
static void img_spiffs_init(void)
{
    //定义挂载点
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/image",                //挂载点
        .partition_label = "image",          //分区名称
        .max_files = 5,                     //最大打开的文件数
        .format_if_mount_failed = false    //挂载失败是否执行格式化
        };
    //挂载spiffs
    ESP_ERROR_CHECK(esp_vfs_spiffs_register(&conf));
}

//获取天气预报成功后的回调函数
void  weather_data_callback(const char* city_name,weather_data_pkt_t pkt[3],int num)
{
    ESP_LOGI(TAG,"Weather data num :%d",num);
    if(num == 3)
    {
        char img_path[16];
        snprintf(img_path,sizeof(img_path),"/img/%s@1x.png",pkt[0].code_day);
        set_today_img(&guider_ui,img_path,pkt[0].low_temp,pkt[0].high_temp);

        snprintf(img_path,sizeof(img_path),"/img/%s@1x.png",pkt[1].code_day);
        set_tomorrow_img(&guider_ui,img_path,pkt[1].low_temp,pkt[1].high_temp);

        snprintf(img_path,sizeof(img_path),"/img/%s@1x.png",pkt[2].code_day);
        set_after_img(&guider_ui,img_path,pkt[2].low_temp,pkt[2].high_temp);
        set_home_city(&guider_ui,city_name);
    }
}

void app_main(void)
{
    // xl9555初始化
    xl9555_init(XL9555_SDA, XL9555_SCL, INT_IO, xl9555_input_cb);
    xl9555_ioconfig((~(LCD_RST_IO | LCD_BL_IO | TP_RST_IO))&0xFFFF);  //配置引脚为输出模式（取反表示其位为0表示输出）
    //按键初始化
    button_init();
    //图像文件系统初始化
    img_spiffs_init();
    
    //初始化nvs
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    // lvgl初始化
    my_lvgl_port_init();
    lvgl_port_lock(0);                      //锁住lvgl
    setup_ui(&guider_ui);                   //初始化GUI
    custom_init(&guider_ui);                //用户自定义
    lvgl_port_unlock();                     //解锁lvgl

    //wifi初始化，wifi连接成功后调用回调函数启动sntp校时
    ap_wifi_init(wifi_state_callback); 

    //天气与城市初始化
    weather_start();

    //然后设置时区，同步时间
    setenv("TZ", "CST-8", 1);
    tzset();
}
