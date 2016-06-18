/**
  ******************************************************************************
  * @file    app.c
  * @author  Nick Thinkfly.studio
  * @version V1.1
  * @date    2014-10-6
  * @brief   main function
  ******************************************************************************
  * @attention
  *
  * FILE FOR THINKFLY.STUDIO ONLY
  *
  * <h2><center>&copy; COPYRIGHT ThinkFly.Studio</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

//#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_usart.h"
#include "bsp_servo.h"

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

int main()
{
    u8 i = 0;

    /* 设置NVIC中断分组2:2位抢占优先级，2位响应优先级 */
    NVIC_PriorityGroupConfig ( NVIC_PriorityGroup_2 );

    BSP_Delay_Init ( 72 );
    BSP_USART_Init ( 115200 );
    BSP_SERVO_Init ( 1000000 );

    while ( true )
    {

    }



}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed ( uint8_t* file, uint32_t line )
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while ( 1 )
    {
    }
}
#endif




