/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RING_H
#define __RING_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "frame_common_define.h"
/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint8_t *buf;  /* Point to the buffer of the ring */
  uint16_t size; /* Size of the ring */
  uint16_t wp;   /* Write pointer */
  uint16_t rp;   /* Read pointer */
}Ring_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/**
  * @brief  Create a ring
  * @param  size : size of the ring
  * @retval pointer point to the ring
  */
Ring_t* Ring_Create(uint16_t size);

/**
  * @brief  Delete a ring
  * @param  ring : the ring will be deleted
  * @retval None
  */
void Ring_Delete(Ring_t* ring);

/**
  * @brief  Get one byte from a certain ring
  * @param  ring : point to the ring
  * @retval value
  */
uint8_t Ring_GetByte(Ring_t *ring, ResultState_t *state);

/**
  * @brief  Write one byte to a certain ring
  * @param  ring : point to the ring
  * @retval None
  */
void Ring_WriteByte(Ring_t *ring, uint8_t val);

/**
  * @brief  Clean a certain ring
  * @param  ring : point to the ring
  * @retval None
  */
void Ring_Clean(Ring_t *ring);

/**
  * @brief  Get the number of byte waiting to read
  * @param  ring : point to the ring
  * @retval return value
  */
uint16_t Ring_GetLen(Ring_t *ring);

#ifdef __cplusplus
}
#endif

#endif /* __RING_H */

/******************************END OF FILE*************************************/
