/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAME_COMMON_DEFINE_H
#define __FRAME_COMMON_DEFINE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum
{
  STATE_OK,
  STATE_ERROR
}ResultState_t;

typedef enum
{
  WAIT_START_BYTE,
  RECEIVING_COMMAND_HEADER,
  RECEIVING_COMMAND_PAYLOAD
} ParseState_t;

/* Exported constants --------------------------------------------------------*/
#define MAX_PAYLOAD_LENGTH 250U
#define RING_BUFFER_SIZE 255U
#define BYTE_RCV_TIMEOUT_MS 200
#define HEADER_LEN 4
#define HEADER_START_BYTE_OFFSET 0
#define HEADER_CMDID_OFFSET 1
#define HEADER_LEN_OFFSET 2
#define HEADER_CS_OFFSET 3
#define FRAME_START_BYTE 0xABU

/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __FRAME_COMMON_DEFINE_H */

/******************************END OF FILE*************************************/
