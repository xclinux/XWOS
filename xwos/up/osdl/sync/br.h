/**
 * @file
 * @brief 玄武OS UP内核操作系统接口描述层：线程栅栏
 * @author
 * + 隐星魂 (Roy.Sun) <https://xwos.tech>
 * @copyright
 * + (c) 2015 隐星魂 (Roy.Sun) <https://xwos.tech>
 * > This Source Code Form is subject to the terms of the Mozilla Public
 * > License, v. 2.0. If a copy of the MPL was not distributed with this
 * > file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef __xwos_up_osdl_sync_br_h__
#define __xwos_up_osdl_sync_br_h__

#include <xwos/up/osdl/sync/sel.h>
#include <xwos/up/sync/evt.h>

#define xwosdl_br xwup_evt
#define XWOSDL_BR_MAXNUM                XWUP_EVT_MAXNUM
#define xwosdl_br_declare_bitmap(name) xwup_evt_declare_bitmap(name)

static __xwcc_inline
xwer_t xwosdl_br_init(struct xwosdl_br * br)
{
        return xwup_evt_init(br, NULL, XWUP_EVT_TYPE_BR);
}

static __xwcc_inline
xwer_t xwosdl_br_destroy(struct xwosdl_br * br)
{
        return xwup_evt_destroy(br);
}

static __xwcc_inline
xwer_t xwosdl_br_create(struct xwosdl_br ** brp)
{
        struct xwosdl_br * br;
        xwer_t rc;

        rc = xwup_evt_create(&br, NULL, XWUP_EVT_TYPE_BR);
        if (XWOK == rc) {
                *brp = br;
        } else {
                *brp = NULL;
        }
        return rc;
}

static __xwcc_inline
xwer_t xwosdl_br_delete(struct xwosdl_br * br)
{
        return xwup_evt_delete(br);
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
xwer_t xwosdl_br_sync(struct xwosdl_br * br, xwsq_t pos, xwbmp_t sync[])
{
        return xwup_evt_sync(br, pos, sync);
}

static __xwcc_inline
xwer_t xwosdl_br_timedsync(struct xwosdl_br * br, xwsq_t pos,
                           xwbmp_t sync[], xwtm_t * xwtm)
{
        return xwup_evt_timedsync(br, pos, sync, xwtm);
}

#endif /* xwos/up/osdl/sync/br.h */
