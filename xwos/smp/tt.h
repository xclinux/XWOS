/**
 * @file
 * @brief XuanWuOS内核：调度器的时间树
 * @author
 * + 隐星魂 (Roy.Sun) <https://xwos.tech>
 * @copyright
 * + (c) 2015 隐星魂 (Roy.Sun) <https://xwos.tech>
 * > This Source Code Form is subject to the terms of the Mozilla Public
 * > License, v. 2.0. If a copy of the MPL was not distributed with this
 * > file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef __xwos_smp_tt_h__
#define __xwos_smp_tt_h__

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********      include      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#include <xwos/standard.h>
#include <xwos/object.h>
#include <xwos/lib/bclst.h>
#include <xwos/lib/rbtree.h>
#include <xwos/smp/lock/seqlock.h>
#if defined(XWSMPCFG_SD_BH) && (1 == XWSMPCFG_SD_BH)
  #include <xwos/smp/bh.h>
#endif /* XWSMPCFG_SD_BH */

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       macros      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#define XWOS_TTN_TYPE_MASK            (3UL)

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       types       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
struct xwos_irq_resource;
struct xwos_scheduler;
struct xwos_tt;

/**
 * @brief 系统硬件定时器
 */
struct xwos_syshwt {
        xwtm_t timetick; /**< 系统时间 */
        struct xwlk_sqlk lock; /**< 保护本结构体的锁 */
        const struct xwos_irq_resource * irqrsc; /**< 中断资源 */
        xwsz_t irqs_num; /**< 中断资源的数量 */
};

struct xwos_ttn;

/**
 * @brief XWOS时间树
 */
struct xwos_tt {
        struct xwlib_rbtree rbtree; /**< 红黑树（关键字：时间） */
        xwtm_t deadline; /**< 红黑树中最小（最左边）的关键字 */
        struct xwos_ttn * leftmost; /**< 指向最小关键字节点的指针 */
        struct xwlib_bclst_head timeout; /**< 超时链表的表头 */
        struct xwlk_sqlk lock; /**< 保护本结构体的自旋锁 */
#if defined(XWSMPCFG_SD_BH) && (1 == XWSMPCFG_SD_BH)
        struct xwos_bh_node bhn; /**< 中断底半部节点 */
#endif /* XWSMPCFG_SD_BH */
        struct xwos_syshwt hwt; /**< 硬件定时器 */
};

/**
 * @brief 时间树节点的回调函数
 */
typedef void (*xwos_tt_cb_f)(void *);

/**
 * @brief 唤醒原因枚举
 */
enum xwos_ttn_wkup_reasaon_em {
        XWOS_TTN_WKUPRS_UNKNOWN = 0,
        XWOS_TTN_WKUPRS_TIMEDOUT, /**< 超时 */
        XWOS_TTN_WKUPRS_INTR, /**< 被中断 */
};

/**
 * @brief 时间树节点的类型枚举
 */
enum xwos_ttn_type_em {
        XWOS_TTN_TYPE_THREAD = 0, /**< 线程 */
        XWOS_TTN_TYPE_SWT, /**< 软件定时器 */
};

/**
 * @brief 时间树节点
 */
struct xwos_ttn {
        struct xwlib_bclst_node rbb; /**< 此有相同关键字的红黑树节点，
                                          组成双循环链表，此为链表节点 */
        struct xwlib_rbtree_node rbn; /**< 红黑树节点 */
        xwtm_t wkup_xwtm; /**< 唤醒时间 */
        __xwcc_atomic xwsq_t wkuprs; /**< 唤醒原因 */
        xwos_tt_cb_f cb; /**< 回调函数：NULL表示节点不在时间树上 */
        struct xwos_tt * xwtt; /**< 时间树 */
        union {
                xwptr_t addr; /**< XWOS对象要求至少4字节对齐
                                   （32位系统，若为64位系统则至少8字节对齐），
                                   因此，低2位始终为0 */
                xwptr_t type; /**< 低2位作为类型标识 */
        } entry; /**< 时间树节点所属的对象 */
};

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       .data       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********         function prototypes         ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
/******** time tree node ********/
__xwos_code
void xwos_ttn_init(struct xwos_ttn * ttn, xwptr_t entry, xwptr_t type);

/******** time tree ********/
__xwos_code
xwer_t xwos_tt_init(struct xwos_tt * xwtt);

__xwos_code
xwer_t xwos_tt_add_locked(struct xwos_tt * xwtt, struct xwos_ttn * ttn,
                          xwreg_t cpuirq);

__xwos_code
xwer_t xwos_tt_remove_locked(struct xwos_tt * xwtt, struct xwos_ttn * ttn);

__xwos_isr
xwer_t xwos_tt_check_deadline(struct xwos_tt * xwtt);

__xwos_code
struct xwos_scheduler * xwos_tt_get_scheduler(struct xwos_tt * xwtt);

/******** system timer ********/
__xwos_code
xwer_t xwos_syshwt_init(struct xwos_syshwt * hwt);

__xwos_code
xwer_t xwos_syshwt_start(struct xwos_syshwt * hwt);

__xwos_code
xwer_t xwos_syshwt_stop(struct xwos_syshwt * hwt);

__xwos_code
xwtm_t xwos_syshwt_get_timetick(struct xwos_syshwt * hwt);

__xwos_code
xwu64_t xwos_syshwt_get_tickcount(struct xwos_syshwt * hwt);

__xwos_code
xwtm_t xwos_syshwt_get_timestamp(struct xwos_syshwt * hwt);

__xwos_isr
void xwos_syshwt_task(struct xwos_syshwt * hwt);

__xwos_code
struct xwos_tt * xwos_syshwt_get_tt(struct xwos_syshwt * hwt);

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********  inline functions implementations   ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
/**
 * @brief 得到时间树节点所属的对象的地址
 * @param ttn: (I) 时间树节点的指针
 * @return 时间树节点所属的对象的地址
 */
static __xwcc_inline
void * xwos_ttn_get_entry(struct xwos_ttn * ttn)
{
        return (void *)(ttn->entry.addr & ~XWOS_TTN_TYPE_MASK);
}

/**
 * @brief 得到时间树节点的类型
 * @param ttn: (I) 时间树节点的指针
 * @return 类型
 */
static __xwcc_inline
xwptr_t xwos_ttn_get_type(struct xwos_ttn * ttn)
{
        return ttn->entry.type & XWOS_TTN_TYPE_MASK;
}

/**
 * @brief 增加对象的引用计数
 * @param ttn: (I) 时间树节点的指针
 * @return 错误码
 */
static __xwcc_inline
xwer_t xwos_ttn_grab(struct xwos_ttn * ttn)
{
        return xwos_object_grab(xwos_static_cast(struct xwos_object *,
                                                 xwos_ttn_get_entry(ttn)));
}

/**
 * @brief 减少对象的引用计数
 * @param ttn: (I) 时间树节点的指针
 * @return 错误码
 */
static __xwcc_inline
xwer_t xwos_ttn_put(struct xwos_ttn * ttn)
{
        return xwos_object_put(xwos_static_cast(struct xwos_object *,
                                                xwos_ttn_get_entry(ttn)));
}

#endif /* xwos/smp/tt.h */
