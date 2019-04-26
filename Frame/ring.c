/* Includes ------------------------------------------------------------------*/
#include "ring.h"
#include "stdlib.h"
#include "string.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variable -----------------------------------------------------------*/
/* Private function prototypes------------------------------------------------*/
/* Function implementation ---------------------------------------------------*/
/**
  * @brief  Reset members of the ring
  * @param  Ring pointer
  * @retval None
  */
void Ring_Reset(Ring_t *ring)
{
  ring->tail = 0;
  ring->head = 0;
	ring->vars.byteCount = 0;
	ring->vars.checksum = 0;
	ring->vars.commandID = 0;
	ring->vars.commandReceived = 0;
	ring->vars.payloadLen = 0;
	ring->vars.timeTick = 0;
	ring->vars.state = WAIT_START_BYTE;
}

/**
  * @brief  Get the oldest byte from ring.
  * @param  ring: ring pointer
  * @param  value: get byte result
  * @retval state
  */
ResultState_t Ring_GetByte(Ring_t *ring, uint8_t *value)
{
  if((ring == NULL) || (value == NULL))
    return STATE_ERROR;
  if(!Ring_IsEmpty(ring))
  {
    *value = ring->buf[ring->tail];
    ring->tail++;
    if(ring->tail == RING_BUFFER_SIZE)
      ring->tail = 0;
    
    return STATE_OK;
  }

  return STATE_ERROR;
}

/**
  * @brief  Write one byte to a certain ring
  * @param  ring : ring pointer
  * @param  val : value written
  * @retval None
  */
void Ring_WriteByte(Ring_t *ring, uint8_t val)
{
  if(ring == NULL)
    return;
  ring->buf[ring->head] = val;
  ring->head++;
  if(ring->head == RING_BUFFER_SIZE)
    ring->head = 0;
}

/**
  * @brief  check if a ring empty or not
  * @param  ring : point to the ring
  * @retval true: empty, false: not empty
  */
bool Ring_IsEmpty(Ring_t *ring)
{
  if(ring == NULL)
    return true;

  return (ring->head != ring->tail) ? false : true;
}
/*****************************END OF FILE**************************************/
