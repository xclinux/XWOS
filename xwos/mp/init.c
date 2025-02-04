/**
 * @file
 * @brief 玄武OS MP内核：初始化
 * @author
 * + 隐星魂 (Roy Sun) <xwos@xwos.tech>
 * @copyright
 * + Copyright © 2015 xwos.tech, All Rights Reserved.
 * > This Source Code Form is subject to the terms of the Mozilla Public
 * > License, v. 2.0. If a copy of the MPL was not distributed with this
 * > file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <xwos/standard.h>
#include <xwos/mp/pm.h>
#include <xwos/mp/init.h>

/**
 * @brief 初始化XWOS MP内核
 */
__xwmp_init_code
xwer_t xwmp_init(void)
{
        /* 初始化中断管理系统 */
        xwmp_pmdm_init();
        return XWOK;
}
