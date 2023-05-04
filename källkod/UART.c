#include"UART.h"

void UART_Config(void)
{
    /**** STEPS FOLLOWED  ************
    1. Enable the UART CLOCK and GPIO CLOCK
    2. Configure the USART PINs for ALternate Functions
        a) Select Alternate Function in MODER Register
        b) Select Open Drain Output 
        c) Select High SPEED for the PINs
        d) Select Pull-up for both the Pins
        e) Configure the Alternate Function in AFR Register
    3. Configure USART 	
    */


   /* The USART2 module can be configured to use different clock sources, 
   such as the system clock or an external clock. Enabling the USART2 clock 
   allows us to set the desired clock source and configure the module 
   accordingly.
   
   GPIOA pins can be configured as inputs or outputs, allowing us to read 
   signals from external sensors or control external devices such as LEDs 
   or motors. Enabling the GPIOA clock allows us to configure the pins as 
   inputs or outputs and use them for our application.
    */
   
   // Enable USART2 clock and GPIOA clock
   RCC-> APB1ENR |= 0x20000; // Enable USART2 clock
   RCC-> AHB1ENR |=0x00001;  // Enable GPIOA clock

   /* The USART2 module is a hardware peripheral that needs to be enabled 
   before it can be used. Enabling the USART2 clock allows the MCU to 
   access the USART2 module and use its features.
    */

   //Configure the USART PINs for ALternate Functions
   GPIOA-> MODER |= 0x000A0; //Bits7:6 = 1:0 and bits 5:4 = 1:0 to set pin PA3 and PA2 in alternet mode
   GPIOA->OTYPER|= 0x0000C  // bit 3=1 and bit 2=1 output open drain 
   GPIOA->OSPEEDR |= 0x000F0 // Bits 7:6 =1:1 and bits 5:4 = 1:1 to set pin PA3 and PA2 in high speed 
   GPIOA ->PUPDR |= 0x00050 // Bits 7:6 =0:1 and bits 5:4 = 0:1 to set pin PA3 and PA2 in pull up
   GPIOA -> AFR[0] |= 0x07700  // Bits 15:14:13:12 =0:1:1:1 and bits 11:10:9:8 = 0:1:1:1 to set pin PA3 and PA2 in alternate function 

   //Reset the USART
    USART2->BRR |= 0x0683; // setting standerd baud-rate which is 9600 bps.
    USART2->CR1 |= 0x0000C; // Activate transmit and recever by putting 1 in bit 2 and 3
    USART2->CR2 |= 0x00000; // deactivate control resister 2
    USART2->CR3 |= 0X00000; // deactivate control resister 3
    USART2->CR1 |= 0x02000; // enable usart by put 1 in bit  13 
}

void UART_Write(uint8_t data)
{
    while(!(USART2->SR &0x00080)){} // putting rules to check the transmit data resister is empty
    USART2->DR = data; //putting 8 bit value in data resister
    
}


void UART_Read (uint8_t Address, uint8_t *buffer, uint8_t size)
{
/**** STEPS FOLLOWED  ************
1. If only 1 BYTE needs to be Read
	a) Write the slave Address, and wait for the ADDR bit (bit 5 in SR) to be set
	b) Wait for the RXNE (Receive Buffer not Empty) bit to set
	c) Read the data from the DR
2. If Multiple BYTES needs to be read
    a) Write the slave Address, and wait for the ADDR bit (bit 5 in SR1) to be set
	b) Wait for the RXNE (Receive buffer not empty) bit to set
	c) Read the data from the DR 
	
*/		
	
	int remaining = size;
	
/**** STEP 1 ****/	
	if (size == 1)
	{
		/**** STEP 1-a ****/	
		USART2->DR = Address;  //  send the address
		while (!(USART2->SR &0x00080));  
			
		/**** STEP 1-b ****/	
		while (!(USART2->SR & 0x00010));  // wait for RxNE to set
		
		/**** STEP 1-c ****/	
		buffer[size-remaining] = USART2->DR;  // Read the data from the DATA REGISTER
		
	}

/**** STEP 2 ****/		
	else 
	{
		/**** STEP 2-a ****/
		USART2->DR = Address;  //  send the address
		while (!(USART2->SR &0x00080));  // wait for ADDR bit to set
						
		while (remaining>2)
		{
			/**** STEP 2-c ****/
			while (!(USART2->SR & 0x00010));  // wait for RxNE to set
			
			/**** STEP 2-d ****/
			buffer[size-remaining] = USART2->DR;  // copy the data into the buffer			
			remaining--;
		}
    }
}
void UART_Address (uint8_t Address)
{
/**** STEPS FOLLOWED  ************
1. Send the Slave Address to the DR Register
2. Wait for the ADDR (bit 5 in SR) to set. This indicates the end of address transmission
3. clear the ADDR by reading the SR
*/	
	USART2->DR = Address;  //  send the address
	while (!(USART2->SR &0x00080));  // wait for ADDR bit to set
	uint8_t temp = USART2->SR; // read SR to clear the ADDR bit
}