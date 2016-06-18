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

#ifndef __BSP_USART_H
#define __BSP_USART_H

/* Includes ------------------------------------------------------------------*/

#include "includes.h"

/* Exported typedef ----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void BSP_USART_Init         ( u32 baudrate );
void BSP_USART_Send         ( u8  bufSize );

#endif  /* __USART_H */

