#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "Timers.h"
#include "ultra.h"
//#include "LCD_Interface.h"
// #define F_CPU 8000000
// #include <util/delay.h>
#define maxtimer 20001
static volatile u16 time ,t1,t2 ;
static  volatile s8 flag =-1 ;
static volatile u32 c  ;
static volatile u32 c1  ;
void ultr_init (void){
	//do noting
	// 	Timer1_ICU_SetCallBack(ICUFUN);
	// 	Timer1_ICU_InterruptEnable() ;
}

void ultr_Start (ultr_type data_ultra ){
	if (flag == -1) {
		//TCNT1 = 0 ;
		
		Timer1_InputCaptureEdge(RISING) ;
		DIO_WritePin(data_ultra.pintrig,HIGH) ;
		_delay_us(10) ;
		DIO_WritePin(data_ultra.pintrig,LOW) ;
		flag++ ;
	}
}
u8 ultr_GetRead_Noblock (ultr_type * data_ultra ){
	if (flag==2){
		time = ((s32)t2-t1)+(c1*maxtimer) ;
		
		data_ultra->d = time/58 ;

		flag = -1 ;
		return  1 ;
		}else {

		return 0 ;
	}
}
// void ultr_Read ( s8 countertemp ){
// 	if (counter==-1){
// 		counter = countertemp ;
// 	}
// 	if (data_ultra[counter].flag == -1 ) {
// 		LCD_WriteString("  ") ;
// 		data_ultra[counter].flag  = 0 ;
// 		TCNT1 = 0 ;
// 		Timer1_InputCaptureEdge(RISING) ;
// 		DIO_WritePin(data_ultra[counter].pintrig,HIGH) ;
// 		_delay_us(10) ;
// 		DIO_WritePin(data_ultra[counter].pintrig,LOW) ;
// 	}
// 	//else if(data_ultra[counter].flag == 2 ) {
// 	//}
// }
// u16 ultra_getRead(u8 data ){
// 	return data_ultra[data].d ;
// }
void ICUFUN(void){
	
	if (flag == 0 ){
		t1 = ICR1	;
		c = 0 ; 
		Timer1_InputCaptureEdge(FALLING) ;
		flag++ ;
	}
	else if (flag == 1 ){
		t2= ICR1	;
		c1 = c ;
		Timer1_InputCaptureEdge(RISING) ;
		flag++ ;
	}
}
void OVF_FUN(void){
	
	c ++ ;
}