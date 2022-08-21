#include <stdint.h>
#include "I2C.h"


#define FM_DUTY		0

void I2C_ENABLE(I2C_Regdef *I2Cx)
{
	/* I2C1 Clock Enable */
	I2C1_CLK_ENABLE();
	/* Peripheral Enable */
	I2Cx->I2C_CR1 |= (1 << 0);

}


void I2C_INIT(I2C_Regdef *I2Cx,uint8_t SM_FM_MODE,uint8_t BUS_FREQ,uint8_t DEVICE)
{



	/* Enable Acknowledge */
	I2Cx->I2C_CR1 |= (1 << 10);

	/* Bus frequency value in MHz */
	I2Cx->I2C_CR2 |= ((BUS_FREQ_VALUE << 0) & 0x3F);

	/*Store Device address */
	DEVICE=(DEVICE << 1) ;						/* Left shift by one because 7-bit Slave */
	I2Cx->I2C_OAR1 |=  	DEVICE;
	I2Cx->I2C_OAR1 |=  	(1<<14);				/* Set 14 bit as per data-sheet*/

	/* CCR(Clock control Register) Calculation */
	if(SM_FM_MODE==SM_MODE)
	{
		I2Cx->I2C_CCR &=  ~(1<<15); 			/* Set SM Mode*/
		uint16_t CCR=((BUS_FREQ_VALUE*1000)/(2*SM_SERIAL_FREQ));
		I2Cx->I2C_CCR |= (CCR<<0) & 0XFFF ;
	}
	else
	{
		#if(FM_DUTY ==0)
		{
			I2Cx->I2C_CCR &= ~(1<<14); 		/* Set Duty=0*/
			I2Cx->I2C_CCR |=  (1<<15); 		/* Set FM Mode*/
			uint16_t CCR=((BUS_FREQ_VALUE*1000)/(3*FM_SERIAL_FREQ));
			I2Cx->I2C_CCR |= (CCR<<0) ;
		}
		#else
		{
			I2Cx->I2C_CCR |= (1<<14); 		/* Set Duty=1*/
			I2Cx->I2C_CCR |=  (1<<15); 		/* Set FM Mode*/
			uint16_t CCR=((BUS_FREQ_VALUE*1000)/(25*FM_SERIAL_FREQ));
			I2Cx->I2C_CCR |= (CCR<<0) & 0XFFF ;
		}
		#endif
	}

	/* Trise Calculation */

	if(SM_FM_MODE==SM_MODE)
	{
		uint8_t Trise=((1000*BUS_FREQ_VALUE)/1000)+1;
		I2Cx->I2C_TRISE = (Trise<<0);
	}
	else
	{
		uint8_t Trise=((300*BUS_FREQ_VALUE)/1000)+1;
		I2Cx->I2C_TRISE = (Trise<<0);
	}

}


void MASTER_SEND(I2C_Regdef *I2Cx,uint8_t *Tx_Data,uint32_t len,uint8_t Slave_Add)
{
	/* [1] first set Start bit  then check the status of it */
	I2Cx->I2C_CR1 |=(1<< 8);
	while(!(I2Cx->I2C_SR1 & (1<<0)));


	/* [2] send Slave add and then check the respective flag*/
	Slave_Add =Slave_Add << 1 ;
	Slave_Add &=~(1);							// Write mode bit[0]
	I2Cx->I2C_DR = Slave_Add;
	while(!(I2Cx->I2C_SR1 & (1<<1)));

	/* [3] Clear Data Register by reading SR1 & SR2*/
	uint8_t dummy=I2Cx->I2C_SR1 ;
	dummy=I2Cx->I2C_SR2 ;
	(void)dummy;


	/* [4] Write 8-bit data in data Register*/
	while(len>0)
	{
		/* [5] Check TX flag before writing the data*/
		while(!(I2Cx->I2C_SR1 & (1<< 7)));
		I2Cx->I2C_DR =*Tx_Data;
		Tx_Data++;
		len--;
	}

	/* [6] Check TXe  & BTF flag before close the transmission*/

	while(!(I2Cx->I2C_SR1 & (1<< 7)));
	while(!(I2Cx->I2C_SR1 & (1<< 2)));

	/* [7] Set Stop bit */
	I2Cx->I2C_CR1 |=(1<< 9);


}


void MASTER_RECEIVE(I2C_Regdef *I2Cx,uint8_t *Rx_Data,uint32_t len,uint8_t Slave_Add)
{
	/* [1] first set Start bit  then check the status of it */
		I2Cx->I2C_CR1 |=(1<< 8);
		while(!(I2Cx->I2C_SR1 & (1<<0)));

		/* [2] send Slave add and then check the respective flag*/
		Slave_Add =Slave_Add << 1 ;
		Slave_Add |=(1<<0);						// Read mode bit[1]
		I2Cx->I2C_DR = Slave_Add;
		while(!(I2Cx->I2C_SR1 & (1<<1)));

		/* [3] Clear Data Register by reading SR1 & SR2*/
		uint8_t dummy=I2Cx->I2C_SR1 ;
		dummy=I2Cx->I2C_SR2 ;
		(void)dummy;

		if(len==1)
		{
			/* Disable Acknowledge */
			I2Cx->I2C_CR1 |= (1 << 10);

			/* [3] Clear Data Register by reading SR1 & SR2*/
			uint8_t dummy=I2Cx->I2C_SR1 ;
			dummy=I2Cx->I2C_SR2 ;
			(void)dummy;

			while((I2Cx->I2C_SR1 & (1<< 6)));

			/* [7] Set Stop bit */
			I2Cx->I2C_CR1 |=(1<< 9);

			/* Received data */
			*Rx_Data=I2Cx->I2C_DR ;

		}


}



