/*
 * modbus_master_example.c
 *
 *  Created on: 2022��4��29��
 *      Author: hello
 */


#include "mbrtu_master.h"
#include "usart.h"
#include "tim.h"

#ifdef USE_RTOS

static void mutex_lock(void)
{

}

static void mutex_unlock(void)
{

}

#endif

static void timerStop(void)
{
    HAL_TIM_Base_Stop_IT(&htim3);
}

static void timerStart(void)
{
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    HAL_TIM_Base_Start_IT(&htim3);
}

static void delayms(uint32_t nms)
{
    HAL_Delay(nms);
}

static uint32_t sendData(const void* buf, uint32_t len)
{
    if(HAL_UART_Transmit(&huart3, (uint8_t *)buf, len, 100) != HAL_OK)
    {
        len = 0;
    }
    return len;
}

MBRTUMaterTypeDef MBRTUHandle =
{
    .delayms                      = delayms,
    .timerStart                   = timerStart,
    .timerStop                    = timerStop,
    .sendData                     = sendData,

#ifdef USE_RTOS  
    .lock                         = mutex_lock,
    .unlock                       = mutex_unlock,
#endif
};

#include <string.h>

int ret;
uint8_t ucBuf[10];
uint16_t usBuf[10];

int main_example(void)
{
    // ��ʱ����ʼ��,����Ϊ3.5���ַ��ĳ�ʱʱ��
    // Timer_Init();

    // ���ڳ�ʼ��,��ʼ�������ʵ�
    // UART_Init();

    // д������Ȧ
    ret = MBRTUMasterWriteSingleCoil(&MBRTUHandle, 1, 0, 1, 500);
    printf(" write single coil %s. \r\n", ret < 0 ? "failed" : "ok");
    HAL_Delay(100);

    // д�����Ĵ���
    ret = MBRTUMasterWriteSingleRegister(&MBRTUHandle, 1, 0, 0XAABB, 500);
    printf(" write single reg %s. \r\n", ret < 0 ? "failed" : "ok");
    HAL_Delay(100);

    // д�����Ȧ
    memset(ucBuf, 0X01, 10);
    ret = MBRTUMasterWriteMultipleCoils(&MBRTUHandle, 1, 0, 10, ucBuf, 500);
    printf(" write coils %s. \r\n", ret < 0 ? "failed" : "ok");
    HAL_Delay(100);

    // д����Ĵ���
    memset(usBuf, 0XFF, 20);
    ret = MBRTUMasterWriteMultipleRegisters(&MBRTUHandle, 1, 0, 10, usBuf, 500);
    printf(" write regs %s. \r\n", ret < 0 ? "failed" : "ok");
    HAL_Delay(100);

    // ����Ȧ
    MBRTUMasterReadCoils(&MBRTUHandle, 1, 0, 10, 500, ucBuf);
    printf(" read coils %s. \r\n", ret < 0 ? "failed" : "ok");
    HAL_Delay(100);

    // ����ɢ������
    MBRTUMasterReadDiscreteInputs(&MBRTUHandle, 1, 0, 10, 500, ucBuf);
    printf(" read discs %s. \r\n", ret < 0 ? "failed" : "ok");
    HAL_Delay(100);

    // �����ּĴ���
    MBRTUMasterReadHoldingRegisters(&MBRTUHandle, 1, 0, 10, 500, usBuf);
    printf(" read hold regs %s. \r\n", ret < 0 ? "failed" : "ok");
    HAL_Delay(100);

    // ������Ĵ���
    MBRTUMasterReadInputRegisters(&MBRTUHandle, 1, 0, 10, 500, usBuf);
    printf(" read input regs %s. \r\n", ret < 0 ? "failed" : "ok");
    HAL_Delay(100);

    return 0;
}
