/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @author
  * + 隐星魂 (Roy Sun) <xwos@xwos.tech>
  * @copyright
  * + Copyright © 2015 xwos.tech, All Rights Reserved.
  * > Licensed under the Apache License, Version 2.0 (the "License");
  * > you may not use this file except in compliance with the License.
  * > You may obtain a copy of the License at
  * >
  * >         http://www.apache.org/licenses/LICENSE-2.0
  * >
  * > Unless required by applicable law or agreed to in writing, software
  * > distributed under the License is distributed on an "AS IS" BASIS,
  * > WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * > See the License for the specific language governing permissions and
  * > limitations under the License.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <bm/stm32cube/standard.h>
#include <xwos/osal/lock/spinlock.h>
#include <xwos/osal/sync/cond.h>
#include <xwcd/ds/uart/dma.h>

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */
struct MX_UART_DriverData {
  UART_HandleTypeDef * halhdl;
  struct xwds_dmauartc * dmauartc;
  struct {
    struct xwos_cond cond; /**< 条件量 */
    struct xwos_splk splk; /**< 保证发送状态只被单一上下文访问的锁 */
    xwer_t rc;
  } tx;
};

extern struct MX_UART_DriverData huart1_drvdata;

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void MX_USART1_UART_DeInit(void);
void MX_USART1_Timer_Init(void);
void MX_USART1_Timer_DeInit(void);
void MX_USART1_Timer_Start(void);
void MX_USART1_Timer_Stop(void);
void MX_USART1_Timer_Callback(void);
xwer_t MX_USART1_RXDMA_Start(xwu8_t * mem, xwsz_t size);
xwsq_t MX_USART1_RXDMA_GetCounter(void);
xwer_t MX_USART1_TXDMA_Start(xwu8_t * mem, xwsz_t size);
xwer_t MX_USART1_Putc(xwu8_t byte);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
