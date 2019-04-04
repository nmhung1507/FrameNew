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
  * @brief  Create a ring
  * @param  size : size of the ring
  * @retval pointer point to the ring
  */
Ring_t* Ring_Create(uint16_t size)
{
  Ring_t *ring = (Ring_t*)calloc(1, sizeof(Ring_t));
  uint8_t *buffer = (uint8_t*)calloc(size, sizeof(uint8_t));
  ring->buf = buffer;
  ring->size = size;
  ring->rp = 0;
  ring->wp = 0;
  return ring;
}

/**
  * @brief  Delete a ring
  * @param  ring : the ring would be deleted
  * @retval None
  */
void Ring_Delete(Ring_t* ring)
{
  free(ring->buf);
  free(ring);
}

/**
  * @brief  Get one byte from a certain ring
  * @param  ring : point to the ring
  * @param  state : get byte state
  * @retval value
  */
uint8_t Ring_GetByte(Ring_t *ring, ResultState_t *state)
{
  uint8_t ret = 0;
  if((ring == NULL) || (state == NULL))
    return ret;
  if(Ring_GetLen(ring) != 0)
  {
    ret = ring->buf[ring->rp];
    ring->rp++;
    if(ring->rp == ring->size)
      ring->rp = 0;
    
    *state = STATE_OK;
  }
  else
  {
    *state = STATE_ERROR;
  }
  return ret;
}

/**
  * @brief  Write one byte to a certain ring
  * @param  ring : point to the ring
  * @retval None
  */
void Ring_WriteByte(Ring_t *ring, uint8_t val)
{
  if(ring == NULL)
    return;
  ring->buf[ring->wp] = val;
  ring->wp++;
  if(ring->wp == ring->size)
    ring->wp = 0;
}

/**
  * @brief  Clean a certain ring
  * @param  ring : point to the ring
  * @retval None
  */
void Ring_Clean(Ring_t *ring)
{
  if(ring == NULL)
    return;
  ring->rp = 0;
  ring->wp = 0;
  memset(ring->buf, 0, ring->size);
}

/**
  * @brief  Get the number of byte waiting to read
  * @param  ring : point to the ring
  * @retval return value
  */
uint16_t Ring_GetLen(Ring_t *ring)
{
  if(ring == NULL)
    return 0;
  int16_t len = 0;
  len = ring->wp - ring->rp;
  if(len < 0)
  {
    len += ring->size;
  }
  return (uint16_t)len;
}
/*****************************END OF FILE**************************************/
