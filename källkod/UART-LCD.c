#include "Delay.h"// includes the Delay header file
#include "UART.h" // includes the UART header file
#include"UART-LCD.h"

#define SLAVE_ADDRE_LCD 0x4E  // change this according to  setup


// This function writes data to the LCD
void Lcd_Write(uint8_t Address, uint8_t *Data, int size)
{
    UART_Address(Address);  // Set the slave address for the UART communication
    for(int i=0; i<size; i++) {
        UART_Write(*Data++);  // Write the data byte to the UART
    }
}

void lcd_send(uint8_t rs, char data) {
    uint8_t data_t[4];
    
    // Set the data bytes for enabling and disabling the TS and RS pins
    data_t[0] = data;       //ts=1, rs=0 or 1
    data_t[1] = data|0x04;  //ts=0, rs=0 or 1
    data_t[2] = data|0x06;  //ts=0, rs=1
    data_t[3] = data|0x02;  //ts=1, rs=1

    // Set the RS bit
    if (rs == 0) {
        data_t[0] &= ~0x02; // Clear RS bit
        data_t[1] &= ~0x02; // Clear RS bit
        data_t[2] &= ~0x02; // Clear RS bit
        data_t[3] &= ~0x02; // Clear RS bit
    } 
    else 
    {
        data_t[0] |= 0x02; // Set RS bit
        data_t[1] |= 0x02; // Set RS bit
        data_t[2] |= 0x02; // Set RS bit
        data_t[3] |= 0x02; // Set RS bit
    }

    // Write the command or data bytes to the LCD
    LCD_Write (SLAVE_ADDRE_LCD,(uint8_t *) data_t, 4);
}


// This function clears the LCD display
void lcd_clear (void)
{
    lcd_send (0, 0x01);  //send clear cmd
    
    Delay_ms(2); // delay 2 ms
}

// This function sets the LCD cursor position
void lcd_put_cur(int row, int col)
{
    switch (row) {
        case 0:
            col |= 0x80;  // Set the DDRAM address for the first row
            break;
        case 1:
            col |= 0xC0;  // Set the DDRAM address for the second row
            break;
    }
    // Send the command to set the DDRAM address
    lcd_send(0,col);
}

void lcd_init (void)
{
	// 4 bit initialisation
	Delay_ms(50);  // wait for >40ms
	lcd_send (0,0x30);
	Delay_ms(5);  // wait for >4.1ms
	lcd_send (0, 0x30);
	Delay_us(150);  // wait for >100us
	lcd_send (0, 0x30);
	Delay_ms(10);
	lcd_send (0, 0x20);  // 4bit mode
	Delay_ms(10);

  // dislay initialisation
	lcd_send (0, 0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	Delay_ms(1);
	lcd_send (0, 0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	Delay_ms(1);
	lcd_clear(); // clear LCD screen
	lcd_send (0, 0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	Delay_ms(1);
	lcd_send (0, 0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send (1, *str++);
}
