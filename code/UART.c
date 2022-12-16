#include "UART.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"

void UART0_Init(void){
		
	SYSCTL_RCGCUART_R |= 0x01;    //enable clock for UART
	SYSCTL_RCGCGPIO_R |= 0x01;		//enable clock for port A
	
	GPIO_PORTA_AFSEL_R |= 0x03;
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0XFFFFFF00) + 0X011;
	GPIO_PORTA_DEN_R |= 0x03;
	GPIO_PORTA_AMSEL_R &= ~0x03;
	
  UART0_CTL_R = 0;
	UART0_IBRD_R = 104;
	UART0_FBRD_R = 11;
	UART0_CC_R = 0;
	UART0_LCRH_R = 0x060;
	UART0_CTL_R = 0x0301;
	
  
	
	NVIC_PRI7_R = 7<<21;
	NVIC_EN0_R |= 1 <<30;
	
	// PORT A Initializtion
	
	
		
	GPIO_PORTA_DEN_R |= 0x03;			//enable digital I/O of TX and RX pins as output
	GPIO_PORTA_AFSEL_R |= 0x03;		//enable alternate function for pins
	GPIO_PORTA_PCTL_R |= 0x11;		//Configue pins for UART

}

void UART0_sendChar(char Char)
{
    while( (UART0_FR_R & 0x20) != 0){};
    UART0_DR_R = Char;
}
void UART0_sendNum(int number)  
{
	    int temp = number;
			if(temp == 0){
				UART0_sendChar('0');
			}
			else{
				uint8_t index = 0;
				uint8_t myArray[10];
				while (temp != 0){
					uint8_t number = temp%10;
					temp = (uint8_t)temp/10;
					number  += 48;
					myArray[index++] = number;
				}
				for(int i = index - 1; i>=0;i--){
					UART0_sendChar((char)myArray[i]);
				}
		}          
}

void UART0_sendState(char *string)
{
  while(*string)
  {
      UART0_sendChar(*(string++));
  }
}

char UART0_getChar(void)
{
char data;
   while( (UART0_FR_R & 0x10) != 0) {} ;
    data = UART0_DR_R;
	return data;
}


int UART0_getString(void)
{
	int number=0;
	char Char=0;
	char check=0;
	do {
		number = number * 10 + (Char);
		Char = UART0_getChar() - 48;
		check = Char + 48;
	}while( check != 13);
	return number;
}

