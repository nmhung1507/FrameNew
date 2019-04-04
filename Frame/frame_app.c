/* Includes ------------------------------------------------------------------*/
#include "frame_app.h"
#include "frame_parser.h"
#include "frame_driver.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "usart.h"
/* Private defines -----------------------------------------------------------*/
#define CMD_TOTAL_NUM 2
#define RING_SIZE 100
#define PAY_LOAD_MAX_LEN 100
/* Private typedef -----------------------------------------------------------*/
typedef void (*CALLBACK_FCN)(uint8_t*, uint16_t);

typedef struct {
    uint8_t cmdID;
    CALLBACK_FCN callbackFnc;
} S_CMD_TBL;

/* Private function prototypes------------------------------------------------*/
static void CallbackFcn1(uint8_t* data, uint16_t len);
static void CallbackFcn2(uint8_t* data, uint16_t len);

/* Private variables ---------------------------------------------------------*/
static S_CMD_TBL cmd_table[CMD_TOTAL_NUM] =
{
	{ 0x01, &CallbackFcn1},
	{ 0x02, &CallbackFcn2},											
};

/* Global variable -----------------------------------------------------------*/

/* Function implementation ---------------------------------------------------*/
/**
  * @brief  Callback function of command 1
  * @param  data : data buffer
  * @param  len : data length
  * @retval None
  */
static void CallbackFcn1(uint8_t* data, uint16_t len)
{
	printf("CallbackFcn1\r\nData: ");
	for(uint8_t i = 0; i < len; i++)
	 printf("%x ", data[i]);
}

/**
  * @brief  Callback function of command 2
  * @param  data : data buffer
  * @param  len : data length
  * @retval None
  */
static void CallbackFcn2(uint8_t* data, uint16_t len)
{
	printf("CallbackFcn2\r\nData: ");
	for(uint8_t i = 0; i < len; i++)
	 printf("%x ", data[i]);
}

/**
  * @brief  Init frame
  * @param  None
  * @retval None
  */
Ring_t* Frame_Init(void)
{
	return(Ring_Create(RING_SIZE));
}

/**
  * @brief  Deinit frame
  * @param  point to the ring will be deleted
  * @retval None
  */
void Frame_DeInit(Ring_t* ring)
{
	Ring_Delete(ring);
}

/**
  * @brief  Packet and send a frame
  * @param  cmdID : command ID
  * @param  data : data buffer
  * @param  len : data lenght
  * @retval None
  */
void Frame_Send(uint8_t cmdID, uint8_t *data, uint8_t len)
{
	uint8_t header[HEADER_LEN] = {0}, checkSum = 0;
	
	/* Prepare header */
	header[HEADER_SFD_OFFSET] = FRAME_SFD;
	header[HEADER_CMDID_OFFSET] = cmdID;
	header[HEADER_LEN_OFFSET] = len;
	for(uint8_t i = 0; i < HEADER_LEN -  1; i++)
	  checkSum ^= header[i];
	header[HEADER_CS_OFFSET] = checkSum;
	/* Send header */
	FDRV_UartSend_LL(header, HEADER_LEN);
	
	/* Send payload */
	FDRV_UartSend_LL(data, HEADER_LEN);
	
	/* Prepare and send check sum value of data */
	checkSum = 0;
	for(uint8_t i = 0; i < len; i++)
	  checkSum ^= data[i];
	FDRV_UartSend_LL(&checkSum, 1);
}

/**
  * @brief  Frame receive function, this should be called in a while loop
  * @param  ring : pointer point to the ring
  * @retval None
  */
void Frame_Receive(Ring_t *ring)
{
	uint8_t cmdID = 0;
	uint16_t payLoadSize = 0;
	uint8_t payLoad[PAY_LOAD_MAX_LEN];
	ResultState_t result = Frame_Parse(ring, &cmdID, payLoad, &payLoadSize);
	
	if(result == STATE_OK)
	{
		for(uint16_t i = 0; i < CMD_TOTAL_NUM; i++)
		{
			if(cmdID == cmd_table[i].cmdID)
				cmd_table[i].callbackFnc(payLoad, payLoadSize);
		}
	}
}
/*****************************END OF FILE**************************************/
