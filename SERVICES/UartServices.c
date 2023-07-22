#include "StdTypes.h"
#include "UART.h"
#include "UartServices.h"

void UART_SendString(u8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
		
}


void UART_ReceiveString(u8*str)
{
	u8 i=0;
	str[i]=UART_Receive();
	for(;str[i]!=13;)
	{
		i++;
		str[i]=UART_Receive();
	}
	str[i]=0;
	
}

void UART_SendNumber(u32 num)
{
	UART_Send((u8)num);
	UART_Send((u8)(num>>8));
	UART_Send((u8)(num>>16));
	UART_Send((u8)(num>>24));
	/*u8*p=&num;
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);*/
	
}

u32 UART_RecieveNumber(void)
{
	u32 num;
	
	u8 b0=UART_Receive();
	u8 b1=UART_Receive();
	u8 b2=UART_Receive();
	u8 b3=UART_Receive();
	
	num=(u32)b0|((u32)b1<<8)|((u32)b2<<16)|((u32)b3<<24);
	
// 	u8*p=(u8*)&num;
// 	p[0]=UART_Receive();
// 	p[1]=UART_Receive();
// 	p[2]=UART_Receive();
// 	p[3]=UART_Receive();
	
	return num;
	
}



u8 endian_check(void)
{
	u32 num=1;
	u8*p=(u8*)&num;
	if(*p==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

u32 endian_convert(u32 num)
{
// 	u8*p=(u8*)&num;
// 	u8 temp;
// 	temp=p[0];
// 	p[0]=p[3];
// 	p[3]=temp;
// 	temp=p[1];
// 	p[1]=p[2];
// 	p[2]=temp;
	
	num=(num>>24)|(num<<24)|((num>>8)&0x0000ff00)|((num<<8)&0x00ff0000);
	return num;
	
}

u16 endian_convert16(u16 num)
{
	num=num>>8|num<<8;
	return num;
	
}


void UART_SendStringCheckSum(u8*str)
{
	u8 i;
	u16 sum=0;
	u8 len;
	for (i=0;str[i];i++)
	{
		sum=sum+str[i];
	}
	len=i;
	UART_Send(len);
	for (i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
	UART_Send((u8)sum);
	UART_Send((u8)(sum>>8));
}

u8 UART_ReceiveStringCheckSum(u8*str)
{
	u8 len,i,b1,b0;
	u16 sumCalc=0,sumRec;
	len=UART_Receive();
	for (i=0;i<len;i++)
	{
		str[i]=UART_Receive();
		sumCalc+=str[i];
	}
	b0=UART_Receive();
	b1=UART_Receive();
	sumRec=(u16)b0|((u16)b1<<8);
	if (sumRec==sumCalc)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
	
}


static void TX_Func(void);

static u8*TXStr;

void UART_SendStringAsynch(u8*str)
{
	UART_SendNoBlock(str[0]);
	UART_TX_InterruptEnable();
	UART_TX_SetCallBack(TX_Func);
	TXStr=str;
	
	
}

static void TX_Func(void)
{
	static  u8 i=1;
	
	if (TXStr[i]!=0)
	{
		UART_SendNoBlock(TXStr[i]);
		i++;
	}
	else
	{
		i=1;
		
	}
	
	
}


/*
void UART_SendStringRunnable(void)
{
	static u8 i=0;
  if (flag==1)
  {
	  if (TXStr[i]!=0)
	  {
		  UART_SendNoBlock(TXStr[i]);
		  i++;
	  }
	  else 
	  {
		  i=0;
	  }
	  flag=0;
  }

}


UART_SendStringPeroidic(u8*str)
{
	TXStr=str;
}
*/
u8*RXStr;
static void RX_Func(void);
void UART_ReceiveStringAsynch(u8*str)
{
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(RX_Func);
	RXStr=str;
}


static void RX_Func(void)
{
	static u8 i=0;
	RXStr[i]=UART_ReceiveNoBlock();
	i++;
}

u8 UartFrameSeparate (u8 * inside ,u8 *string , u32* data ){

	// 	u8*p = (u8*)data ;
	// 	u8 j = 0 ;
	* data =0;
	u8 i = 0;
	for ( i = 0 ;inside[i]!=' '&&inside[i] ; i++  ){

		string[i] = inside[i] ;
	}
	string[i] = 0 ;
	i++ ;
	// 	for ( j = 0 ; j < 4 ; j++ ){
	// 		if (inside[i]!= 0 ){
	// 			p[j] = inside[i] ;
	// 			i++ ;
	// 			}else {
	// 			p[j] = 0 ;
	// 		}
	while(inside[i] >='0' &&inside[i] <='9'){
		
		*data  = (*data*10)+inside[i]-'0';
		i++ ;
	}
	//}


	return 0  ;
}

void UartReciveStringS_D (u8*data){
	u8 i = 0 ;
	data[i] = UART_Receive() ;
	for (;data[i]!=10;){
		i++ ;
		data[i] = UART_Receive()  ;
	}
	data[i-1]= 0 ;
}

 