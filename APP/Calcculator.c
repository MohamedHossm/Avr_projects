#include "StdTypes.h"
#include "keybad_interface.h"
#include "LCD_Interface.h"
#include "Calculator_Interface.h"
#define F_CPU 8000000
#include <util/delay.h>
/*
u8 N_1_S ;
u8 N_2_S ;
u8 OP ;
s64 num_1 ;
s64 num_2 ;
*/
calculater_Frame_type data ={0,0,' ',0,0,0};
u8 EQ_Flage = 0 ;
u8 last_op = ' ' ;


s32 (*fun[4])(s32  , s32 )= {
	Sum ,Sub, MuL , Div
} ;

void Calculator_Init(void){
	//do noting
	LCD_SetCursor(0,0) ;
	LCD_WriteString("    Calculator  ")  ;
	_delay_ms(500) ;
	LCD_SetCursor(1,0) ;
	LCD_WriteString("     Welcome  ")  ;
	_delay_ms(500) ;
	LCD_Clear();
}

void Calculator_Rannable(void){
	u8 key  ;
	key = KEY_Read_ch() ;
	if (key!=NO_KEY_PRESSED){
		if (key =='-' && last_op==data.OP && data.N_1_S==0 &&data.num_1==0){
			data.N_1_S=1 ;
			
		}
		else if (key >='0' &&key <='9'&&data.OP==' '){
			
			LCD_Clear();
			if (EQ_Flage > 0){
				data.num_1 = 0 ;
				
				//data.num_2 = 0 ;
				last_op = ' ';
				EQ_Flage= 0;
			}
			
			data.num_1 = data.num_1*10 +key -'0';
		}
		else if (key >='0' &&key <='9'&&data.N_2_S==0){
			
			data.num_2 = data.num_2*10 +(key -'0');
			}else if (key >='0' &&key <='9'&&data.N_2_S==1){
			
			data.num_2 = data.num_2*10 -(key -'0');
		}
		else if (key =='+' || key =='-'||key =='*'||key =='/'){
			if (data.OP==' '){
				LCD_SetCursor(1,0) ;
				LCD_Clear();
				if (data.OP!=last_op )
				data.num_1 = data.res;
				data.num_2 = 0 ;
				data.OP =key ;
				EQ_Flage= 0 ;
				
				}else if (data.OP=='*'||data.OP=='/'){
				if (key=='-'){
					data.N_2_S = 1 ;
					//data.num_2 = 0 ;
					
					EQ_Flage= 0 ;
				}
				}else if ((data.OP!='*'||data.OP!='/')){
				data.OP =key ;
				EQ_Flage= 0 ;
			}
			
			
		}
		else if (key =='='){
			LCD_SetCursor(1,0) ;
			if (data.N_1_S==1){
				
				data.num_1 = -1 *data.num_1 ;
				data.N_1_S= 0;
			}
			//if (data.OP!=' ')
			if (EQ_Flage >= 1 ){
				reset_Cal();
			}
			data.res =  fun [handel_fun(data.OP)](data.num_1 , data.num_2 ) ;
			//if (data.OP!=data.OP)
			data.num_2  = 0 ;
			data.N_2_S= 0;
			LCD_WriteNumber(data.res) ;
			last_op=data.OP;
			data.OP = ' ';
			EQ_Flage ++ ;
		}
		
		
		else if (key =='c'){
			reset_Cal();
		}
		print_Calcaulator();
	}
	
}



void reset_Cal(){
	data.num_1 = 0 ;
	data.num_2 = 0 ;
	data.N_1_S =0;
	data.N_2_S =0;
	data.res = 0 ;
	data.OP = ' ';
	last_op= ' ';
	LCD_Clear();
}

void print_Calcaulator(void){

	if (data.OP==' '){
		if (data.N_1_S == 1 ){
			LCD_SetCursor(0,0) ;
			LCD_WriteChar('-');
			LCD_WriteNumber(data.num_1) ;
			//data.num_1 = -1*data.num_1;
			}else{
			LCD_SetCursor(0,0) ;
			LCD_WriteNumber(data.num_1) ;
		}
		
	}
	else if (data.num_2==0) {
		
		LCD_SetCursor(0,0) ;
		if (data.N_1_S == 1 ){
			LCD_WriteChar('-') ;
		}
		LCD_WriteNumber(data.num_1) ;
		LCD_WriteChar(data.OP) ;
		if (data.N_2_S == 1 ){
			LCD_WriteChar('-') ;
		}
		
	}
	else if (data.num_2!=0) {
		if (data.N_1_S == 1 ){
			data.num_1 = -1 * data.num_1  ;
			data.N_1_S = 0 ;
		}
		LCD_SetCursor(0,0) ;
		LCD_WriteNumber(data.num_1) ;
		LCD_WriteChar(data.OP) ;
		//if (data.N_2_S == 1){
		//	data.num_2 = -1 * data.num_2  ;
		//	data.N_2_S = 0 ;
		//}
		LCD_WriteNumber(data.num_2) ;

		}else{
		if (data.N_1_S == 1 ){
			data.num_1 = -1 * data.num_1  ;
			data.N_1_S = 0 ;
		}
		LCD_SetCursor(0,0) ;
		LCD_WriteNumber(data.num_1) ;
		LCD_WriteChar(data.OP) ;
		
	}
	
}

u8 handel_fun(u8 data_in){
	switch(data_in){
		case '+' :
		return 0;
		//break;
		case '-':
		return 1;
		//break;
		case '*' :
		return 2;
		//break;
		case '/' :
		return 3;
		//break;
		default:

		return 0 ;
	}


}

s32 Sum(s32 data1 , s32 data2 ){

	return data1 +data2 ;
}
s32 MuL(s32 data1 , s32 data2 ){

	return data1 *data2 ;
}
s32 Div(s32 data1 , s32 data2 ){

	return data1  / data2 ;
}
s32 Sub(s32 data1 , s32 data2 ){

	return data1 - data2 ;
}