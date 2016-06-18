/**
  ******************************************************************************
  * @file    bsp_delay.h
  * @author  Nick Thinkfly.studio
  * @version V1.0
  * @date    2014-10-6
  * @brief   This file contains all the functions prototypes for the BOARD
  *  bsp_delay
  ******************************************************************************
  * @attention
  *
  * FILE FOR THINKFLY.STUDIO ONLY
  *
  * <h2><center>&copy; COPYRIGHT ThinkFly.Studio</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H

/* Includes ------------------------------------------------------------------*/

#include "includes.h"

/* Exported typedef ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void BSP_Delay_Init ( u8 sysclck );
void BSP_Delay_ms   ( u16 nms );
void BSP_Delay_us   ( u32 nus );

#endif  /* __DELAY_H */

