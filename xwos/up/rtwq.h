/**
 * @file
 * @brief 玄武OS UP内核：实时等待队列
 * @author
 * + 隐星魂 (Roy.Sun) <https://xwos.tech>
 * @copyright
 * + (c) 2015 隐星魂 (Roy.Sun) <https://xwos.tech>
 * > This Source Code Form is subject to the terms of the Mozilla Public
 * > License, v. 2.0. If a copy of the MPL was not distributed with this
 * > file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef __xwos_up_rtwq_h__
#define __xwos_up_rtwq_h__

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********      include      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#include <xwos/standard.h>
#include <xwos/lib/rbtree.h>
#include <xwos/up/wqn.h>

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       types       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
struct xwup_wqn;

/**
 * @brief 实时等待队列
 */
struct xwup_rtwq {
        struct xwlib_rbtree tree; /**< 红黑树（关键字：优先级） */
        xwpr_t max_prio; /**< 红黑树中最大关键字 */
        struct xwup_wqn * rightmost; /**< 拥有最大关键字的节点 */
};

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********      macros       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
/**
 * @brief 以删除为目的，遍历实时等待队列中所有节点
 * @param c: (I) 作为循环光标的等待队列节点结构体(struct xwup_wqn)指针
 * @param xwrtwq: (I) 等待队列的指针
 */
#define xwup_rtwq_itr_thrd_rm(c, xwrtwq) \
        for (c = (xwrtwq)->rightmost; c; c = (xwrtwq)->rightmost)

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********         function prototypes         ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
void xwup_rtwq_init(struct xwup_rtwq * xwrtwq);
void xwup_rtwq_add(struct xwup_rtwq * xwrtwq, struct xwup_wqn * wqn, xwpr_t prio);
xwer_t xwup_rtwq_remove(struct xwup_rtwq * xwrtwq, struct xwup_wqn * wqn);
struct xwup_wqn * xwup_rtwq_choose(struct xwup_rtwq * xwrtwq);

#endif /* xwos/up/rtwq.h */
