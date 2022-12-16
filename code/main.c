#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "UART.h"
#include "ADC.h"
#include "GPIO.h"
#include "lcdd.h"
#include "LEDandBUZZER.h"

char state;
//const int ON = 1;
//const int OFF = 0;
//#define OFF 0

//*************************TASKS PROTOYPE******************************//

static void Task1(void *pvParameters);	//main controller
static void Task2(void *pvParameters);  //UART controller
static void Task3(void *pvParameters);  //LCD  controller
static void Task4(void *pvParameters);  //Buzz controller

//*************************QUEUE HANDLES******************************//

xQueueHandle xUARTQueue;
xQueueHandle xLCDQueue;
xQueueHandle xBuzzQueue;

//*************************GLOBAL VARIABLES***************************//

int setpoint=25;
int actual_temp;
int AlarmValue = 27;

typedef struct Messsage
	{
		int Txt1;
		//int Txt2;
	} AMessage;

//******************************MAIN**********************************//


	
int main(void)
{
	// Initialization Functions //
	LCD_init();
	
	UART0_Init();
	ADC_Init();
	portF_Init();
	
	
	
	
	// Queues //
	xUARTQueue = xQueueCreate(10, sizeof(char));
	xLCDQueue = xQueueCreate(10, sizeof(AMessage));
	xBuzzQueue = xQueueCreate(5, sizeof(char));

	// Taks creation //
	xTaskCreate(Task1, "MAIN CONTROLLER", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(Task2, "UART CONTROLLER", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(Task3, "LCD  CONTROLLER", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(Task4, "BUZZ CONTROLLER", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	
	//Starting the scheduler
	vTaskStartScheduler();
}

//******************************TASKS**********************************//

static void Task1(void *pvParameters)
{
	
	
	AMessage msg;
	LED_ON();
	while(1)
	{
		//xQueueReceive(xUARTQueue, &setpoint, 0);					// Recieve Data
		actual_temp = ADC_getValue();												// Read adc

		if(actual_temp < setpoint)
		{
			LED_ON();
		}
		else
		{
			LED_OFF();
		}
		
		msg.Txt1=actual_temp;
		//msg.Txt2=setpoint;
		
		xQueueSend(xLCDQueue, &msg, 0);
		
		if (actual_temp > AlarmValue){
			state = 1;
			xQueueSendToBack(xBuzzQueue, &state,0);
		}
		else{
			state = 0;
			xQueueSendToBack(xBuzzQueue, &state, 0);
		}
		taskYIELD();
	}
}

static void Task2 (void *pvParameters)
{
	while(1)
	{
		// UART write text "\n\r\n\rEnter Temperature Setpoint (Degrees): "
		setpoint=UART0_getString();
		UART0_sendNum(setpoint);
		
		//xQueueSend(xUARTQueue, &setpoint, pdMS_TO_TICKS(10));	// Send via queue to main controller
		UART0_sendState("\nSetpoint Changed\n");
		AlarmValue = setpoint+2;
		taskYIELD();

	}
}

static void Task3 (void *pvParameters)
{

	
	AMessage msg;
	LCD4bit_Cmd(0x01);
	LCD4bit_Cmd(0x80);
	
	while (1)
	{
		
		xQueueReceive(xLCDQueue, &msg, 0);										// Recieve data
		
		LCD_moveCursor(0,1);
		
		//LCD4bit_String("Actual:");
		//delay_milli(50);
		int_to_number_print(msg.Txt1);
		
		//LCD4bit_String(" Setpoint:");
		//delay_milli(50);
		//LCD4bit_Number(msg.Txt2);
		vTaskDelay(200);
		taskYIELD();
	}
}

static void Task4 (void *pvParameters)
{
	unsigned char BuzzerState;
	
	// additional config if needed
	BuzzerState = 0;
	
	while(1)
	{
		xQueueReceive(xBuzzQueue, &BuzzerState, 0);
		if(BuzzerState == 1)
		{
			Buzzer_ON();
		}
		else
		{
			Buzzer_OFF();
		}
		taskYIELD();
	}
}

/*
static void UART_sender (void *param)
{
	xSemaphoreTake(semaphore, portMAX_DELAY);
	
	char recievedValue;
	xQueueReceive(xQueue, &recievedValue, waitingTICKS);
	UART0_sendState(&recievedValue);
}
*/


