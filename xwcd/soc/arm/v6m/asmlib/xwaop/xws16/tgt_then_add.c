/**
 * @file
 * @brief 原子操作库：xwaop__xws16__tgt_then_add
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
 */

#include <xwos/standard.h>
#include <arch_irq.h>
#include <xwos/lib/xwaop.h>

__xwlib_code
xwer_t xwaop__xws16__tgt_then_add(xws16_a * a,
                                  xws16_t t,
                                  xws16_t v,
                                  xws16_t * nv, xws16_t * ov)
{
        xws16_t n;
        xws16_t o;
        xwer_t rc;
        xwreg_t flag;

        arch_cpuirq_save_lc(&flag);
        o = *a;
        if (o > t) {
                n = o + v;
                rc = XWOK;
                *a = n;
        } else {
                n = o;
                rc = -EACCES;
        }
        arch_cpuirq_restore_lc(flag);
        if (nv) {
                *nv = n;
        }
        if (ov) {
                *ov = o;
        }
        return rc;
}
