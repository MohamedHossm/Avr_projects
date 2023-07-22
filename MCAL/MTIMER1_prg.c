/*
 * MTIMER1_prg.c
 *
 *  Created on: Jun 13, 2023
 *      Author: elray
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "MTIMER1_priv.h"
#include "MTIMER1_config.h"
#include "MTIMER1_int.h"
#include <avr/interrupt.h>
#include <stdlib.h>

static void (*g_ICU_CallBackPtr[2])(void)={NULL,NULL};
static volatile u8 flag=0;
ErrorState_t MTIMER1_enInit(void)
{
	CLR_BIT(TCCR1A_REG,WGM10_BIT);
	CLR_BIT(TCCR1A_REG,WGM11_BIT);
	CLR_BIT(TCCR1A_REG,WGM12_BIT);
	CLR_BIT(TCCR1A_REG,WGM13_BIT);
	return SUCCES;
}
//timer mode
ErrorState_t MTIMER1_enStart(void)
{
#if(MTIMER1_CLK >= MTIMER1_NO_CLOCK && MTIMER1_CLK <= MTIMER1_ECTTCL_RAISs_EDGE)

	//step1 :clear bits by applying Mask
	TCCR1B_REG &=MTIMER1_CS_MASK;
	//step 2 :set clock value
	TCCR1B_REG |=MTIMER1_CLK;
#else
	#error ("Wrong Timer Clock")
#endif
return SUCCES;
}//clock
ErrorState_t MTIMER1_enStop(void)
{

	TCCR1B_REG &= MTIMER1_CS_MASK;
	return SUCCES;
}//stop
ErrorState_t MTIMER1_ICU_enInit(void)
{


	MTIMER1_ICU_enSetTrigger(MTIMER1_ICU_RAIS_EDGE_TRIG);


		return SUCCES;
}//first trigger to the ISR
ErrorState_t MTIMER1_ICU_enEnableInt(void)
{
	SET_BIT(TIMSK_REG,TICIE1_BIT);


	return SUCCES;
}
ErrorState_t MTIMER1_ICU_enDisableInt(void)
{

	CLR_BIT(TIMSK_REG,TICIE1_BIT);


	return SUCCES;
}
ErrorState_t MTIMER1_ICU_enSetCallBack(u8 copy_u8IntID,void (* ptrfn)(void))
{
	ErrorState_t Local_enstate=SUCCES;
	if(ptrfn !=NULL)
	{
if(copy_u8IntID==MTIME1_CAPT_ID){
		g_ICU_CallBackPtr[0]=ptrfn;
}
else if(copy_u8IntID==MTIME1_OVF_ID){

	g_ICU_CallBackPtr[1]=ptrfn;
}

	}
	else
	{

		Local_enstate=NULL_PTR_ERR;
	}

	return Local_enstate;
}
ErrorState_t MTIMER1_ICU_enRead(volatile u16 * ptrReadValue)
{

	ErrorState_t Local_enstate=SUCCES;
		if(ptrReadValue!=NULL)
		{
			* ptrReadValue=ICR1_REG;
		}
		else
		{

			Local_enstate=NULL_PTR_ERR;
		}

		return Local_enstate;


}
ErrorState_t MTIMER1_ICU_enSetTrigger(u8 copy_u8Trigg)
{

	ErrorState_t Local_enstate=SUCCES;
switch(copy_u8Trigg)
{

case MTIMER1_ICU_FALL_EDGE_TRIG:
	CLR_BIT(TCCR1B_REG,ICES1_BIT);
	break;
case MTIMER1_ICU_RAIS_EDGE_TRIG:
	SET_BIT(TCCR1B_REG,ICES1_BIT);
	break;

default:
Local_enstate=OUT_OF_RANGE;
break;
}

	return Local_enstate;
}

ErrorState_t MTIMER1_OVF_enEnableInt(void)
{
SET_BIT(TIMSK_REG,TOIE1_BIT);



}
ErrorState_t MTIMER1_OVF_enDisableInt(void)
{


CLR_BIT(TIMSK_REG,TOIE1_BIT);

}


ISR(TIMER1_CAPT_vect)
{

	if(g_ICU_CallBackPtr!= NULL&&flag!=0)
		{
		g_ICU_CallBackPtr[MTIME1_CAPT_ID]();	//call fn on higher layer (APP)
		}

flag=1;
}

ISR(TIMER1_OVF_vect)
{

	if(g_ICU_CallBackPtr!= NULL)
			{
			g_ICU_CallBackPtr[MTIME1_OVF_ID]();	//call fn on higher layer (APP)
			}

}

