/**
 * @file
 * @brief XuanWuOS的内存管理机制：伙伴算法内存块分配器
 * @author
 * + 隐星魂 (Roy.Sun) <https://xwos.tech>
 * @copyright
 * + (c) 2015 隐星魂 (Roy.Sun) <https://xwos.tech>
 * > This Source Code Form is subject to the terms of the Mozilla Public
 * > License, v. 2.0. If a copy of the MPL was not distributed with this
 * > file, You can obtain one at http://mozilla.org/MPL/2.0/.
 * @note
 * - 此算法是在所有上下文（线程、中断、中断底半部）都是安全的。
 */

#ifndef __xwos_mm_bma_h__
#define __xwos_mm_bma_h__

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********      include      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#include <xwos/standard.h>
#include <xwos/lib/bclst.h>
#include <xwos/lib/xwbop.h>
#include <xwos/osal/lock/spinlock.h>
#include <xwos/mm/common.h>

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       macros      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
/* #define XWMM_BMA_LOG */

#define XWMM_BMA_MAX_ORDER              (126) /**< 最大的阶 */
#define XWMM_BMA_COMBINED               (127) /**< 块已被合并 */
#define XWMM_BMA_ORDER_MASK             (0x7FU) /**< 阶的掩码 */
#define XWMM_BMA_INUSED                 (BIT(7)) /**< 块正在使用的标记 */

/**
 * @brief log function of bma
 */
#if defined(XWMM_BMA_LOG)
  #define xwmm_bmalogf(lv, fmt, ...) xwlogf(lv, fmt, ##__VA_ARGS__)
#else /* XWMM_BMA_LOG */
  #define xwmm_bmalogf(lv, fmt, ...)
#endif /* !XWMM_BMA_LOG */

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       types       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
/**
 * @brief 阶链表
 */
struct xwmm_bma_orderlist {
        struct xwlib_bclst_head head; /**< 链表头 */
        struct xwos_splk lock; /**< 保护list的锁 */
};

/**
 * @brief 块控制块
 */
struct xwmm_bma_bcb {
        xwu8_t order; /**< 块的阶:
                           0~126: 阶数
                           127: 块已经被前面的块合并
                           bit(7): 块正在使用中 */
};

/**
 * @brief 伙伴算法内存块分配器
 */
struct xwmm_bma {
        struct xwmm_zone zone; /**< 内存区域 */
        const char * name; /**< 名字 */
        xwsz_t blksize; /**< 单位块的大小（单位：字节） */
        xwsq_t max_order; /**< 最大阶数 */
        struct xwmm_bma_orderlist * orderlists; /**< 阶链表数组指针 */
        struct xwmm_bma_bcb * bcbs; /**< 内存块控制块数组指针 */
};

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********     internal function prototypes    ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ********       internal inline function implementations        ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********       API function prototypes       ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
/**
 * @brief XWMM API：静态方式初始化伙伴算法内存块分配器
 * @param bma: (I) 伙伴算法内存块分配器对象的指针
 * @param name: (I) 名字
 * @param origin: (I) 内存区域的起始地址
 * @param total: (I) 内存区域的总大小
 * @param blksize: (I) 单位内存块的大小
 * @param orderlists: (I) 阶链表数组的指针
 * @param bcbs: (I) 块控制块数组的指针
 * @return 错误码
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：不可重入
 */
__xwos_api
xwer_t xwmm_bma_init(struct xwmm_bma * bma, const char * name,
                     xwptr_t origin, xwsz_t total, xwsz_t blksize,
                     struct xwmm_bma_orderlist * orderlists,
                     struct xwmm_bma_bcb * bcbs);

/**
 * @brief XWMM API：销毁静态方式初始化的伙伴算法内存块分配器
 * @param bma: (I) 伙伴算法内存块分配器对象的指针
 * @return 错误码
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：不可重入
 */
__xwos_api
xwer_t xwmm_bma_destroy(struct xwmm_bma * bma);

/**
 * @brief XWMM API：动态方式创建伙伴算法内存块分配器
 * @param ptrbuf: (O) 用于返回新的伙伴算法内存块分配器对象指针的缓存
 * @param name: (I) 名字
 * @param origin: (I) 内存区域的起始地址
 * @param total: (I) 内存区域的总大小
 * @param blksize: (I) 单位内存块的大小
 * @return 错误码
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：不可重入
 */
__xwos_api
xwer_t xwmm_bma_create(struct xwmm_bma ** ptrbuf, const char * name,
                       xwptr_t origin, xwsz_t total, xwsz_t blksize);

/**
 * @brief XWMM API：删除动态方式创建的伙伴算法内存块分配器
 * @param bma: (I) 伙伴算法内存块分配器对象的指针
 * @return 错误码
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：不可重入
 */
__xwos_api
xwer_t xwmm_bma_delete(struct xwmm_bma * bma);

/**
 * @brief XWMM API：申请一块连续的内存
 * @param bma: (I) 伙伴算法内存块分配器对象的指针
 * @param order: (I) 块数量的阶，内存块大小：((1 << order) * bma->blksize)
 * @param membuf: (O) 指向地址缓存的指针，通过此指针缓存返回申请到的内存的首地址
 * @return 错误码
 * @retval -EFAULT: 空指针
 * @retval -ERANGE: order无效
 * @retval -ENOMEM: 内存不足
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：可重入
 */
__xwos_api
xwer_t xwmm_bma_alloc(struct xwmm_bma * bma, xwsq_t order, void ** membuf);

/**
 * @brief XWMM API：释放内存块
 * @param bma: (I) 伙伴算法内存块分配器对象的指针
 * @param mem: (I) 内存块的首地址指针
 * @return 错误码
 * @retval XWOK: 没有错误
 * @retval -EINVAL: 参数错误
 * @retval -ERANGE: 内存块不属于指定的伙伴算法内存块分配器对象
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：可重入
 */
__xwos_api
xwer_t xwmm_bma_free(struct xwmm_bma * bma, void * mem);

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********      inline API implementations     ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

#endif /* xwos/mm/bma.h */
