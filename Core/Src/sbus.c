#include "sbus.h"

void RemoteDataProcess(uint8_t *pData, RC_Ctl_t * pCtrlData)
{
  if((pData == NULL) || (pCtrlData == NULL))
  {
    return;
  }
  pCtrlData->rc.ch0  = ((int16_t)pData[1] | (((int16_t)pData[2] << 8) & 0x07FF));
  pCtrlData->rc.ch1  = (((int16_t)pData[2] >> 3) | (((int16_t)pData[3] << 5) & 0x07FF));
  pCtrlData->rc.ch2  = (((int16_t)pData[3] >> 6) | ((int16_t)pData[4] << 2) | (((int16_t)pData[5] << 10) & 0x07FF));
  pCtrlData->rc.ch3  = (((int16_t)pData[5] >> 1) | (((int16_t)pData[6] << 7) & 0x07FF));
  pCtrlData->rc.ch4  = (((int16_t)pData[6] >> 4) | (((int16_t)pData[7] << 4) & 0x07FF));
  pCtrlData->rc.ch5 =  (((int16_t)pData[7] >> 7) | ((int16_t)pData[8] << 1) | (((int16_t)pData[9] << 9) & 0x07FF));
  pCtrlData->rc.ch6  = (((int16_t)pData[9] >> 2) | (((int16_t)pData[10] << 6) & 0x07FF));
  pCtrlData->rc.ch7  = (((int16_t)pData[10] >> 5) | (((int16_t)pData[11] << 3) & 0x07FF));
  pCtrlData->rc.ch8  = ((int16_t)pData[12] | (((int16_t)pData[13] << 8) & 0x07FF));
  pCtrlData->rc.ch9  = (((int16_t)pData[13] >> 3) | (((int16_t)pData[14] << 5) & 0x07FF));
  pCtrlData->rc.ch10 = (((int16_t)pData[14] >> 6) | ((int16_t)pData[15] << 2) | (((int16_t)pData[16] << 10) & 0x07FF));
  pCtrlData->rc.ch11 = (((int16_t)pData[16] >> 1) | (((int16_t)pData[17] << 7) & 0x07FF));
  pCtrlData->rc.ch12 = (((int16_t)pData[17] >> 4) | (((int16_t)pData[18] << 4) & 0x07FF));
  pCtrlData->rc.ch13 = (((int16_t)pData[18] >> 7) | ((int16_t)pData[19] << 1) | (((int16_t)pData[20] << 9) & 0x07FF));
  pCtrlData->rc.ch14 = (((int16_t)pData[20] >> 2) | (((int16_t)pData[21] << 6) & 0x07FF));
  pCtrlData->rc.ch15 = (((int16_t)pData[21] >> 5) | (((int16_t)pData[22] << 3) & 0x07FF));
  pCtrlData->rc.s1 = pCtrlData->rc.ch4 > RC_CH_VALUE_OFFSET ? RC_SW_UP : RC_SW_DOWN;
}
