/**
 * @file
 * @brief 原子操作库: xwaop__xwu64__and
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
#include <riscv_isa.h>
#include <xwos/lib/xwaop.h>

__xwlib_code
void xwaop__xwu64__and(xwu64_a * a,
                       xwu64_t v,
                       xwu64_t * nv, xwu64_t * ov)
{
        xwu64_t n;
        xwu64_t o;

        do {
                o = (xwu64_t)rv_lrd(a);
                n = o & v;
                xwmb_mp_mb();
        } while (rv_scd(a, (xwu64_t)n));
        if (nv) {
                *nv = n;
        }
        if (ov) {
                *ov = o;
        }
}
