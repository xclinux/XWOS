/**
 * @file
 * @brief 位图原子操作汇编库：xwbmpaop_t1i
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

#include <xwos/standard.h>
#include <asmlib/xwbop.h>

__xwlib_code __xwcc_naked
bool xwbmpaop_t1i(__xwcc_unused __xwcc_atomic xwbmp_t * bmp,
                  __xwcc_unused xwsq_t idx)
{
        __asm__ volatile("      lsr     r2, r1, #5"); /* r2 = n / 32; */
        __asm__ volatile("      and     r3, r1, #31"); /* r3 = n % 32; */
        __asm__ volatile("      mov     r1, #1");
        __asm__ volatile("      lsl     r1, r3"); /* r1 = bitmask; */
        __asm__ volatile("      ldr     r3, [r0, r2, lsl #2]"); /* r3 = *(addr + r2); */
        xwmb_mp_ddb();
        __asm__ volatile("      tst     r1, r3"); /* r0 = r1 & r3; */
        __asm__ volatile("      ite     ne"); /* if (result is non-zero (Z != 1)) */
        __asm__ volatile("      movne   r0, #1"); /* then r0 = 1; */
        __asm__ volatile("      moveq   r0, #0"); /* else r0 = 0; */
        __asm__ volatile("      bx      lr"); /* return r0; */
}
