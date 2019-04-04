/* Includes ------------------------------------------------------------------*/
#include "frame_driver.h"
#include "stm32f7xx_hal.h"
#include "usart.h"
#include "ring.h"
/* Private defines -----------------------------------------------------------*/
#define UART_TRANSMIT_TIMEOUT 1000
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variable -----------------------------------------------------------*/
/* Private function prototypes------------------------------------------------*/
/* Function implementation ---------------------------------------------------*/
/**
  * @brief  Send data low-level UART
  * @param  data : data buffer
  * @param  length : length of the buffer
  * @retval None
  */
void FDRV_UartSend_LL(unsigned char *data, unsigned short length)
{
  HAL_UART_Transmit(&huart1, data, length, UART_TRANSMIT_TIMEOUT);
}

/**
  * @brief  Get time tick in milisecond
  * @param  None
  * @retval Time tick
  */
uint32_t FDRV_GetTick_LL(void)
{
  return HAL_GetTick();
}

/*****************************END OF FILE**************************************/
