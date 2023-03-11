#ifndef MBRTU_MASTER_H_
#define MBRTU_MASTER_H_

#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include "gd32f30x.h"
#include "gd32f30x_usart.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// MODBUS RTU ??????
///
///
typedef struct
{
	//
	// ??????
	//
	uint8_t ucBuf[128];
	
	//
	// ??????
	//
	uint16_t usStatus;
	
	//
	// ?????RTOS??????,???????????????
	//
	void (*lock)(void);
	void (*unlock)(void);
	
	//
	// ??????,??????
	//
	void (*delayms)(uint32_t nms);
	
	//
	// ??????????
	//
	void (*timerStop)(void);
	void (*timerStart)(void);
	
	//
	// ??????,??????TCP?
	//
	uint32_t (*sendData)(const void* buf, uint32_t len);

}MBRTUMaterTypeDef;

extern MBRTUMaterTypeDef MBRTUHandle;
extern uint32_t count_modbus;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// MODBUS RTU ?? API
///
///
int MBRTUMasterReadCoils(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint16_t usNum, uint16_t usTimeout, uint8_t* pucCoilsBuffer);
int MBRTUMasterReadDiscreteInputs(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint16_t usNum, uint16_t usTimeout, uint8_t* pucDiscBuffer);
int MBRTUMasterReadHoldingRegisters(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint16_t usNum, uint16_t usTimeout, uint16_t* pusRegBuffer);
int MBRTUMasterReadInputRegisters(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint16_t usNum, uint16_t usTimeout, uint16_t* pusRegBuffer);
int MBRTUMasterWriteSingleCoil(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint8_t ucState, uint16_t usTimeout);
int MBRTUMasterWriteSingleRegister(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint16_t usRegVal, uint16_t usTimeout);
int MBRTUMasterWriteMultipleCoils(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint16_t usNum, const uint8_t* pucStateBitsBuf, uint16_t usTimeout);
int MBRTUMasterWriteMultipleRegisters(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint16_t usNum, const uint16_t* pusRegVal, uint16_t usTimeout);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// MODBUS RTU ?????????????????
/// 
/// MBRTUMasterRecvByteISRCallback:??????????
/// MBRTUMasterTimerISRCallback:???????????
///
void MBRTUMasterRecvByteISRCallback(MBRTUMaterTypeDef* psModbus, uint8_t ucByte);
void MBRTUMasterTimerISRCallback(MBRTUMaterTypeDef* psModbus);


#ifdef __cplusplus
}
#endif

#endif
