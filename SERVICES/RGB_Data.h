


#ifndef RGB_DATA_H_
#define RGB_DATA_H_
#define  BUFFER_SIZE 5 
#define LEDS_NUM 85
typedef struct{
	u8 Red ; 
	u8 Green ; 
	u8 blue ;
	u8 intinsty;
	}RGB_data_type;

void RGB_DATA_Init ();
void RGB_DATA_Rannable();
void RGB_DATA_ISR_fun();
u8 RGB_DATA_Getter(u8 led_ID , RGB_data_type * data);
#endif /* RGB_DATA_H_ */