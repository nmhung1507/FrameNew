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

/* Exported constants --------------------------------------------------------*/
#define HEADER_LEN 4
#define HEADER_SFD_OFFSET 0
#define HEADER_CMDID_OFFSET 1
#define HEADER_LEN_OFFSET 2
#define HEADER_CS_OFFSET 3
/* SFD (Start of Frame Delimiter) */
#define FRAME_SFD 0xABu

/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __FRAME_COMMON_DEFINE_H */

/******************************END OF FILE*************************************/
