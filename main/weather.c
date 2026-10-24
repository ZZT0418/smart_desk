#include "weather.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "esp_crt_bundle.h"
#include "cJSON.h"
#include "custom.h"
#include "nvs_flash.h"
#include "wifi_manager.h"

#define TAG "weather"

//心知天气秘钥(注意替换成自己的密钥)
#define WEATHER_PRIVATE_KEY     "SyyIYl7_qEcP8dfIA"

extern lv_ui guider_ui;

//最大输出缓冲区长度
#define MAX_OUTPUT_BUFFER_LEN   2048
//http接收到的数据，用于接收通过http协议返回的数据
static  char http_buffer[MAX_OUTPUT_BUFFER_LEN] = {0};  
//http接收到的数据长度
static int http_buffer_len = 0;

//当获取到城市的名字后，保存在如下数组
static char s_city_name[128];

/*=====================解析天气数据=========================
 *功能：解析http服务器返回的JSON天气数据
 *参数：weather_data：天气数据
 *返回：错误类型 ESP_OK or ESP_FAIL
 *=========================================================*/
static esp_err_t weather_parse(char *weather_jsdata)
{
    cJSON *weather_json = cJSON_Parse(weather_jsdata);
    if(weather_json == NULL)
    {
        ESP_LOGI(TAG,"weather_json is null!");
        return ESP_FAIL;
    }
    cJSON *result_js = cJSON_GetObjectItem(weather_json,"results");
    if(!result_js)
    {
        ESP_LOGI(TAG,"非法结果,请查看私钥是否正确!");
        return ESP_FAIL;
    }
    cJSON *result_child_js = result_js->child;
    weather_data_pkt_t  weather_data[3];
    char city_name[32] = {0};
    int index = 0;
    while(result_child_js)
    {
        cJSON *location_js = cJSON_GetObjectItem(result_child_js,"location");
        cJSON *cityname_js = NULL;
        if(location_js)
        {
            cityname_js = cJSON_GetObjectItem(location_js,"name");
            if(cityname_js)
            {
                snprintf(city_name,sizeof(city_name),"%s",cJSON_GetStringValue(cityname_js));
            }
        }
        cJSON *daily_js = cJSON_GetObjectItem(result_child_js,"daily");
        if(daily_js)
        {
            cJSON *daily_child_js = daily_js->child;
            while(daily_child_js)
            {
                cJSON* date_js = cJSON_GetObjectItem(daily_child_js,"date");
                cJSON* code_day = cJSON_GetObjectItem(daily_child_js,"code_day");
                cJSON* code_night = cJSON_GetObjectItem(daily_child_js,"code_night");
                cJSON* high_js = cJSON_GetObjectItem(daily_child_js,"high");
                cJSON* low_js = cJSON_GetObjectItem(daily_child_js,"low");
                if(index < 3)
                {
                    snprintf(weather_data[index].date,16,"%s",cJSON_GetStringValue(date_js));
                    snprintf(weather_data[index].code_day,4,"%s",cJSON_GetStringValue(code_day));
                    snprintf(weather_data[index].code_night,4,"%s",cJSON_GetStringValue(code_night));
                    sscanf(cJSON_GetStringValue(high_js),"%d",&weather_data[index].high_temp);
                    sscanf(cJSON_GetStringValue(low_js),"%d",&weather_data[index].low_temp);
                }
                index++;
                daily_child_js = daily_child_js->next;
            }
            //调用显示接口，把天气信息设置到LVGL里面去
            set_home_city(&guider_ui,city_name);
            char img_path[32];
            snprintf(img_path,sizeof(img_path),"/image/%s@1x.png",weather_data[0].code_day);
            set_today_img(&guider_ui,img_path,weather_data[0].low_temp,weather_data[0].high_temp);

            snprintf(img_path,sizeof(img_path),"/image/%s@1x.png",weather_data[1].code_day);
            set_tomorrow_img(&guider_ui,img_path,weather_data[1].low_temp,weather_data[1].high_temp);

            snprintf(img_path,sizeof(img_path),"/image/%s@1x.png",weather_data[2].code_day);
            set_after_img(&guider_ui,img_path,weather_data[2].low_temp,weather_data[2].high_temp);
        }
        result_child_js = result_child_js->next;
    }
    cJSON_Delete(weather_json);
    return ESP_OK;

}

/**====================解析返回的位置数据======================
 * 功能：解析位置数据
 * 参数： json数据
 * 返回： ESP_OK or ESP_FAIL
 *=========================================================*/
static esp_err_t parse_location(char* location_js)
{
    cJSON *lo_js = cJSON_Parse(location_js);
    if(!lo_js)
    {
        ESP_LOGI(TAG,"invaild json format");
        return ESP_FAIL;
    }
    cJSON *city_js = cJSON_GetObjectItem(lo_js,"city");
    if(!city_js)
    {
        ESP_LOGI(TAG,"invaild location result");
        return ESP_FAIL;
    }
    snprintf(s_city_name,sizeof(s_city_name),"%s",cJSON_GetStringValue(city_js));
    cJSON_Delete(lo_js);
    return ESP_OK;
}

static esp_err_t http_client_event_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id) { //evt->event_id等价于(*evt).event_id
        case HTTP_EVENT_ERROR:    //错误事件
            ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:    //连接成功事件
            ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:    //发送头事件
            ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:    //接收头事件
            printf("%.*s", evt->data_len, (char*)evt->data);
            break;
        case HTTP_EVENT_ON_DATA:    //接收数据事件
        {
            /*因为这个HTTP_EVENT_ON_DATA事件可能会不只一次的触发，也就是
            会分多次接收，因此这里需要考虑多次接收数据的完整
            http_buffer_len会记录数据的长度
            http_buffer则保存了收到的所有http数据*/
            int copy_len = 0;
            if(http_buffer_len + evt->data_len < MAX_OUTPUT_BUFFER_LEN)
            {
                copy_len = evt->data_len;
            }
            else
            {
                copy_len = MAX_OUTPUT_BUFFER_LEN - http_buffer_len;
            }
            memcpy(&http_buffer[http_buffer_len], evt->data,copy_len);
            http_buffer_len += evt->data_len;
            break;
        }
        case HTTP_EVENT_ON_FINISH:    //会话完成事件
            http_buffer_len = 0;
            break;
        case HTTP_EVENT_DISCONNECTED:    //断开事件
            http_buffer_len = 0;
            break;
        case HTTP_EVENT_REDIRECT:
            break;
    }
    return ESP_OK;
}


/*=====================天气http的连接=========================
 *功能：连接天气相关的http服务器，发起http请求，获取天气数据
 *参数：无
 *返回：错误类型 ESP_OK or ESP_FAIL
 *=========================================================*/
static esp_err_t weather_http_connect(void)
{
    //定义存储URL的数组
    char weather_url[256];
    //格式化url为指定格式(snprintf：安全的字符串拼接函数，防止数组溢出)
    snprintf(weather_url,sizeof(weather_url),
    "http://api.seniverse.com/v3/weather/daily.json?key=%s&location=%s&language=zh-Hans&unit=c&start=0&days=3",
        WEATHER_PRIVATE_KEY,s_city_name);

    //创建http结构体,并配置客户端参数（相当于设置"连接规则"）
    esp_http_client_config_t config = 
    {
        .url = weather_url,                                 //url
        .crt_bundle_attach = esp_crt_bundle_attach,         //加载证书（访问HTTPS时必需，这里HTTP也可保留）
        .event_handler = http_client_event_handler,         //设置http事件处理函数
    };
    //初始化HTTP客户端（相当于"创建一个浏览器"），并应用配置
    esp_http_client_handle_t http_client = esp_http_client_init(&config);	
    if(!http_client)
    {
        ESP_LOGI(TAG,"http_client init fail!");
        return ESP_FAIL;
    }

    //设置发送请求 
    esp_http_client_set_method(http_client, HTTP_METHOD_GET);
    //esp_http_client_perform函数将完成一个完整HTTP请求才返回
    esp_err_t err  = esp_http_client_perform(http_client);
    if(err != ESP_OK)
    {
        return ESP_FAIL;
    }
    //获取返回的内容长度
    weather_parse(http_buffer);             //等价于weather_parse(&http_buffer[0]);
    //释放http连接结构体
    esp_http_client_cleanup(http_client);

    return ESP_OK;
}

/** 发起http请求，获取当前城市
 * @param 无
 * @return ESP_OK or ESP_FAIL
*/
static esp_err_t location_http_connect(void)
{
    esp_err_t ret_code = ESP_OK;

    //定义http配置结构体
    esp_http_client_config_t config = 
    {
        .url = "http://ip-api.com/json/?lang=en",                       //获取当前城市
        //.url = "http://whois.pconline.com.cn/ipJson.jsp?json=true";
        .event_handler = http_client_event_handler,                     //设置http事件处理函数
    };
    //初始化结构体
    esp_http_client_handle_t http_client = esp_http_client_init(&config);	//初始化http连接
    if(!http_client)
    {
        ESP_LOGI(TAG,"http_client init fail!");
        return ESP_FAIL;
    }

    //设置发送请求 
    esp_http_client_set_method(http_client, HTTP_METHOD_GET);
    //esp_http_client_perform函数将完成一个完整HTTP请求才返回
    esp_err_t err  = esp_http_client_perform(http_client);
    if(err != ESP_OK)
    {
        return ESP_FAIL;
    }
    //解析收到的json数据
    parse_location(http_buffer);
    //清理
    esp_http_client_cleanup(http_client);
    return ret_code;
}

static void weather_task(void *param)
{
    while(1)
    {
        //先判断一下网络是否已经连接了，如果没有连接循环2秒等待
        if(!wifi_manager_is_connect())
        {
            vTaskDelay(pdMS_TO_TICKS(2000));
        }
        else    //发现已经连接上网络
        {
            //先根据ip地址请求地理位置
            location_http_connect();
            //然后获取天气相关信息
            weather_http_connect();
            //延时半小时
            vTaskDelay(pdMS_TO_TICKS(1000*1800));
        }
    }
}

void weather_start(void)
{
    xTaskCreatePinnedToCore(weather_task,"weather",4096,NULL,2,NULL,1);
}