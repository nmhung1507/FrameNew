/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAME_PARSER_H
#define __FRAME_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ring.h"

/* Exported define -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/**
  * @brief  Parse data from a ring.
  * @param  ring : pointer point to the ring
  * @retval None
  */
void Frame_Parse(Ring_t *ring);

/**
  * @brief  Packet and send a frame
  * @param  cmdID : command ID
  * @param  data : data buffer
  * @param  len : data lenght
  * @retval None
  */
void Frame_Send(uint8_t cmdID, uint8_t *data, uint8_t len);

#ifdef __cplusplus
}
#endif

#endif /* __FRAME_PARSER_H */

/******************************END OF FILE*************************************/
