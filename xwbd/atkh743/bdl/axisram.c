/**
 * @file
 * @brief 玄武OS内核适配代码：AXISRAM区域内存池
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

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********      include      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#include <xwos/standard.h>
#include <xwos/lib/xwbop.h>
#include <xwos/mm/common.h>
#include <xwos/mm/bma.h>
#include <bdl/axisram.h>

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       macros      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********         function prototypes         ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       .data       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
extern struct xwmm_bma * axisram_bma;

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********      function implementations       ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#if ((BRDCFG_MM_AXISRAM_BLKSZ % XWMMCFG_STACK_ALIGNMENT) != 0)
  #error BRDCFG_MM_AXISRAM_BLKSZ is not aligned to XWMMCFG_STACK_ALIGNMENT!
#endif

__xwos_code
xwer_t axisram_alloc(xwsz_t memsize, void ** membuf)
{
        xwsz_t stknum;
        xwsq_t numodr;
        xwer_t rc;

        stknum = DIV_ROUND_UP(memsize, BRDCFG_MM_AXISRAM_BLKSZ);
        numodr = (xwsq_t)xwbop_fls(xwsz_t, stknum);
        if (stknum & (stknum - 1U)) {
                numodr++;
        }
        rc = xwmm_bma_alloc(axisram_bma, numodr, membuf);
        return rc;
}

__xwos_code
xwer_t axisram_free(void * mem)
{
        return xwmm_bma_free(axisram_bma, mem);
}
