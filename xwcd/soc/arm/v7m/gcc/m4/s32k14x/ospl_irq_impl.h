/**
 * @file
 * @brief 玄武OS内核移植层：中断
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

#ifndef __ospl_irq_impl_h__
#define __ospl_irq_impl_h__

#ifndef __xwos_ospl_irq_h__
  #error "This file should be included from <xwos/ospl/irq.h>."
#endif

#include <arch_irq.h>

struct soc_irq_cfg {
        struct cortexm_nvic_irq_cfg irqcfg;
};

struct soc_irq_data {
        void * data;
};

struct soc_isr_table {
        xwisr_f arch[ARCHCFG_IRQ_NUM];
        xwisr_f soc[SOCCFG_IRQ_NUM];
};

struct soc_isr_data_table {
        void * arch[ARCHCFG_IRQ_NUM];
        void * soc[SOCCFG_IRQ_NUM];
};

static __xwbsp_inline
void xwospl_cpuirq_enable_lc(void)
{
        arch_cpuirq_enable_lc();
}

static __xwbsp_inline
void xwospl_cpuirq_disable_lc(void)
{
        arch_cpuirq_disable_lc();
}

static __xwbsp_inline
void xwospl_cpuirq_restore_lc(xwreg_t cpuirq)
{
        arch_cpuirq_restore_lc(cpuirq);
}

static __xwbsp_inline
void xwospl_cpuirq_save_lc(xwreg_t * cpuirq)
{
        arch_cpuirq_save_lc(cpuirq);
}

#endif /* ospl_irq_impl.h */
