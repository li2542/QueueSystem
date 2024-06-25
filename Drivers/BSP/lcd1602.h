#ifndef __LCD1602_H_
#define __LCD1602_H_

#include "stm32f1xx.h"
#include "stdint.h"

#define TRUE 1
#define FALSE 0

void lcd1602_init(void);

void lcd1602_gpio_init(void);

void lcd1602_start(void);

void lcd1602_write_cmd(char cmd);
void lcd1602_write_data(char dataShow);

void lcd1602_show_char(void);
void lcd1602_show_line(char row,char col,char *string);
#endif
