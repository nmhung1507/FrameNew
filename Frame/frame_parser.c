/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "frame_parser.h"
#include "frame_driver.h"

/* Private defines -----------------------------------------------------------*/
#define MAX_COMMAND_NUMBER 5
#define FRAME_DBG_EN 1
#if FRAME_DBG_EN
#define FRAME_DBG printf
#else
#define FRAME_DBG(...)
#endif

/* Private typedef -----------------------------------------------------------*/
typedef void (*commandHandler_t)(uint8_t* commandData, uint8_t commandLength);

typedef enum
{
  CMD_ID1,
  CMD_ID2,
  CMD_ID3,
  CMD_ID4,
  CMD_ID5,
} commandID_t;

typedef struct
{
  uint8_t cmdID;
  commandHandler_t commandHandler;
} commandObject_t;


/* Global variable -----------------------------------------------------------*/
/* Private function prototypes------------------------------------------------*/
static void command_1_handler(uint8_t* commandData, uint8_t commandLength);
static void command_2_handler(uint8_t* commandData, uint8_t commandLength);
static void command_3_handler(uint8_t* commandData, uint8_t commandLength);
static void command_4_handler(uint8_t* commandData, uint8_t commandLength);
static void command_5_handler(uint8_t* commandData, uint8_t commandLength);

/**< This function searches command ID in the table */
static uint8_t searchCommandIDFromTable(uint8_t commandID);

/* Private variables ---------------------------------------------------------*/
/* Command table */
/* Command ID is it's index in the table */
static const commandObject_t gCommandTable[MAX_COMMAND_NUMBER] =
{
  {CMD_ID1, command_1_handler},  /* Command 1 */
  {CMD_ID2, command_2_handler},  /* Command 2 */
  {CMD_ID3, command_3_handler},  /* Command 3 */
  {CMD_ID4, command_4_handler},  /* Command 4 */
  {CMD_ID5, command_5_handler},  /* Command 5 */
};

/* Function implementation ---------------------------------------------------*/
static void command_1_handler(uint8_t* commandData, uint8_t commandLength)
{
  printf("Call command_1_handler \r\n");
}

static void command_2_handler(uint8_t* commandData, uint8_t commandLength)
{
  printf("Call command_2_handler \r\n");
}

static void command_3_handler(uint8_t* commandData, uint8_t commandLength)
{
  printf("Call command_3_handler \r\n");
}

static void command_4_handler(uint8_t* commandData, uint8_t commandLength)
{
  printf("Call command_4_handler \r\n");
}

static void command_5_handler(uint8_t* commandData, uint8_t commandLength)
{
  printf("Call command_5_handler \r\n");
}

/**< Search command ID in the table */
static uint8_t searchCommandIDFromTable(uint8_t commandID)
{
  uint8_t i;
  
  for(i = 0; i<MAX_COMMAND_NUMBER; i++)
  {
    if (commandID == gCommandTable[i].cmdID)
    {
      /* Found command */
      break;
    }
  }
  
  return i;
}

/**
  * @brief  Parse data from a ring.
  * @param  ring : pointer point to the ring
  * @retval None
  */
void Frame_Parse(Ring_t *ring)
{
  uint8_t byteData;
  if(!ring)
    return;
  /* Get byte from ring */
  if(Ring_GetByte(ring, &byteData) == STATE_ERROR)
    return;
  
  FRAME_DBG("State: %d \r\n", ring->vars.state);
  /* process data base on state */
  switch (ring->vars.state)
  {
  case WAIT_START_BYTE:
    if(byteData == FRAME_START_BYTE)
    {
      /* Received command start byte, change to Receiving header */
      ring->vars.state = RECEIVING_COMMAND_HEADER;
      ring->vars.checksum = 0;
      ring->vars.checksum ^= byteData;
      ring->vars.byteCount = 0;
      ring->vars.timeTick = FDRV_GetTick_LL();
    }
    break;
  case RECEIVING_COMMAND_HEADER:
    ring->vars.byteCount++;
    if((FDRV_GetTick_LL() - ring->vars.timeTick) > BYTE_RCV_TIMEOUT_MS)
    {
    	FRAME_DBG("Timeout\r\n");
    	ring->vars.state = WAIT_START_BYTE;
    	return;
    }
    ring->vars.timeTick = FDRV_GetTick_LL();
    if(ring->vars.byteCount == HEADER_CMDID_OFFSET)
    {
      /* Command ID value */
      ring->vars.commandID = byteData;
      ring->vars.checksum ^= byteData;
    }
    else if (ring->vars.byteCount == HEADER_LEN_OFFSET)
    {
      ring->vars.payloadLen = byteData;
      ring->vars.checksum ^= byteData;
    }
    else if (ring->vars.byteCount == HEADER_CS_OFFSET)
    {
      /* Checksum of header */
      /* Check checksum */
      if(ring->vars.checksum == byteData)
      {
        /* Correct checksum */
        if(ring->vars.payloadLen == 0)
        {
          /* No payload, set received command flag */
          ring->vars.commandReceived = 1;
          /* Wait to receive next command */
          ring->vars.state = WAIT_START_BYTE;
        }
        else
        {
          /* Change to receive payload */
          ring->vars.state = RECEIVING_COMMAND_PAYLOAD;
          /* reset checksum value and Byte count */
          ring->vars.checksum = 0;
          ring->vars.byteCount = 0;
        }
      }
      else
      {
      	ring->vars.state = WAIT_START_BYTE;
      	return;
      }
    }
    else
    {
      /* Should not reach here */
    }
    break;
  case RECEIVING_COMMAND_PAYLOAD:
    if((FDRV_GetTick_LL() - ring->vars.timeTick) > BYTE_RCV_TIMEOUT_MS)
    {
    	FRAME_DBG("Timeout\r\n");
    	ring->vars.state = WAIT_START_BYTE;
    	return;
    }
    ring->vars.timeTick = FDRV_GetTick_LL();
    if(ring->vars.byteCount != ring->vars.payloadLen)
    {
      /* payload byte, save in to command payload and calculate checksum */
      ring->vars.payload[ring->vars.byteCount++] = byteData;
      ring->vars.checksum ^= byteData;
    }
    else
    {
      /* Checksum byte */
      if(ring->vars.checksum == byteData)
      {
        /* Correct checksum, set received command flag */
        ring->vars.commandReceived = 1;
      }
      else
      {
      	ring->vars.state = WAIT_START_BYTE;
      	return;
      }
    }
    break;
  default:
    /* Should not reach here */
    break;
  }
  
  /* Check received command or not */
  if(ring->vars.commandReceived == 1)
  {
    uint8_t commandIndex = MAX_COMMAND_NUMBER;
    /* Call command handler base on table */
    commandIndex = searchCommandIDFromTable(ring->vars.commandID);
    
    if(commandIndex < MAX_COMMAND_NUMBER)
    {
      /* found command, call command handler */
      gCommandTable[commandIndex].commandHandler(ring->vars.payload, ring->vars.payloadLen);
    }
    /* Reset ring to receive next command */
    ring->vars.state = WAIT_START_BYTE;
    ring->vars.commandReceived = 0;
  }
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
	header[HEADER_START_BYTE_OFFSET] = FRAME_START_BYTE;
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

/******************************END OF FILE*************************************/
