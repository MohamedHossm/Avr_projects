/*
* tempSensor.h
*
* Created: 4/20/2023 12:47:05 PM
*  Author: Amm
*/


#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_
/*
typedef enum {
SEN_PIN0,
SEN_PIN1,
SEN_PIN2,
SEN_PIN3,
SEN_PIN4,
SEN_PIN5,
SEN_PIN6,
SEN_PIN7
}sensor_type;
*/
#define  LM32 (ADC_Channel_type) CH_0
#define  MPX (ADC_Channel_type) CH_7
void tempSensor_Init() ;
u16 tempSensor_Read()  ;
u16 tempSensor_Read2();
u32 Maping(u32 X1 , u32 X2 , u32 Y1 , u32 Y2 , u32 ADC);
#endif /* TEMPSENSOR_H_ */