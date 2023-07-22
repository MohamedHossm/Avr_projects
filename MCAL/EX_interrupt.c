#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "EX_interrupt.h"
static void (*Ex_p0)(void) = (void*)(0);
static void (*Ex_p1)(void)= (void*)(0);

void Enable_EX(EX_type num , EX_state_type state){
	switch(num) {
		case Ex0 :
		WRITE_BIT (MCUCR ,ISC01,READ_BIT(state , 1) ) ;
		WRITE_BIT (MCUCR ,ISC00,READ_BIT(state , 0) ) ;
		SET_BIT(GICR,INT0) ;
		break;
		case Ex1 :
		
		WRITE_BIT (MCUCR ,ISC11,READ_BIT(state , 1) ) ;
		WRITE_BIT (MCUCR ,ISC10,READ_BIT(state , 0) ) ;
		SET_BIT(GICR,INT1) ;

		break;
		case Ex2 :
		SET_BIT(GICR,INT1) ;
		break;
	}
	
	
}
void Disable_EX(EX_type num ){
	switch(num) {
		case Ex0 :
		CLR_BIT(GICR,INT0) ;
		break;
		case Ex1 :
		CLR_BIT(GICR,INT1) ;
		break;
		case Ex2 :
		CLR_BIT(GICR,INT2) ;
		break;
	}
}
void EXCall_Back(EX_type num , void (*fpt)(void)){
	switch(num){
		case Ex0 :
		Ex_p0 = fpt ;
		break;
		case Ex1 :
		Ex_p1 = fpt ;
		break;
		case Ex2 :
		break;
	}
	
}
ISR(INT0_vect){
	if (Ex_p0!= (void*)(0))
	Ex_p0();
	
}
ISR(INT1_vect){
	if (Ex_p1!= (void*)(0))
	Ex_p1();
	
}