/**
  ******************************************************************************
  * @file    bsp_usart.c
  * @author  Nick Thinkfly.studio
  * @version V1.0
  * @date    2014-10-6
  * @brief  This file provides all the bsp_usart  functions.
  ******************************************************************************
  * @attention
  *
  * FILE FOR THINKFLY.STUDIO ONLY
  *
  * <h2><center>&copy; COPYRIGHT ThinkFly.Studio</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include    "bsp_usart.h"
#include    "bsp_servo.h"
#include    "bsp_dma.h"
#include    "stdio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

#define DATA_BUF_SIZE     (50)

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/



//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
    int handle;

};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
_sys_exit ( int x )
{
    x = x;
}
//重定义fputc函数
int fputc ( int ch, FILE *f )
{
    while ( ( USART2->SR & 0X40 ) == 0 ); //循环发送,直到发送完毕
    USART2->DR = ( u8 ) ch;
    return ch;
}
#endif


/**
  * @brief  Initialize the USART2
  * @note   None
  * @param  baudrate    baud rate for usart2
  * @retval None
  * @author Nick
  */
void BSP_USART_Init ( u32 baudrate )
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd ( RCC_APB1Periph_USART2, ENABLE );
    RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOA , ENABLE );


    USART_DeInit ( USART2 );

    //USART2_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

    GPIO_Init ( GPIOA, &GPIO_InitStructure );

    //USART2_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init ( GPIOA, &GPIO_InitStructure );

    //USART 初始化设置
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init ( USART2, &USART_InitStructure );
    USART_ITConfig ( USART2, USART_IT_IDLE, ENABLE ); 
    USART_Cmd ( USART2, ENABLE );
    USART_ClearFlag ( USART2, USART_FLAG_TC );

    //DMA for TX
    BSP_DMA_Init ( DMA1_Channel7, ( u32 ) &USART2->DR, ( u32 ) &g_servo_data.rx[0],
                   DMA_DIR_PeripheralDST, DMA_Priority_Low, SERVO_BUF_SIZE );
    //DMA for RX
    BSP_DMA_Init ( DMA1_Channel6, ( u32 ) &USART2->DR, ( u32 ) &g_servo_data.tx[0],
                   DMA_DIR_PeripheralSRC, DMA_Priority_Low, SERVO_BUF_SIZE );

    USART_DMACmd ( USART2, USART_DMAReq_Tx | USART_DMAReq_Rx, ENABLE );
    DMA_Cmd ( DMA1_Channel6, ENABLE );


    //DMA1 CH4 NVIC for USART TX
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init ( &NVIC_InitStructure );
}


/**
  * @brief  Enable USART1 TX via DMA
  * @note   None
  * @param  None
  * @retval None
  * @author Nick
  */
void BSP_USART_Send ( u8 bufSize )
{   
    BSP_DMA_Enable ( DMA1_Channel7, bufSize );
}


/**
  * @brief  IRQ for USART2
  * @note   None
  * @param  None
  * @retval None
  * @author Nick
  */
void USART2_IRQHandler ( void )
{
    u16 tmp = 0;

    if ( USART_GetITStatus ( USART2, USART_IT_IDLE ) == SET )
    {
        //!!! clear IT flag
        USART_ReceiveData ( USART2 );

        tmp = SERVO_BUF_SIZE - DMA1_Channel6->CNDTR;

//        if ( tmp >= 6 && g_servo_data.tx[0] == 0xff && g_servo_data.tx[1] == 0xff )
//        {
            BSP_SERVO_Send ( tmp );
//        }

        BSP_DMA_Enable ( DMA1_Channel6, SERVO_BUF_SIZE );
    }
}
