#include "stm32f10x.h"                  // Device header

int main()
{
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; //|= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN); // Taktirovanie PA pins s alternativnoy functiey
	//RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Taktirovanime PB
	
  GPIOA->CRL |= GPIO_CRL_MODE0_1;
  GPIOA->CRL &= ~GPIO_CRL_CNF0_0;
	
	GPIOA->CRL |= GPIO_CRL_MODE1_1;
  GPIOA->CRL &= ~GPIO_CRL_CNF1_0;
	
	GPIOA->CRL |= GPIO_CRL_MODE2_1;
  GPIOA->CRL &= ~GPIO_CRL_CNF2_0;
	
	RCC->APB1ENR |= (RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN);
	
	TIM2->PSC = 36000-1;
	TIM2->ARR = 2000;
	TIM2->DIER |= TIM_DIER_UIE;
  TIM2->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM2_IRQn);
	
  TIM3->PSC = 36000-1;
	TIM3->ARR = 2000;
	TIM3->DIER |= TIM_DIER_UIE;
  TIM3->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM3_IRQn);
	
	TIM4->PSC = 36000-1;
	TIM4->ARR = 2000;
	TIM4->DIER |= TIM_DIER_UIE;
  TIM4->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM4_IRQn);
	
	while(1) {}
}

void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~TIM_SR_UIF;
  if(GPIOA->IDR & GPIO_IDR_IDR1) {
		GPIOA->ODR &= !GPIO_ODR_ODR1;
	} else {
		GPIOA->ODR |= GPIO_ODR_ODR1;
	}
}


void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF;
  if(GPIOA->IDR & GPIO_IDR_IDR0) {
		GPIOA->ODR &= !GPIO_ODR_ODR0;
	} else {
		GPIOA->ODR |= GPIO_ODR_ODR0;
	}
}

void TIM4_IRQHandler(void)
{
	TIM4->SR &= ~TIM_SR_UIF;
  if(GPIOA->IDR & GPIO_IDR_IDR2) {
		GPIOA->ODR &= !GPIO_ODR_ODR2;
	} else {
		GPIOA->ODR |= GPIO_ODR_ODR2;
	}
}
