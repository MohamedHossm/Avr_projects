/*
* EX_interrupt.h
*
* Created: 5/8/2023 6:37:59 PM
*  Author: Amm
*/


#ifndef EX_INTERRUPT_H_
#define EX_INTERRUPT_H_
typedef enum {
	Ex0 ,
	Ex1 ,
	Ex2
}EX_type;
typedef enum {
	EX_LOW_lEVEL = 0 ,
	EX_ANY_CHANGE ,
	EX_FALLING ,
	EX_RISING

}EX_state_type;
void Enable_EX(EX_type num , EX_state_type state);
void Disable_EX(EX_type num);
void EXCall_Back(EX_type num , void (*fpt)(void));


#endif /* EX_INTERRUPT_H_ */