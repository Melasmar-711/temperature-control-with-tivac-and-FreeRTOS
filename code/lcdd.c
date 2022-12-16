#include "TM4C123.h"                    // Device header
#include "tm4c123gh6pm.h"
#include "lcdd.h" 
#include <stdlib.h>



void LCD_init(void)
{
 SYSCTL_RCGCGPIO_R |=0x04;
 SYSCTL_RCGCGPIO_R |=0x02;
 GPIO_PORTB_DIR_R |=0xF0;
 GPIO_PORTB_DEN_R |=0xF0;
 GPIO_PORTC_DIR_R |=0xF0;
 GPIO_PORTC_DEN_R |=0xF0;
 
 LCD4bit_Cmd(0x20);
 LCD4bit_Cmd(0x28);
 LCD4bit_Cmd(0x06);
 LCD4bit_Cmd(0x01);
 LCD4bit_Cmd(0x0F);
	

}
void LCD4bit_Data(unsigned char data)
{
 unsigned char temp;
 GPIO_PORTC_DATA_R = RS;
 temp = data;
 temp = temp<<4;
 LCD_DATAP = temp;
 GPIO_PORTC_DATA_R = RS |EN;
 delay_micro(10);
 GPIO_PORTC_DATA_R =RS;
 delay_micro(37);
 
 temp =data;
 //LCD_CTRLP->DATA = RS;
 LCD_DATAP = temp;
 GPIO_PORTC_DATA_R = RS |EN;
 delay_micro(10);
 GPIO_PORTC_DATA_R =0x00;
 delay_micro(37);
 
}

void LCD4bit_String(const char *Str)
{
	int i=0;
	while (Str[i] !='\0') {
		LCD4bit_Data((Str[i]));
		i++;
	}
}

 
void LCD4bit_Cmd(unsigned char command)
{
 unsigned char temp;
 GPIO_PORTC_DATA_R = 0x00;
 temp = command;
 temp = temp<<4;
 	LCD_DATAP =temp;
 GPIO_PORTC_DATA_R = EN;
 delay_micro(0);
 GPIO_PORTC_DATA_R = 0x00;
 if(command < 4) delay_milli(2); 
 else delay_micro(37); temp = command; 	LCD_DATAP =temp;
 GPIO_PORTC_DATA_R = EN;
 delay_micro(0);
 GPIO_PORTC_DATA_R =0x00;
 

}

void int_to_number_print(int number){
	
	int temp = number;
	
	char buff[16];
	

	if(temp == 0){
				buff[0]='0';
				buff[1]='\n';
				
			}else{
				uint8_t index = 0;
				while (temp != 0){
					uint8_t number = temp%10;
					temp = (uint8_t)temp/10;
					number  += 48;
					buff[index++] = number;
				}
				for(int i = index - 1; i>=0;i--){
					LCD4bit_Data(buff[i]);
				}
		}
	}

	
	
	void LCD_moveCursor(unsigned char row,unsigned char col)
{
	unsigned char lcd_memory_address;
	
	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}					
	/* Move the LCD cursor to this specific address */
	LCD4bit_Cmd(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

 
void delay_milli(int n)
{
 int i,j;
 for(i=0;i<n;i++)
 for(j=0;j<3180;j++)
 {}
}
 
void delay_micro(int n)
{
 int i,j;
 for(i=0;i<n;i++)
 for(j=0;j<3;j++)
 {}
 
}
