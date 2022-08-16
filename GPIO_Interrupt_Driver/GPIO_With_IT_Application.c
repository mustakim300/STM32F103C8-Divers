#include <stdint.h>
#include <String.h>

/* Include section */
#include "GPIO.h"
#include "delay.h"
#include "GPIO_Interrupt.h"


/* LED & Button PINs */
#define  LED		11  	// B11
#define  BUTTON		15		// B15


int main(void)
{
	GPIO_CLK(GPIOB,ENABLE);
	GPIO_MODE(GPIOB, INPUT, OPEN_DRAIN,BUTTON);
	GPIO_MODE(GPIOB, OUTPUT, PUSH_PULL,LED);

	GPIO_Interrupt_Set(B, BUTTON, RT);
	GPIO_Interrupt_Enable(40, ENABLE);

	while(1)
	{
		GPIO_WRITE(GPIOB, HIGH,LED);
	}

}

void EXTI15_10_IRQHandler(void)
{
	// For de-bounce purpose
	delay(50);
	// Interrupt handling
	GPIO_Interrupt_Handling(BUTTON);

	//LED will off for 0.5 second when button will press.
	GPIO_WRITE(GPIOB,LOW,LED);
	delay(500);


}



