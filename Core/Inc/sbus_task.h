#ifndef _SBUS_TASK_H_
#define _SBUS_TASK_H_

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

#define SBUS_MSG_LEN	28

#define SBUS_MSG_QUENE_SIZE 16
#define CTRL_MSG_QUENE_SIZE 32

#define CTRL_TYPE_SBUS_RC 0
#define CTRL_TYPE_PC      1
#define CTRL_TYPE_MAG     2

#define RACECAR_MAX_SPEED 1800
#define RACECAR_MIN_SPEED 1200
#define RACECAR_MAX_OMEGA 120
#define RACECAR_MIN_OMEGA 60

typedef struct{
    uint8_t Msg[SBUS_MSG_LEN];
    uint16_t MsgLen;
}SbusMsg_t;

extern uint8_t SbusBuff[SBUS_MSG_LEN];

extern osMailQId SbusMail;
extern osMailQId CtrlMail;

extern SbusMsg_t *pSbusMsg;

extern volatile uint32_t CtrlFlag;

extern osThreadId SbusTaskHandle;

void SbusTaskInit(void);

#endif
