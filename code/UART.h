#ifndef _UART_
#define _UART_

void UART0_Init(void);
void UART0_sendChar(char Char);
void UART0_sendNum(int Num);
void UART0_sendState(char *string);
char UART0_getChar(void);
int UART0_getString(void);

#endif