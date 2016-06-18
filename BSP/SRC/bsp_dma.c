/**
  ******************************************************************************
  * @file    bsp_dma.c
  * @author  Nick Thinkfly.studio
  * @version V1.0
  * @date    2014-10-6
  * @brief  This file provides all the bsp_dma  functions.
  ******************************************************************************
  * @attention
  *
  * FILE FOR THINKFLY.STUDIO ONLY
  *
  * <h2><center>&copy; COPYRIGHT ThinkFly.Studio</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include    "bsp_dma.h"

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Global variables ---------------------------------------------------------*/
/* Functions ---------------------------------------------------------*/

/**
  * @brief
  * @note   None
  * @param  None
  * @retval None
  * @author Nick
  */
void BSP_DMA_Init ( DMA_Channel_TypeDef* DMA_CHx, u32 peripheralBaseAddr,
                    u32 memoryBaseAddr, u32 direction, u32 priority, u16 bufSize )
{
    DMA_InitTypeDef ds;

    //Enable clock
    if ( ( u32 ) DMA_CHx > DMA2_BASE )
    {
        RCC_AHBPeriphClockCmd ( RCC_AHBPeriph_DMA2, ENABLE );
    }
    else
    {
        RCC_AHBPeriphClockCmd ( RCC_AHBPeriph_DMA1, ENABLE );
    }

    DMA_DeInit ( DMA_CHx );                                  //将DMA的通道x寄存器重设为缺省值

    ds.DMA_PeripheralBaseAddr = peripheralBaseAddr;          //DMA外设基地址
    ds.DMA_MemoryBaseAddr = memoryBaseAddr;                  //DMA内存基地址
    ds.DMA_DIR = direction;                                  //外设作为数据传输的目的地
    ds.DMA_BufferSize = bufSize;                             //DMA通道的DMA缓存的大小
    ds.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        //外设地址寄存器不变
    ds.DMA_MemoryInc = DMA_MemoryInc_Enable;                 //内存地址寄存器递增
    ds.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //数据宽度为8位
    ds.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         //数据宽度为8位
    ds.DMA_Mode = DMA_Mode_Normal;                           //工作在正常缓存模式
    ds.DMA_Priority = priority;                              //DMA通道 x拥有中优先级
    ds.DMA_M2M = DMA_M2M_Disable;                            //DMA通道x没有设置为内存到内存传输

    DMA_Init ( DMA_CHx, &ds );

}

/**
  * @brief
  * @note   None
  * @param  None
  * @retval None
  * @author Nick
  */
void BSP_DMA_Enable ( DMA_Channel_TypeDef*DMA_CHx, u16 bufSize )
{
    DMA_Cmd ( DMA_CHx, DISABLE );
    DMA_SetCurrDataCounter ( DMA_CHx, bufSize );
    DMA_Cmd ( DMA_CHx, ENABLE );
}
