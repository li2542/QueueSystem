#include "task.h"
#include "led.h"
#include "beep.h"

uint32_t led1_task_cnt = 0;
uint32_t led2_task_cnt = 0;

uint8_t led1_task_flag = 0;
uint8_t led2_task_flag = 0;

void systick_isr(void){
    if(led1_task_cnt < 1000){
        led1_task_cnt++;
    }else{
        led1_task_flag = 1;
        led_toggle();
        led1_task_cnt = 0;
    }
    
    if(led2_task_cnt < 200){
        
        led2_task_cnt++;
    }else{
        led2_task_flag = 1;
        led2_toggle();
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_6);
        led2_task_cnt = 0;
    }
    
}

