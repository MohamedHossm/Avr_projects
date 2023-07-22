#include "StdTypes.h"
#include "ADC_Interface.h"
/*#include "LCD_Interface.h"*/
#include "ADC_SERVICE.h"


static u16 QueueAdc[SIZE_MAX_ADC_Queue] = {0};
static u8 Pointer_Head  = 0 ;
static u8 Pointer_tail  = 0 ;
static u8 QUE_Flag  = 0 ;


Que_S_t inQueue_ADC(u16 data){

	if (IsFull()== FULL_QUE){
		return FULL_QUE ;
		}else {
				if (Pointer_Head ==SIZE_MAX_ADC_Queue-1 )QUE_Flag = 1 ; 
		QueueAdc[Pointer_Head] = data ;
// 		LCD_SetCursor(1,10);
// 		LCD_WriteNumber(Pointer_Head);
// 		LCD_SetCursor(1,12);
// 		LCD_WriteNumber(Pointer_tail);
// 		LCD_SetCursor(1,14);
// 		LCD_WriteNumber(QUE_Flag);
		Pointer_Head++ ;
		Pointer_Head= Pointer_Head%SIZE_MAX_ADC_Queue ;
	}
		return FINE_QUE ; 
}
Que_S_t DeQueue_ADC(u16* data ){
	
	
	if (IsEmpty()== EMPTY_QUE){
		return EMPTY_QUE ; 
		}else {
			if (Pointer_tail ==SIZE_MAX_ADC_Queue-1 )QUE_Flag =0 ; 
// 		LCD_SetCursor(1,10);
// 		LCD_WriteNumber(Pointer_Head);
// 		LCD_SetCursor(1,12);
// 		LCD_WriteNumber(Pointer_tail);
// 		LCD_SetCursor(1,14);
// 		LCD_WriteNumber(QueueAdc[Pointer_tail]);
		*data  = QueueAdc[Pointer_tail] ;
		Pointer_tail++ ;
		Pointer_tail= Pointer_tail%SIZE_MAX_ADC_Queue ;
	}
	return FINE_QUE ; 
}
Que_S_t IsEmpty(void){
		if(Pointer_tail == Pointer_Head&&QUE_Flag==0) return EMPTY_QUE ;
		return FINE_QUE ;
}
Que_S_t IsFull(void){
	if((Pointer_tail == Pointer_Head ) && QUE_Flag==1 ) return FULL_QUE ; 
	  return FINE_QUE ; 
}