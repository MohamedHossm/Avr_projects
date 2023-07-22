/*
 * ADC_filter.h
 *
 * Created: 4/29/2023 6:18:21 PM
 *  Author: Amm
 */ 

#ifndef ACD_SERVICE_H_
#define ACD_SERVICE_H_

#define FILTER_CH CH_7
typedef enum{
	EMPTY_QUE,
	FINE_QUE,
	FULL_QUE
}Que_S_t;

#define SIZE_MAX_ADC_Queue_filer 10
void printQUE() ; 
Que_S_t inQueue_ADC_Filter(u16 data);
Que_S_t DeQueue_ADC_Filter(u16* data );
Que_S_t IsEmpty_Filter(void);
Que_S_t IsFull_Filter(void);
void ADC_Call_Filter ();
u16 ADC_Getter_Filter();
void ADC_filter_init ();


#endif /* ADC_FILTER_H_ */