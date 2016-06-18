/**
  ******************************************************************************
  * @file    bsp_servo.c
  * @author  Nick Thinkfly.studio
  * @version V1.0
  * @date    2014-10-6
  * @brief  This file provides all the bsp_servo  functions.
  ******************************************************************************
  * @attention
  *
  * FILE FOR THINKFLY.STUDIO ONLY
  *
  * <h2><center>&copy; COPYRIGHT ThinkFly.Studio</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include    "bsp_servo.h"
#include    "bsp_led.h"
#include    "bsp_dma.h"
#include    "bsp_usart.h"
#include    "bsp_delay.h"

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

//#define SERVO_EN          PCout(13)
//#define SERVO_EN_RX       (0X00)
//#define SERVO_EN_TX       (0X01)

/* Private function prototypes -----------------------------------------------*/

/* Global variables ----------------------------------------------------------*/

SERVO_DataStruct g_servo_data;

/* Functions -----------------------------------------------------------------*/


/**
  * @brief  Init Servo usart port
  * @note   None
  * @param  None
  * @retval None
  * @author Nick
  */
void BSP_SERVO_Init ( u32 baudrate )
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    //three state gate share EN pin with LED
    BSP_LED_Init();

    g_servo_data.state = SERVO_RXing;

    //使能时钟
    RCC_APB2PeriphClockCmd ( RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE );

    USART_DeInit ( USART1 );

    //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

    GPIO_Init ( GPIOA, &GPIO_InitStructure );

    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init ( GPIOA, &GPIO_InitStructure );

    //USART 初始化设置
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init ( USART1, &USART_InitStructure );
    USART_HalfDuplexCmd(USART1, ENABLE);
    USART_Cmd ( USART1, ENABLE );
    USART_ITConfig ( USART1, USART_IT_IDLE, ENABLE ); //开启空闲中断
    USART_ClearFlag ( USART1, USART_FLAG_TC );

    //DMA for TX
    BSP_DMA_Init ( DMA1_Channel4, ( u32 ) &USART1->DR, ( u32 ) &g_servo_data.tx[0],
                   DMA_DIR_PeripheralDST, DMA_Priority_VeryHigh, SERVO_BUF_SIZE );
    //DMA for RX
    BSP_DMA_Init ( DMA1_Channel5, ( u32 ) &USART1->DR, ( u32 ) &g_servo_data.rx[0],
                   DMA_DIR_PeripheralSRC, DMA_Priority_VeryHigh, SERVO_BUF_SIZE );

    USART_DMACmd ( USART1, USART_DMAReq_Tx | USART_DMAReq_Rx, ENABLE );
    DMA_Cmd ( DMA1_Channel5, ENABLE );

    DMA_ITConfig ( DMA1_Channel4, DMA_IT_TC, ENABLE );

    //DMA1 CH4 NVIC for USART TX
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init ( &NVIC_InitStructure );


    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;

    NVIC_Init ( &NVIC_InitStructure );

}



/**
  * @brief  Enable USART1 TX via DMA
  * @note   None
  * @param  None
  * @retval None
  * @author Nick
  */
void BSP_SERVO_Send ( u8 bufSize )
{
    g_servo_data.state = SERVO_TXing;
    
    //disable the dma rx or you will get what you send
    USART_DMACmd ( USART1,USART_DMAReq_Rx, DISABLE );
    
    BSP_DMA_Enable ( DMA1_Channel4, bufSize);
}

/**
  * @brief  DMA1_Channel4 IRQ Handler
  * @note   None
  * @param  None
  * @retval None
  * @author Nick
  */
void DMA1_Channel4_IRQHandler ( void )
{
    if ( DMA_GetITStatus ( DMA1_IT_TC4 ) == SET ) 
    {
        g_servo_data.state = SERVO_RXing;
        DMA_ClearITPendingBit ( DMA1_IT_TC4 );
        
        //clear RXN flag or you will get one more byte
        USART_ReceiveData(USART1);
        
        USART_DMACmd ( USART1, USART_DMAReq_Rx, ENABLE );
    }

}


/**
  * @brief  IRQ for USART1
  * @note   None
  * @param  None
  * @retval None
  * @author Nick
  */
void USART1_IRQHandler ( void )
{
    u16 tmp = 0;

    if ( USART_GetITStatus ( USART1, USART_IT_IDLE ) == SET )
    {
        //!!! clear IT flag
        USART_ReceiveData ( USART1 );

        tmp = SERVO_BUF_SIZE - DMA1_Channel5->CNDTR;

//        if ( tmp >= 6 && g_servo_data.rx[0] == 0xff && g_servo_data.rx[1] == 0xff )
//        {
            BSP_USART_Send ( tmp );
//        }

        BSP_DMA_Enable ( DMA1_Channel5, SERVO_BUF_SIZE );
    }
}
