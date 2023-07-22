#include "StdTypes.h"
#include "DIO_Interface.h"
#include "ultra.h"
#define F_CPU 800000
#include "util/delay.h"
#include "Ultra_Array.h"
//#include "LCD_Interface.h"
static u8  counter  = 0 ;
static ultr_type data_ultra[ARRAY_NUM] =
{ //  pin   dis
	{PINC7 , 0},
	{PINC6 , 0},
	{PIND0 , 0},
	{PINC5 , 0}
};
// static u16 Distances [ARRAY_NUM] ;
static u16 Temp_Distances [ARRAY_NUM] ;
void Ultra_Array_Init (void) {
	// do nothing
}
void Ultra_Array_Rannable (void) {
	ultr_Start (data_ultra[counter]) ;
	if (ultr_GetRead_Noblock(&data_ultra[counter])){
		// data_ultra[counter].d ;
		counter ++ ;
// 		LCD_SetCursor(0,10) ; 
// 		LCD_WriteNumber(counter);
		}else {
	}
	

	
	if (counter==ARRAY_NUM){
		for (int i =0 ; i < ARRAY_NUM ; i ++ ){
			Temp_Distances[i]=data_ultra[i].d ;
// 			LCD_SetCursor(0,10) ;
// 			LCD_WriteString("update");
// 			_delay_ms(1000) ; 
		}
// 		LCD_SetCursor(0,10) ;
// 		LCD_WriteString("          ");
		counter = 0 ;
	}
}
u16 Ultra_Array_Getter (u8 Ultrasonic_Num)
{
	return Temp_Distances[Ultrasonic_Num];
}