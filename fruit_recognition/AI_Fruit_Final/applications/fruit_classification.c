#include <rtthread.h>
#include "drv_common.h"
#include <rtdevice.h>
#include "drv_spi_ili9488.h"  // spi lcd driver
#include <lcd_spi_port.h>  // lcd ports
#include <rt_ai_network_model.h>
#include <rt_ai.h>
#include <rt_ai_log.h>
#include <backend_cubeai.h>
#include <logo.h>
#include <fruits.h>
#include <boarder.h>
#include "other.h"
#include "other.c"
#define LED_PIN GET_PIN(I, 8)
#define OUT_PIN1 GET_PIN(D,13)
#define OUT_PIN2 GET_PIN(B,2)
#define OUT_PIN3 GET_PIN(B,1)
struct rt_event ov2640_event;
rt_ai_buffer_t ai_flag = 0;

int num_ai = 0, num_ai_rev = 0, pin_flag = 0, fruit_flag = 0;
int judge[10];

void ai_run_complete(void *arg){
    *(int*)arg = 1;
}
void ai_camera();
void bilinera_interpolation(rt_uint8_t *in_array, short height, short width,
                            rt_uint8_t *out_array, short out_height, short out_width);
void show_leds(int x1,int x2, int x3){
   rt_thread_mdelay(200);
   if(x1 == 1) rt_pin_write(OUT_PIN1, PIN_HIGH); else rt_pin_write(OUT_PIN1, PIN_LOW);
   if(x2 == 1) rt_pin_write(OUT_PIN2, PIN_HIGH); else rt_pin_write(OUT_PIN2, PIN_LOW);
   if(x3 == 1) rt_pin_write(OUT_PIN3, PIN_HIGH); else rt_pin_write(OUT_PIN3, PIN_LOW);
}

int fruit_app(void *param){
    /* init spi data notify event */
    rt_event_init(&ov2640_event, "ov2640", RT_IPC_FLAG_FIFO);

    struct drv_lcd_device *lcd;
    struct rt_device_rect_info rect_info = {0, 0, LCD_WIDTH, 240};
    lcd = (struct drv_lcd_device *)rt_device_find("lcd");

    rt_thread_mdelay(2000);
    lcd_show_image(0, 0, 320, 240, FRUITS);
    lcd_show_string(100, 250, 16, "    TEAM FRUIT");
    lcd_show_string(70, 266, 16, "Fruit Classification AI");
    rt_thread_mdelay(2000);

//    rt_err_t result = RT_EOK;
    int ai_run_complete_flag = 0;

    /* find a registered model handle */
    static rt_ai_t model = NULL;
    model = rt_ai_find(RT_AI_NETWORK_MODEL_NAME);
    if(!model) {rt_kprintf("ai model find err\r\n"); return -1;}

    // allocate input memory
    rt_ai_buffer_t *input_image = rt_malloc(RT_AI_NETWORK_IN_1_SIZE_BYTES);
    if (!input_image) {rt_kprintf("malloc err\n"); return -1;}

    // allocate calculate memory
    rt_ai_buffer_t *work_buf = rt_malloc(RT_AI_NETWORK_WORK_BUFFER_BYTES);
    if (!work_buf) {rt_kprintf("malloc err\n"); return -1;}

    // allocate output memory
    rt_ai_buffer_t *_out = rt_malloc(RT_AI_NETWORK_OUT_1_SIZE_BYTES);
    if (!_out) {rt_kprintf("malloc err\n"); return -1;}

    // ai model init
    rt_ai_buffer_t model_init = rt_ai_init(model, work_buf);
    if (model_init != 0) {rt_kprintf("ai init err\n"); return -1;}
    rt_ai_config(model, CFG_INPUT_0_ADDR, input_image);
    rt_ai_config(model, CFG_OUTPUT_0_ADDR, _out);

    ai_camera();
    lcd_show_image(0, 240, 320, 240, BOARDER);
    temp_humi_get();
    rt_pin_mode(OUT_PIN1, PIN_MODE_OUTPUT);
    rt_pin_mode(OUT_PIN2, PIN_MODE_OUTPUT);
    rt_pin_mode(OUT_PIN3, PIN_MODE_OUTPUT);
    rt_pin_mode(GET_PIN(B,0), PIN_MODE_INPUT_PULLDOWN);
    rt_pin_write(OUT_PIN1, PIN_LOW);
    rt_pin_write(OUT_PIN2, PIN_LOW);
    rt_pin_write(OUT_PIN3, PIN_LOW);
    int i = 0, jud = 1;
    clock_t tmp;
    jud = time_get();
    while(1)
    {
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_event_recv(&ov2640_event,
                            1,
                            RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                            RT_WAITING_FOREVER,
                            RT_NULL);
        rt_pin_write(LED_PIN, PIN_HIGH);
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);
        if (ai_flag > 0)
        {
            if(rt_pin_read(GET_PIN(B,0)) == PIN_HIGH && i % 2 == 0){
                bilinera_interpolation(lcd->lcd_info.framebuffer, 240, 320, input_image, 64, 64);// resize
                num_ai_rev++;
                rt_ai_run(model, NULL, NULL);
                           uint8_t *out = (uint8_t *)rt_ai_output(model, 0);
                          rt_kprintf("pred: %d %d %d %d %d %d %d\n", out[0],out[1],out[2],out[3],out[4], out[5], out[6]);
                          lcd_show_string(20, 20, 16, "Scanning");
                for(int i = 0; i < 7; i++)
                    judge[i] += out[i];
                pin_flag = 1;
            }
            if(rt_pin_read(GET_PIN(B,0)) == PIN_LOW && pin_flag == 1)
            {
                pin_flag = 0;
                int max_judge = judge[0];
                for(int i = 1; i < 7; i++)
                    max_judge = max_judge > judge[i] ? max_judge : judge[i];
                if(max_judge == judge[0]) fruit_flag = 1;
                else if (max_judge == judge[1]) fruit_flag = 2;
                else if (max_judge == judge[2]) fruit_flag = 3;
                else if (max_judge == judge[3]) fruit_flag = 4;
                else if (max_judge == judge[4]) fruit_flag = 5;
                else if (max_judge == judge[5]) fruit_flag = 6;
                else if (max_judge == judge[6]) fruit_flag = 7;
                judge[0] = judge[1] = judge[2] = judge[3] = judge[4] = judge[5] = judge[6] = 0;
                tmp = clock();
            }
            if(fruit_flag == 1 && pin_flag == 0 && tmp + 1000 < clock())
            {
                lcd_show_string(100, 290, 16, "Apple      ");
                lcd_show_string(66, 306, 16, "Suggested Environment:"),
                lcd_show_string(60, 322, 16, "  1-5  Celcius    95  %");
                show_leds(0,0,0);
            }
            else if (fruit_flag == 2 && pin_flag == 0 && tmp + 1000 < clock()){
                lcd_show_string(100, 290, 16, "Lemon      ");
                lcd_show_string(66, 306, 16, "Suggested Environment:"),
                lcd_show_string(60, 322, 16, "   6   Celcius    85 %");
                show_leds(1,0,0);
            }
            else if (fruit_flag == 3 && pin_flag == 0 && tmp + 1000 < clock()){
                lcd_show_string(100, 290, 16, "Kiwi       ");
                lcd_show_string(66, 306, 16, "Suggested Environment:"),
                lcd_show_string(60, 322, 16, "   1   Celcius    93 %");
                show_leds(0,1,0);
            }
            else if (fruit_flag == 4 && pin_flag == 0 && tmp + 1000 < clock()){
                lcd_show_string(100, 290, 16, "Limes      ");
                lcd_show_string(66, 306, 16, "Suggested Environment:"),
                lcd_show_string(60, 322, 16, "   5   Celcius    90 %");
                show_leds(1,1,0);
            }
            else if (fruit_flag == 5 && pin_flag == 0 && tmp + 1000 < clock()){
                lcd_show_string(100, 290, 16, "Apple_stale");
                lcd_show_string(66, 306, 16, "Suggested Environment:"),
                lcd_show_string(60, 322, 16, "   5   Celcius    90 %");
                show_leds(0,0,1);
            }
            else if (fruit_flag == 6 && pin_flag == 0 && tmp + 1000 < clock()){
                lcd_show_string(100, 290, 16, "Lemon_stale");
                lcd_show_string(66, 306, 16, "Suggested Environment:"),
                lcd_show_string(60, 322, 16, "   5   Celcius    90 %");
                show_leds(1,0,1);
            }
            else if (fruit_flag == 7 && pin_flag == 0 && tmp + 1000 < clock()){
                lcd_show_string(100, 290, 16, "kiwi_stale ");
                lcd_show_string(66, 306, 16, "Suggested Environment:"),
                lcd_show_string(60, 322, 16, "   5   Celcius    90 %");
                show_leds(0,1,1);
            }
        }
        i++;
        if(i > 2147483640) i = 0;
        DCMI_Start();
        if(jud == 1) jud = time_get();
        else  print_time();
    }
    rt_free(input_image);
    rt_free(work_buf);
    rt_free(_out);
    return 0;
}
MSH_CMD_EXPORT(fruit_app,fruit_app);


void ai_camera()
{
    rt_gc0328c_init();
    ai_flag = 1;
    DCMI_Start();
}


int is_in_array(short x, short y, short height, short width)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        return 1;
    else
        return 0;
}


void bilinera_interpolation(rt_uint8_t* in_array, short height, short width,
                            rt_uint8_t* out_array, short out_height, short out_width)
{
    double h_times = (double)out_height / (double)height,
           w_times = (double)out_width / (double)width;
    short  x1, y1, x2, y2, f11, f12, f21, f22;
    double x, y;

    for (int i = 0; i < out_height; i++){
        for (int j = 0; j < out_width*3; j=j+3){
            for (int k =0; k <3; k++){
                x = j / w_times + k;
                y = i / h_times;

                x1 = (short)(x - 3);
                x2 = (short)(x + 3);
                y1 = (short)(y + 1);
                y2 = (short)(y - 1);
                f11 = is_in_array(x1, y1, height, width*3) ? in_array[y1*width*3+x1] : 0;
                f12 = is_in_array(x1, y2, height, width*3) ? in_array[y2*width*3+x1] : 0;
                f21 = is_in_array(x2, y1, height, width*3) ? in_array[y1*width*3+x2] : 0;
                f22 = is_in_array(x2, y2, height, width*3) ? in_array[y2*width*3+x2] : 0;
                out_array[i*out_width*3+j+k] = (rt_uint8_t)(((f11 * (x2 - x) * (y2 - y)) +
                                           (f21 * (x - x1) * (y2 - y)) +
                                           (f12 * (x2 - x) * (y - y1)) +
                                           (f22 * (x - x1) * (y - y1))) / ((x2 - x1) * (y2 - y1)));
            }
        }
    }
}
