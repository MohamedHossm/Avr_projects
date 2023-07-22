


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


#define FREERUNNING_MODE 1 
#define NORMAL_MODE 2 
#define MODE FREERUNNING_MODE
#define VOLTREF (u16)50 

typedef enum{
	ADC_SCALER_2=1,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128,
}ADC_Prescaler_type;

typedef enum{
	AREF,
	AVCC,
	INTER_256 = 3
}VREF_Type;

typedef enum{
	R_ADJAST=0,
	L_ADJAST
}ADJUST_Type;

typedef enum{
	CH_0=0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}ADC_Channel_type;

void ADC_Init(VREF_Type vref,ADJUST_Type state,ADC_Prescaler_type prescaler  );

u16 ADC_Read(ADC_Channel_type ch);

u16 ADC_Read_MV(ADC_Channel_type ch);

void ADC_Sellect_CH(ADC_Channel_type ch ) ; 
u16 ADC_Getter(void);
void ADC_Interrup_enable(void);
void ADC_Interrup_Disable(void);
void ADC_Interrup_Callback(void (*ptr)(void));

#endif /* ADC_INTERFACE_H_ */