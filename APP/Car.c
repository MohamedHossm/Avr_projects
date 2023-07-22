#include "StdTypes.h"

#include "DIO_Interface.h"
#include "Motor_Interface.h"
#include "Button_Interface.h"

#include "Car_Interface.h"
#include "Car_Private.h"


void CAR_Init()
{
	/* DO Nothing*/
	
}


void CAR_Runnable(void)
{
	if (BUTTON_Status(B_F)==PRESSED){
		MoveForward();
	}
	else if (BUTTON_Status(B_B)==PRESSED){
		MoveBack();
	}
	else if (BUTTON_Status(B_R)==PRESSED){
		MoveRight();
	}
	else if (BUTTON_Status(B_L)==PRESSED){
		MoveLeft();
	}
	else {
		MoveStop();	
	}
}

static void MoveForward(void)
{
	MOTOR_CW(M1);
	MOTOR_CW(M2);
	MOTOR_CW(M3);
	MOTOR_CW(M4);
}

static void MoveBack(void){
	MOTOR_CCW(M1);
	MOTOR_CCW(M2);
	MOTOR_CCW(M3);
	MOTOR_CCW(M4);
}

static void MoveRight(void){
	MOTOR_CW(M1);
	MOTOR_CW(M2);
	MOTOR_CCW(M3);
	MOTOR_CCW(M4);
}
static void MoveLeft(void){
	MOTOR_CCW(M1);
	MOTOR_CCW(M2);
	MOTOR_CW(M3);
	MOTOR_CW(M4);
}
static void MoveStop(void){
	MOTOR_Stop(M1);
	MOTOR_Stop(M2);
	MOTOR_Stop(M3);
	MOTOR_Stop(M4);
}