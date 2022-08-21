/* Header guard */
#ifndef I2C_H_
#define I2C_H_

/* Include section */
#include <stdint.h>

/* I2C Base address */
#define I2C1_BASE_ADD 			0x40005400U
#define I2C2_BASE_ADD 			0x40005800U
#define RCC_BASE_ADD			0x40021000U

/* I2C Clock Register */
#define I2C_CLK_REG				*(volatile uint32_t*)(RCC_BASE_ADD + 0x1CU)

/* I2C Clock Enable/Disable */
#define I2C1_CLK_ENABLE()		I2C_CLK_REG	|= (1U<<21)
#define I2C2_CLK_ENABLE()		I2C_CLK_REG	|= (1U<<22)
#define I2C1_CLK_DISABLE()		I2C_CLK_REG	&=~(1U<<21)
#define I2C2_CLK_DISABLE()		I2C_CLK_REG	&=~(1U<<22)

/* I2C Register definition */

typedef struct
{
	volatile uint32_t I2C_CR1;
	volatile uint32_t I2C_CR2;
	volatile uint32_t I2C_OAR1;
	volatile uint32_t I2C_OAR2;
	volatile uint32_t I2C_DR;
	volatile uint32_t I2C_SR1;
	volatile uint32_t I2C_SR2;
	volatile uint32_t I2C_CCR;
	volatile uint32_t I2C_TRISE;
}I2C_Regdef;


#define I2C1		((I2C_Regdef*)I2C1_BASE_ADD )
#define I2C2		((I2C_Regdef*)I2C2_BASE_ADD )


#define SM_MODE		0			/* Standard Mode of I2C*/
#define FM_MODE		1			/* Fast Mode of I2C*/

/* Others Macro */
#define DEVICE_ADD				0x61
#define SLAVE_ADD				0x68
#define BUS_FREQ_VALUE			8	 	/* MHz */
#define SM_SERIAL_FREQ			100		/* KHz */
#define FM_SERIAL_FREQ			400		/* KHz */


/* Function prototype*/

void I2C_ENABLE(I2C_Regdef *I2Cx);

void I2C_INIT(I2C_Regdef *I2Cx,uint8_t SM_FM_MODE,uint8_t BUS_FREQ,uint8_t DEVICE);

void MASTER_SEND(I2C_Regdef *I2Cx,uint8_t *Data,uint32_t len,uint8_t Slave_Add);

void MASTER_RECEIVE(I2C_Regdef *I2Cx,uint8_t *Rx_Data,uint32_t len,uint8_t Slave_Add);













#endif /* I2C_H_ */
