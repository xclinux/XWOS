/**
 * @file
 * @brief 玄武OS内核移植层：调度
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
#include <xwos/ospl/skd.h>
#include <arch_irq.h>
#include <arch_skd.h>

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********      function implementations       ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
__xwbsp_code
xwer_t xwospl_skd_init(struct xwospl_skd * xwskd)
{
        return arch_skd_init_pendsv(xwskd);
}

__xwbsp_code
void xwospl_skd_init_stack(struct xwospl_skd_stack_info * stk,
                           void (* exit)(xwer_t),
                           xwsq_t attr)
{
        arch_skd_init_stack(stk, exit, attr);
}

__xwbsp_code
xwid_t xwospl_skd_get_id(void)
{
        return 0;
}

__xwbsp_code __xwcc_naked
xwer_t xwospl_skd_start_lc(__xwcc_unused struct xwospl_skd * xwskd)
{
        arch_cpuirq_enable_lc();
        __asm__ volatile("      svc     0");
        return XWOK;
}

__xwbsp_code __xwcc_naked
xwer_t xwospl_skd_suspend(__xwcc_unused struct xwospl_skd * xwskd)
{
        __asm__ volatile(
        "       svc     9\n"
        "       bx      lr\n");
}

__xwbsp_code __xwcc_naked
xwer_t xwospl_skd_resume(__xwcc_unused struct xwospl_skd * xwskd)
{
        __asm__ volatile(
        "       svc     10\n"
        "       bx      lr\n");
}

__xwbsp_code __xwcc_naked
void xwospl_thrd_exit_lc(__xwcc_unused struct xwospl_tcb * tcb,
                         __xwcc_unused xwer_t rc)
{
        __asm__ volatile(
        "       svc     7\n");
        while (true) {
        }
        __asm__ volatile(
        "       bx      lr\n");
}

__xwbsp_code __xwcc_naked
xwer_t xwospl_thrd_freeze_lc(__xwcc_unused struct xwospl_tcb * tcb)
{
        __asm__ volatile(
        "       svc     5\n"
        "       bx      lr\n");
}

#if defined(XuanWuOS_CFG_CORE__mp)
__xwbsp_code __xwcc_naked
xwer_t xwospl_thrd_outmigrate(__xwcc_unused struct xwospl_tcb * tcb,
                              __xwcc_unused xwid_t cpuid)
{
        __asm__ volatile(
        "       svc     11\n"
        "       bx      lr\n");
}

__xwbsp_code
void xwospl_thrd_immigrate(struct xwospl_tcb * tcb, xwid_t cpuid)
{
        XWOS_UNUSED(cpuid);
        xwmp_thrd_immigrate_lic(tcb);
}
#endif /* XuanWuOS_CFG_CORE__mp */
