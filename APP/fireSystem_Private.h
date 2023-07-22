/*
 * fireSystem_Private.h
 *
 * Created: 4/24/2023 6:54:31 PM
 *  Author: Amm
 */ 


#ifndef FIRESYSTEM_PRIVATE_H_
#define FIRESYSTEM_PRIVATE_H_

static void Smoke_state();
static void LED_state();
static void Print_Status_led();
static void PasswordCheck () ;
static Bool_t CompareTowPasswords (u8  * data1 , u8 *data2) ;
static void Temp_SensorState (void);





#endif /* FIRESYSTEM_PRIVATE_H_ */