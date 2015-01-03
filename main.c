#include "stm32f10x.h"                  // Device header

int position;
int arr;

int main()
{
	arr = 500;
	position = 0;
	
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; //|= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN); // Taktirovanie PA pins s alternativnoy functiey
	
  GPIOA->CRL |= GPIO_CRL_MODE0_1;
  GPIOA->CRL &= ~GPIO_CRL_CNF0_0;
	
	GPIOA->CRL |= GPIO_CRL_MODE1_1;
  GPIOA->CRL &= ~GPIO_CRL_CNF1_0;
	
	GPIOA->CRL |= GPIO_CRL_MODE2_1;
  GPIOA->CRL &= ~GPIO_CRL_CNF2_0;
	
	RCC->APB1ENR |= (RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN);
	
	TIM2->PSC = 36000-1;
	TIM2->ARR = arr;
	TIM2->DIER |= TIM_DIER_UIE;
  TIM2->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM2_IRQn);
	
	
	while(1) {
		if(position == 0) {
			GPIOA->ODR &= !GPIO_ODR_ODR1;
			GPIOA->ODR &= !GPIO_ODR_ODR2;
			GPIOA->ODR |= GPIO_ODR_ODR0;
		}
		
		if(position == 1) {
			GPIOA->ODR &= !GPIO_ODR_ODR2;
			GPIOA->ODR &= !GPIO_ODR_ODR0;
			GPIOA->ODR |= GPIO_ODR_ODR1;
		}
		
		if(position == 2) {
			GPIOA->ODR &= !GPIO_ODR_ODR0;
			GPIOA->ODR &= !GPIO_ODR_ODR1;
			GPIOA->ODR |= GPIO_ODR_ODR2;
		}
	}
}

void TIM2_IRQHandler(void)
{
	arr = arr - 20;
	TIM2->ARR = arr;
	
	TIM2->SR &= ~TIM_SR_UIF;
	
	if(position == 2) {
		position = 0;
	} else {
		position += 1;
	}
}

