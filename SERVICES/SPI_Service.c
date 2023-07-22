#include "StdTypes.h"
#include "SPI.h"
#include "SPI_Service.h"
static u8 SPI_STACK [SPI_BUFFER_SIZE] ;
u8 stack_ptr = 0 ; 
void SPI_Service_Init(){
	SPI_Interrupt_CAll_Back(SPI_Service_Interrupt) ; 
}
 Stack_error_t SPI_Stack_Push(u8 data){
	if (stack_ptr==SPI_BUFFER_SIZE){
		return STACK_FUll ; 
	}
	SPI_STACK[stack_ptr++] = data ; 
	return STACK_FINE ; 
}
Stack_error_t SPI_Stack_Pop(u8* data){
	if (stack_ptr == 0 ){
		return STACK_EMPTY ;
	}
	stack_ptr-- ;
	*data = SPI_STACK[stack_ptr] ; 
	return STACK_FINE ;
}
void SPI_Service_Interrupt(){
	SPI_Stack_Push(SPI_Recive_NOblock());
	
}