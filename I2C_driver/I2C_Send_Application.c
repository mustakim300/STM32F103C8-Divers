/* Include section */
#include <stdint.h>
#include <String.h>

/* Include section */
#include "GPIO.h"
#include "I2C.h"

/* I2C PINs */
#define CLK		6
#define SDA		7

char user_data[]= "Hello Everyone";

int main(void)
{
	GPIO_CLK(GPIOB,ENABLE);
	GPIO_MODE(GPIOB, OUTPUT, AF_OPEN_DRAIN, CLK);
	GPIO_MODE(GPIOB, OUTPUT, AF_OPEN_DRAIN, SDA);


	I2C_INIT(I2C1, SM_MODE, BUS_FREQ_VALUE, DEVICE_ADD);

	I2C_ENABLE(I2C1);

	MASTER_SEND(I2C1,(uint8_t*)user_data,strlen(user_data),SLAVE_ADD);
}





