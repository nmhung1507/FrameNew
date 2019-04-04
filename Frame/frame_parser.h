/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAME_PARSER_H
#define __FRAME_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "ring.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/**
  * @brief  Parse data from a ring.
  * @param  ring : pointer point to the ring
  * @param  cmdId : command ID if parse success
  * @param  data : payload if parse success
  * @param  dataSize : data size if parse success
  * @retval PARSE_OK : parse success, PARSE_ERROR : not success
  */
ResultState_t Frame_Parse(Ring_t *ring, uint8_t *cmdId, 
                                        uint8_t *data, uint16_t *dataSize);

#ifdef __cplusplus
}
#endif

#endif /* __FRAME_PARSER_H */

/******************************END OF FILE*************************************/
