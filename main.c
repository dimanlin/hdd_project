#include "stm32f10x.h"                  // Device header

int status_led_1;
int status_led_2;
int status_led_3;

int main()
{
	status_led_1 = 0;
	status_led_2 = 0;
	status_led_3 = 0;
	
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; //|= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN); // Taktirovanie PA pins s alternativnoy functiey
	
  GPIOA->CRL |= GPIO_CRL_MODE0_1;
  GPIOA->CRL &= ~GPIO_CRL_CNF0_0;
	
	GPIOA->CRL |= GPIO_CRL_MODE1_1;
  GPIOA->CRL &= ~GPIO_CRL_CNF1_0;
	
	GPIOA->CRL |= GPIO_CRL_MODE2_1;
  GPIOA->CRL &= ~GPIO_CRL_CNF2_0;
	
	RCC->APB1ENR |= (RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN);
	
	TIM2->PSC = 36000-1;
	TIM2->ARR = 1000;
	TIM2->DIER |= TIM_DIER_UIE;
  TIM2->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM2_IRQn);
	
  TIM3->PSC = 36000-1;
	TIM3->ARR = 2000;
	TIM3->DIER |= TIM_DIER_UIE;
  TIM3->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM3_IRQn);
	
	TIM4->PSC = 36000-1;
	TIM4->ARR = 3000;
	TIM4->DIER |= TIM_DIER_UIE;
  TIM4->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM4_IRQn);
	
	while(1) {
		if(status_led_1 == 0) {
			GPIOA->ODR &= !GPIO_ODR_ODR0;
		} else {
			GPIOA->ODR |= GPIO_ODR_ODR0;
		}
		
		if(status_led_2 == 0) {
			GPIOA->ODR &= !GPIO_ODR_ODR1;
		} else {
			GPIOA->ODR |= GPIO_ODR_ODR1;
		}
		
		if(status_led_3 == 0) {
			GPIOA->ODR &= !GPIO_ODR_ODR2;
		} else {
			GPIOA->ODR |= GPIO_ODR_ODR2;
		}
	}
}

void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~TIM_SR_UIF;
	if(status_led_1 == 0) {
		status_led_1 = 1;
	} else {
		status_led_1 = 0;
	}
}

void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF;
	if(status_led_2 == 0) {
		status_led_2 = 1;
	} else {
		status_led_2 = 0;
	}
}

void TIM4_IRQHandler(void)
{
	TIM4->SR &= ~TIM_SR_UIF;
  if(status_led_3 == 0) {
		status_led_3 = 1;
	} else {
		status_led_3 = 0;
	}
}
