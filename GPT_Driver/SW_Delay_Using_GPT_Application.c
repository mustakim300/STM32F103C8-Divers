#include <stdint.h>
#include <stdio.h>

/* Include section */
#include "GPIO.h"
#include  "GPT.h"

#define LED		5

int main(void)
{

	GPIO_CLK(GPIOA,ENABLE);
	GPIO_MODE(GPIOA, OUTPUT, PUSH_PULL,LED);

	while(1)
	{
		GPIO_WRITE(GPIOA, HIGH,LED);
		Delay_With_Timer(TIM2, 500);

		GPIO_WRITE(GPIOA, LOW, LED);
		Delay_With_Timer(TIM2, 500);
	}


}



