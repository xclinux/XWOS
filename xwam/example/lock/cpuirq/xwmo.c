/**
 * @file
 * @brief 示例：CPU总中断控制
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
#include <string.h>
#include <xwos/lib/xwbop.h>
#include <xwos/lib/xwlog.h>
#include <xwos/osal/scheduler.h>
#include <xwos/osal/thread.h>
#include <xwos/osal/irq.h>
#include <xwos/osal/swt.h>
#include <xwam/example/lock/cpuirq/xwmo.h>

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       macros      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#define XWCPUIRQDEMO_THRD_PRIORITY \
        XWOSAL_SD_PRIORITY_DROP(XWOSAL_SD_PRIORITY_RT_MAX, 1)

#if defined(XWLIBCFG_LOG) && (1 == XWLIBCFG_LOG)
  #define XWCPUIRQDEMO_LOG_TAG     "swt"
  #define swtlogf(lv, fmt, ...) \
        xwlogf(lv, XWCPUIRQDEMO_LOG_TAG, fmt, ##__VA_ARGS__)
#else /* XWLIBCFG_LOG */
  #define swtlogf(lv, fmt, ...)
#endif /* !XWLIBCFG_LOG */

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       types       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********         function prototypes         ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
void xwcpuirqdemo_swt_callback(struct xwosal_swt * swt, void * arg);
xwer_t xwcpuirqdemo_thrd_func(void * arg);

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       .data       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
/**
 * @brief 线程描述表
 */
const struct xwosal_thrd_desc xwcpuirqdemo_tbd = {
        .name = "xwcpuirqdemo.thrd",
        .prio = XWCPUIRQDEMO_THRD_PRIORITY,
        .stack = XWOSAL_THRD_STACK_DYNAMIC,
        .stack_size = 2048,
        .func = (xwosal_thrd_f)xwcpuirqdemo_thrd_func,
        .arg = NULL,
        .attr = XWSDOBJ_ATTR_PRIVILEGED,
};
xwid_t xwcpuirqdemo_tid;

struct xwosal_swt xwcpuirqdemo_swt;
xwid_t xwcpuirqdemo_swtid;

xwsq_t xwcpuirqdemo_shared_count = 0;

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********      function implementations       ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
/**
 * @brief 模块的加载函数
 */
xwer_t example_cpuirq_start(void)
{
        xwer_t rc;

        /* 初始化定时器 */
        rc = xwosal_swt_init(&xwcpuirqdemo_swt, "xwcpuirqdemo_swt",
                             XWOSAL_SWT_FLAG_RESTART);
        if (rc < 0) {
                goto err_swt_init;
        }
        xwcpuirqdemo_swtid = xwosal_swt_get_id(&xwcpuirqdemo_swt);

        /* 创建线程 */
        rc = xwosal_thrd_create(&xwcpuirqdemo_tid,
                                xwcpuirqdemo_tbd.name,
                                xwcpuirqdemo_tbd.func,
                                xwcpuirqdemo_tbd.arg,
                                xwcpuirqdemo_tbd.stack_size,
                                xwcpuirqdemo_tbd.prio,
                                xwcpuirqdemo_tbd.attr);
        if (rc < 0) {
                goto err_thrd_create;
        }

        return XWOK;

err_thrd_create:
        xwosal_swt_destroy(&xwcpuirqdemo_swt);
err_swt_init:
        return rc;
}

/**
 * @brief 定时器的回调函数
 * @note
 * - UP系统
 *   - 当配置(XWUPCFG_SD_BH == 1)，此函数运行在中断底半部；
 *   - 当配置(XWUPCFG_SD_BH == 0)，此函数运行在中断上下文；
 * - SMP系统
 *   - 当配置(XWSMPCFG_SD_BH == 1)，此函数运行在中断底半部；
 *   - 当配置(XWSMPCFG_SD_BH == 0)，此函数运行在中断上下文；
 * - 此函数中不可调用会导致线程睡眠或阻塞的函数。
 */
void xwcpuirqdemo_swt_callback(struct xwosal_swt * swt, void * arg)
{
        xwreg_t cpuirq;

        XWOS_UNUSED(swt);
        XWOS_UNUSED(arg);

        xwosal_cpuirq_save_lc(&cpuirq);
        /* 临界区 */
        xwcpuirqdemo_shared_count++;
        xwosal_cpuirq_restore_lc(cpuirq);
}

/**
 * @brief 线程的主函数
 */
xwer_t xwcpuirqdemo_thrd_func(void * arg)
{
        xwtm_t ts;
        xwsq_t cnt;
        xwer_t rc;

        XWOS_UNUSED(arg);

        swtlogf(INFO, "[线程] 启动。\n");

        ts = xwosal_scheduler_get_timetick_lc();

        swtlogf(INFO, "[线程] 启动定时器。\n");
        rc = xwosal_swt_start(xwcpuirqdemo_swtid,
                              ts, 500 * XWTM_MS,
                              xwcpuirqdemo_swt_callback, NULL);

        while (!xwosal_cthrd_frz_shld_stop(NULL)) {
                ts = 1 * XWTM_S;
                xwosal_cthrd_sleep(&ts);

                xwosal_cpuirq_disable_lc();
                /* 临界区 */
                cnt = xwcpuirqdemo_shared_count;
                xwosal_cpuirq_enable_lc();

                ts = xwosal_scheduler_get_timestamp_lc();
                swtlogf(INFO,
                        "[线程] 时间戳：%lld 纳秒，计数器：%d。\n",
                        ts, cnt);

        }

        swtlogf(INFO, "[线程] 退出。\n");
        xwosal_thrd_delete(xwosal_cthrd_get_id());
        return rc;
}
