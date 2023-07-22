

#ifndef SPI_H_
#define SPI_H_
typedef enum {
	MASTER,
	SLAVE
}SPI_MODE_type ;
typedef enum {
	F_2 = 4 ,
	F_4 = 0 ,
	F_8 = 5 ,
	F_16 = 1,
	F_32 = 6,
	F_64 = 2,
	F_128 = 7

}SPI_SPEED_type ;
typedef enum {
	ZERO ,
	ONE ,
	TWO ,
	THREE

}SPI_MODE_signal_type ;
typedef enum {
	TIMEOUT ,
	RECIVED 
}SPI_Recive_type ;

void SPI_Init(SPI_MODE_type mode,SPI_SPEED_type speed);
void SPI_Enable();
void SPI_Mode(SPI_MODE_signal_type mode) ;
void SPI_CLOCK(SPI_SPEED_type speed) ;
u8 SPI_SendRecive(u8 data); // for master
// time us 
SPI_Recive_type SPI_SendRecive_Timeout(u8 Sdata ,u8 *Rdata, u8 time );
void SPI_Send_NOblock(u8 data ); // for slave
u8 SPI_Recive_NOblock() ; // for slave
void SPI_Interrupt_Enable() ;
void SPI_Interrupt_Disable() ;
void SPI_Interrupt_CAll_Back()  ;

#endif /* SPI_H_ */