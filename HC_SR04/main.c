#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdio.h>
#include <stdlib.h>
#include "dwt_delay.h"

char str[50];
int i;
int msticks;
USART_InitTypeDef USART_InitStructure;

GPIO_InitTypeDef GPIO_InitStructure;

uint32_t sensor_time;
uint16_t distance;


void USART_puts(USART_TypeDef* USARTx, volatile char *s)
{
	while(*s)
	{
		while( !(USARTx->SR & 0x00000040) );

		USART_SendData(USARTx, *s);
		*s++;
	}
}
void delay_ms(int t){
	int tt=msticks;
	while(t<(msticks-tt));
}
void myUART_Init(void)
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

USART_InitStructure.USART_BaudRate = 9600;
USART_InitStructure.USART_WordLength = USART_WordLength_8b;
USART_InitStructure.USART_StopBits = USART_StopBits_1;
USART_InitStructure.USART_Parity = USART_Parity_No;
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

USART_Init(USART1, &USART_InitStructure); // USART configuration
USART_Cmd(USART1, ENABLE);
USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}
void Port_Init(void){
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //Enable clock for GPIOB
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //Enable clock for GPIOB
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOD, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOA, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOA, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOB, &GPIO_InitStructure);
GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);//Connect PB6 to USART1_Tx
GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
}
void USART_putb(char s){

while( !(USART1->SR & 0x00000040) );
USART_SendData(USART1, s);
}

uint32_t Read_HCSR04()
{
	uint32_t local_time = 0;

	GPIO_SetBits(GPIOA, GPIO_Pin_1);		// pull the trig pin high
	DWT_Delay_us(10);										// wait for 10 us
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);	// pull the trig pin low

	// wait for the echo pin to go high

	while(!(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)));

	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2))				// while the pin is high
	{
		local_time++;										// increment local time
		DWT_Delay_us(1);									// every 1 us
	}

	return local_time * 2;
}
int main()
{
	Port_Init();
	//myUART_Init();



	while(1)
	{
			  sensor_time = Read_HCSR04();			// get the high time
			  distance = sensor_time * .034 / 2;	// user the formula to get the distance

			  if(distance <= 4)
				  GPIO_SetBits(GPIOD, GPIO_Pin_All);
			  else if(distance > 4 && distance <= 6)
			  {
				  GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
				  GPIO_ResetBits(GPIOD, GPIO_Pin_15);
			  }

			  else if(distance > 6 && distance <= 8)
			  {
				  GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13);
				  GPIO_ResetBits(GPIOD, GPIO_Pin_14 | GPIO_Pin_15);
			  }

			  else if(distance > 8 && distance <= 10)
			  {
				  GPIO_SetBits(GPIOD, GPIO_Pin_12);
				  GPIO_ResetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
			  }
			  else
			  {
				  GPIO_ResetBits(GPIOD, GPIO_Pin_All);
			  }

	}
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
