#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "LCD_Interface.h"
#include "ADC_SERVICE.h"
volatile u16 ADC_data = 0 ;



void ADC_Init(VREF_Type vref,ADJUST_Type state,ADC_Prescaler_type prescaler  )
{
	/* vref */
	ADMUX =(ADMUX&0x3f ) ;
	vref = vref << 6 ;
	ADMUX = ADMUX|vref ;
	/* prescaller */
	WRITE_BIT(ADCSRA,ADPS0,READ_BIT(prescaler,0));
	WRITE_BIT(ADCSRA,ADPS1,READ_BIT(prescaler,1));
	WRITE_BIT(ADCSRA,ADPS2,READ_BIT(prescaler,2));
	/* ADJUST */
	WRITE_BIT(ADMUX,ADLAR,state); // ADLAR

	/*mode */
	#if MODE== FREERUNNING_MODE
	// auto trigger free running mode
	//SET_BIT(ADCSRA,ADATE);
	// 	CLR_BIT(SFIOR , ADTS2);
	// 	CLR_BIT(SFIOR , ADTS1);
	// 	CLR_BIT(SFIOR , ADTS0);
	#endif
	
	/*enable*/
	SET_BIT(ADCSRA,ADEN);
	#if MODE== FREERUNNING_MODE
	SET_BIT (ADCSRA,ADSC);
	#endif
	
}

u16 ADC_Read(ADC_Channel_type ch ){
	/* select channel */
	u16 data = 0 ;
	
	ADMUX =ADMUX&0xE0 ;
	ch = ch &0x1F ;
	ADMUX =ADMUX|ch  ;
	/* start conversion */
	SET_BIT (ADCSRA,ADSC);
	while(READ_BIT(ADCSRA,ADSC)==1);
	
	/* Read Data */
	data =  ADC ;
	return data&(0x03ff) ;
}
void ADC_Sellect_CH(ADC_Channel_type ch ){
	/* select channel */
	//u16 data = 0 ;
	ADMUX =ADMUX&0xE0 ;
	ch = ch &0x1F ;
	ADMUX =ADMUX|ch  ;
	
}
u16 ADC_Read_MV(ADC_Channel_type ch){
	//LCD_WriteNumber(ADC_Read(ch));
	return (ADC_Read(ch)*(u32)(VOLTREF*100))/1023 ;
	
}

void ADC_Interrup_enable(void){
	SET_BIT(ADCSRA,ADIE);
}
void ADC_Interrup_Disable(void){
	CLR_BIT(ADCSRA,ADIE);
}
void ADC_Interrup_Callback(void (*ptr)(void)){
	
}
// convention completed
void __vector_16 (void) __attribute__ ((signal));
void __vector_16 (void)
{
	inQueue_ADC(ADC) ;
	
	//SET_BIT (ADCSRA,ADSC);

	//LCD_WriteNumber(ADC_data);
}
u16 ADC_Getter(){
	return ADC_data ;
}