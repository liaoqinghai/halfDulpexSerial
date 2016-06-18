/**
  ******************************************************************************
  * @file    deftype.h
  * @author  Nick Thinkfly.studio
  * @version V1.0
  * @date    2014-10-6
  * @brief   define data type
  ******************************************************************************
  * @attention
  *
  * ALWAYS INCLUDE THIS FILE
  *
  * <h2><center>&copy; COPYRIGHT ThinkFly.Studio</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __DEFTYPE_H
#define __DEFTYPE_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported typedef ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef int64_t     s64;
typedef int32_t     s32;
typedef int16_t     s16;
typedef int8_t      s8;

typedef uint64_t    u64;
typedef uint32_t    u32;
typedef uint16_t    u16;
typedef uint8_t     u8;

typedef u8          bool;

/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define true    (0x01)
#define false   (0x00)


/* Exported functions ------------------------------------------------------- */

#endif  /* __DEFTYPE_H */



