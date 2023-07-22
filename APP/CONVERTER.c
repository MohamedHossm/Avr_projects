#include "StdTypes.h"
#include <string.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "LCD_Interface.h"
#include "CONVERTER_Interface.h"
#include "CONVERTER_Pivate.h"
#include "keybad_interface.h"
int lastnum = 55 ;

void (*	gets[3])(void) =
{Get_D ,Get_B,Get_H };


void (*sets[3])(void) =
{Set_D,Set_B,Set_H };



void CONVEER_Init (void){
	LCD_SetCursor(0,3) ;
	LCD_WriteString("Calculator ");
	LCD_SetCursor(1,3) ;
	LCD_WriteString("  M.Hosam ");
	_delay_ms(500) ;
}

void CONVEER_Rannable (void){
	if (moves <2){
		Chose_Convert() ;
	    lastnum =55 ;
		}else {
		//	LCD_Clear();
		gets[from]();
		if (lastnum!=num){
			sets[TO]();
		}
		lastnum = num ; 
	}

}



void Reset_Valls(){

	from = DES ;
	TO = DES ;
	num = 0 ;
	binary_pos = 0 ;
	hex_pos = 0 ;
	key = 0 ;
	flag = 0  ;
	moves = 0 ;
	
}

void Get_B(){
	LCD_SetCursor(0,0) ;
	LCD_WriteString("BIN :");
	key = KEY_Read_ch();
	if (key!=NO_KEY_PRESSED){
		if (key =='c'&&binary_pos==0){
			Reset_Valls();
		}
		if (key =='c'){
			binary_pos = 0 ;
			for (int i = 0 ; i < 8 ; i++ ){
				bin_str[i] = ' ' ;
			}
			
		}
		if (key >='0'&& key <='1'){
			bin_str[7-(binary_pos++)]=key ;
			if (binary_pos==9){
				binary_pos = 0 ;
				for (int i = 0 ; i < 8 ; i++ ){
					bin_str[i] = ' ' ;
				}
			}
		}
	}
	LCD_WriteString(bin_str);
	num = Convert_B_D((u8*)bin_str);
}

void Get_H(){
	LCD_SetCursor(0,0) ;
	LCD_WriteString("HEX :0x");
	key = KEY_Read_ch();
	if (key!=NO_KEY_PRESSED){
		if (key =='c'&&hex_pos==0){
			Reset_Valls();
		}
		if (key =='c'){
			hex_pos = 0 ;
			hex_str[0]= ' ' ;
			hex_str[1]= ' ' ;
		}
		if (key >='0'&& key <='9'){
			if (hex_pos==2){
				hex_pos = 0 ;
				hex_str[0]= ' ' ;
				hex_str[1]= ' ' ;
			}
			hex_str[1-(hex_pos++)]=key ;
		}
		else if (key =='/'){
			if (hex_pos==2){
				hex_pos = 0 ;
				hex_str[0]= ' ' ;
				hex_str[1]= ' ' ;
			}
			hex_str[1-(hex_pos++)]='C' ;
		}
		else if (key =='*'){
			if (hex_pos==2){
				hex_pos = 0 ;
				hex_str[0]= ' ' ;
				hex_str[1]= ' ' ;
			}
			hex_str[1-(hex_pos++)]='D' ;
		}
		else if (key =='-'){
			if (hex_pos==2){
				hex_pos = 0 ;
				hex_str[0]= ' ' ;
				hex_str[1]= ' ' ;
			}
			hex_str[1-(hex_pos++)]='E' ;
		}
		else if (key =='+'){
			if (hex_pos==2){
				hex_pos = 0 ;
				hex_str[0]= ' ' ;
				hex_str[1]= ' ' ;
			}
			hex_str[1-(hex_pos++)]='F' ;
		}
		
	}
	LCD_WriteString((char*)hex_str);
	num = Convert_H_D((u8*)hex_str);
	
}

void Get_D (){
	LCD_SetCursor(0,0) ;
	LCD_WriteString("Des :");
	key = KEY_Read_ch();
	if (key!=NO_KEY_PRESSED){
		if (key =='c'&&num==0){
			Reset_Valls();
		}
		if (key =='c'){
			num = 0 ;
		}
		if (key >='0'&& key <='9'){
			num = num * 10 +(key -'0') ;
			if (num>1000)num = 0 ;
			
		}
		LCD_SetCursor(0,0) ;
		LCD_WriteString("Des :");
		LCD_WriteNumber(num);
		LCD_WriteString("             ");
	}
}

void Set_H(){
	LCD_SetCursor(1,0);
	LCD_WriteString("HEX :");

	LCD_SetCursor(1,5);
	LCD_WriteString("                             " );
	LCD_SetCursor(1,5);
	LCD_WriteHex(num);
}

void Set_B(){
	LCD_SetCursor(1,0);
	LCD_WriteString("BIN :");

	LCD_SetCursor(1,5);
	LCD_WriteString("                             " );
	LCD_SetCursor(1,5);
	LCD_WriteBinary(num);
}

void Set_D(){
	LCD_SetCursor(1,0);
	LCD_WriteString("Des :");
	
	LCD_SetCursor(1,5);
	LCD_WriteString("                             " );
	LCD_SetCursor(1,5);
	LCD_WriteNumber(num);
	
}




static void Chose_Convert(){
	
	key = KEY_Read_ch();
	if (key!=NO_KEY_PRESSED){
		if (key >='1' && key <='3'){
			if (flag ==1 ){
				LCD_SetCursor(0,0);
				LCD_WriteString("                       ");
				flag = 2 ;
			}
			
			LCD_SetCursor(0,0);
			if (moves== 0 ){
				LCD_WriteString("F: ");
				from = key-'1' ;
				LCD_WriteString((char*)strings[from]);
				moves++ ;
				
			}
			
			else if (moves==1 ){
				LCD_SetCursor(0,7);
				LCD_WriteString("T: ");
				TO = key-'1'  ;
				LCD_WriteString((char*)strings[TO]);
				moves++ ;
				_delay_ms(500);
				LCD_Clear();
			}
		}
	}
	if (flag == 0 ){
		LCD_Clear() ;
		LCD_SetCursor(0,2) ;
		LCD_WriteString(" Choose ");
		LCD_SetCursor(1,0) ;
		LCD_WriteString("1-DS 2-BN 3-HX");
		
		flag = 1 ;
	}
	

}

static u8 Convert_B_D(u8 * data ){
	u8 Ssize = strlen((char*)data)-1 ;
	u8 i = 0 ;
	u8 R_data = 0;
	u8 size  =(sizeof(R_data)*8)  ;
	for (i = 0 ; i < size && data[i] ; i++ ){
		if (data[i] >='0'&&data[i] <='1')
		R_data =R_data + ((data[i]-'0') * (1<<(Ssize -i))) ;
	}
	return R_data ;
}



// static void Convert_get_B (u8 key , u8 *str , u8 pos){
// 	if (pos > 8) return ;
// 	if (pos == 0) {for (int i = 0 ; i < 8 ; i++ )str[i] = 0 ;} ;
// 	str[pos] = key ;
// };

static u8 Convert_H_D(u8 * data ){
	u8 High = 0 ;
	u8 Low = 0  ;
	u8 R_data = 0 ;
	if (data[0]>='A' && data[0]<='F'){
		High = ((data[0] - 'A')+ 10)<<4 ;
		}else if (data[0]>='0' && data[0]<='9'){
		High =  (data[0]-'0')<<4 ;
	}
	if (data[1]>='A' && data[1]<='F'){
		Low = (data[1] - 'A')+ 10 ;
		
		} else if (data[1]>='0' && data[1]<='9'){
		Low = data[1]-'0' ;
	}
	R_data = High|Low ;


	return R_data ;
}