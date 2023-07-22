/*
 * SEVEN_SEG.h
 *
 * Created: 3/27/2023 5:25:55 PM
 *  Author: Amm
 */ 


#ifndef SEVEN_SEG_H_
#define SEVEN_SEG_H_


# define SEGAMENT_DIS_DIG_DATA  PORTA
# define SEGAMENT_DIS_DIG_CNTROL  PORTC
void segment_display(unsigned char n) ;
void segment_display_hex(unsigned char n);
void segment_display_BCD(unsigned char n);
void segment_display_KIT(unsigned char n);
void segment_display_8DIG(unsigned char string []);
void StringFill(unsigned char str[] , int pos , char data);


#endif /* SEVEN_SEG_H_ */