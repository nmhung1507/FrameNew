/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RING_H
#define __RING_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "frame_common_define.h"
#include <stdbool.h>
#include <stdint.h>
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
typedef struct
{
	ParseState_t state;
  uint8_t checksum;
  uint8_t byteCount;
  uint8_t payloadLen;
  uint8_t commandID;
  uint8_t *payload;
  uint8_t commandReceived;
	uint32_t timeTick;
}ParseVars_t;

typedef struct
{
  uint8_t buf[RING_BUFFER_SIZE];  /* Buffer of the ring */
  uint16_t head;                  /* Write pointer */
  uint16_t tail;                  /* Read pointer */
	ParseVars_t vars;               /* Variables for parse data */
}Ring_t;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/**
  * @brief  Reset members of the ring
  * @param  Ring pointer
  * @retval None
  */
void Ring_Reset(Ring_t *ring);

/**
  * @brief  Get the oldest byte from ring.
  * @param  ring: ring pointer
  * @param  value: get byte result
  * @retval state
  */
ResultState_t Ring_GetByte(Ring_t *ring, uint8_t *value);

/**
  * @brief  Write one byte to a certain ring
  * @param  ring : ring pointer
  * @param  val : value written
  * @retval None
  */
void Ring_WriteByte(Ring_t *ring, uint8_t val);

/**
  * @brief  check if a ring empty or not
  * @param  ring : point to the ring
  * @retval true: empty, false: not empty
  */
bool Ring_IsEmpty(Ring_t *ring);

#ifdef __cplusplus
}
#endif

#endif /* __RING_H */

/******************************END OF FILE*************************************/
