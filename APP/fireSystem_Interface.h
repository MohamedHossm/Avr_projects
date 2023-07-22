/*
 * fireSystem_Interface.h
 *
 * Created: 4/23/2023 6:51:54 PM
 *  Author: Amm
 */ 


#ifndef FIRESYSTEM_INTERFACE_H_
#define FIRESYSTEM_INTERFACE_H_

#define PASSLEN 20
#define HESTESS_TOP 50
#define HESTESS_BOT 45
typedef enum {
	PASS_OK , 
	PASS_NOT_OK ,
	PASS_W8
	}Password_S_t;
typedef enum {
TEMP_FINE = 0 , 
TEMP_NOT_FINE ,
TEMP_NOT_FINE_Smoke
}temp_S_t;
void fireSystem_Init(void) ; 
void fireSystem_Runnable(void) ;



#endif /* FIRESYSTEM_INTERFACE_H_ */