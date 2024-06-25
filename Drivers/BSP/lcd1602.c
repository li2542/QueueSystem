#include "lcd1602.h"


//RS���Ŷ���
#define RS_GPIO_Port  GPIOB
#define RS_GPIO_Pin   GPIO_PIN_1
#define RS_HIGH       HAL_GPIO_WritePin(RS_GPIO_Port,RS_GPIO_Pin,GPIO_PIN_SET)
#define RS_LOW        HAL_GPIO_WritePin(RS_GPIO_Port,RS_GPIO_Pin,GPIO_PIN_RESET)

//RS���Ŷ���
#define RW_GPIO_Port  GPIOB
#define RW_GPIO_Pin   GPIO_PIN_2
#define RW_HIGH       HAL_GPIO_WritePin(RW_GPIO_Port,RW_GPIO_Pin,GPIO_PIN_SET)
#define RW_LOW        HAL_GPIO_WritePin(RW_GPIO_Port,RW_GPIO_Pin,GPIO_PIN_RESET)

//RS���Ŷ���
#define EN_GPIO_Port  GPIOB
#define EN_GPIO_Pin   GPIO_PIN_10
#define EN_HIGH       HAL_GPIO_WritePin(EN_GPIO_Port,EN_GPIO_Pin,GPIO_PIN_SET)
#define EN_LOW        HAL_GPIO_WritePin(EN_GPIO_Port,EN_GPIO_Pin,GPIO_PIN_RESET)

void lcd1602_init(){
    //��ʼ��GPIO
    lcd1602_gpio_init();
    //�ϵ��ʼ��
    lcd1602_start();
    
}

void lcd1602_gpio_init(){
    
    GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable,����ʱ�� */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins  ��ʼ��GPIOA����*/
  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3| GPIO_PIN_4| GPIO_PIN_5| GPIO_PIN_6| GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;  
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;  
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    
   
    
}

void lcd1602_start(){
    
    //��ʱ15ms
    HAL_Delay(15);
    //дָ��38H
    lcd1602_write_cmd(0x38);
    //��ʱ5ms
    HAL_Delay(5);
    //дָ��38H,��ʾģʽ����
    lcd1602_write_cmd(0x38);
    //дָ��08H,��ʾ�ر�
    lcd1602_write_cmd(0x08);
    //дָ��38H,��ʾ����
    lcd1602_write_cmd(0x01);
    //дָ��06H,��ʾ����ƶ�����
    lcd1602_write_cmd(0x06);
    //дָ��0CH,��ʾ�����������
    lcd1602_write_cmd(0x0C);
    
}

void lcd1602_write_cmd(char cmd){
    RS_LOW;
    RW_LOW;
    EN_LOW;
    GPIOA->ODR = cmd;
    HAL_Delay(5);
    EN_HIGH;
    HAL_Delay(5);
    EN_LOW;
}

void lcd1602_write_data(char dataShow){
    RS_HIGH;
    RW_LOW;
    EN_LOW;
    GPIOA->ODR = dataShow;
    HAL_Delay(5);
    EN_HIGH;
    HAL_Delay(5);
    EN_LOW;
}

void lcd1602_show_char(){
    //��������ʾ
    lcd1602_write_cmd(0x80+0x02);
    //��ʾʲô
    lcd1602_write_data('C');
}

void lcd1602_show_line(char row,char col,char *string){
    switch(row){
        case 1:
            lcd1602_write_cmd(0x80+col);
            while(*string){
                lcd1602_write_data(*string);
                string++;
            }
            break;
        case 2:
            lcd1602_write_cmd(0x80+0x40+col);
            while(*string){
                lcd1602_write_data(*string);
                string++;
            }
            break;
    }
}


