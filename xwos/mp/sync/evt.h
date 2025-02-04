/**
 * @file
 * @brief 玄武OS MP内核同步机制：事件
 * @author
 * + 隐星魂 (Roy Sun) <xwos@xwos.tech>
 * @copyright
 * + Copyright © 2015 xwos.tech, All Rights Reserved.
 * > This Source Code Form is subject to the terms of the Mozilla Public
 * > License, v. 2.0. If a copy of the MPL was not distributed with this
 * > file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef __xwos_mp_sync_evt_h__
#define __xwos_mp_sync_evt_h__

#include <xwos/standard.h>
#include <xwos/lib/xwbop.h>
#include <xwos/mp/lock/spinlock.h>
#include <xwos/mp/sync/obj.h>
#include <xwos/mp/sync/cond.h>

/**
 * @brief 事件类型枚举
 */
enum xwmp_evt_type_em {
        XWMP_EVT_TYPE_FLG = 0, /**< 事件标志 */
        XWMP_EVT_TYPE_SEL, /**< 信号选择器 */
        XWMP_EVT_TYPE_BR, /**< 线程栅栏 */
        XWMP_EVT_TYPE_MAX,
        XWMP_EVT_TYPE_MASK = 0xFF,
};

/**
 * @brief 事件对象
 */
struct xwmp_evt {
        struct xwmp_cond cond; /**< C语言面向对象：继承struct xwmp_cond */
        xwsq_t type; /**< 类型 */
        xwsz_t num; /**< 事件的数量 */
        struct xwmp_splk lock; /**< 保护位图的锁 */
        xwbmp_t * bmp; /**< 事件位图 */
        xwbmp_t * msk; /**< 掩码位图 */
};

xwer_t xwmp_evt_init(struct xwmp_evt * evt, xwsq_t type, xwsz_t num,
                     xwbmp_t * bmp, xwbmp_t * msk);
xwer_t xwmp_evt_fini(struct xwmp_evt * evt);
xwer_t xwmp_evt_create(struct xwmp_evt ** ptrbuf, xwsq_t type, xwsz_t num);
xwer_t xwmp_evt_delete(struct xwmp_evt * evt);

xwer_t xwmp_evt_acquire(struct xwmp_evt * evt, xwsq_t tik);
xwer_t xwmp_evt_release(struct xwmp_evt * evt, xwsq_t tik);
xwer_t xwmp_evt_grab(struct xwmp_evt * evt);
xwer_t xwmp_evt_put(struct xwmp_evt * evt);

xwer_t xwmp_evt_bind(struct xwmp_evt * evt, struct xwmp_evt * slt, xwsq_t pos);
xwer_t xwmp_evt_unbind(struct xwmp_evt * evt, struct xwmp_evt * slt);
xwer_t xwmp_evt_intr_all(struct xwmp_evt * evt);
xwer_t xwmp_evt_get_num(struct xwmp_evt * evt, xwsz_t * numbuf);

/******** type:XWMP_EVT_TYPE_FLG ********/
/**
 * @brief 事件触发条件枚举
 */
enum xwmp_flg_trigger_em {
        XWMP_FLG_TRIGGER_SET_ALL = 0, /**< 掩码中所有位被置1 */
        XWMP_FLG_TRIGGER_SET_ANY, /**< 掩码中任何位被置1 */
        XWMP_FLG_TRIGGER_CLR_ALL, /**< 掩码中所有位被清0 */
        XWMP_FLG_TRIGGER_CLR_ANY, /**< 掩码中任何位被清0 */
        XWMP_FLG_TRIGGER_TGL_ALL, /**< 掩码中任何位翻转 */
        XWMP_FLG_TRIGGER_TGL_ANY, /**< 掩码中任何位翻转 */
        XWMP_FLG_TRIGGER_NUM,
};

/**
 * @brief 事件触发后的动作枚举
 */
enum xwmp_flg_action_em {
        XWMP_FLG_ACTION_NONE = 0, /**< 无动作 */
        XWMP_FLG_ACTION_CONSUMPTION, /**< 消费事件 */
        XWMP_FLG_ACTION_NUM,
};

xwer_t xwmp_flg_s1m(struct xwmp_evt * evt, xwbmp_t msk[]);
xwer_t xwmp_flg_s1i(struct xwmp_evt * evt, xwsq_t pos);
xwer_t xwmp_flg_c0m(struct xwmp_evt * evt, xwbmp_t msk[]);
xwer_t xwmp_flg_c0i(struct xwmp_evt * evt, xwsq_t pos);
xwer_t xwmp_flg_x1m(struct xwmp_evt * evt, xwbmp_t msk[]);
xwer_t xwmp_flg_x1i(struct xwmp_evt * evt, xwsq_t pos);
xwer_t xwmp_flg_read(struct xwmp_evt * evt, xwbmp_t out[]);
xwer_t xwmp_flg_wait(struct xwmp_evt * evt,
                     xwsq_t trigger, xwsq_t action,
                     xwbmp_t origin[], xwbmp_t msk[]);
xwer_t xwmp_flg_trywait(struct xwmp_evt * evt,
                        xwsq_t trigger, xwsq_t action,
                        xwbmp_t origin[], xwbmp_t msk[]);
xwer_t xwmp_flg_timedwait(struct xwmp_evt * evt,
                          xwsq_t trigger, xwsq_t action,
                          xwbmp_t origin[], xwbmp_t msk[],
                          xwtm_t * xwtm);


/******** type:XWMP_EVT_TYPE_SEL ********/
xwer_t xwmp_sel_obj_bind(struct xwmp_evt * evt,
                         struct xwmp_synobj * synobj,
                         xwsq_t pos,
                         bool exclusive);
xwer_t xwmp_sel_obj_unbind(struct xwmp_evt * evt,
                           struct xwmp_synobj * synobj,
                           bool exclusive);
xwer_t xwmp_sel_obj_s1i(struct xwmp_evt * evt, struct xwmp_synobj * synobj);
xwer_t xwmp_sel_obj_c0i(struct xwmp_evt * evt, struct xwmp_synobj * synobj);
xwer_t xwmp_sel_select(struct xwmp_evt * evt, xwbmp_t msk[], xwbmp_t trg[]);
xwer_t xwmp_sel_tryselect(struct xwmp_evt * evt, xwbmp_t msk[], xwbmp_t trg[]);
xwer_t xwmp_sel_timedselect(struct xwmp_evt * evt, xwbmp_t msk[], xwbmp_t trg[],
                            xwtm_t * xwtm);

/******** type:XWMP_EVT_TYPE_BR ********/
xwer_t xwmp_br_wait(struct xwmp_evt * evt);
xwer_t xwmp_br_timedwait(struct xwmp_evt * evt, xwtm_t * xwtm);

#endif /* xwos/mp/sync/evt.h */
