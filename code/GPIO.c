#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include <stdint.h>

//Initialize Port F to control the LED
void portF_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x20;		// enable clock for port F
	
	GPIO_PORTF_DIR_R |= 0xFF;			//set direction
	
	//GPIO_PORTF_PUR_R = 0x10U;			//enable internal pull-up
	
	GPIO_PORTF_DEN_R |= 0xFF;			//enable digital i/o
	
//	GPIO_PORTF_IM_R |= (1<<4);		//unmask interrupt
//	GPIO_PORTF_IS_R |= (1<<4);		//make bit 4 level sensitive
//	GPIO_PORTF_IBE_R &= ~(1<<4);
//	GPIO_PORTF_IEV_R &= ~(1<<4);	//low level trigger
//	GPIO_PORTF_ICR_R |= (1<<4);
//	
//	NVIC_PRI7_R = 2 << 21;
//	NVIC_EN0_R |= (1<<30);
}
