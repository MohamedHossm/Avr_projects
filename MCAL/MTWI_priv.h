/*
 * MTWI_priv.h
 *
 *  Created on: Jun 21, 2023
 *      Author: elray
 */

#ifndef MI2C_MTWI_PRIV_H_
#define MI2C_MTWI_PRIV_H_

#define TWCR_REG (*((volatile u8 *)0x56))//control register
#define TWDR_REG (*((volatile u8 *)0x23))//data register
#define TWAR_REG (*((volatile u8 *)0x22))//slave adress register
#define TWSR_REG (*((volatile u8 *)0x21))//status register
#define TWBR_REG (*((volatile u8 *)0x20))//bit rate register

//TWCR
//TWINT TWEA TWSTA TWSTO TWWC TWEN – TWIE
#define TWINT_BIT    7//interrupt flag
#define TWEA_BIT     6//TWI ENABLE AK
#define TWSTA_BIT	 5//to send start condition
#define TWSTO_BIT    4//to send stop condition
#define TWWC_BIT	 3//write collision flag
#define TWEN_BIT 	 2//TWI ENABLE
#define TWIE_BIT	 0//TWI INTERRAPT ENABLE

//TWSR_REG
#define TWSP1_BIT 1 //prescaler bit 1
#define TWSP0_BIT 0 //prescaler bit 0

//TWAR_REG
#define TWGCE_BIT 0 //disable /enable general call register

#define MTWI_STATUS_MASK  0b11111000

#endif /* MI2C_MTWI_PRIV_H_ */
