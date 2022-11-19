
/* Include section */
#include "GPIO.h"
#include  "GPT.h"

#define LED1 0
#define LED2 1

int main(void)
{


	GPIO_CLK(GPIOA, ENABLE);
    GPIO_MODE(GPIOA, OUTPUT,AF_PUSH_PULL, LED1);
    GPIO_MODE(GPIOA, OUTPUT,AF_PUSH_PULL, LED2);

    /* This function takes parameters (TIMx, Channel, Frequency[KHz], Duty_Cycle)
    PWM(TIM2,CH1,1, 100);
    /* This function takes parameters (TIMx, Channel, Frequency[KHz], Duty_Cycle)
    PWM(TIM2,CH2,1, 5);


}

