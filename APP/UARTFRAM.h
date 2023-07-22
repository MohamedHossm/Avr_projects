/*
* UARTFRAM.h
*
* Created: 6/1/2023 2:44:32 AM
*  Author: Amm
*/


#ifndef UARTFRAM_H_
#define UARTFRAM_H_



typedef struct
{
	u8  Startbit :1;
	u8  data :8;
	u8  data1 :1;
	u8  parity : 1;
	u8  endbits : 2;

} UartStruct_type;
typedef enum
{
	DISABLE,
	ODD,
	EVEN
} parityOptions;
typedef enum
{
	ONE = 1, // 1
	TWO = 3 // 11
} stopBitOptions;
//    
void UartframeRunnable ();
//                        5->9
void CreateFrame ( u8 dataSize, u16 data, parityOptions parity, stopBitOptions stop);
u8 parityCheck (parityOptions par, u8 OnesTemp  );
void printFrame (UartStruct_type frame, u8 dataSize,parityOptions op,
stopBitOptions stop );
/*
char calculatr_ones (short data, char data_size);
*/



#endif /* UARTFRAM_H_ */