#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "SPI.h"
#define F_CPU 8000000
#include "util\delay.h"
#include "LCD_Interface.h"
void (*Call_Back_ptr) (void) ;
void SPI_Enable(){
	
	SET_BIT(SPCR , SPE);
}
void SPI_Init(SPI_MODE_type mode,SPI_SPEED_type speed) {
	// select master or slave
	if (mode==MASTER){
		SET_BIT(SPCR , MSTR);
		SPI_CLOCK(speed) ;
		}else {
		CLR_BIT(SPCR , MSTR);
	}
	
	// data mode  0
	//SPI_Mode(zero) ;
	
	SPI_Enable() ;
	
}
//SPI2X SPR1 SPR0 
void SPI_CLOCK(SPI_SPEED_type speed) {
	WRITE_BIT(SPCR ,SPR0,READ_BIT(speed, 0)) ;
	WRITE_BIT(SPCR ,SPR1,READ_BIT(speed, 1)) ;
	WRITE_BIT(SPSR ,SPI2X,READ_BIT(speed, 2)) ;
}


SPI_Recive_type SPI_SendRecive_Timeout(u8 Sdata ,u8 *Rdata, u8 time ){
	// to make SPIF =0 ;
	*Rdata=SPDR ;
	*Rdata = READ_BIT( SPSR,SPIF );
	//--------------------------------
	SPDR=Sdata ;
	while(!READ_BIT( SPSR,SPIF )){
		time -- ;
		_delay_us(1);
		if (time == 0) {	
			return TIMEOUT;
		}
	}
	*Rdata = SPDR ;
	return RECIVED ;
}


u8 SPI_SendRecive(u8 data) {
	SPDR=data ;
	while(!READ_BIT( SPSR,SPIF ));
	return SPDR;
}
u8 SPI_Recive_NOblock() {
	return SPDR;
}
void SPI_Send_NOblock(u8 data ) {
	SPDR = data ;
}
void SPI_Interrupt_Enable() {
	SET_BIT(SPCR , SPIE);
}
void SPI_Interrupt_Disable() {
	CLR_BIT(SPCR , SPIE);
}
void SPI_Interrupt_CAll_Back(void (*fun) (void)  )  {
	
	Call_Back_ptr  = fun  ;
}
ISR(SPI_STC_vect){
	if (Call_Back_ptr!=0){
		Call_Back_ptr() ;
		}else {
		
		//do nothing
	}
	
}