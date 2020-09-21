/**
  ******************************************************************************
  * File Name          : USART.h
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @author
  * + 隐星魂 (Roy.Sun) <https://xwos.tech>
  * @copyright
  * + (c) 2015 隐星魂 (Roy.Sun) <https://xwos.tech>
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
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <bm/stm32cube/standard.h>
#include <xwos/osal/lock/spinlock.h>
#include <xwos/osal/sync/condition.h>
#include <xwmd/ds/uart/dma.h>

/* USER CODE END Includes */

extern UART_HandleTypeDef husart1;
extern UART_HandleTypeDef husart2;

/* USER CODE BEGIN Private defines */
#define HAL_UART_TXMEM_MAXSIZE    512U /**< 单次最大发送的字节数 */

struct HAL_UART_Xwds_driver_data {
  UART_HandleTypeDef * halhdl;
  struct xwds_dmauartc * dmauartc;
  struct {
    struct xwosal_cdt cdt; /**< 条件量 */
    struct xwosal_splk splk; /**< 保证发送状态只被单一上下文访问的锁 */
    xwer_t rc;
    xwu8_t mem[HAL_UART_TXMEM_MAXSIZE] __xwcc_aligned_l1cacheline; /**< 发送缓冲区 */
    xwu32_t size; /**< 待发送的数据大小 */
  } tx;
};

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */
extern struct HAL_UART_Xwds_driver_data husart1_xwds_drvdata;

void MX_USART1_UART_DeInit(void);
void MX_USART1_Timer_Init(void);
void MX_USART1_Timer_DeInit(void);
void MX_USART1_Timer_Start(void);
void MX_USART1_Timer_Stop(void);
xwer_t MX_USART1_RXDMA_Start(xwu8_t * mem, xwsz_t size);
xwsq_t MX_USART1_RXDMA_GetCounter(void);
void MX_USART1_TXDMA_Prepare(const xwu8_t * mem, xwsz_t size);
xwer_t MX_USART1_TXDMA_Start(void);
xwer_t MX_USART1_Putc(xwu8_t byte);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
