/*
 * SPI_Service.h
 *
 * Created: 6/12/2023 7:27:22 AM
 *  Author: Amm
 */ 


#ifndef SPI_SERVICE_H_
#define SPI_SERVICE_H_
#define SPI_BUFFER_SIZE 20 

typedef enum {
	STACK_EMPTY , 
	STACK_FUll,
	STACK_FINE
	}Stack_error_t;

void SPI_Service_Init();
 Stack_error_t SPI_Stack_Push(u8 data);
 Stack_error_t SPI_Stack_Pop(u8* data);
void SPI_Service_Interrupt() ;
#endif /* SPI_SERVICE_H_ */