/**
  ******************************************************************************
  * @file    bsp_@fileName.h
  * @author  Nick Thinkfly.studio
  * @version V1.0
  * @date    2014-10-6
  * @brief   This file contains all the functions prototypes for the BOARD
  *  bsp_@fileName
  ******************************************************************************
  * @attention
  *
  * FILE FOR THINKFLY.STUDIO ONLY
  *
  * <h2><center>&copy; COPYRIGHT ThinkFly.Studio</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __BSP_SERVO_H
#define __BSP_SERVO_H

/* Includes ------------------------------------------------------------------*/

#include "includes.h"

/* Exported macro ------------------------------------------------------------*/

#define SERVO_BUF_SIZE    (0xFF)
#define SERVO_TXing       (0x01)
#define SERVO_RXing       (0x00)
/* Exported typedef ----------------------------------------------------------*/

typedef struct
{
    u8 rx[SERVO_BUF_SIZE];
    u8 tx[SERVO_BUF_SIZE];
    u8 state;
} SERVO_DataStruct;

/* Exported variables --------------------------------------------------------*/

extern SERVO_DataStruct g_servo_data;

/* Exported functions ------------------------------------------------------- */

void BSP_SERVO_Init         ( u32 baudrate );
void BSP_SERVO_Send         ( u8 bufSize );

#endif  /* __SERVO_H */

