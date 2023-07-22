

#include "StdTypes.h"
#include "ERROR_STATES.h"
#include "Utils.h"
//#include "DIO_Interface.h"
#include "MTWI_int.h"
#include "HEEPROM_config.h"
#include "HEEPROM_int.h"

void HEEPROM_enInit(void)
{
	// init TWI
	MTWI_enInit(10);
	
}

ErrorState_t HEEPROM_enWriteByte(u16 copy_u16Address, u8 copy_u8DByte)
{
	u8 Status;

	MTWI_enSendStart();

	MTWI_enReadStatus(&Status);
	if(Status != MTWI_MT_START_SUCCESS)
	{
		return FAILIUR;
	}


	MTWI_enSendByte( 0xA0); 
	
	MTWI_enReadStatus(&Status);
	if(Status != MTWI_MT_SLA_W_ACK)
	{
		return FAILIUR;
	}


	
	MTWI_enSendByte(copy_u16Address>>8);

	MTWI_enReadStatus(&Status);
	if(Status != MTWI_MT_DATA_ACK)
	{
		return FAILIUR;
	}
	MTWI_enSendByte((u8) copy_u16Address);


	MTWI_enReadStatus(&Status);
	if(Status != MTWI_MT_DATA_ACK)
	{
		return FAILIUR;
	}

	MTWI_enSendByte((u8) copy_u8DByte);

	
	MTWI_enReadStatus(&Status);
	if(Status != MTWI_MT_DATA_ACK)
	{
		return FAILIUR;
	}

	// Step 9 : Send Stop
	MTWI_enSendStop();

	return SUCCES;
}

ErrorState_t HEEPROM_enReadByte(u16 copy_u16Address, u8 *PtrRecData)
{
	u8 Status;

	MTWI_enSendStart();

	MTWI_enReadStatus(&Status);
	if(Status != MTWI_MT_START_SUCCESS)
	{
		return FAILIUR;
	}


	MTWI_enSendByte(0xA0);  // address for I2C

	MTWI_enReadStatus(&Status);

	if(Status != MTWI_MT_SLA_W_ACK)
	{
		return FAILIUR;
	}

	
	
	MTWI_enSendByte(copy_u16Address>>8);
	// Step 6 : Check Status
	MTWI_enReadStatus(&Status);
	if(Status != MTWI_MT_DATA_ACK)
	{
		return FAILIUR;
	}
	MTWI_enSendByte((u8) copy_u16Address);

	
	MTWI_enReadStatus(&Status);
	if(Status != MTWI_MT_DATA_ACK)
	{
		return FAILIUR;
	}


	MTWI_enSendStart();

	// Step 8 : Check Status
	MTWI_enReadStatus(&Status);
	if(Status != MTWI_MR_REPEATED_START_SUCCESS)
	{
		return FAILIUR;
	}

	
	MTWI_enSendByte(0xA0 | 0x01);

	// Step 10 : Check Status
	MTWI_enReadStatus(&Status);
	if(Status != MTWI_MR_SLA_R_ACK)
	{
		return FAILIUR;
	}


	MTWI_enRecByteAck(PtrRecData);


	MTWI_enReadStatus(&Status);
	if(Status != MTWI_MR_DATA_ACK)
	{
		return FAILIUR;
	}


	MTWI_enSendStop();
	return SUCCES;
}
