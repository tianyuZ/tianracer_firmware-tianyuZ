#ifndef _SBUS_H_
#define _SBUS_H_

#include "stm32f4xx_hal.h"

#define RC_CH_VALUE_MIN ((uint16_t)172)
#define RC_CH_VALUE_OFFSET ((uint16_t)992)
#define RC_CH_VALUE_MAX ((uint16_t)1810)

#define SBUS_TIMEOUT 20

#define RC_MIN_CTRL 5

/* -------------------------- RC Switch Definition RC Switch Definition RC Switch Definition RC Switch Definition----------------*/
#define RC_SW_UP ((uint16_t)1)
#define RC_SW_MID ((uint16_t)3)
#define RC_SW_DOWN ((uint16_t)2)
/* ----------------------- PC Key Definition PC Key Definition PC Key Definition ------------------*/
#define KEY_PRESSED_OFFSET_W ((uint16_t)0x01 << 0)
#define KEY_PRESSED_OFFSET_S ((uint16_t)0x01 << 1)
#define KEY_PRESSED_OFFSET_A ((uint16_t)0x01 << 2)
#define KEY_PRESSED_OFFSET_D ((uint16_t)0x01 << 3)
#define KEY_PRESSED_OFFSET_Q ((uint16_t)0x01 << 4)
#define KEY_PRESSED_OFFSET_E ((uint16_t)0x01 << 5)
#define KEY_PRESSED_OFFSET_SHIFT ((uint16_t)0x01 << 6)
#define KEY_PRESSED_OFFSET_CTRL ((uint16_t)0x01 << 7)
#define RC_FRAME_LENGTH 25u

/* -----------------------Data Struct Data Struct ------------------------------------- */
#pragma pack(push)
#pragma pack(1)
typedef struct
{
  struct
  {
    uint16_t ch0;
    uint16_t ch1;
    uint16_t ch2;
    uint16_t ch3;
    uint16_t ch4;
    uint16_t ch5;
    uint16_t ch6;
    uint16_t ch7;
    uint16_t ch8;
    uint16_t ch9;
    uint16_t ch10;
    uint16_t ch11;
    uint16_t ch12;
    uint16_t ch13;
    uint16_t ch14;
    uint16_t ch15;
    uint8_t s1;
  } rc;
} RC_Ctl_t;

typedef struct
{
  float vx;
  float vy;
  float w;
  float steering_angle;
  uint16_t motor_pwm;
} MotionCtrl_t;

#pragma pack(pop)

void RemoteDataProcess(uint8_t *pData, RC_Ctl_t *pCtrlData);

#endif

