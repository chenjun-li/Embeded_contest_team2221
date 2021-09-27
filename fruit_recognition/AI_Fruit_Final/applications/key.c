/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-11     冷月枫       the first version
 */

#include "key.h"
#include "rtdevice.h"
#include "drv_common.h"
#include "rtthread.h"

extern int num_ai;

/* 按键中断回调函数  */
void Key_handler()
{
    rt_kprintf("AI is running\n");
    num_ai+=2;
}

/* 按键初始化 */
void Key_init()
{
  //rt_pin_mode(KEYUser_PIN, PIN_MODE_INPUT);  // 输入模式
//  rt_pin_mode(KEY1_PIN, PIN_MODE_INPUT_PULLDOWN);  // 输入模式
  /* 配置中断 */
  /* 绑定中断 */
 // rt_pin_attach_irq(KEYUser_PIN, PIN_IRQ_MODE_FALLING , Key_handler, RT_NULL);  // 下降沿触发
  //rt_pin_attach_irq(KEY1_PIN, PIN_IRQ_MODE_FALLING , Key_handler, RT_NULL);
  /* 使能中断 */
  //rt_pin_irq_enable(KEYUser_PIN, PIN_IRQ_ENABLE);
  //rt_pin_irq_enable(KEY1_PIN, PIN_IRQ_ENABLE);
}
