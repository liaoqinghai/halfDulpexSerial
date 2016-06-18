/**
  ******************************************************************************
  * @file    bsp_led.h
  * @author  Nick Thinkfly.studio
  * @version V1.0
  * @date    2014-10-6
  * @brief   This file contains all the functions prototypes for the BOARD
  *  bsp_led
  ******************************************************************************
  * @attention
  *
  * FILE FOR THINKFLY.STUDIO ONLY
  *
  * <h2><center>&copy; COPYRIGHT ThinkFly.Studio</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __BSP_LED_H
#define __BSP_LED_H

/* Includes ------------------------------------------------------------------*/

#include "includes.h"

/* Exported typedef ----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/*  PC13 LED */
#define LED    PCout(13)
#define LED_ON  (0)
#define LED_OFF (1)

/* Exported functions ------------------------------------------------------- */

void BSP_LED_Init ( void );

#endif  /* __LED_H */

