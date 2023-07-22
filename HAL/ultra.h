/*
 * ultra.h
 *
 * Created: 5/24/2023 7:23:27 PM
 *  Author: Amm
 */ 


#ifndef ULTRA_H_
#define ULTRA_H_

typedef struct {

	DIO_Pin_type pintrig ; 
	u16 d ;

	}ultr_type;

void ultr_init (void); 
u16 ultra_getRead(u8 data );
//void ultr_Read ( s8 countertemp );
void ultr_Start (ultr_type data_ultra );
u8 ultr_GetRead_Noblock (ultr_type * data_ultra );
void ICUFUN(void) ;
void OVF_FUN(void);
#endif /* ULTRA_H_ */