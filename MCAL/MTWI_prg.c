
#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#include "ERROR_STATES.h"
#include "MTWI_priv.h"
#include "MTWI_config.h"
#include "MTWI_int.h"


 static void I2C_SetAdderss(u8 address) {
	TWAR = address<<1 ;
}

static void I2C_SetClock() {
	TWSR&=0xf8 ;
	TWBR = 0 ;
}
static void I2C_Enable() {
	SET_BIT(TWCR ,TWEN) ;
}

void MTWI_enInit(u8 address)
{
	I2C_SetAdderss(address);
	I2C_SetClock() ;
	// enable for Acknowledge
	SET_BIT(TWCR ,TWEA) ;
	I2C_Enable()  ;


}

ErrorState_t MTWI_enSendStart(void)
{
	//	STEP1: clear flag + set start bit + Enable TWI
	TWCR_REG = (1<<TWINT_BIT)|(1<<TWSTA_BIT)|(1<<TWEN_BIT);
	// step 2 : wait until operation starts
	while (!(TWCR_REG & (1<<TWINT_BIT)));  //GET BIT

	return SUCCES;
}

ErrorState_t MTWI_enSendStop(void)
{
	TWCR_REG = (1<<TWINT_BIT)|(1<<TWEN_BIT)|(1<<TWSTO_BIT);
	return SUCCES;
}
ErrorState_t MTWI_enSendByte(u8 copy_u8Data)
{//load data into register
	TWDR_REG = copy_u8Data;
	//clear flag + set Enable
	TWCR_REG = (1<<TWINT_BIT) | (1<<TWEN_BIT);
	//wait
	while (!(TWCR_REG & (1<<TWINT_BIT)));  //GET BIT
	return SUCCES;
}
ErrorState_t MTWI_enRecByteAck(u8 *ptrRECdata)
{
	//clear flag + set Enable
	TWCR_REG = (1<<TWINT_BIT) | (1<<TWEN_BIT)|(1<<TWEA_BIT);
	while (!(TWCR_REG & (1<<TWINT_BIT)));  //GET BIT
	//load data
	*ptrRECdata=TWDR_REG;

	return SUCCES;
}
ErrorState_t MTWI_enRecByteNoAck(u8 *ptrRECdata)
{
	//clear flag + set Enable
	TWCR_REG = (1<<TWINT_BIT) | (1<<TWEN_BIT);
	while (!(TWCR_REG & (1<<TWINT_BIT)));  //GET BIT
	//load data
	*ptrRECdata=TWDR_REG;
	return SUCCES;
}
ErrorState_t MTWI_enReadStatus(u8 * ptrStatusValue)
{
	//apply mask on status register
	* ptrStatusValue =TWSR_REG & MTWI_STATUS_MASK;
	return SUCCES;
}
