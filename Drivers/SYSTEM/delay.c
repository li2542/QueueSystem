#include "delay.h"



void delay_us(uint32_t nus){
    uint32_t temp  =0;
    //ȷ��Ҫ�����ٸ���
    SysTick->LOAD = 72 * nus;
    //��յ�ǰ����
    SysTick->VAL = 0x00;
    //���÷�Ƶϵ��
    SysTick->CTRL |= 1<<2;
    //������ʱ��
    SysTick->CTRL |= 1<<0;
    
    do{
        temp = SysTick->CTRL;
    }while((temp & 0x01) && (!(temp & (1<<16))));//�ж϶�ʱ����û�д�
    SysTick->CTRL &= ~(1<<0);//�رն�ʱ��
}
