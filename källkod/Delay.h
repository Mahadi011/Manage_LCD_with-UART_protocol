
#ifndef __Delay_H
#define __Delay_H    // defines the __DELAY_H macro if it is not already defined

#include <stdint.h>   // includes the stdint header file, which provides typedefs for integer types

void TIM5Config(void);  // function prototype for the TIM5Config function

void Delay_us(uint16_t us);  // function prototype for the Delay_us function, which takes a uint16_t argument named us

void Delay_ms(uint16_t ms);  // function prototype for the Delay_ms function, which takes a uint16_t argument named ms

#endif   // end of include guard
