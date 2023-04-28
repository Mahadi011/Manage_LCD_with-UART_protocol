
#include "Delay.h"     // includes the Delay header file
#include "UART-LCD.h"  // includes the UART-LCD header file
#include "UART.h"      // includes the UART header file


int main(void)         // main function
{
    TIM5Config();      // calls the TIM5Config function
    UART_Config();     // calls the UART_Config function
    lcd_init();        // calls the lcd_init function
    lcd_put_cur(0,0);  // calls the lcd_put_cur function with arguments 0 and 0
    lcd_send_string("hello");  // calls the lcd_send_string function with argument "hello"
    while(1)              // infinite loop
    {
        
    }
}
