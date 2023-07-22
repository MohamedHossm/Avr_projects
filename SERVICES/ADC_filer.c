#include "StdTypes.h"
#include "ADC_Interface.h"
#include "LCD_Interface.h"
#include "ADC_filter.h"

static u32 filterData  =  0 ;
static u16 QueueAdc[SIZE_MAX_ADC_Queue_filer] = {0};
static u8 Pointer_Head  = 0 ;
static u8 Pointer_tail  = 0 ;
static u8 QUE_Flag  = 0 ;


Que_S_t inQueue_ADC_Filter(u16 data){
	
	if (IsFull_Filter()== FULL_QUE){
	
		return FULL_QUE ;
		}else {
			if (Pointer_Head ==(SIZE_MAX_ADC_Queue_filer-1 ))QUE_Flag = 1 ;	
		QueueAdc[Pointer_Head] = data ;
		Pointer_Head++ ;
		Pointer_Head= Pointer_Head%SIZE_MAX_ADC_Queue_filer ;
	}
	return FINE_QUE ;
}
Que_S_t DeQueue_ADC_Filter(u16* data ){
	
	
	if (IsEmpty_Filter()== EMPTY_QUE){

		return EMPTY_QUE ;
		}else {
		if (Pointer_tail ==(SIZE_MAX_ADC_Queue_filer-1) )QUE_Flag =0 ;
		*data  = QueueAdc[Pointer_tail] ;
		Pointer_tail++ ;
		Pointer_tail= Pointer_tail%SIZE_MAX_ADC_Queue_filer ;
	}
	
	return FINE_QUE ;
}
Que_S_t IsEmpty_Filter(void){
	if((Pointer_tail == Pointer_Head)&&QUE_Flag==0) return EMPTY_QUE ;
	return FINE_QUE ;
}
Que_S_t IsFull_Filter(void){
	if((Pointer_tail == Pointer_Head ) && QUE_Flag==1 ) return FULL_QUE ;
	return FINE_QUE ;
}

void ADC_filter_init (){
	u16 data = 0 ;
	for (u8 i = 0 ; i < SIZE_MAX_ADC_Queue_filer ; i++)
	{
		data = ADC_Read(FILTER_CH) ;
		filterData = filterData + data ;
		inQueue_ADC_Filter(data);
	}
	//filterData = filterData/SIZE_MAX_ADC_Queue ;
}
void ADC_Call_Filter (){
	u16 data = 0 ;
	u16 data2 = 0 ;
	data =ADC_Read(FILTER_CH) ;
	DeQueue_ADC_Filter(&data2) ;
	// 	LCD_SetCursor(1,7);
	// 	LCD_WriteNumber(data2) ;
	// 	LCD_SetCursor(1,10);
	// 	LCD_WriteNumber(data) ;
	filterData = filterData - data2 ;
	filterData =filterData+data ;
	inQueue_ADC_Filter(data);
}
u16 ADC_Getter_Filter(){
	return filterData/SIZE_MAX_ADC_Queue_filer ;
}
void printQUE(){
	LCD_SetCursor(0 ,0 ) ;
	for (u8 i = 0 ; i < SIZE_MAX_ADC_Queue_filer ; i++)
	{
		LCD_WriteNumber(QueueAdc[i]) ;
		LCD_WriteString(" ");
	}
}