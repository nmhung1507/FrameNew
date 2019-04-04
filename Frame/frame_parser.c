/* Includes ------------------------------------------------------------------*/
#include "frame_parser.h"
#include "ring.h"
#include "frame_driver.h"
#include "stdbool.h"
/* Private defines -----------------------------------------------------------*/
#define WAIT_DATA_TIMEOUT 10  /* Timeout wait each byte in ms */

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variable -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Function implementation ---------------------------------------------------*/
/**
  * @brief  Parse data from a ring.
  * @param  ring : pointer point to the ring
  * @param  cmdId : command ID if parse success
  * @param  data : payload if parse success
  * @param  dataSize : data size if parse success
  * @retval FRAME_OK : parse success, FRAME_ERROR : not success
  */
ResultState_t Frame_Parse(Ring_t *ring, uint8_t *cmdId, 
                                       uint8_t *data, uint16_t *dataSize)
{
  uint8_t header[HEADER_LEN] = {0}, rcvCnt = 0, tempRcv = 0, checkSum = 0;
  bool rcvCplt = false;
  uint32_t timeTick = 0;
  ResultState_t getByteState = STATE_ERROR;
  if(Ring_GetLen(ring) == 0)
    return STATE_ERROR;
  
  tempRcv = Ring_GetByte(ring, &getByteState);
  
  /* Check if the tempRcv is SFD */
  if(tempRcv != FRAME_SFD)
    return STATE_ERROR;
  else
    header[HEADER_SFD_OFFSET] = tempRcv;
  
  timeTick = FDRV_GetTick_LL();
  rcvCnt = 1; /* Because receive SFD already */
  
  /* Loop if not timeout and get bytes */
  while((FDRV_GetTick_LL() - timeTick) < WAIT_DATA_TIMEOUT)
  {
    tempRcv = Ring_GetByte(ring, &getByteState);
    if(getByteState == STATE_OK)
    {
      header[rcvCnt++] = tempRcv;
      timeTick = FDRV_GetTick_LL();
      if(rcvCnt == HEADER_LEN)
      {
        rcvCplt = true;
        break;
      }
    }
  }
  
  if(rcvCplt == true)
  {
    for(uint8_t i = 0; i < HEADER_LEN - 1; i++)
      checkSum ^= header[i];
  }
  else
    return STATE_ERROR; /* Timeout, return error */
  
  if(checkSum != header[HEADER_CS_OFFSET])
    return STATE_ERROR;
  
  /* Receive payload */
  *dataSize = header[HEADER_LEN_OFFSET];
  *cmdId = header[HEADER_CMDID_OFFSET];
  
  /* Reinitial varialbles */
  timeTick = FDRV_GetTick_LL();
  rcvCnt = 0;
  rcvCplt = false;
  checkSum = 0;
  
  /* Check if timeout and receive bytes */
  while((FDRV_GetTick_LL() - timeTick) < WAIT_DATA_TIMEOUT)
  {
    tempRcv = Ring_GetByte(ring, &getByteState);
    if(getByteState == STATE_OK)
    {
      data[rcvCnt++] = tempRcv;
      timeTick = FDRV_GetTick_LL();
      if(rcvCnt == ((*dataSize) + 1))
      {
        rcvCplt = true;
        break;
      }
    }
  }
  
  if(rcvCplt == true)
  {
    for(uint8_t i = 0; i < (*dataSize); i++)
      checkSum ^= data[i];
  }
  else
    return STATE_ERROR; /* Timeout, return error */
  
  if(checkSum != data[(*dataSize)])
    return STATE_ERROR;
  return STATE_OK;
}

/*****************************END OF FILE**************************************/
