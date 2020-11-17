/**
 * @file
 * @brief 玄武OS UP内核：中断底半部
 * @author
 * + 隐星魂 (Roy.Sun) <https://xwos.tech>
 * @copyright
 * + (c) 2015 隐星魂 (Roy.Sun) <https://xwos.tech>
 * > This Source Code Form is subject to the terms of the Mozilla Public
 * > License, v. 2.0. If a copy of the MPL was not distributed with this
 * > file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef __xwos_up_bh_h__
#define __xwos_up_bh_h__

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********      include      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#include <xwos/standard.h>
#include <xwos/lib/bclst.h>

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       macros      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       types       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
/**
 * @brief 中断底半部控制块
 */
struct xwup_bh_cb {
        struct xwlib_bclst_head list; /**< 链表头 */
};

/**
 * @brief 中断底半部任务函数类型
 */
typedef void (* xwup_bh_f)(void *);

/**
 * @brief 中断底半部链表节点
 */
struct xwup_bh_node {
        struct xwlib_bclst_node node; /**< 链表节点 */
        xwup_bh_f func; /**< 中断底半部任务函数 */
        void * arg; /**< 中断底半部任务函数的参数 */
};

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       .data       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********     internal function prototypes    ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ********       internal inline function implementations        ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********       API function prototypes       ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
void xwup_bh_cb_init(struct xwup_bh_cb * bhcb);
void xwup_bh_node_init(struct xwup_bh_node * bhn, xwup_bh_f func, void * arg);
void xwup_bh_node_eq(struct xwup_bh_cb * bhcb, struct xwup_bh_node * bhn);
void xwup_bh_node_dq(struct xwup_bh_cb * bhcb, struct xwup_bh_node * bhn);

#endif /* xwos/up/bh.h */
