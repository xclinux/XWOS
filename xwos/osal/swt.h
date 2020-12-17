/**
 * @file
 * @brief 操作系统抽象层：软件定时器
 * @author
 * + 隐星魂 (Roy.Sun) <https://xwos.tech>
 * @copyright
 * + (c) 2015 隐星魂 (Roy.Sun) <https://xwos.tech>
 * > This Source Code Form is subject to the terms of the Mozilla Public
 * > License, v. 2.0. If a copy of the MPL was not distributed with this
 * > file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef __xwos_osal_swt_h__
#define __xwos_osal_swt_h__

#include <xwos/standard.h>
#include <xwos/osal/jack/swt.h>

/**
 * @brief XWOS API：软件定时器
 */
struct xwos_swt {
        struct xwosdl_swt osswt;
};

/**
 * @brief XWOS API：软件定时器回调函数指针类型
 */
typedef void (* xwos_swt_f)(struct xwos_swt * /*swt*/, void * /*arg*/);

/**
 * @brief XWOS API：软件定时器对象描述符
 */
typedef struct {
        struct xwos_swt * swt; /**< 软件定时器对象的指针 */
        xwsq_t tik; /**< 标签 */
} xwos_swt_d;

/**
 * @brief XWOS API：空的软件定时器对象描述符
 */
#define XWOS_SWT_NILD ((xwos_swt_d){NULL, 0,})

/**
 * @brief XWOS API：软件定时器标志 —— 无
 */
#define XWOS_SWT_FLAG_NULL            XWOSDL_SWT_FLAG_NULL

/**
 * @brief XWOS API：软件定时器标志 —— 自动重启
 * @note 不可与XWOS_SWT_FLAG_RESTART同时使用
 */
#define XWOS_SWT_FLAG_RESTART         XWOSDL_SWT_FLAG_RESTART

/**
 * @brief XWOS API：软件定时器标志 —— 自动销毁
 * @note
 * - 不可与XWOS_SWT_FLAG_RESTART同时使用
 * - 不可用于静态初始化的软件定时器
 */
#define XWOS_SWT_FLAG_AUTORM          XWOSDL_SWT_FLAG_AUTORM

/**
 * @brief XWOS API：静态方式初始化软件定时器
 * @param swt: (I) 软件定时器的指针
 * @param name: (I) 软件定时器的名字
 * @param flag: (I) 软件定时器的标志
 * @return 错误码
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：不可重入
 */
static __xwos_inline_api
xwer_t xwos_swt_init(struct xwos_swt * swt, const char * name, xwsq_t flag)
{
        return xwosdl_swt_init(&swt->osswt, name, flag);
}

/**
 * @brief XWOS API：销毁静态方式初始化的软件定时器
 * @param swt: (I) 软件定时器的指针
 * @return 错误码
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：不可重入
 */
static __xwos_inline_api
xwer_t xwos_swt_destroy(struct xwos_swt * swt)
{
        return xwosdl_swt_destroy(&swt->osswt);
}

/**
 * @brief XWOS API：动态方式创建软件定时器
 * @param swtbuf: (O) 指向缓冲区的指针，通过此缓冲区返回软件定时器的指针
 * @param name: (I) 软件定时器的名字
 * @param flag: (I) 软件定时器的标志
 * @return 错误码
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：不可重入
 */
static __xwos_inline_api
xwer_t xwos_swt_create(struct xwos_swt ** swtbuf, const char * name, xwsq_t flag)
{
        return xwosdl_swt_create((struct xwosdl_swt **)swtbuf, name, flag);
}

/**
 * @brief XWOS API：删除动态方式创建的软件定时器
 * @param swt: (I) 软件定时器的指针
 * @return 错误码
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：不可重入
 */
static __xwos_inline_api
xwer_t xwos_swt_delete(struct xwos_swt * swt)
{
        return xwosdl_swt_delete(&swt->osswt);
}

/**
 * @brief XWOS API：获取软件定时器对象的标签
 * @param swt: (I) 软件定时器对象的指针
 * @return 软件定时器对象的标签
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：可重入
 */
static __xwos_inline_api
xwsq_t xwos_swt_gettik(struct xwos_swt * swt)
{
        return xwosdl_swt_gettik(&swt->osswt);
}

/**
 * @brief XWOS API：获取软件定时器对象的描述符
 * @param swt: (I) 软件定时器对象的指针
 * @return 软件定时器对象的描述符
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：可重入
 */
static __xwos_inline_api
xwos_swt_d xwos_swt_getd(struct xwos_swt * swt)
{
        xwos_swt_d swtd;

        swtd.swt = swt;
        swtd.tik = xwosdl_swt_gettik(&swt->osswt);
        return swtd;
}

/**
 * @brief XWOS API：检查软件定时器对象的标签并增加引用计数
 * @param swtd: (I) 软件定时器对象的描述符
 * @return 错误码
 * @retval XWOK: OK
 * @retval -EOBJDEAD: 对象无效
 * @retval -EACCES: 对象标签检查失败
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：可重入
 */
static __xwos_inline_api
xwer_t xwos_swt_acquire(xwos_swt_d swtd)
{
        return xwosdl_swt_acquire(&swtd.swt->osswt, swtd.tik);
}

/**
 * @brief XWOS API：检查对象的标签并减少引用计数
 * @param swtd: (I) 软件定时器对象的描述符
 * @return 错误码
 * @retval XWOK: OK
 * @retval -EOBJDEAD: 对象无效
 * @retval -EACCES: 对象标签检查失败
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：可重入
 */
static __xwos_inline_api
xwer_t xwos_swt_release(xwos_swt_d swtd)
{
        return xwosdl_swt_release(&swtd.swt->osswt, swtd.tik);
}

/**
 * @brief XWOS API：增加软件定时器对象的引用计数
 * @param swt: (I) 软件定时器对象的指针
 * @return 错误码
 * @retval XWOK: OK
 * @retval -EOBJDEAD: 对象无效
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：可重入
 */
static __xwos_inline_api
xwer_t xwos_swt_grab(struct xwos_swt * swt)
{
        return xwosdl_swt_grab(&swt->osswt);
}

/**
 * @brief XWOS API：减少软件定时器对象的引用计数
 * @param swt: (I) 软件定时器对象的指针
 * @return 错误码
 * @retval XWOK: OK
 * @retval -EOBJDEAD: 对象无效
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：可重入
 */
static __xwos_inline_api
xwer_t xwos_swt_put(struct xwos_swt * swt)
{
        return xwosdl_swt_put(&swt->osswt);
}

/**
 * @brief XWOS API：启动软件定时器
 * @param swt: (I) 软件定时器的指针
 * @param base: (I) 软件定时器的初始时间
 * @param period: (I) 软件定时器的周期时间
 * @param callback: (I) 软件定时器的回调函数
 * @param arg: (I) 回调函数的参数
 * @return 错误码
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：不可重入
 */
static __xwos_inline_api
xwer_t xwos_swt_start(struct xwos_swt * swt, xwtm_t base, xwtm_t period,
                      xwos_swt_f callback, void * arg)
{
        return xwosdl_swt_start(&swt->osswt, base, period,
                                (xwosdl_swt_f)callback, arg);
}

/**
 * @brief XWOS API：停止软件定时器
 * @param swt: (I) 软件定时器的指针
 * @return 错误码
 * @note
 * - 同步/异步：同步
 * - 上下文：中断、中断底半部、线程
 * - 重入性：不可重入
 */
static __xwos_inline_api
xwer_t xwos_swt_stop(struct xwos_swt * swt)
{
        return xwosdl_swt_stop(&swt->osswt);
}

#endif /* xwos/osal/swt.h */
