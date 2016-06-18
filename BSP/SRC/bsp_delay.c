/**
  ******************************************************************************
  * @file    delay.c
  * @author  Nick Thinkfly.studio
  * @version V1.0
  * @date    2014-10-6
  * @brief  This file provides all the delay  functions.
  ******************************************************************************
  * @attention
  *
  * FILE FOR THINKFLY.STUDIO ONLY
  *
  * <h2><center>&copy; COPYRIGHT ThinkFly.Studio</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include    "bsp_delay.h"

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* us延时倍乘数 ms延时倍乘数*/
static u8  fac_us = 0;
static u16 fac_ms = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialise the delay function
  * @note   None
  * @param  sysclk systemColock
  * @retval None
  * @author Nick
  */
void BSP_Delay_Init ( u8 sysclk )
{
    /* 选择外部时钟  HCLK/8 */
    SysTick_CLKSourceConfig ( SysTick_CLKSource_HCLK_Div8 );
    fac_us = sysclk / 8;
    fac_ms = ( u16 ) fac_us * 1000;
}

/**
  * @brief  delay selected ms
  * @note   call BSP_Delay_Init first
  * @param  nms 0-1864 when systemColck@72MHz
  * @retval None
  * @author Nick
  */
void BSP_Delay_ms   ( u16 nms )
{
    u32 temp;

    /* 时间加载(SysTick->LOAD为24bit) */
    SysTick->LOAD = ( u32 ) nms * fac_ms;
    /* 清空计数器 */
    SysTick->VAL = 0x00;
    /* 开始倒数 */
    SysTick->CTRL = 0x01 ;
    do
    {
        temp = SysTick->CTRL;
    }
    /* 等待时间到达 */
    while ( temp & 0x01 && ! ( temp & ( 1 << 16 ) ) );
    /* 关闭计数器 */
    SysTick->CTRL = 0x00;
    /* 清空计数器 */
    SysTick->VAL = 0X00;

}

/**
  * @brief  Delay selected us
  * @note   call BSP_Delay_Init first
  * @param  nus 0-0xffffff*8*1000000/sysclk
  * @retval None
  * @author Nick
  */
void BSP_Delay_us   ( u32 nus )
{
    u32 temp;
    SysTick->LOAD = nus * fac_us;
    SysTick->VAL = 0x00 ;
    SysTick->CTRL = 0x01 ;
    do
    {
        temp = SysTick->CTRL;
    }
    while ( temp & 0x01 && ! ( temp & ( 1 << 16 ) ) );
    SysTick->CTRL = 0x00;
    SysTick->VAL = 0X00;
}


