/*
 * MTIMER1_int.h
 *
 *  Created on: Jun 13, 2023
 *      Author: elray
 */

#ifndef MTIMER1_MTIMER1_INT_H_
#define MTIMER1_MTIMER1_INT_H_

#define MTIMER1_ICU_FALL_EDGE_TRIG 0
#define MTIMER1_ICU_RAIS_EDGE_TRIG 1

#define MTIME1_CAPT_ID 0
#define MTIME1_OVF_ID 1

ErrorState_t MTIMER1_enInit(void);//timer mode
ErrorState_t MTIMER1_enStart(void);//clock
ErrorState_t MTIMER1_enStop(void);//stop
ErrorState_t MTIMER1_ICU_enInit(void);//first trigger to the ISR
ErrorState_t MTIMER1_ICU_enEnableInt(void);
ErrorState_t MTIMER1_ICU_enDisableInt(void);
ErrorState_t MTIMER1_ICU_enSetCallBack(u8 copy_u8IntID,void (* ptrfn)(void));
ErrorState_t MTIMER1_ICU_enRead(volatile u16 * ptrReadValue);
ErrorState_t MTIMER1_ICU_enSetTrigger(u8 copy_u8Trigg);
ErrorState_t MTIMER1_OVF_enEnableInt(void);
ErrorState_t MTIMER1_OVF_enDisableInt(void);

#endif /* MTIMER1_MTIMER1_INT_H_ */
