#include "StdTypes.h"

#include "DIO_Interface.h"
#include "Button_Interface.h"
#include "SEVEN_SEG.h"
#include  "LCD_Interface.h"

#define F_CPU 8000000
#include <util/delay.h>

#include "StopWatch_Cfg.h"
#include "Stopwatch_Interface.h"

static u8 FStart = START_BOS ;
static u8 Start = START_BOS ;

stopWatch_Mode_Type mode = MODE_1 ;
u8 B1_Flage = 0 ;
u8 B2_Flage = 0 ;

void StopWatch_Init(){
	// do noting

}

void StopWatch_Rannable(){
	for (int i = 0 ; i < 500 ; i++ ){
		if (BUTTON_Status(B_1)==PRESSED){
			_delay_ms(5);
			while(BUTTON_Status(B_1)==PRESSED){
				
				if (mode==MODE_1){
					segment_display_KIT(Start);
					_delay_ms(1);
				}
				else if (mode==MODE_2){
					segment_display_KIT(FStart);
					FStart -- ;
					if (FStart==0)FStart = 99;
					for(int i = 0 ; i < 100; i++){
						segment_display_KIT(FStart);
						_delay_ms(1) ;
					}
				}
			}
			_delay_ms(5);
			if (mode==MODE_1){
				B1_Flage = !B1_Flage ;
			}
		}
		else if (BUTTON_Status(B_2)==PRESSED){
			_delay_ms(5);
			while(BUTTON_Status(B_2)==PRESSED){
				if (mode==MODE_1){
					segment_display_KIT(Start);
					_delay_ms(1);
				}
				else if (mode==MODE_2){
					segment_display_KIT(FStart);
					
					FStart -- ;
					FStart =FStart%99 ;
					for(int i = 0 ; i < 100 ;i++){
						segment_display_KIT(FStart);
						_delay_ms(1) ;
					}
				}
			}
			_delay_ms(1);
			if (mode==MODE_1){
				B2_Flage = 1 ;
			}
		}
		
		if (BUTTON_Status(B_3)==PRESSED){
			_delay_ms(5);
			while(BUTTON_Status(B_3)==PRESSED){
				switch(mode){
					case MODE_1 :
					segment_display_KIT(Start);
					break;
					case MODE_2 :
					segment_display_KIT(FStart);
					break;
					case MODE_3 :
					segment_display_KIT(FStart);
					break;
				}
				_delay_ms(1);
			}
			_delay_ms(5);
			mode++ ;
			mode=mode % (MODE_t) ;
			B1_Flage = 0 ;
			B2_Flage = 0 ;
		}
		switch(mode){
			case MODE_1 :
			segment_display_KIT(Start);
			break;
			case MODE_2 :
			segment_display_KIT(FStart);
			break;
			case MODE_3 :
			segment_display_KIT(FStart);
			break;
		}
		_delay_ms(1);
	}
	switch (mode){
		case MODE_1 :
		if (Start > FStart) Start  =FStart ;
		if (B1_Flage == 1 ){
			Start -- ;
		}
		if (B2_Flage == 1 ){
			B2_Flage = 0 ;
			Start = FStart ;
		}
		
		DIO_WritePort( PB,LED_MODE1 );
		if (Start == 0 ){
			DIO_WritePin( Buzzer , HIGH );
			DIO_WritePort(PB , 0xff);
			DIO_WritePin( Buzzer , HIGH );
			DIO_WritePort(PB , 0xff);
			for(int i = 0 ; i < 1000 ; i++){
				segment_display_KIT(0);
				_delay_ms(1) ;
			}
			DIO_WritePin( Buzzer , LOW );
			DIO_WritePort(PB , 0x00);
			for(int i = 0 ; i < 1000 ; i++){
				segment_display_KIT(0);
				_delay_ms(1) ;
			}
			DIO_WritePin( Buzzer , HIGH );
			DIO_WritePort(PB , 0xff);
			for(int i = 0 ; i < 1000 ; i++){
				segment_display_KIT(0);
				_delay_ms(1) ;
			}
			DIO_WritePin( Buzzer , LOW );
			DIO_WritePort(PB , 0x00);
			Start = FStart ;
			B1_Flage = 0 ;
			B2_Flage = 0 ;
		}
		break;

		case MODE_2 :
		DIO_WritePort( PB,LED_MODE2 );
		break;
		
		case MODE_3 :
		DIO_WritePort( PB,LED_MODE3 );
		break;
	}
}
void StopWatch_Rannable_Seg(){


	for (int i = 0 ; i < 500 ; i++ ){
		if (BUTTON_Status(B_1)==PRESSED){
			
			_delay_ms(10);
			while(BUTTON_Status(B_1)==PRESSED){
				if (mode ==MODE_2){
					FStart++ ;
					FStart=FStart%99 ;
					LCD_SetCursor(1,7) ;
					LCD_WriteNumber(FStart);
					_delay_ms(200);
				}
			}
			_delay_ms(10);
			if (mode==MODE_1)
			B1_Flage= !B1_Flage ;
			
		}
		else if (BUTTON_Status(B_2)==PRESSED){
			B2_Flage = 1 ;
			_delay_ms(10);
			while(BUTTON_Status(B_2)==PRESSED){
				if (mode ==MODE_2){
					FStart-- ;
					if (FStart==0)FStart=99;
					LCD_SetCursor(1,7) ;
					LCD_WriteNumber(FStart);
					_delay_ms(100);
				}
			}
			_delay_ms(10);
		}
		if (BUTTON_Status(B_3)==PRESSED){
			B2_Flage = 0 ;
			B1_Flage = 0 ;
			_delay_ms(10);
			while(BUTTON_Status(B_3)==PRESSED);
			_delay_ms(10);
			mode ++ ;
			mode = mode % MODE_t;
			
		}
		_delay_ms(1);
	}
	
	switch (mode){
		case MODE_1 :
		LCD_Clear() ;
		LCD_SetCursor(0,5) ;
		LCD_WriteString("MODE_1") ;
		LCD_SetCursor(1,0) ;
		LCD_WriteString("Time") ;
		LCD_SetCursor(1,5) ;
		LCD_WriteString("      ");
		if (B2_Flage==1){
			B2_Flage=0 ;
			Start = FStart ;
		}
		if (B1_Flage==0){
			if (Start!=0){
				Start-- ;
			}
			if (Start==0){
				for (int i = 0 ; i <10  ; i ++ ){
					LCD_SetCursor(1,10) ;
					LCD_WriteString(" Fire ");
					_delay_ms(100) ;
					DIO_WritePin(Buzzer,HIGH) ;
					DIO_WritePort(PB , 0xff);
					LCD_SetCursor(1,10) ;
					LCD_WriteString("      ");
					DIO_WritePin(Buzzer,LOW) ;
					DIO_WritePort(PB , 0x00);
					_delay_ms(100) ;
				}
				B1_Flage = 1 ;
				Start = FStart ;
			}
			
		}
		LCD_SetCursor(1,5) ;
		LCD_WriteNumber(Start);
		
		break;
		
		case MODE_2 :
		LCD_Clear() ;
		LCD_SetCursor(0,5) ;
		LCD_WriteString("MODE_2") ;
		LCD_SetCursor(1,0) ;
		LCD_WriteString("S_Time") ;
		LCD_SetCursor(1,7) ;
		LCD_WriteString("  ");
		LCD_SetCursor(1,7) ;
		LCD_WriteNumber(FStart);
		break;
		
		case MODE_3 :
		LCD_Clear() ;
		LCD_SetCursor(0,5) ;
		LCD_WriteString("MODE_3") ;
		LCD_SetCursor(1,0) ;
		LCD_WriteString("Time") ;
		LCD_SetCursor(1,5) ;
		LCD_WriteString("      ");
		LCD_SetCursor(1,5) ;
		LCD_WriteNumber(Start);
		break;
	}
}

