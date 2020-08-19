/**
 * @file
 * @brief xwmd设备栈：I2C外设
 * @author
 * + 隐星魂 (Roy.Sun) <https://xwos.tech>
 * @copyright
 * + (c) 2015 隐星魂 (Roy.Sun) <https://xwos.tech>
 * > This Source Code Form is subject to the terms of the Mozilla Public
 * > License, v. 2.0. If a copy of the MPL was not distributed with this
 * > file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********      include      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#include <xwmd/ds/standard.h>
#include <xwos/osal/scheduler.h>
#include <xwmd/ds/i2c/perpheral.h>

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       macros      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********     static function prototypes      ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
static __xwds_vop
xwer_t xwds_i2cp_cvop_probe(struct xwds_i2cp * i2cp);

static __xwds_vop
xwer_t xwds_i2cp_cvop_remove(struct xwds_i2cp * i2cp);

static __xwds_vop
xwer_t xwds_i2cp_cvop_start(struct xwds_i2cp * i2cp);

static __xwds_vop
xwer_t xwds_i2cp_cvop_stop(struct xwds_i2cp * i2cp);

#if defined(XWMDCFG_ds_PM) && (1 == XWMDCFG_ds_PM)
static __xwds_vop
xwer_t xwds_i2cp_cvop_suspend(struct xwds_i2cp * i2cp);

static __xwds_vop
xwer_t xwds_i2cp_cvop_resume(struct xwds_i2cp * i2cp);
#endif /* XWMDCFG_ds_PM */

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       .data       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
__xwds_rodata const struct xwds_base_virtual_operations xwds_i2cp_cvops = {
        .probe = (void *)xwds_i2cp_cvop_probe,
        .remove = (void *)xwds_i2cp_cvop_remove,
        .start = (void *)xwds_i2cp_cvop_start,
        .stop = (void *)xwds_i2cp_cvop_stop,
#if defined(XWMDCFG_ds_PM) && (1 == XWMDCFG_ds_PM)
        .suspend = (void *)xwds_i2cp_cvop_suspend,
        .resume = (void *)xwds_i2cp_cvop_resume,
#endif /* XWMDCFG_ds_PM */
};

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********      function implementations       ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
/******** ******** ******** constructor & destructor ******** ******** ********/
/**
 * @brief I2C外设的构造函数
 * @param i2cp: (I) I2C外设对象指针
 */
__xwds_api
void xwds_i2cp_construct(struct xwds_i2cp * i2cp)
{
        xwds_device_construct(&i2cp->dev);
        i2cp->dev.cvops = &xwds_i2cp_cvops;
}

/**
 * @brief I2C外设的构造函数
 * @param i2cp: (I) I2C外设对象指针
 */
__xwds_api
void xwds_i2cp_destruct(struct xwds_i2cp * i2cp)
{
        xwds_device_destruct(&i2cp->dev);
}

/******** ******** base virtual operations ******** ********/
/**
 * @brief XWDS VOP：探测I2C外设
 * @param i2cp: (I) I2C外设对象指针
 * @return 错误码
 */
static __xwds_vop
xwer_t xwds_i2cp_cvop_probe(struct xwds_i2cp * i2cp)
{
        xwer_t rc;

        if (i2cp->bus) {
                rc = xwds_i2cm_grab(i2cp->bus);
        } else {
                rc = -EHOSTUNREACH;
        }
        if (__xwcc_unlikely(rc < 0)) {
                goto err_i2cm_grab;
        }

        rc = xwds_device_cvop_probe(&i2cp->dev);
        if (__xwcc_unlikely(rc < 0)) {
                goto err_dev_cvop_probe;
        }
        return XWOK;

err_dev_cvop_probe:
        xwds_i2cm_put(i2cp->bus);
err_i2cm_grab:
        return rc;
}

/**
 * @brief XWDS VOP：移除I2C外设
 * @param i2cp: (I) I2C外设对象指针
 * @return 错误码
 */
static __xwds_vop
xwer_t xwds_i2cp_cvop_remove(struct xwds_i2cp * i2cp)
{
        xwer_t rc;

        XWDS_VALIDATE(i2cp->bus, "nullptr", -EHOSTUNREACH);

        rc = xwds_device_cvop_remove(&i2cp->dev);
        if (__xwcc_unlikely(rc < 0)) {
                goto err_dev_cvop_remove;
        }

        xwds_i2cm_put(i2cp->bus);
        return XWOK;

err_dev_cvop_remove:
        return rc;
}

/**
 * @brief XWDS VOP：启动I2C外设
 * @param i2cp: (I) I2C外设对象指针
 * @return 错误码
 */
static __xwds_vop
xwer_t xwds_i2cp_cvop_start(struct xwds_i2cp * i2cp)
{
        xwer_t rc;

        if (i2cp->bus) {
                rc = xwds_i2cm_request(i2cp->bus);
        } else {
                rc = -EHOSTUNREACH;
        }
        if (__xwcc_unlikely(rc < 0)) {
                goto err_i2cm_request;
        }

        rc = xwds_device_cvop_start(&i2cp->dev);
        if (__xwcc_unlikely(rc < 0)) {
                goto err_dev_cvop_start;
        }
        return XWOK;

err_dev_cvop_start:
        xwds_i2cm_release(i2cp->bus);
err_i2cm_request:
        return rc;
}

/**
 * @brief XWDS VOP：停止I2C外设
 * @param i2cp: (I) I2C外设对象指针
 * @return 错误码
 */
static __xwds_vop
xwer_t xwds_i2cp_cvop_stop(struct xwds_i2cp * i2cp)
{
        xwer_t rc;

        XWDS_VALIDATE(i2cp->bus, "nullptr", -EHOSTUNREACH);

        rc = xwds_device_cvop_stop(&i2cp->dev);
        if (__xwcc_unlikely(rc < 0)) {
                goto err_dev_cvop_stop;
        }

        xwds_i2cm_release(i2cp->bus);
        return XWOK;

err_dev_cvop_stop:
        return rc;
}

#if defined(XWMDCFG_ds_PM) && (1 == XWMDCFG_ds_PM)
/******** ******** pm ******** ********/
/**
 * @brief XWDS VOP：暂停I2C外设
 * @param i2cp: (I) I2C外设对象指针
 * @return 错误码
 */
static __xwds_vop
xwer_t xwds_i2cp_cvop_suspend(struct xwds_i2cp * i2cp)
{
        xwer_t rc;

        XWDS_VALIDATE(i2cp->bus, "nullptr", -EHOSTUNREACH);

        rc = xwds_device_cvop_suspend(&i2cp->dev);
        if (__xwcc_unlikely(rc < 0)) {
                goto err_dev_cvop_suspend;
        }

        xwds_i2cm_release(i2cp->bus);
        return XWOK;

err_dev_cvop_suspend:
        return rc;
}

/**
 * @brief XWDS VOP：继续I2C外设
 * @param i2cp: (I) I2C外设对象指针
 * @return 错误码
 */
static __xwds_vop
xwer_t xwds_i2cp_cvop_resume(struct xwds_i2cp * i2cp)
{
        xwer_t rc;

        if (i2cp->bus) {
                rc = xwds_i2cm_request(i2cp->bus);
        } else {
                rc = -EHOSTUNREACH;
        }
        if (__xwcc_unlikely(rc < 0)) {
                goto err_i2cm_request;
        }

        rc = xwds_device_cvop_resume(&i2cp->dev);
        if (__xwcc_unlikely(rc < 0)) {
                goto err_dev_cvop_resume;
        }
        return XWOK;

err_dev_cvop_resume:
        xwds_i2cm_release(i2cp->bus);
err_i2cm_request:
        return rc;
}
#endif /* XWMDCFG_ds_PM */

/******** ******** ******** APIs ******** ******** ********/
__xwds_api
xwer_t xwds_i2cp_ioctl(struct xwds_i2cp * i2cp, xwsq_t cmd, ...)
{
        const struct xwds_i2cp_driver * drv;
        va_list args;
        xwer_t rc;

        XWDS_VALIDATE(i2cp, "nullptr", -EFAULT);

        rc = xwds_i2cp_grab(i2cp);
        if (__xwcc_unlikely(rc < 0)) {
                goto err_i2cp_grab;
        }
        rc = xwds_i2cp_request(i2cp);
        if (__xwcc_unlikely(rc < 0)) {
                goto err_i2cp_request;
        }

        va_start(args, cmd);
        drv = xwds_static_cast(const struct xwds_i2cp_driver *, i2cp->dev.drv);
        if ((drv) && (drv->ioctl)) {
                rc = drv->ioctl(i2cp, cmd, args);
        } else {
                rc = -ENOSYS;
        }
        va_end(args);
        if (__xwcc_unlikely(rc < 0)) {
                goto err_drv_ioctl;
        }

        xwds_i2cp_release(i2cp);
        xwds_i2cp_put(i2cp);
        return XWOK;

err_drv_ioctl:
        xwds_i2cp_release(i2cp);
err_i2cp_request:
        xwds_i2cp_put(i2cp);
err_i2cp_grab:
        return rc;
}
