#include "lcd1602.h"


//RS引脚定义
#define RS_GPIO_Port  GPIOB
#define RS_GPIO_Pin   GPIO_PIN_1
#define RS_HIGH       HAL_GPIO_WritePin(RS_GPIO_Port,RS_GPIO_Pin,GPIO_PIN_SET)
#define RS_LOW        HAL_GPIO_WritePin(RS_GPIO_Port,RS_GPIO_Pin,GPIO_PIN_RESET)

//RS引脚定义
#define RW_GPIO_Port  GPIOB
#define RW_GPIO_Pin   GPIO_PIN_2
#define RW_HIGH       HAL_GPIO_WritePin(RW_GPIO_Port,RW_GPIO_Pin,GPIO_PIN_SET)
#define RW_LOW        HAL_GPIO_WritePin(RW_GPIO_Port,RW_GPIO_Pin,GPIO_PIN_RESET)

//RS引脚定义
#define EN_GPIO_Port  GPIOB
#define EN_GPIO_Pin   GPIO_PIN_10
#define EN_HIGH       HAL_GPIO_WritePin(EN_GPIO_Port,EN_GPIO_Pin,GPIO_PIN_SET)
#define EN_LOW        HAL_GPIO_WritePin(EN_GPIO_Port,EN_GPIO_Pin,GPIO_PIN_RESET)

void lcd1602_init(){
    //初始化GPIO
    lcd1602_gpio_init();
    //上电初始化
    lcd1602_start();
    
}

void lcd1602_gpio_init(){
    
    GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable,开启时钟 */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins  初始化GPIOA引脚*/
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
    
    //延时15ms
    HAL_Delay(15);
    //写指令38H
    lcd1602_write_cmd(0x38);
    //延时5ms
    HAL_Delay(5);
    //写指令38H,显示模式设置
    lcd1602_write_cmd(0x38);
    //写指令08H,显示关闭
    lcd1602_write_cmd(0x08);
    //写指令38H,显示清屏
    lcd1602_write_cmd(0x01);
    //写指令06H,显示光标移动设置
    lcd1602_write_cmd(0x06);
    //写指令0CH,显示开几光标设置
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
    //在那里显示
    lcd1602_write_cmd(0x80+0x02);
    //显示什么
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


