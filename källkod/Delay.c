
#include "Delay.h"// includes the Delay header file
#include "UART.h" // includes the UART header file

void TIM5Config (void)
{
	/************** STEPS TO FOLLOW *****************
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	*/

// 1. Enable Timer clock
	RCC->APB1ENR |= (1U<<3);  // Enable the timer5 clock
	
// 2. Set the prescalar and the ARR
	TIM5->PSC = 90-1;  // 90MHz/90 = 1 MHz ~~ 1 uS delay
	TIM5->ARR = 0xffff;  // MAX ARR value
	
// 3. Enable the Timer, and wait for the update Flag to set
	TIM5->CR1 |= (1U<<0); // Enable the Counter
	while (!(TIM5->SR & (1U<<0)));  // UIF: Update interrupt flag..  This bit is set by hardware when the registers are updated
}

void Delay_us (uint16_t us)
{
	/************** STEPS TO FOLLOW *****************
	1. RESET the Counter
	2. Wait for the Counter to reach the entered value. As each count will take 1 us, 
		 the total waiting time will be the required us delay
	*/
	TIM5->CNT = 0;
	while (TIM5->CNT < us);
}

void Delay_ms (uint16_t ms)
{
	for (uint16_t i=0; i<ms; i++)
	{
		Delay_us (1000); // delay of 1 ms
	}
}