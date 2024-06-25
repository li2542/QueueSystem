#include "delay.h"



void delay_us(uint32_t nus){
    uint32_t temp  =0;
    //确定要数多少个数
    SysTick->LOAD = 72 * nus;
    //清空当前计数
    SysTick->VAL = 0x00;
    //配置分频系数
    SysTick->CTRL |= 1<<2;
    //开启定时器
    SysTick->CTRL |= 1<<0;
    
    do{
        temp = SysTick->CTRL;
    }while((temp & 0x01) && (!(temp & (1<<16))));//判断定时器有没有打开
    SysTick->CTRL &= ~(1<<0);//关闭定时器
}
