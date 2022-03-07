#include <stddef.h>
#include "stm32l0xx.h"

uint16_t i;
void delay(uint32_t t){
	while(t--);
}
void DAC1_Config()
{
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

	RCC->APB1ENR |= RCC_APB1ENR_DACEN;

	DAC->CR |= 0x00000001;		// DAC Channel 1 enable
	DAC->SWTRIGR |= 0x00000000; // DAC Channel 1 software trigger disable
	DAC->DHR12R1 |= 0x00000000;	// DAC Channel 1 12-bit right-aligned data
}

int main(void)
{
	DAC1_Config();


  while (1)
  {
	  for(i=0; i < 4096; i++)
		  {
			  DAC->DHR12R1 = i;
			  delay(2100);
		  }
		  i = 0;
  }

  return 0;
}
