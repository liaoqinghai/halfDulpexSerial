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

#ifndef __BSP_DMA_H
#define __BSP_DMA_H

/* Includes ------------------------------------------------------------------*/

#include "includes.h"

/* Exported typedef ----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macros ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void BSP_DMA_Init   ( DMA_Channel_TypeDef* DMA_CHx, u32 peripheralBaseAddr,
                      u32 memoryBaseAddr, u32 direction, u32 priority, u16 bufSize );
void BSP_DMA_Enable ( DMA_Channel_TypeDef*DMA_CHx, u16 bufSize );

#endif
/* __DMA_H */

