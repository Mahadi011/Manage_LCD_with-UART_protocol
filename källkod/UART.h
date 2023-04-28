
#ifndef _UART_H
#define _UART_H

// The required header files are included.
#include <stdint.h>
#include"stm32f4xx.h"

// Function prototypes for UART configuration, write, address, and read are declared.
void UART_Config (void);
void UART_Write (uint8_t data);
void UART_Address (uint8_t Address);
void UART_Read (uint8_t Address, uint8_t *buffer, uint8_t size);
#endif