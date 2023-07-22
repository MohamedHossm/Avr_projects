

#ifndef I2C_H_
#define I2C_H_
#define START 0x08
#define ADD_RECIVE 0x18
#define DATA_RECIVE 0x28
void I2C_Init(u8 address );
void I2C_SetAdderss(u8 address) ;
void I2C_SetClock() ;
void I2C_Enable() ;
void I2C_StartCondition_Rstart() ;
void I2C_StopCondition() ;
void I2C_SendDataLine( u8 data ) ; 
void I2C_R_Flag();
void I2C_SendData_Block(u16 data , u8 address);
void I2C_SendData_Block_sequance(u8* data ,u8 dataSize, u8 address);
u8 I2C_ReadStatus();
u8 I2C_Flag() ;
void I2C_Send_ACK(); 
void I2C_Send_NO_ACK();

#endif /* I2C_H_ */