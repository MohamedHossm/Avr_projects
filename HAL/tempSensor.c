#include "StdTypes.h"
#include "ADC_Interface.h"
#include "tempSensor.h"

void tempSensor_Init() {
	//do nothing
}
u16 tempSensor_Read() {
	u16 temp = 0 ;
	u16  read = ADC_Read_MV(LM32) ;
	temp =read/10 ;
	return temp ;
}
u32 Maping(u32 X1 , u32 X2 , u32 Y1 , u32 Y2 , u32 ADC){
	u32 dataout = 0;
	//y = slop *(x -x1 ) - y2
	//slop = y-y1 / x-x1
	// y  = (y-y1 / x-x1) *(x -x1 ) -y2
	dataout = (((ADC-X1)*(Y2 - Y1))/(X2 - X1 ))+Y1 ;
	return dataout ;
}

u16 tempSensor_Read2() {
u16 temp = 0 ;	
//u16 temp2 = 0 ;
//u16  read = ADC_Read_MV(MPX) ;
u16  read = ADC_Read(MPX) ;
//temp =((u32)(((u32)read-268)*100)/4497)+15;
temp = Maping(55 , 976 , 15,155,read );
	// u32 Pressure = ((10 * (u32)read * 1000 / 5000) + 950) / 9 - 15;
return  temp;
}