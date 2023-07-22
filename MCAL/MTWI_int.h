/*
 * MTWI_int.h
 *
 *  Created on: Jun 21, 2023
 *      Author: elray
 */

#ifndef MI2C_MTWI_INT_H_
#define MI2C_MTWI_INT_H_
//MT status codes
#define MTWI_MT_START_SUCCESS				0x08
#define MTWI_MT_REPEATED_START_SUCCESS		0x10
#define MTWI_MT_SLA_W_ACK					0x18
#define MTWI_MT_SLA_W_NOACK					0x20 //slave address
#define MTWI_MT_DATA_ACK					0x28
#define MTWI_MT_DATA_NOACK					0x30
#define MTWI_MT_ABITRATION_LOST				0x38
//MR status codes
#define MTWI_MR_START_SUCCESS				0x08
#define MTWI_MR_REPEATED_START_SUCCESS		0x10
#define MTWI_MR_SLA_R_ACK					0x40
#define MTWI_MR_SLA_R_NOACK					0x48
#define MTWI_MR_DATA_ACK					0x50
#define MTWI_MR_DATA_NOACK					0x58
#define MTWI_MR_ABITRATION_LOST				0x38

//master mode
void MTWI_enInit( u8 data);

ErrorState_t MTWI_enSendStart(void);

ErrorState_t MTWI_enSendStop(void);
ErrorState_t MTWI_enSendByte(u8 copy_u8Data);
ErrorState_t MTWI_enRecByteAck(u8 *ptrRECdata);
ErrorState_t MTWI_enRecByteNoAck(u8 *ptrRECdata);
ErrorState_t MTWI_enReadStatus(u8 * ptrStatusValue);



#endif /* MI2C_MTWI_INT_H_ */
