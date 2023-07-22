/*
 * RGB.h
 *
 * Created: 6/8/2023 12:08:24 PM
 *  Author: Amm
 */ 


#ifndef RGBA_H_
#define RGBA_H_
#define LEDS_COLLOR_SIZE 78
# define INCODE(R,G,B) ((R*27)+(G*33)+(B*25)) // try and error .. hash equation for colors  
s8 BinarySearch(u16 data);
void RGBA_Rannable() ;
void ColorCheck(RGB_data_type *colors );


#endif /* RGB_H_ */