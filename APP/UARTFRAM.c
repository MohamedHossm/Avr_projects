#include "StdTypes.h"
#define F_CPU 8000000
#include "util\delay.h"
#include "keybad_interface.h"
#include "LCD_Interface.h"
#include "UARTFRAM.h"
static u16 data = 0;
static u8 flag = 0;
static u8 size  = 0;
static u8 Parity = 0;
static u16 FrameData  = 0;
static u8 Stop = 0;
void UartframeRunnable (){
	if (flag==0){
		//LCD_Clear();
		//LCD_SetCursor(0 ,0 ) ;
		//	LCD_WriteString("                            ");
				LCD_SetCursor(0 ,0 ) ;
		LCD_WriteString("data size  :     ");
		}else if (flag==1){
	
		LCD_SetCursor(0 ,0 ) ;
		LCD_WriteString("PR NO:0 O:1 E:2");
	}
	else if (flag==2){
		
		LCD_SetCursor(0 ,0 ) ;
		LCD_WriteString("Stop ONE:1 TWO:2        ");
		}else if(flag==3)  {
		//LCD_Clear();
		LCD_SetCursor(0 ,0 ) ;
		LCD_WriteString("data                    ");
	}
	
	u8 key= KEY_Read_ch() ;
	if (key!=NO_KEY_PRESSED){
		LCD_SetCursor(0 , 0 ) ;
		LCD_WriteChar(key) ;
		if (key!='='){
			
			data=(data*10)+(key-'0');
			}else{
			
			if (flag==0){
				size = data ;
			}
			else if (flag==1){
				Parity = data ;
			}
			else if (flag==2){
				Stop = data ;
				if (Stop==2){
					Stop =3 ;
				}
			}
			else if(flag==3)  {
				FrameData = data ;
			}
			data = 0 ;
			flag++ ;
		}
		LCD_SetCursor(1 , 10 ) ;
		LCD_WriteNumber(data) ;
		//data = 0 ;
		
		}else {
		
		//LCD_SetCursor(1, 10 ) ;
		//LCD_WriteString("NO") ;
		
	}
	if(flag==4)  {
		LCD_Clear();
		LCD_SetCursor(0 ,0 ) ;
		LCD_WriteString("Frame is  ");
				_delay_ms(2000);
while (key!='c'){
	CreateFrame(size , FrameData ,Parity,Stop) ;
	key = KEY_Read_ch() ; 
}
		
		//_delay_ms(3000);
		flag = 0 ;
	}
	
}
void CreateFrame ( u8 dataSize, u16 data, parityOptions parity,
stopBitOptions stop)
{
	short mask  = 0 ;
	UartStruct_type frame = {0} ;
	char OnesTemp = 0 ;
	for (char i  = 0 ; i < dataSize ; i ++ )
	{
		if ((data>>i) &1)OnesTemp++ ;
		mask=mask|(1<<i) ;
	}

	frame.Startbit = 0 ;
	if (dataSize<9)
	{

		frame.data = data&mask ;
	}
	else
	{
		frame.data = data&(mask>>1) ;
		frame.data1 = (data>>8)&1 ;
	}
	frame.parity = parityCheck(parity,OnesTemp) ;
	frame.endbits = stop ;
	printFrame(frame,dataSize,parity,stop);
}
void printFrame (UartStruct_type frame, u8 dataSize,parityOptions op,
stopBitOptions stop )
{
	LCD_SetCursor(0 ,0 ) ;
	LCD_WriteNumber(frame.Startbit);
	LCD_WriteString(" ") ;
	for (char i = 0 ; i < dataSize ; i++ )
	{
		if (i < 8)
		{
			LCD_WriteNumber((frame.data>>i)&1);
		}
		else
		{
			LCD_WriteNumber(frame.data1);
		}
	}
	LCD_WriteString(" ") ;
	if (op!=DISABLE)
	{
		LCD_WriteNumber(frame.parity);
	}
	LCD_WriteString(" ") ;
	if (stop==ONE)  LCD_WriteNumber(frame.endbits&1);
	if (stop==TWO)
	{
		LCD_WriteNumber(frame.endbits&1);
		LCD_WriteNumber((frame.endbits>>1)&1);
	}
}
u8 parityCheck (parityOptions par, u8 OnesTemp  )
{
	if ( par == ODD )
	{
		if (OnesTemp&1)
		{
			return 0 ;
		}
		else return 1 ;
	}
	else if ( par == EVEN )
	{
		if (OnesTemp&1)
		{
			return 1 ;
		}
		else return 0 ;
	}
	return 0 ;
}
/*
char calculatr_ones (short data, char data_size)
{
char c = 0 ;
for (char i = 0 ; i < data_size  ; i++)
{

}
return c ;
}
*/

