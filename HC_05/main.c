#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
USART_InitTypeDef USART_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef  NVIC_InitStructure;
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

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOD, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOB, &GPIO_InitStructure);
GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);//Connect PB6 to USART1_Tx
GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
}
void NVICInitialize(void)
{

NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

NVIC_Init(&NVIC_InitStructure);
}

void USART_puts(char *s){

while(*s){
// wait until data register is empty
while( !(USART1->SR & 0x00000040) );
USART_SendData(USART1, *s);
*s++;
}
}
int size=5;
char rec_buf[10];
uint8_t state=0;
int i=0;

int count=0;
void USART1_IRQHandler(){
count++;
	char rec_byte=0x00;
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)){

		rec_byte=USART_ReceiveData(USART1);
		rec_buf[i]=rec_byte;
		if(i<10) i++;
		else i=0;
      if(count==4){
		if(rec_buf[0]=='O'){
			if(rec_buf[1]=='N'){

					USART_puts("led on\n");
					GPIO_SetBits(GPIOD,GPIO_Pin_12);
				    i=0;
					while(i<10){
						rec_buf[i]='\0';
						i++;
					}
					i=0;

					count=0;


			}}}
			else if(count==5){
		if(rec_buf[0]=='O'){
			if(rec_buf[1]=='F'){
							if(rec_buf[2]=='F'){
								i=0;
								GPIO_ResetBits(GPIOD,GPIO_Pin_12);
								USART_puts("led off\n");
								while(i<10){
											rec_buf[i]='\0';
											i++;
											}
											i=0;

											count=0;
								}
				}}
		}
		}



}


int main(void)
{
 Port_Init();
 myUART_Init();
 NVICInitialize();
  while (1)
  {
	  //USART_puts("hello world!!");


  }
}



void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}
