#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
void clkConfig(){
	RCC->CR |= 0x30000;//HSEON
	while(!(RCC->CR & 0x20000);//HSERDY flag
	RCC->CR |= 0x80000;// CSS ENABLE
	RCC->PLLCFGR |= 0x400000;//PLL choosen as HSE
	RCC->PLLCFGR |= 0x4;//M=4
	RCC->PLLCFGR |= 0x5A00;//N=168
	RCC->PLLCFGR |= 0x0;//P=0
	RCC->CFGR |= 0x0;//AHB Prescalar=1
	RCC->CFGR |=0x80000;//APB2 Prescalar=2
	RCC->CFGR |=0x1400;//APB1 Prescalar=4
	RCC->CIR |= 0x80000;//HSERDY flag clear
	RCC->CIR |= 0x800000;//CSS flag clear

}

void GPIO_Config(){
	RCC->AHB1ENR |= 0x9;//GPIOA & GPIOD clk enable
    GPIOD->MODER |= 0x55000000;//pin12 to pin15 output
    GPIOD->OSPEEDR |=0xFF000000;
    GPIOD->OTYPER |= 0x0;
    GPIOD->PUPDR |= 0x0;

}
void EXTI_Config(){

	RCC->APB2ENR |= 0x4000;//syscfg clk enable
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_SetPriority(EXTI0_IRQn,0);
	NVIC_SetPriority(EXTI1_IRQn,1);
	NVIC_SetPriority(EXTI2_IRQn,2);

	EXTI->IMR |= 0x7;
	EXTI->RTSR |=0x7;

}
void delay(uint32_t t){
	while(t--);
}
void EXTI0_IRQHandler(){

	if(EXTI->PR & 0x1){
		GPIOD->ODR=0x1000;
		delay(33600000);
		EXTI->PR=0x1;

	}
}
void EXTI1_IRQHandler(){

	if(EXTI->PR & 0x2){
		GPIOD->ODR=0x2000;
		delay(33600000);
		EXTI->PR=0x2;

	}
}
void EXTI2_IRQHandler(){

	if(EXTI->PR & 0x4){
		GPIOD->ODR=0x4000;
		delay(33600000);
		EXTI->PR=0x4;

	}
}

int main(void)
{
  clkConfig();
  GPIO_Config();
  EXTI_Config();
  while (1)
  {
    GPIOD->ODR |= 0xF000;
  }
}
