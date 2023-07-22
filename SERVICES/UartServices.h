/*
 * UartServices.h
 *
 * Created: 6/5/2023 9:10:59 PM
 *  Author: Amm
 */ 


#ifndef UARTSERVICES_H_
#define UARTSERVICES_H_

#define LITTLE   1
#define BIG     0
void UART_SendString(u8*str);
void UART_ReceiveString(u8*str);

void UART_SendNumber(u32 num);
u32 UART_RecieveNumber(void);
u8 endian_check(void);

void UART_SendStringCheckSum(u8*str);

u8 UART_ReceiveStringCheckSum(u8*str);
void UART_SendStringAsynch(u8*str);
void UART_ReceiveStringAsynch(u8*str);
u8 UartFrameSeparate (u8 * inside ,u8 *string , u32* data );
void UartReciveStringS_D (u8*data);


#endif /* UARTSERVICES_H_ */