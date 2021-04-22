/**
 * @file
 * @brief 玄武OS移植实现层：调度
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

#ifndef __xwosimpl_skd_h__
#define __xwosimpl_skd_h__

#ifndef __xwos_ospl_skd_h__
  #error "This file should be included from <xwos/ospl/skd.h>."
#endif

extern struct e200x_context soc_context;

void soc_skd_req_swcx(struct xwospl_skd * xwskd);
void soc_skd_isr_swcx(void);
void soc_skd_isr_swi(void);

/**
 * @brief 玄武OS内核调度器适配函数：发起切换上下文的软中断
 * @param xwskd: (I) 调度器的指针
 */
static __xwbsp_inline
void xwospl_skd_req_swcx(struct xwospl_skd * xwskd)
{
        soc_skd_req_swcx(xwskd);
}

#endif /* xwosimpl_skd.h */
