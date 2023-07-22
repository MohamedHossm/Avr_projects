/*
 * HEEPROM_init.h
 *
 *  Created on: Jun 21, 2023
 *      Author: elray
 */

#ifndef HAL_HEEPROM_HEEPROM_INT_H_
#define HAL_HEEPROM_HEEPROM_INT_H_

void HEEPROM_enInit(void);

ErrorState_t HEEPROM_enWriteByte(u16 copy_u16Address, u8 copy_u8Byte);

ErrorState_t HEEPROM_enReadByte(u16 copy_u16Address, u8 *ptrData);

#endif /* HAL_HEEPROM_HEEPROM_INT_H_ */
