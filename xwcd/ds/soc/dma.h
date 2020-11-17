/**
 * @file
 * @brief xwcd设备栈：SOC DMA
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
 */

#ifndef __xwcd_ds_soc_dma_h__
#define __xwcd_ds_soc_dma_h__

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********      include      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#include <xwcd/ds/standard.h>
#include <xwos/lib/xwbop.h>
#include <xwcd/ds/soc/chip.h>

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       macros      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
/**
 * @brief XWDS DMA 通道
 */
#define XWDS_DMA_CH(x)          ((xwid_t)x)

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       types       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********       API function prototypes       ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
xwer_t xwds_dma_req(struct xwds_soc * soc, xwid_t ch);
xwer_t xwds_dma_rls(struct xwds_soc * soc, xwid_t ch);
xwer_t xwds_dma_cfg(struct xwds_soc * soc, xwid_t ch, void * cfg,
                    xwds_dma_f cb, xwds_dma_cbarg_t arg);
xwer_t xwds_dma_enable(struct xwds_soc * soc, xwid_t ch);
xwer_t xwds_dma_disable(struct xwds_soc * soc, xwid_t ch);
xwer_t xwds_dma_start(struct xwds_soc * soc, xwid_t ch);
xwer_t xwds_dma_stop(struct xwds_soc * soc, xwid_t ch);

#endif /* xwcd/ds/soc/dma.h */
