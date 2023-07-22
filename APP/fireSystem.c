#include "StdTypes.h"
#include "Utils.h"
#define F_CPU 1000000
#include <util/delay.h>
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "keybad_interface.h"
#include "ADC_Interface.h"
#include "tempSensor.h"
#include "FireSystem_Cfg.h"
#include "fireSystem_Private.h"
#include "fireSystem_Interface.h"




static Password_S_t pass_state = PASS_W8;
static u8 Password[PASSLEN] = {"12345"} ;
static temp_S_t TempState = TEMP_FINE ;
static u16 temp_read = 0 ;
static temp_S_t unreverseFLAG = TEMP_FINE ;

void fireSystem_Init(void){
	//do nothing
}
void fireSystem_Runnable(void) {

	/*
	while(pass_state==PASS_W8){
	PasswordCheck();
	}
	*/
	
	Temp_SensorState();
	Smoke_state();
	Print_Status_led();
	if (TempState==TEMP_NOT_FINE_Smoke){
		PasswordCheck();
		if (pass_state == PASS_OK){
			pass_state = PASS_W8;
			TempState = TEMP_FINE ;
			unreverseFLAG = TEMP_FINE ;
			LCD_SetCursor(1,0);
			LCD_WriteString("                            ") ;
			}else if(pass_state == PASS_NOT_OK)  {
			pass_state = PASS_W8;
			LCD_SetCursor(1,0);
			LCD_WriteString("                 ") ;
			LCD_SetCursor(1,0);
			LCD_WriteString(" Wrong") ;
		}
	}

}









void Print_Status_led(){
	if (TempState == TEMP_FINE){
		LCD_SetCursor(0,0);
		LCD_WriteString("T :");
		LCD_WriteNumber(temp_read) ;
		LCD_WriteString("C");
		LCD_SetCursor(0,6);
		LCD_WriteString(" FINE");
		LCD_SetCursor(0,13) ;
		LCD_WriteString("   ");

		}else if (TempState == TEMP_NOT_FINE){
		LCD_SetCursor(0,0);
		LCD_WriteString("T :");
		LCD_WriteNumber(temp_read) ;
		LCD_WriteString("C");
		LCD_SetCursor(0,6);
		LCD_WriteString(" HEAT");
	
		
	}
	else if (TempState == TEMP_NOT_FINE_Smoke){
		LCD_SetCursor(0,0);
		LCD_WriteString("T :");
		LCD_WriteNumber(temp_read) ;
		LCD_WriteString("C ");
		LCD_SetCursor(0,6);
		LCD_WriteString(" FIRE");
		LCD_WriteString("   ");
		
	}
	LED_state();
}
void Smoke_state(){
	if(TempState==TEMP_FINE) return ;
	u16 ReadSmoke = tempSensor_Read2();
	ReadSmoke= ReadSmoke / 10 ;
	LCD_SetCursor(0,13) ;
	LCD_WriteNumber(ReadSmoke);
	LCD_WriteString(" ");
	if (ReadSmoke >= HESTESS_TOP){
		TempState = TEMP_NOT_FINE_Smoke ;
		unreverseFLAG = TEMP_NOT_FINE_Smoke;
	}

}
void LED_state(){
	switch(TempState){
		case TEMP_FINE :
		DIO_WritePin(GREEN_LED ,HIGH);
		DIO_WritePin(RED_LED ,LOW);
		DIO_WritePin(YELLOW_LED ,LOW);
		DIO_WritePin(FAN,LOW);
		break;
		case TEMP_NOT_FINE :
		DIO_WritePin(GREEN_LED ,LOW);
		DIO_WritePin(RED_LED ,LOW);
		DIO_WritePin(YELLOW_LED ,HIGH);
		DIO_WritePin(FAN,LOW);
		break;
		case TEMP_NOT_FINE_Smoke :
		DIO_WritePin(GREEN_LED ,LOW);
		DIO_WritePin(RED_LED ,HIGH);
		DIO_WritePin(YELLOW_LED ,LOW);
		DIO_WritePin(FAN,HIGH);
		break;
	}

}
static void PasswordCheck (){
	static u8 temp_Password[PASSLEN] = {0} ;
	static u8 pos = 0 ;
	u8  key =NO_KEY_PRESSED ;
	//LCD_Clear() ;

	key = 	KEY_Read_ch() ;
	if (key !=NO_KEY_PRESSED){
		if (key=='c'){
			pos  = 0 ;
			LCD_Clear();
			
		}
		else if (key=='='){
			//LCD_WriteString((char*)temp_Password) ;
			if (CompareTowPasswords(Password , temp_Password)==TRUE) {
				
				pos  = 0 ;
				pass_state =  PASS_OK ;
				}else {
				
				pos  = 0 ;
				pass_state = PASS_NOT_OK ;
			}
		}
		else {
			//LCD_WriteChar(key) ;
			//_delay_ms(50);
			temp_Password[pos++] = key ;
			temp_Password[pos] = 0 ;
			LCD_SetCursor(1,0);
			LCD_WriteString("                             ");
			LCD_SetCursor(1,0);
			for (u8 g = 0 ; g < pos ; g++ ){
				LCD_WriteChar('*');
			}
			//LCD_WriteString((char*)temp_Password);
		}
		//LCD_Clear() ;
	}

}

static Bool_t CompareTowPasswords (u8  * data1 , u8 *data2){
	for (u8 x = 0 ; data1[x]||data2[x] ; x++){
		if (data1[x]!=data2[x]){
			return FALSE ;
		}
	}
	return TRUE ;
}

void Temp_SensorState (){
	temp_read = tempSensor_Read() ;
	if (unreverseFLAG == TEMP_NOT_FINE_Smoke) return ;
	if (temp_read >= HESTESS_TOP){
		TempState = TEMP_NOT_FINE ;
		}else if (temp_read >= HESTESS_BOT){
		
		}else {
		TempState = TEMP_FINE ;
	}
}