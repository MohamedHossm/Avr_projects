/*
 * ACD_SERVICE.h
 *
 * Created: 4/26/2023 6:56:48 PM
 *  Author: Amm
 */ 


#ifndef ACD_SERVICE_H_
#define ACD_SERVICE_H_
typedef enum{
	EMPTY_QUE,
	FINE_QUE,
	FULL_QUE
}Que_S_t;
#define SIZE_MAX_ADC_Queue 10
Que_S_t inQueue_ADC(u16 data);
Que_S_t DeQueue_ADC(u16* data );
Que_S_t IsEmpty(void);
Que_S_t IsFull(void);

#endif /* ACD_SERVICE_H_ */