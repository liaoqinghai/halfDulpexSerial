/**
  ******************************************************************************
  * @file    led.c
  * @author  Nick Thinkfly.studio
  * @version V1.0
  * @date    2014-10-6
  * @brief  This file provides all the led  functions.
  ******************************************************************************
  * @attention
  *
  * FILE FOR THINKFLY.STUDIO ONLY
  *
  * <h2><center>&copy; COPYRIGHT ThinkFly.Studio</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include    "bsp_led.h"

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize the LED
  * @note   None
  * @param  None
  * @retval None
  * @author Nick
  */
void BSP_LED_Init ( void )
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* 使能PC端口时钟 */
    RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOC, ENABLE );

    /* LED0-->PC.13 端口配置 推挽输出 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init ( GPIOC, &GPIO_InitStructure );

    /* PC.13 输出高 */
    GPIO_ResetBits ( GPIOC, GPIO_Pin_13 );
}

