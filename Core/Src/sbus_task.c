#include "sbus_task.h"
#include "sbus.h"
#include "cmsis_os.h"
#include "usart.h"
#include "stdlib.h"
#include "param.h"
#include "protocol_task.h"
#include "racecar_task.h"

osMailQId SbusMail;
osMailQId CtrlMail;
osMailQDef(SbusMail, SBUS_MSG_QUENE_SIZE, SbusMsg_t);
osMailQDef(CtrlMail, CTRL_MSG_QUENE_SIZE, MotionCtrl_t);

uint8_t SbusBuff[SBUS_MSG_LEN];

osThreadId SbusTaskHandle;

volatile uint32_t CtrlFlag = CTRL_TYPE_PC;

static void SbusTaskEntry(void const *argument)
{
  osEvent evt;
  SbusMsg_t *p;

  osDelay(1000);

  HAL_UART_Receive_DMA(&huart3, SbusBuff, SBUS_MSG_LEN);
  __HAL_UART_CLEAR_IDLEFLAG(&huart3);
  __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
  /* Infinite loop */
  for (;;)
  {
    evt = osMailGet(SbusMail, SBUS_TIMEOUT);
    if (evt.status == osEventMail)
    {
      p = evt.value.p;

      if (p->MsgLen == RC_FRAME_LENGTH)
      {
        RC_Ctl_t CtrlData;
        RemoteDataProcess(p->Msg, &CtrlData);
//        ProtocolSend(PACK_TYPE_SBUS_RESPONSE, (uint8_t *)&CtrlData, sizeof(RC_Ctl_t));
        if (CtrlData.rc.s1 == RC_SW_UP)
        {
          CtrlFlag = CTRL_TYPE_PC;
        }
//      else if(CtrlData.rc.s1 == RC_SW_DOWN)
//      {
//        CtrlFlag = CTRL_TYPE_MAG;
//      }
        else {
          MotionCtrl_t * pMotionData = osMailAlloc(CtrlMail, osWaitForever);
          CtrlFlag = CTRL_TYPE_SBUS_RC;
          if (abs(CtrlData.rc.ch2 - RC_CH_VALUE_OFFSET) < RC_MIN_CTRL) {
            CtrlData.rc.ch2 = RC_CH_VALUE_OFFSET;
          }

          if (abs(CtrlData.rc.ch3 - RC_CH_VALUE_OFFSET) < RC_MIN_CTRL) {
            CtrlData.rc.ch3 = RC_CH_VALUE_OFFSET;
          }

          if (abs(CtrlData.rc.ch4 - RC_CH_VALUE_OFFSET) < RC_MIN_CTRL) {
            CtrlData.rc.ch4 = RC_CH_VALUE_OFFSET;
          }

          if (abs(CtrlData.rc.ch0 - RC_CH_VALUE_OFFSET) < RC_MIN_CTRL) {
            CtrlData.rc.ch0 = RC_CH_VALUE_OFFSET;
          }

//          pMotionData->vx = (CtrlData.rc.ch2 - RC_CH_VALUE_OFFSET) * param.max_speed / ((RC_CH_VALUE_MAX - RC_CH_VALUE_MIN)/2);
          pMotionData->motor_pwm = (float)(abs(CtrlData.rc.ch2 - RC_CH_VALUE_MIN)) / (RC_CH_VALUE_MAX - RC_CH_VALUE_MIN) *
                                    (MOTOR_MAX - MOTOR_MIN) + MOTOR_MIN;
          pMotionData->steering_angle = (CtrlData.rc.ch0 - RC_CH_VALUE_OFFSET) * param.racecar.max_steer_angle /
                                        ((RC_CH_VALUE_MAX - RC_CH_VALUE_MIN) / 2);
          osMailPut(CtrlMail, pMotionData);
        }
      }

      osMailFree(SbusMail, p);
    }
    else if (evt.status == osEventTimeout)
    {
      CtrlFlag = CTRL_TYPE_PC;
    }
  }
}
osThreadDef(SbusTask, SbusTaskEntry, osPriorityRealtime, 0, 512);
void SbusTaskInit(void)
{
    SbusMail = osMailCreate(osMailQ(SbusMail), NULL);
    CtrlMail = osMailCreate(osMailQ(CtrlMail), NULL);

    SbusTaskHandle = osThreadCreate(osThread(SbusTask), NULL);
}
