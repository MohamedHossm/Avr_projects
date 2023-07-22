#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "I2C.h"
//*****************************************
#include "LCD_Interface.h"
#define F_CPU 8000000UL
#include "util\delay.h"
//*****************************************
void I2C_Init(u8 address ){
	I2C_SetAdderss(address);
	I2C_SetClock() ;
	// enable for Acknowledge
	SET_BIT(TWCR ,TWEA) ;
	I2C_Enable()  ;
}
void I2C_SetAdderss(u8 address) {
	TWAR = address<<1 ;
}

void I2C_SetClock() {
	TWSR&=0xf8 ;
	TWBR = 0 ;
}
void I2C_Enable() {
	SET_BIT(TWCR ,TWEN) ;
}
void I2C_StartCondition_Rstart() {
	// 	SET_BIT(TWCR ,TWSTA) ;
	// 	SET_BIT(TWCR ,TWINT) ;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // Send start condition

	
}
void I2C_StopCondition() {
	SET_BIT(TWCR ,TWSTO) ;
	SET_BIT(TWCR ,TWINT) ;
}
void I2C_SendData_Block(u16 data , u8 address) {
	I2C_StartCondition_Rstart() ;
	while(!I2C_Flag()) ;
	if (I2C_ReadStatus() != START)  ;
	I2C_SendDataLine(address<<1) ;  // last bit is 0 coz of write
	while(!I2C_Flag()) ;
	if (I2C_ReadStatus() != ADD_RECIVE)  ;
	I2C_SendDataLine(data) ;
	while(!I2C_Flag()) ;
	if (I2C_ReadStatus() != DATA_RECIVE)  ;
	I2C_StopCondition() ;
}
void I2C_SendData_Block_sequance(u8* data ,u8 dataSize, u8 address) {
	I2C_StartCondition_Rstart() ;
	I2C_R_Flag() ;
	while(!I2C_Flag()) ;
	if (I2C_ReadStatus() != START)  ;
	I2C_SendDataLine(address<<1) ;  // last bit is 0 coz of write
	while(!I2C_Flag()) ;
	if (I2C_ReadStatus() != ADD_RECIVE)  ;
	for (u8 i = 0 ; i <dataSize ; i++ ){
		I2C_SendDataLine(data[i]) ;
		while(!I2C_Flag()) ;
		if (I2C_ReadStatus() != DATA_RECIVE)  ;
	}
	I2C_StopCondition() ;
}
//void I2C_SendData_Block(u8 data , u8 address) {

//TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN) ;
//while (!(TWCR & (1<<TWINT))) ;
//if ((TWSR & 0xF8) != START) ;
// 	LCD_SetCursor(1,0) ;
// 	LCD_WriteString("S ");

// 	SET_BIT(TWCR , TWINT);
// 	CLR_BIT(TWCR , TWSTA);
// 	TWDR = address<<1;
// 	while (!(TWCR & (1<<TWINT))) ;
// 	if ((TWSR & 0xF8) != ADD_RECIVE) ;
// 	//LCD_SetCursor(1,0) ;
// 	LCD_WriteString("A ");
// 	SET_BIT(TWCR , TWINT);
// 	TWDR =data;
// 	while (!(TWCR & (1<<TWINT))) ;
// 	if ((TWSR & 0xF8) != DATA_RECIVE) ;
// 	LCD_WriteString("D ");
// }
void I2C_SendDataLine( u8 data ){
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
}

u8 I2C_ReadStatus(){
	u8 status  = TWSR&0xf8 ;
	return status ;
}
u8 I2C_Flag(){
	return (TWCR>>TWINT)&(1) ;
}
void I2C_R_Flag(){
	SET_BIT(TWCR , TWINT)  ;
	SET_BIT(TWCR ,TWEN) ;
}