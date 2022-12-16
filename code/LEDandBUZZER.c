#include <stdint.h>
# include "tm4c123gh6pm.h"

void Buzzer_ON(void){
GPIO_PORTF_DATA_R |= 0x10;
}
void Buzzer_OFF(void){
GPIO_PORTF_DATA_R &= ~(0x10);

}
void LED_ON(void){
GPIO_PORTF_DATA_R |= 0x02;
}
void LED_OFF(void){
GPIO_PORTF_DATA_R &= ~(0x02);
}