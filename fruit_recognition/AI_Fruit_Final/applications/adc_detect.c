#include "netdev_ipaddr.h"
#include "netdev.h"
#include <rtdevice.h>
#include "drv_common.h"
#include "time.h"
#include "ntp.h"
#include <rtdbg.h>
#include <board.h>
#define ADC_DEV_NAME        "adc1"      /* ADC 设备名称 */
#define ADC_DEV_CHANNEL     1           /* ADC 通道 */
#define REFER_VOLTAGE       500         /* 参考电压 5.0v,数据精度乘以100保留2位小数*/
#define CONVERT_BITS        (1 << 16)   /* 转换位数为16位 */

rt_thread_t Adc_thread = RT_NULL;


static void Adc_entry(void* paremeter);

void adc_detect(){

Adc_thread = rt_thread_create("adc1",
            Adc_entry,
            RT_NULL,
            1024,
            25,
            5);
    if(Adc_thread != RT_NULL)
        rt_thread_startup(Adc_thread);

}
static void Adc_entry(void* paremeter)
    {
        rt_adc_device_t adc_dev;
        rt_uint32_t value,vol;
        rt_err_t ret = RT_EOK;

        adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
        if (adc_dev == RT_NULL)
        {
            rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
        }
        /* 使能设备 */
        ret = rt_adc_enable(adc_dev, ADC_DEV_CHANNEL);
        if(ret == RT_EOK)
        {
            rt_kprintf("adc sample run success!  find %s device!\n", ADC_DEV_NAME);
        }
        while(1)
        {
            /* 读取采样值 */
            value = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
            rt_kprintf("the value is :%d \n", value);
            /* 转换为对应电压值 */
            vol = value * REFER_VOLTAGE / CONVERT_BITS;
            rt_kprintf("the voltage is :%d.%02d \n", vol / 100, vol % 100);

            rt_thread_delay(500);
        }
    }
