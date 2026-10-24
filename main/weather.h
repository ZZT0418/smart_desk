#ifndef _WEATHER_H_
#define _WEATHER_H_ 

//天气数据结构体
typedef struct
{
    char date[16];
    int high_temp;
    int low_temp;
    char code_day[4];
    char code_night[4];
}weather_data_pkt_t;


/** 启动天气获取任务
 * @param 无
 * @return 无
*/
void weather_start(void);


#endif