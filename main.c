#include "stm32f10x.h"                  // Device header
//volatile uint32_t i;

int main()
{
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; //|= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN); // Taktirovanie PA pins s alternativnoy functiey
	//RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Taktirovanime PB
	
  GPIOA->CRL |= GPIO_CRL_MODE0;
  GPIOA->CRL &= ~GPIO_CRL_CNF0;
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	//TIM3->CNT = 0; // 72000 , this is 333ms
  TIM3->PSC = 36000-1;
	TIM3->ARR = 2000;
	TIM3->DIER |= TIM_DIER_UIE;
  TIM3->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM3_IRQn);
	while(1) {}
}

void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF;
  if(GPIOA->IDR & GPIO_IDR_IDR0) {
		GPIOA->ODR &= !GPIO_ODR_ODR0;
	} else {
		GPIOA->ODR = GPIO_ODR_ODR0;
	}
}
