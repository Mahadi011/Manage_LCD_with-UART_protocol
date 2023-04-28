#ifndef __UARTLCD_H
#define __UARTLCD_H

// The required header files are included.
#include"stm32f4xx.h"
#include<stdint.h>

void lcd_init (void);   // initialize lcd

void Lcd_Send_Cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_put_cur(int row, int col);  // put cursor at the entered position row (0 or 1), col (0-15);

void lcd_clear (void);
#endif