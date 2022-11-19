#include <stdint.h>
#include <stdio.h>

/* Include section */
#include "GPIO.h"
#include "GPT.h"


/* LEDs PINs */
#define  LED1	5
#define  LED2	0

int main(void)
{
	GPIO_CLK(GPIOA,ENABLE);
	GPIO_MODE(GPIOA,OUTPUT,PUSH_PULL,LED1);
	GPIO_MODE(GPIOA,OUTPUT,PUSH_PULL,LED2);


	Delay_With_Timer_IT(TIM2,100);
	Delay_With_Timer_IT(TIM3,1000);

	GPT_IT_Enable(TIM2,28, UIE);
	GPT_IT_Enable(TIM3,29, UIE);

}

void TIM2_IRQHandler (void)
{
	GPT_IT_Handler(TIM2, UIE);

	GPIO_TOGGLE(GPIOA, LED1);
}

void TIM3_IRQHandler (void)
{
	GPT_IT_Handler(TIM3, UIE);

	GPIO_TOGGLE(GPIOA, LED2);
}


