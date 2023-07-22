

#include "Utils.h"
#include "MemMap.h"
#include "SEVEN_SEG.h"
#define F_CPU 8000000
#include "util\delay.h"
void segment_display_8DIG(unsigned char string [])
{
	char segmentArr[]={0X3f,0X06,0X5b,0X4f,0X66,0X6d,0X7d,0X07,0X7f,0X6f};

	for (int i = 0 ;i < 8 ; i++ ){
		if (string[i]==' '){
			
		}
		else {
			SET_BIT (SEGAMENT_DIS_DIG_CNTROL , i );
			SEGAMENT_DIS_DIG_DATA = ~segmentArr[string[i]-'0'] ;
			_delay_us(120) ;
			CLR_BIT (SEGAMENT_DIS_DIG_CNTROL , i );
			
		}
		
		
		
	}
}
void segment_display(unsigned char n)
{
	unsigned char d0,d1, segmentArr[]={0X3f,0X06,0X5b,0X4f,0X66,0X6d,0X7d,0X07,0X7f,0X6f};
	d0=n%10;
	d1=n/10;
	
	PORTD=segmentArr[d0]<<1;
	PORTC=~segmentArr[d1];
	
}
void segment_display_hex(unsigned char n)
{
	unsigned char d0,d1, segmentArr[]={0X3f,0X06,0X5b,0X4f,0X66,0X6d,0X7d,0X07,0X7f,0X6f,};
	d0=n&0x0f;
	d1=n>>4;
	PORTD=segmentArr[d0]<<1;
	PORTC=~segmentArr[d1];
}

void segment_display_BCD(unsigned char n)
{
	PORTA = (PORTA&(0xf0)) |((n%10)&(0x0f));
	PORTA = (PORTA &(0x0f))|((n/10)<<4 );
}


void segment_display_KIT(unsigned char n){
	unsigned char d0,d1, segmentArr[]={0X3f,0X06,0X5b,0X4f,0X66,0X6d,0X7d,0X07,0X7f,0X6f};
	d0=((n%10));
	d1 = ((n/10));
	
	PORTA=segmentArr[d0]<<1;
	SET_BIT(PORTC ,6);
	_delay_us(10);
	CLR_BIT(PORTC ,6);
	PORTA=segmentArr[d1]<<1;
	SET_BIT(PORTC ,7);
	_delay_us(10);
	CLR_BIT(PORTC ,7);
	
}
void StringFill(unsigned char str[] , int pos , char data){
	
	str[pos] = data%10+'0' ;
	str[pos+1] = data/10+'0' ;

}
