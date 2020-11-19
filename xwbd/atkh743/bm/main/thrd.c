/**
 * @file
 * @brief 主模块：子线程
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

#include <xwos/mm/mempool/allocator.h>
#include <xwos/osal/skd.h>
#include <xwcd/ds/soc/gpio.h>
#include <xwcd/perpheral/i2c/eeprom/driver.h>
#include <bdl/standard.h>
#include <bm/stm32cube/mif.h>
#include <bm/main/thrd.h>

#define LED_TASK_PRIORITY                                       \
        (XWOS_SKD_PRIORITY_RAISE(XWOS_SKD_PRIORITY_RT_MIN, 1))

#define MEMTST_TASK_PRIORITY                                    \
        (XWOS_SKD_PRIORITY_RAISE(XWOS_SKD_PRIORITY_RT_MIN, 1))

xwer_t led_task(void * arg);

xwer_t memtst_task(void * arg);

const struct xwos_thrd_desc child_tbd[] = {
        [0] = {
                .name = "task.led",
                .prio = LED_TASK_PRIORITY,
                .stack = NULL,
                .stack_size = 4096,
                .func = led_task,
                .arg = NULL,
                .attr = XWOS_SKDATTR_PRIVILEGED,
        },
        [1] = {
                .name = "task.memtst",
                .prio = MEMTST_TASK_PRIORITY,
                .stack = NULL,
                .stack_size = 2048,
                .func = memtst_task,
                .arg = NULL,
                .attr = XWOS_SKDATTR_PRIVILEGED,
        },
};

xwid_t child_tid[xw_array_size(child_tbd)];

xwer_t child_thrd_start(void)
{
        xwer_t rc;
        xwsq_t i;

        for (i = 0; i < xw_array_size(child_tbd); i++) {
                rc = xwos_thrd_create(&child_tid[i], child_tbd[i].name,
                                      child_tbd[i].func,
                                      child_tbd[i].arg,
                                      child_tbd[i].stack_size,
                                      child_tbd[i].prio,
                                      child_tbd[i].attr);
                if (rc < 0) {
                        goto err_thrd_create;
                }
        }
        return XWOK;

err_thrd_create:
        BDL_BUG();
        return rc;
}

xwer_t eeprom_task(void)
{
        xwer_t rc;
        xwtm_t xwtm;
        xwsz_t size;
        xwu8_t eedata[8] = {0};

        xwtm = 1 * XWTM_S;
        rc = xwds_eeprom_reset(&stm32cube_at24c02_cb, &xwtm);
        if (rc < 0) {
                goto err_eeprom_reset;
        }

        size = 8;
        xwtm = 1 * XWTM_S;
        rc = xwds_eeprom_pgread(&stm32cube_at24c02_cb, eedata, &size, 0, &xwtm);
        if (rc < 0) {
                goto err_eeprom_read;
        }

        size = 8;
        xwtm = 1 * XWTM_S;
        rc = xwds_eeprom_pgread(&stm32cube_at24c02_cb, eedata, &size, 1, &xwtm);
        if (rc < 0) {
                goto err_eeprom_read;
        }

        return XWOK;

err_eeprom_read:
err_eeprom_reset:
        return rc;
}

xwer_t led_task(void * arg)
{
        xwer_t rc;
        xwtm_t xwtm;

        XWOS_UNUSED(arg);

        rc = eeprom_task();
        if (rc < 0) {
                BDL_BUG();
        }

        xwds_gpio_req(&stm32cube_soc_cb,
                      XWDS_GPIO_PORT_B, XWDS_GPIO_PIN_0);
        while (!xwos_cthrd_shld_stop()) {
                if (xwos_cthrd_shld_frz()) {
                        xwos_cthrd_freeze();
                }
                xwtm = 1 * XWTM_S;
                xwos_cthrd_sleep(&xwtm);
                xwds_gpio_toggle(&stm32cube_soc_cb,
                                 XWDS_GPIO_PORT_B,
                                 XWDS_GPIO_PIN_0);
        }
        return XWOK;
}

xwer_t memtst_task(void * arg)
{
        xwer_t rc;
        void * mem;
        xwtm_t xwtm;
        __xw_io bool running = true;

        XWOS_UNUSED(arg);
        rc = XWOK;
        while ((!xwos_cthrd_frz_shld_stop(NULL)) && (running)) {
                xwtm = 2 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_malloc(sdram_mempool, 8, &mem);
                xwtm = 10 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_free(sdram_mempool, mem);

                xwtm = 3 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_malloc(sdram_mempool, 16, &mem);
                xwtm = 6 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_free(sdram_mempool, mem);

                xwtm = 8 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_malloc(sdram_mempool, 32, &mem);
                xwtm = 12 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_free(sdram_mempool, mem);

                xwtm = 4 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_malloc(sdram_mempool, 64, &mem);
                xwtm = 9 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_free(sdram_mempool, mem);

                xwtm = 15 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_malloc(sdram_mempool, 128, &mem);
                xwtm = 8 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_free(sdram_mempool, mem);

                xwtm = 15 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_malloc(sdram_mempool, 192, &mem);
                xwtm = 8 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_free(sdram_mempool, mem);

                xwtm = 18 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_malloc(sdram_mempool, 256, &mem);
                xwtm = 6 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_free(sdram_mempool, mem);

                xwtm = 15 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_malloc(sdram_mempool, 384, &mem);
                xwtm = 8 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_free(sdram_mempool, mem);

                xwtm = 1 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_malloc(sdram_mempool, 512, &mem);
                xwtm = 1 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_free(sdram_mempool, mem);

                xwtm = 15 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_malloc(sdram_mempool, 768, &mem);
                xwtm = 8 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_free(sdram_mempool, mem);

                xwtm = 3 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_malloc(sdram_mempool, 1024, &mem);
                xwtm = 11 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_free(sdram_mempool, mem);

                xwtm = 8 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_malloc(sdram_mempool, 2048, &mem);
                xwtm = 3 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_free(sdram_mempool, mem);

                xwtm = 7 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_malloc(sdram_mempool, 4096, &mem);
                xwtm = 5 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_free(sdram_mempool, mem);

                xwtm = 3 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_malloc(sdram_mempool, 8192, &mem);
                xwtm = 2 * XWTM_MS;
                xwos_cthrd_sleep(&xwtm);
                rc = xwmm_mempool_free(sdram_mempool, mem);
        }

        return rc;
}
