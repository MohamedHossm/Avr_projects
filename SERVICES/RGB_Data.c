#include "StdTypes.h"
#include "UART.h"
#include "RGB_Data.h"
//****************************
#include "LCD_Interface.h"
/************************************/
volatile static u8 index = 0 ;
volatile static u8 RC_flag = 0 ;
volatile static u8 Data_access = 1 ;
volatile static u8 RGB_puffer1 [BUFFER_SIZE] ;
volatile static u8 RGB_puffer2 [BUFFER_SIZE] ;

RGB_data_type leds [85] ;
// {
// 	{255, 6, 0},
// 	{255, 28, 0},
// 	{255, 0, 49},
// 	{255, 0, 77},
// 	{255, 62, 0},
// 	{0, 255, 21},
// 	{0, 84, 255},
// 	{255, 0, 99},
// 	{0, 201, 110},
// 	{0, 201, 110},
// 	{0, 95, 255},
// 	{255, 85, 0},
// 	{255, 0, 119},
// 	{0, 106, 255},
// 	{18, 92, 255},
// 	{18, 92, 255},
// 	{24, 255, 46},
// 	{255, 0, 138},
// 	{255, 105, 0},
// 	{0, 127, 255},
// 	{255, 0, 156},
// 	{65, 82, 255},
// 	{0, 138, 255},
// 	{0, 255, 102},
// 	{255, 125, 0},
// 	{34, 131, 232},
// 	{234, 103, 58},
// 	{2, 146, 255},
// 	{255, 0, 176},
// 	{69, 255, 44},
// 	{90, 81, 255},
// 	{0, 161, 255},
// 	{0, 255, 136},
// 	{54, 138, 233},
// 	{110, 80, 255},
// 	{0, 173, 255},
// 	{255, 155, 5},
// 	{255, 11, 196},
// 	{127, 78, 255},
// 	{0, 186, 255},
// 	{0, 255, 164},
// 	{113, 255, 43},
// 	{255, 168, 10},
// 	{142, 77, 255},
// 	{0, 200, 255},
// 	{0, 255, 188},
// 	{157, 76, 255},
// 	{255, 180, 15},
// 	{255, 139, 71},
// 	{142, 255, 42},
// 	{170, 74, 255},
// 	{255, 35, 219},
// 	{255, 192, 19},
// 	{0, 255, 212},
// 	{165, 255, 42},
// 	{197, 70, 255},
// 	{235, 168, 86},
// 	{0, 234, 255},
// 	{255, 221, 0},
// 	{139, 123, 255},
// 	{255, 205, 23},
// 	{209, 68, 255},
// 	{0, 255, 234},
// 	{185, 255, 41},
// 	{255, 51, 244},
// 	{255, 218, 27},
// 	{0, 254, 255},
// 	{237, 62, 255},
// 	{203, 255, 40},
// 	{238, 242, 32},
// 	{255, 231, 30},
// 	{219, 255, 39},
// 	{235, 255, 38},
// 	{255, 244, 34},
// 	{114, 195, 255},
// 	{251, 255, 37},
// 	{250, 213, 185},
// 	{255, 255, 255}
// };
void RGB_DATA_Init (){
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(RGB_DATA_ISR_fun);
	
}
void RGB_DATA_Rannable(){
	/******************************************/
	LCD_SetCursor(0 ,15);
	LCD_WriteNumber(index);
	LCD_SetCursor(1 ,15);
	LCD_WriteNumber(Data_access);
	// 	LCD_WriteString(" ");
	/*******************************************/
	if (RC_flag){
		
		//asume that data is correct
		if (Data_access==0){
			leds[RGB_puffer1[0]].Red =   RGB_puffer1[1];
			leds[RGB_puffer1[0]].Green = RGB_puffer1[2];
			leds[RGB_puffer1[0]].blue =  RGB_puffer1[3];
			leds[RGB_puffer1[0]].intinsty =  RGB_puffer1[4];
			RC_flag = 0 ;
		}
		if (Data_access==1){
			leds[RGB_puffer2[0]].Red =   RGB_puffer2[1];
			leds[RGB_puffer2[0]].Green = RGB_puffer2[2];
			leds[RGB_puffer2[0]].blue =  RGB_puffer2[3];
			leds[RGB_puffer2[0]].intinsty =  RGB_puffer2[4];
			RC_flag = 0 ;
		}
		}else {
		
		//do noting
	}
}
u8 RGB_DATA_Getter(u8 led_ID , RGB_data_type * data){
	if (led_ID>=0 &&led_ID<=LEDS_NUM){
		*data = leds[led_ID] ;
		return 1 ;
	}
	else {
		return 0 ;
	}
	
}
void RGB_DATA_ISR_fun(){
	if (Data_access){
		RGB_puffer1[index]=UART_ReceiveNoBlock() ;
		index++ ;
		}else {
		RGB_puffer2[index]=UART_ReceiveNoBlock() ;
		index++ ;
	}
	
	if (index==BUFFER_SIZE){
		index = 0 ;
		RC_flag = 1 ;
		Data_access=!Data_access ;
	}
	
}
