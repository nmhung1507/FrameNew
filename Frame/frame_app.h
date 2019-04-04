/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAME_APP_H
#define __FRAME_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ring.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
/**
  * @brief  Init frame
  * @param  None
  * @retval point to the ring created
  */
Ring_t* Frame_Init(void);

/**
  * @brief  Deinit frame
  * @param  point to the ring will be deleted
  * @retval None
  */
void Frame_DeInit(Ring_t* ring);

/**
  * @brief  Packet and send a frame
  * @param  cmdID : command ID
  * @param  data : data buffer
  * @param  len : data lenght
  * @retval None
  */
void Frame_Send(uint8_t cmdID, uint8_t *data, uint8_t len);

/**
  * @brief  Frame receive function, this should be called in a while loop
  * @param  ring : pointer point to the ring
  * @retval None
  */
void Frame_Receive(Ring_t *ring);

#ifdef __cplusplus
}
#endif

#endif /* __FILE_H */

/******************************END OF FILE*************************************/
