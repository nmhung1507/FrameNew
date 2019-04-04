/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAME_DRIVER_H
#define __FRAME_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/**
  * @brief  Send data low-level UART
  * @param  data : data buffer
  * @param  length : length of the buffer
  * @retval None
  */
void FDRV_UartSend_LL(unsigned char *data, unsigned short length);

/**
  * @brief  Get time tick
  * @param  None
  * @retval Time tick
  */
uint32_t FDRV_GetTick_LL(void);

#ifdef __cplusplus
}
#endif

#endif /* __FRAME_DRIVER_H */

/******************************END OF FILE*************************************/
