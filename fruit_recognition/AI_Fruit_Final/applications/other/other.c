#include <rtthread.h>
#include "drv_common.h"
#include <rtdevice.h>
#include "drv_spi_ili9488.h"  // spi lcd driver
#include <lcd_spi_port.h>  // lcd ports
#include <time.h>
#include <stdio.h>

int now_hour ,now_minute, now_sec;
int new_hour ,new_minute, new_sec;
int add_hour, add_minute, add_sec;
clock_t st_time, now_time;
int dif_time;
int time_get(void)
{
    st_time = clock();
    struct tm* clock_NTP;
               time_t now;
               now = time(NULL);
               clock_NTP = gmtime(&now);
    now_hour = clock_NTP->tm_hour,now_minute = clock_NTP->tm_min,now_sec = clock_NTP->tm_sec;
          if(now_minute == 0 && now_hour == 0) return 1;
          if(now_hour >= 10 && now_minute >= 10 && now_sec >= 10) lcd_show_string(45, 399, 16, "Time: %d:%d:%d ",now_hour,now_minute,now_sec);
          else if(now_hour < 10 && now_minute >= 10 && now_sec >= 10) lcd_show_string(45, 399, 16, "Time: 0%d:%d:%d ",now_hour,now_minute,now_sec);
          else if(now_hour < 10 && now_minute < 10 && now_sec >= 10) lcd_show_string(45, 399, 16, "Time: 0%d:0%d:%d ",now_hour,now_minute,now_sec);
          else if(now_hour < 10 && now_minute < 10 && now_sec < 10) lcd_show_string(45, 399, 16, "Time: 0%d:0%d:0%d ",now_hour,now_minute,now_sec);
          else if(now_hour >= 10 && now_minute < 10 && now_sec >= 10) lcd_show_string(45, 399, 16, "Time: %d:0%d:%d ",now_hour,now_minute,now_sec);
          else if(now_hour >= 10 && now_minute < 10 && now_sec < 10) lcd_show_string(45, 399, 16, "Time: %d:0%d:0%d ",now_hour,now_minute,now_sec);
          else if(now_hour >= 10 && now_minute >= 10 && now_sec < 10) lcd_show_string(45, 399, 16, "Time: %d:%d:0%d ",now_hour,now_minute,now_sec);
          else if(now_hour < 10 && now_minute >= 10 && now_sec < 10) lcd_show_string(45, 399, 16, "Time: 0%d:%d:0%d ",now_hour,now_minute,now_sec);
          return 0;
}

void print_time(void)
{
    now_time = clock();
    dif_time = (now_time - st_time)/1000;
    new_sec = dif_time%60 + now_sec, dif_time = dif_time/60; new_minute = dif_time%60 + now_minute, dif_time = dif_time/60; new_hour = dif_time%60 + now_hour;
    if(new_sec >= 60) new_sec -= 60, new_minute++;
    if(new_minute >= 60) new_minute -= 60, new_hour++;
    if(new_hour >= 24) new_hour -= 24;
//          if(now_minute == 0 && now_hour == 0) return;
          if(new_hour >= 10 && new_minute >= 10 && new_sec >= 10) lcd_show_string(45, 399, 16, "Time: %d:%d:%d ",new_hour,new_minute,new_sec);
          else if(new_hour < 10 && new_minute >= 10 && new_sec >= 10) lcd_show_string(45, 399, 16, "Time: 0%d:%d:%d ",new_hour,new_minute,new_sec);
          else if(new_hour < 10 && new_minute < 10 && new_sec >= 10) lcd_show_string(45, 399, 16, "Time: 0%d:0%d:%d ",new_hour,new_minute,new_sec);
          else if(new_hour < 10 && new_minute < 10 && new_sec < 10) lcd_show_string(45, 399, 16, "Time: 0%d:0%d:0%d ",new_hour,new_minute,new_sec);
          else if(new_hour >= 10 && new_minute < 10 && new_sec >= 10) lcd_show_string(45, 399, 16, "Time: %d:0%d:%d ",new_hour,new_minute,new_sec);
          else if(new_hour >= 10 && new_minute < 10 && new_sec < 10) lcd_show_string(45, 399, 16, "Time: %d:0%d:0%d ",new_hour,new_minute,new_sec);
          else if(new_hour >= 10 && new_minute >= 10 && new_sec < 10) lcd_show_string(45, 399, 16, "Time: %d:%d:0%d ",new_hour,new_minute,new_sec);
          else if(new_hour < 10 && new_minute >= 10 && new_sec < 10) lcd_show_string(45, 399, 16, "Time: 0%d:%d:0%d ",new_hour,new_minute,new_sec);
}

extern  unsigned char hightemp[20];
extern  unsigned char lowtemp[20];
extern  unsigned char humi[30];

#include <webclient.h>

void temp_humi_get(void)
{
   sht31_collect();
}
