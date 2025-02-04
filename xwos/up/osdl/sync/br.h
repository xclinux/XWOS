/**
 * @file
 * @brief 玄武OS UP内核操作系统接口描述层：线程栅栏
 * @author
 * + 隐星魂 (Roy Sun) <xwos@xwos.tech>
 * @copyright
 * + Copyright © 2015 xwos.tech, All Rights Reserved.
 * > This Source Code Form is subject to the terms of the Mozilla Public
 * > License, v. 2.0. If a copy of the MPL was not distributed with this
 * > file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef __xwos_up_osdl_sync_br_h__
#define __xwos_up_osdl_sync_br_h__

#include <xwos/up/osdl/sync/sel.h>
#include <xwos/up/sync/evt.h>

#define xwosdl_br xwup_evt

static __xwcc_inline
xwer_t xwosdl_br_init(struct xwosdl_br * br, xwsz_t num,
                      xwbmp_t * bmp, xwbmp_t * msk)
{
        return xwup_evt_init(br, XWUP_EVT_TYPE_BR, num, bmp, msk);
}

static __xwcc_inline
xwer_t xwosdl_br_fini(struct xwosdl_br * br)
{
        return xwup_evt_fini(br);
}

static __xwcc_inline
xwer_t xwosdl_br_create(struct xwosdl_br ** brbuf, xwsz_t num)
{
        return xwup_evt_create(brbuf, XWUP_EVT_TYPE_BR, num);
}

static __xwcc_inline
xwer_t xwosdl_br_delete(struct xwosdl_br * br)
{
        return xwup_evt_delete(br);
}

static __xwcc_inline
xwsq_t xwosdl_br_gettik(struct xwosdl_br * br)
{
        XWOS_UNUSED(br);
        return 0;
}

static __xwcc_inline
xwer_t xwosdl_br_acquire(struct xwosdl_br * br, xwsq_t tik)
{
        XWOS_UNUSED(br);
        XWOS_UNUSED(tik);
        return XWOK;
}

static __xwcc_inline
xwer_t xwosdl_br_release(struct xwosdl_br * br, xwsq_t tik)
{
        XWOS_UNUSED(br);
        XWOS_UNUSED(tik);
        return XWOK;
}

static __xwcc_inline
xwer_t xwosdl_br_grab(struct xwosdl_br * br)
{
        XWOS_UNUSED(br);
        return XWOK;
}

static __xwcc_inline
xwer_t xwosdl_br_put(struct xwosdl_br * br)
{
        XWOS_UNUSED(br);
        return XWOK;
}

static __xwcc_inline
xwer_t xwosdl_br_bind(struct xwosdl_br * br, struct xwosdl_sel * sel, xwsq_t pos)
{
        return xwup_evt_bind(br, sel, pos);
}

static __xwcc_inline
xwer_t xwosdl_br_unbind(struct xwosdl_br * br, struct xwosdl_sel * sel)
{
        return xwup_evt_unbind(br, sel);
}

static __xwcc_inline
xwer_t xwosdl_br_intr_all(struct xwosdl_br * br)
{
        return xwup_evt_intr_all(br);
}

static __xwcc_inline
xwer_t xwosdl_br_get_num(struct xwosdl_br * br, xwsz_t * numbuf)
{
        return xwup_evt_get_num(br, numbuf);
}

static __xwcc_inline
xwer_t xwosdl_br_wait(struct xwosdl_br * br)
{
        return xwup_br_wait(br);
}

static __xwcc_inline
xwer_t xwosdl_br_timedwait(struct xwosdl_br * br, xwtm_t * xwtm)
{
        return xwup_br_timedwait(br, xwtm);
}

#endif /* xwos/up/osdl/sync/br.h */
