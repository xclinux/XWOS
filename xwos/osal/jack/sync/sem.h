/**
 * @file
 * @brief 操作系统抽象层：信号量接口描述
 * @author
 * + 隐星魂 (Roy Sun) <xwos@xwos.tech>
 * @copyright
 * + Copyright © 2015 xwos.tech, All Rights Reserved.
 * > This Source Code Form is subject to the terms of the Mozilla Public
 * > License, v. 2.0. If a copy of the MPL was not distributed with this
 * > file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef __xwos_osal_jack_sync_sem_h__
#define __xwos_osal_jack_sync_sem_h__

#if defined(XuanWuOS_CFG_CORE__mp)
#  include <xwos/mp/osdl/sync/sem.h>
#elif defined(XuanWuOS_CFG_CORE__up)
#  include <xwos/up/osdl/sync/sem.h>
#endif

#endif /* xwos/osal/jack/sync/sem.h */
