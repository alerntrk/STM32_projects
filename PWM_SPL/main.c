#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
TIM_OCInitTypeDef TIM_OCInitStruct,TIM2_OCInitStruct; // OC: Output Channel

void config()
{
	/*
	 * Bu projede TIM4 timer�n� kullanaca��z. Ledlerimizin �zerinde bulundu�u pinlerde mevcut.
	 * Bu sayede farkl� bir komponent kullanmadan direkt olarak yapt���m�z ayar� board �zerinde g�rece�iz.
	*/

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	// AF � belirtti�imiz yer
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
	// Hangi pin hangi fonksiyon i�in tan�mlanacaksa onu se�meliyiz.

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // ��k�� elde edece�iz ancak pwm �zerinden ��k�� verece�iz bu
	// sebeple alternate function oldu�unu belli etmemiz laz�m. AF olarak s�yledik ve pwm ��k�� elde edece�iz
	// e�er AF olarak bir fonksiyon tan�mlad�ysak kesinlikle AF �n �zerinde belirtmemiz gerekir.
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Prescaler = 8399;
	TIM_InitStruct.TIM_Period = 9999;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV4;
	TIM_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM4, &TIM_InitStruct);

	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Prescaler = 16799;
	TIM_InitStruct.TIM_Period = 9999;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV4;
	TIM_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2, &TIM_InitStruct);

	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
	// T�mer PWM Konfigurasyonu

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;  // 1. Modu kullanaca��m�z� s�yledik
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; // ��k�� almay� aktif ettik
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; // HIGH ve LOW olma durumu

	TIM2_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;  // 1. Modu kullanaca��m�z� s�yledik
	TIM2_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; // ��k�� almay� aktif ettik
	TIM2_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; // HIGH ve LOW olma durumu
}

int main(void)
{
	config();
  while (1)
  {

	  TIM_OCInitStruct.TIM_Pulse = 4999;
	  TIM_OC2Init(TIM4, &TIM_OCInitStruct);
	  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);


	  TIM2_OCInitStruct.TIM_Pulse = 4999;
	  TIM_OC2Init(TIM2, &TIM2_OCInitStruct);
	  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  /* TODO, implement your code here */
  return -1;
}
